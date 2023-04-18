#include "x86_64_defs.h"

.section .text

.global tty_puts

.global bootstrap_do_panic
bootstrap_do_panic:
.hang_hlt:
    hlt
    jmp .hang_hlt

.global cputest_cpuid_present
cputest_cpuid_present:
    # copy EFLAGS into EAX
    pushfl
    pop %eax
    # make a copy of EFLAGS in ECX
    mov %eax, %ecx
    # set up CPUID bit in
    xor $X86_64_EFLAGS_CPUID, %eax
    # copy modified EAX to EFLAGS
    push %eax
    popfl
    # copy EFLAGS to EAX (with flipped cpuid bit if supported
    pushfl
    pop %eax
    # restore initial EFLAGS state
    push %ecx
    popfl
    # test the flipped bit
    cmp %eax, %ecx
    je .no_cpuid

    mov $1, %eax
    ret

.no_cpuid:
    xor %eax, %eax
    ret

.global cputest_paging_present
cputest_PAE_present:
    push %ebx

    mov $0x01, %eax
    cpuid

    mov $0x1, %eax

    test $X86_64_CPUID_PAE, %edx
    jnz .has_PAE
    
    xor %eax, %eax

.has_PAE:
    pop %ebx
    ret

.global cputest_64mode_present
cputest_64mode_present:
    push %ebx

    mov $0x80000000, %eax
    cpuid

    cmp $0x80000001, %eax
    jl .no_64mode

    mov $0x80000001, %eax
    cpuid

    test $X86_64_CPUID_64BITMODE, %edx
    jz .no_64mode

    mov $0x1, %eax
    pop %ebx
    ret

.no_64mode:
    xor %eax, %eax
    pop %ebx
    ret

