
.text
.global main
main:
        main:
        subq    $24, %rsp       
        movl    $16, %edi       
        call    malloc  #
        movl    $0x11, (%rax)     
        addq    $4, %rax        
        movl    $0x22, (%rax)     
        addq    $4, %rax        
        movl    $0x33, (%rax)     
        addq    $4, %rax       
        movl    $0x44, (%rax)     
        movl    $0, %eax        
        addq    $24, %rsp       
        ret     