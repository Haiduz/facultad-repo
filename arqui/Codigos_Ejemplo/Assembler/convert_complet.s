.global convert
convert:
        cvtsi2ss %edi, %xmm2    # m
        cvtsi2ss %esi, %xmm3    # k

        xorps %xmm1, %xmm1      # xmm1=0
        ucomiss %xmm1, %xmm0    # comparo x con cero
        jbe menor_igual

        mulss %xmm2, %xmm0      # x*m
        addss %xmm3, %xmm0      # x*m+k
        jmp fin

menor_igual:
        divss %xmm2, %xmm0      # x/m
        subss %xmm3, %xmm0      # x*m-k

fin:

        ret