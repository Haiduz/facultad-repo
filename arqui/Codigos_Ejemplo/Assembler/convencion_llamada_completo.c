struct punto{
 int x;
 int y;
 } p;

 int funcion(int, int, char, float, int, long, long, long, struct punto);

 int main(){
 int a=3, b=5, c=6;
 char d='a';
 float f=3.14;
 long g=78, h=99, l=100;

 p.x=60;
 p.y=90;

 int r = funcion(a,b,d,f,c,g,h,l,p);

 return 0;
 }


 int funcion(int a,int b,char d,float f,int c,long g,long h,long l, struct punto p){
 return a+b+p.y;
 }