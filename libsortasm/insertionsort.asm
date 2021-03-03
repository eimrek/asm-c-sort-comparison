; -------------------------------------------------------------
; insertionsort.asm
; @brief	Insertion sort sorteerimisalgoritmi implementatsioon
; @author	Kristjan Eimre
; @date		04.01.2016
; -------------------------------------------------------------

; if not on windows remove underscores
%ifnidn __OUTPUT_FORMAT__, win32
    %define _asmInsertionSort asmInsertionSort
%endif

global _asmInsertionSort
extern _printf

section .data
    strPrint db "%d ", 0

section .text

; asmInsertionSort(int* a, int n);
_asmInsertionSort:
    ; proloog
    push    ebp
    mov     ebp, esp
    push    ebx
    push    esi

    ; loeme argumendid registritesse
    mov     edx, [ebp+8] ; edx = a
    
    mov     ecx, 1  ; ecx = i = 1
    .while:
        cmp     ecx, [ebp+12]
        jge     .endwhile       ; break if (i>=n)
        
        mov     eax, [edx+ecx*4]    ; eax = t = a[i] 

        mov     ebx, ecx    ; ebx = i
        dec     ebx         ; ebx = j = i - 1

        .innerwhile:
            cmp     ebx, 0
            jl      .endinnerwhile      ; break if (j < 0)

            mov     esi, [edx+ebx*4]    ; esi = a[j]
            
            cmp     esi, eax
            jle     .endinnerwhile      ; break if a[j] <= t
            
            mov     [edx+ebx*4+4], esi  ; a[j+1] = a[j]
            dec     ebx                 ; j--
            jmp     .innerwhile
        .endinnerwhile:

        mov     [edx+ebx*4+4], eax  ; a[j+1] = t
        inc     ecx                 ; i++

        jmp     .while
    .endwhile:

    ; return 0
    mov     eax, 0
    ; epiloog
    pop     esi
    pop     ebx
    mov     esp, ebp
    pop     ebp
    ret

