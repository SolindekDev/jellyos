#include <elf/elf.h>

#include <drivers/serial_port.h>
#include <arch/x86/isr.h>
#include <core/print.h>

#include <mem/kheap.h>
#include <mem/mem.h>

#include <fs/vfs.h>

elf_t* load_elf(File_t* file) {
    elf_t elf;

    elf.header = (Elf32_Ehdr*)kmalloc(sizeof(Elf32_Ehdr));
    elf.header = (Elf32_Ehdr*)file->data;

    // Is this file even elf?
    if (!(
            elf.header->e_ident[0] == ELFMAG0 && elf.header->e_ident[1] == ELFMAG1 &&
            elf.header->e_ident[2] == ELFMAG2 && elf.header->e_ident[3] == ELFMAG3
        )) {
        printf("\"%s\" it's not an ELF file\n", file->name);
        serial_printf("[\x1b[1;33mELF\x1b[0;0m] \"%s\" it's not an ELF file\n", file->name);
        return NULL;
    }

    // Expecting 32 bit elf
    if (elf.header->e_type != ELFCLASS32) {
        printf("Expected 32 bit ELF file\n");
        serial_printf("[\x1b[1;33mELF\x1b[0;0m] Expected 32 bit ELF file\n");
        return NULL;
    }

    serial_printf("[\x1b[1;33mELF\x1b[0;0m] \"%s\" is an ELF File, trying to launch it\n", file->name);

    printf("Info about ELF File:\n");
    printf("\tType: %s\n", elf.header->e_type == 1 ? "32 Bit" : "64 Bit");
    printf("\tEndian: %s\n", elf.header->e_machine == 1 ? "Little Endian" : "Big Endian");
    printf("\tELF Version: %d\n", elf.header->e_version);
    printf("\tELF Entry: 0x%x\n", elf.header->e_entry);
    printf("\tELF Program header table file offset: 0x%x\n", elf.header->e_phoff);
    printf("\tELF Program header table entry size: 0x%x\n", elf.header->e_phentsize);

    elf.pheader = (Elf32_Phdr*)kmalloc(elf.header->e_phnum * sizeof(Elf32_Phdr));
    elf.pheader = (Elf32_Phdr*)(file->data + elf.header->e_phoff);
    
    printf("Program Header:\n");
    printf("\tSegment type: %d\n", elf.pheader->p_type);
    printf("\tSegment file offset: %d\n", elf.pheader->p_offset);
    printf("\tSegment virtual address: %d\n", elf.pheader->p_vaddr);
}   