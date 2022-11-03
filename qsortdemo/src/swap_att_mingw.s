# MingW PE (Windows) ix86
# Compile: gcc  swap_pe.asm -c -m32 

            .text
            .global @swap@8
@swap@8:
            mov     (%edx), %eax
            mov     (%ecx), %ebx
            mov     %ebx, (%edx)
            mov     %eax, (%ecx)
            ret
