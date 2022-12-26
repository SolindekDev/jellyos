#pragma once

#include <arch/x86/isr.h>

#define SYSCALLS_INTERRUPT_NUM 0x80 // 128
#define SYSCALLS_LENGTH 325

typedef void (*SYSCALL_FUNC) (
    int*,  // return (eax)
    int,   // arg0 (eax)
    int,   // arg1 (ebx)
    int,   // arg2 (ecx)
    int,   // arg3 (edx)
    int,   // arg4 (esi)
    int,   // arg5 (edi)
    int);  // arg6 (ebp)

void syscall_handler(registers_t* regs);

void init_syscalls();
