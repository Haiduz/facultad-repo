#include <stdlib.h>
#include <stdio.h>
#include <CL/opencl.h>

#define ARRAY_SIZE 100

void Cleanup(cl_context context = 0,
             cl_command_queue commandQueue = 0,
             cl_program program = 0,
             cl_kernel kernel = 0,
             cl_mem memObjects[3] = 0);

const char* program_source = 
"__kernel void hello_kernel(__global const float *a,"
"                           __global const float *b,"
"                           __global float *result)"
"{"
"        int gid = get_global_id(0);"
"        result[gid] = a[gid] + b[gid];"
"}"
;


int main(int argc, char** argv)
{
        cl_int errNum;

/////////////////////////////
// Crear un contexto de OpenCL usando la primer plataforma disponible
/////////////////////////////
        cl_context context = 0;
        cl_platform_id firstPlatformId;
        cl_uint numPlatforms;
        errNum = clGetPlatformIDs(1, &firstPlatformId, &numPlatforms);
        if (errNum != CL_SUCCESS || numPlatforms <= 0)
        {
                puts("No se encontraron plataformas OpenCL.\n");
                return 1;
        }
        cl_context_properties contextProperties[] =
                {CL_CONTEXT_PLATFORM,
                 (cl_context_properties)firstPlatformId,
                 0
                };
        context = clCreateContextFromType(contextProperties,
                                          CL_DEVICE_TYPE_GPU,
                                          NULL, NULL, &errNum);
        if (errNum != CL_SUCCESS)
        {
                puts("No se pudo crear un contexto en GPU\n");
                return 1;
        }

/////////////////////////////
// Crear una cola de comandos en el primer dispositivo disponible,
// en el contexto creado
/////////////////////////////
        cl_command_queue commandQueue = 0;
        cl_device_id *devices;
        cl_device_id device = 0;
        size_t deviceBufferSize;
        errNum = clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL,
                                  &deviceBufferSize);
        if (errNum != CL_SUCCESS)
        {
                puts("No se pudo obtener deviceBufferSize\n");
                Cleanup(context); 
                return 1;
        }
        devices = (cl_device_id*)malloc(deviceBufferSize);
        errNum = clGetContextInfo(context, CL_CONTEXT_DEVICES,
                                  deviceBufferSize, devices, NULL);
        if (errNum != CL_SUCCESS)
        {
                puts( "No se pudieron obtener los identificadores de los dispositivos\n");
                Cleanup(context); 
                return 1;
        }
        device = devices[0];
        commandQueue = clCreateCommandQueue(context,
                                            device, 0, NULL);
        if (commandQueue == NULL)
        {
                puts( "No se pudo crear la cola de comandos\n");
                Cleanup(context); 
                return 1;
        }
        free(devices);

/////////////////////////////
// Crear un programa OpenCL desde el código fuente en program_source
/////////////////////////////
        cl_program program = 0;
        program = clCreateProgramWithSource(context, 1,
                                            (const char**)&program_source,
                                            NULL,&errNum);
        if (errNum != CL_SUCCESS)
        {
                puts("No se pudo crear el programa.\n");
                Cleanup(context, commandQueue); 
                return 1;
        }
        errNum = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
        if (errNum != CL_SUCCESS)
        {
                puts("No se pudo construir el programa.\n");
                Cleanup(context, commandQueue); 
                return 1;
        }

        
/////////////////////////////
// Crear el kernel de OpenCL
/////////////////////////////
        cl_kernel kernel = 0;
        kernel = clCreateKernel(program, "hello_kernel", NULL);
        if (kernel == NULL)
        {
                puts("No se pudo crear el kernel\n");
                Cleanup(context, commandQueue, program); 
                return 1;
        }
/////////////////////////////
// Crear los objetos de memoria que van a ser usados como
// argumentos del kernel. Primero se crean los arreglos de memoria que
// van a ser usados para guardar los argumentos del kernel.
/////////////////////////////
        cl_mem memObjects[3] = { 0, 0, 0 };
        float result[ARRAY_SIZE];
        float a[ARRAY_SIZE];
        float b[ARRAY_SIZE];
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
                a[i] = i;
                b[i] = i * 2;
        }
        memObjects[0] = clCreateBuffer(context, CL_MEM_READ_ONLY |
                                       CL_MEM_COPY_HOST_PTR,
                                       sizeof(float) * ARRAY_SIZE, a,
                                       NULL);
        memObjects[1] = clCreateBuffer(context, CL_MEM_READ_ONLY |
                                       CL_MEM_COPY_HOST_PTR,
                                       sizeof(float) * ARRAY_SIZE, b,
                                       NULL);
        memObjects[2] = clCreateBuffer(context, CL_MEM_READ_WRITE,
                                       sizeof(float) * ARRAY_SIZE,
                                       NULL, NULL);


        if (memObjects[0] == NULL || memObjects[1] == NULL || memObjects[2] == NULL) {
                Cleanup(context, commandQueue, program, kernel); 
                return 1;
        }

/////////////////////////////
// Establecer los argumentos del kernel (result, a y b)
/////////////////////////////
        errNum = clSetKernelArg(kernel, 0,
                                sizeof(cl_mem), &memObjects[0]);
        errNum |= clSetKernelArg(kernel, 1, sizeof(cl_mem),
                                 &memObjects[1]);
        errNum |= clSetKernelArg(kernel, 2, sizeof(cl_mem),
                                 &memObjects[2]);
        if (errNum != CL_SUCCESS)
        {
                puts("No se pudieron establecer los argumentos del kernel.\n");
                Cleanup(context, commandQueue, program, kernel, memObjects);
                return 1;
        }
/////////////////////////////
// Encolar el kernel para su ejecución
/////////////////////////////
        size_t globalWorkSize[1] = { ARRAY_SIZE };
        size_t localWorkSize[1] = { 1 };
        errNum = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL,
                                        globalWorkSize, localWorkSize,
                                        0, NULL, NULL);
        if (errNum != CL_SUCCESS)
        {
                puts("No se pudo encolar el kernel para ejecutar.\n");
                Cleanup(context, commandQueue, program, kernel, memObjects);
                return 1;
        }
/////////////////////////////
// Copiar el resultado a un buffer en el anfitrión
/////////////////////////////
        errNum = clEnqueueReadBuffer(commandQueue, memObjects[2],
                                     CL_TRUE, 0, ARRAY_SIZE * sizeof(float),
                                     result, 0, NULL, NULL);

        if (errNum != CL_SUCCESS)
        {
                puts("Error reading result buffer.\n");
                Cleanup(context, commandQueue, program, kernel, memObjects);
                return 1;
        }
/////////////////////////////
// Imprimir el resultado
/////////////////////////////
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
                printf("%f ",result[i]);
                /* cout << result[i] << " "; */
        }
        puts("\nExecuted program successfully.\n");
        Cleanup(context, commandQueue, program, kernel, memObjects);
        return 0;
}

void Cleanup(cl_context context,
             cl_command_queue commandQueue,
             cl_program program,
             cl_kernel kernel,
             cl_mem memObjects[3])
{
        if (memObjects) {
                for (int i = 0; i < 3; i++) {
                        if (memObjects[i]) 
                                clReleaseMemObject(memObjects[i]);
                }
        }

        if (kernel) 
                clReleaseKernel(kernel);

        if (program) 
                clReleaseProgram(program);

        if (commandQueue) 
                clReleaseCommandQueue(commandQueue);

        if (context) 
                clReleaseContext(context);
}

