; -------------------------------------------------------------
; quicksort.asm
; @brief	Quicksort sorteerimisalgoritmi implementatsioon
; @author	Kristjan Eimre
; @date		04.01.2016
; -------------------------------------------------------------

; if not on windows remove underscores
%ifnidn __OUTPUT_FORMAT__, win32
    %define _asmQuickSort asmQuickSort
%endif


global _asmQuickSort
extern _printf

section .data
    strPrint db "%d ", 0

section .text

; aquickSort(int* a, int n);
_asmQuickSort:
    ; proloog
    push    ebp
    mov     ebp, esp
    push    ebx
    push    esi
    push    edi

    ; loeme argumendid registritesse
    mov     edx, [ebp+8] ; edx = a
    mov     eax, [ebp+12]; eax = n
    
    cmp     eax, 2 ; if (n < 2)
    jl      .done  ; break;

    ; p = a[n/2] (mediaani v6tmine liiga tylikas)
    mov     ebx, eax            ; ebx = n
    shr     ebx, 1              ; ebx = n/2
    mov     ebx, [edx+ebx*4]    ; ebx = p = a[n/2]
    
    mov     ecx, 0  ; ecx = i = 0
    dec     eax     ; eax = j = n - 1
    
    .while:
        .leftwhile:
            cmp     [edx+ecx*4], ebx
            jge     .endleftwhile       ; break if (a[i]>=p)
            inc     ecx                 ; i++
            jmp     .leftwhile
        .endleftwhile:

        .rightwhile:
            cmp     [edx+eax*4], ebx
            jle      .endrightwhile      ; break if (a[j]<=p)
            dec     eax                 ; j--
            jmp     .rightwhile
        .endrightwhile:

        cmp     ecx, eax    ; if (i >= j)
        jge     .endwhile   ; break;

        ; vahetame vasakult ja paremalt leitud elemendid
        mov     esi, [edx+ecx*4]
        mov     edi, [edx+eax*4]
        mov     [edx+ecx*4], edi
        mov     [edx+eax*4], esi
        
        inc     ecx ; i++
        dec     eax ; j--
        jmp     .while
    .endwhile:

    ; salvestame aadressi a+i ja arvu n-i pysivatesse registritesse
    mov     ebx, ecx    ; ebx = i
    imul    ebx, 4      ; ebx = 4*i (kuna int = 4 baiti)
    add     ebx, edx    ; ebx = a+i
    mov     esi, [ebp+12]   ; esi = n
    sub     esi, ecx        ; esi = n-i 
    
    ; asmQuickSort(a, i);
    push    ecx
    push    edx
    call    _asmQuickSort
    add     esp, 8

    ; asmQuickSort(a+i, n-i);
    push    esi
    push    ebx
    call    _asmQuickSort
    add     esp, 8

    .done:

    ; return 0
    mov     eax, 0
    ; epiloog
    pop     edi
    pop     esi
    pop     ebx
    mov     esp, ebp
    pop     ebp
    ret

