
; if not on windows remove underscores
%ifnidn __OUTPUT_FORMAT__, win32
    %define _sayhello sayhello
%endif

global _sayhello
extern _printf

section .data
    hello db 'Hello world!', 10, 0

section .text
_sayhello:
    push hello
    call _printf
    add esp, 4
    ; return 0;
    mov eax, 0
    ret
