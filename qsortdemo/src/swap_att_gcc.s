# GCC ELF (Linux) i86
# Compile: gcc swap_att.s -c -m32

            .text
            .global swap
swap:
            mov     (%edx), %eax
            mov     (%ecx), %ebx
            mov     %ebx, (%edx)
            mov     %eax, (%ecx)
            ret
