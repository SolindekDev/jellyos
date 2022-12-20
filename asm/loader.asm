; Magic header
FLAGS       equ  0x4
MAGIC_HEADER       equ  0x1BADB002
CHECKSUM    equ -(MAGIC_HEADER + FLAGS)

; Bootloader magic number
BOOTLOADER_MAGIC  equ  0x2BADB002

; Section .multiboot
section .multiboot
    align 4
    dd MAGIC_HEADER
    dd FLAGS
    dd CHECKSUM
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 1024
    dd 768
    dd 32

section .data
    align 4096

section .initial_stack, nobits
    align 4

stack_bottom:
    resb 104856
stack_top:

section .text
    global _start
    global MAGIC_HEADER
    global BOOTLOADER_MAGIC

_start:
    extern main ; Extern c function 
    
    mov esp, stack_top ; Move stack pointer register to top of the stack
    mov eax, BOOTLOADER_MAGIC ; Set eax to bootloader magic (0x2BADB002)
    
    push ebx ; Second argument in entry.cpp (void kernel_entry) (unsigned long addr) have pointer to multiboot info structure
    push eax ; First argument in entry.cpp (void kernel_entry) (unsigned long magic) have BOOTLOADER MAGIC
    
    call main ; Call c function from entry.cpp (void kernel_entry)
loop:
    jmp loop