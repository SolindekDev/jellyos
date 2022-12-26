#pragma once

#include <fs/vfs.h>

// #define ELF_MAGIC 0x464C457F
// #define EI_NIDENT 0x10

// typedef unsigned int    Elf32_Addr;
// typedef unsigned int    Elf32_Off;
// typedef unsigned short  Elf32_Half;
// typedef unsigned int    Elf32_Word;
// typedef signed int      Elf32_Sword;
// typedef unsigned long   Elf32_Xword;
// typedef signed long     Elf32_Sxword;

// typedef struct elf32_ehdr_t {
//     unsigned char e_ident[5];  /* Magic number and other info */
//     Elf32_Half    e_type;              /* Object file type */
//     Elf32_Half    e_machine;           /* Architecture */
//     Elf32_Word    e_version;           /* Object file version */
//     Elf32_Addr    e_entry;             /* Entry point virtual address */
//     Elf32_Off     e_phoff;             /* Program header table file offset */
//     Elf32_Off     e_shoff;             /* Section header table file offset */
//     Elf32_Word    e_flags;             /* Processor-specific flags */
//     Elf32_Half    e_ehsize;            /* ELF header size in bytes */
//     Elf32_Half    e_phentsize;         /* Program header table entry size */
//     Elf32_Half    e_phnum;             /* Program header table entry count */
//     Elf32_Half    e_shentsize;         /* Section header table entry size */
//     Elf32_Half    e_shnum;             /* Section header table entry count */
//     Elf32_Half    e_shstrndx;          /* Section header string table index */
// } elf32_ehdr_t;

// typedef struct elf32_phdr_t {
//   Elf32_Word p_type;    /* Segment type */
//   Elf32_Off  p_offset;  /* Segment file offset */
//   Elf32_Addr p_vaddr;   /* Segment virtual address */
//   Elf32_Addr p_paddr;   /* Segment physical address */
//   Elf32_Word p_filesz;  /* Segment size in file */
//   Elf32_Word p_memsz;   /* Segment size in memory */
//   Elf32_Word p_flags;   /* Segment flags */
//   Elf32_Word p_align;   /* Segment alignment */
// } elf32_phdr_t;

#include <elf.h>

typedef struct elf_t {
    unsigned char* memory;
    Elf32_Ehdr* header;
    Elf32_Phdr* pheader;
} elf_t;

elf_t* load_elf(File_t* file);
