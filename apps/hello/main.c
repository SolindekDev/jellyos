#include <sys/syscall.h>

#include <string.h>

void _start() {
    char* buf = "Hello";
    syscall(SYS_write, 0, (int)&buf, strlen(buf), 0, 0, 0);
}