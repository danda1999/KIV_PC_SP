# GCC ELF (Linux) i86_x64
# Compile: gcc swap_att_x64.s -c -m64

            .text
            .global swap
swap:
            mov     (%rdi),%eax
            mov     (%rsi),%edx
            mov     %edx,(%rdi)
            mov     %eax,(%rsi)
            ret
