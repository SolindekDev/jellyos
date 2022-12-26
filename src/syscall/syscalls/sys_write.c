#include <syscall/syscalls/sys_write.h>

#include <core/print.h>

#include <syscall/syscall.h>

void sys_write(int* syscall_return, int eax, int ebx, int ecx, int edx, int esi, int edi, int edp) {
    const char* buf = (const char*)ecx;
    int fd = ebx;
    int count = edx;

    for (int i = 0; i < count; i++)
        printf("%c", buf[i]);

    *syscall_return = 1;
}
