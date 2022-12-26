#include <fs/ata.h>

#include <arch/x86/ports.h>
#include <drivers/serial_port.h>

#include <core/print.h>
#include <core/kpanic.h>

#include <mem/kheap.h>

identify_device_t ident;
unsigned short drive;
char HDD;

void write_sector(unsigned int addr) {
    serial_printf("[\x1b[1;33mATA\x1b[0;0m] Writting %d sector\n", addr);

    outb(0x1F1, 0x00);
    outb(0x1F2, 0x01);
    outb(0x1F3, (unsigned char)addr);
    outb(0x1F4, (unsigned char)(addr >> 8));
    outb(0x1F5, (unsigned char)(addr >> 16));
    outb(0x1F6, 0xE0 | (drive << 4) | ((addr >> 24) & 0x0F));
    outb(0x1F7, 0x30);
}

void _sleep(int ms) {    
    for(int i = 0; i < (ms * 100); i++) {}
}

void read_sector(unsigned int addr) {
    serial_printf("[\x1b[1;33mATA\x1b[0;0m] Readding %d sector\n", addr);

    outb(0x1F1, 0x00);
    outb(0x1F2, 0x01);
    outb(0x1F3, (unsigned char)addr);
    outb(0x1F4, (unsigned char)(addr >> 8));
    outb(0x1F5, (unsigned char)(addr >> 16));
    outb(0x1F6, 0xE0 | (drive << 4) | ((addr >> 24) & 0x0F));
    outb(0x1F7, 0x20);
}

void hdd_a_handler() {
    serial_printf("[\x1b[1;33mATA\x1b[0;0m] nSecondary hard disk sent you an interrupt\n");
}

void hdd_b_handler() {
    serial_printf("[\x1b[1;33mATA\x1b[0;0m] Primary hard disk sent you an interrupt\n");
}

void init_ata() {
    serial_printf("[\x1b[1;33mATA\x1b[0;0m] Initializing ATA Driver\n");

    outb(0x1F7,0xA0);
    _sleep(10);
    outb(0x1F2,0);
    outb(0x1F3,0);
    outb(0x1F4,0);
    outb(0x1F5,0);
    outb(0x1F7,0xEC);
    _sleep(10);

    if(inb(0x1F7)&&!(inb(0x1F7)&0x01)) {
        serial_printf("[\x1b[1;33mATA\x1b[0;0m] Drive 0xA0 exists\n");
        for(int i = 0; (((inb(0x1F7)) & (1 << 7)) != 0); i++)
            if(i >= 1000)
                return;
        
        if(inb(0x1F5)||inb(0x1F3)) {
            serial_printf("[\x1b[1;33mATA\x1b[0;0m] Drive 0xA0 not compatible with ATA SPECS ");
            return;
        }

        if((inb(0x1F7) & 0x08 )) {
            unsigned short* identdata = (unsigned short*)&ident;
            for(int idx = 0; idx < 255; idx++)
                identdata[idx] = inw(0x1F0);

            HDD='P';
            outb(0x1F0 + ATA_REG_CONTROL, 0x02);
            serial_printf("[\x1b[1;33mATA\x1b[0;0m] Hard Disk Initialized\n");
            serial_printf("[\x1b[1;33mATA\x1b[0;0m]\tPATA Info, Heads: %d\n",  ident.heads);
            serial_printf("[\x1b[1;33mATA\x1b[0;0m]\tSectors: %d\n",  ident.sectors);
            serial_printf("[\x1b[1;33mATA\x1b[0;0m]\tCylinders: %d\n", ident.cyls);
            serial_printf("[\x1b[1;33mATA\x1b[0;0m]\tBytes per Sector %d\n", ident.sector_bytes);
            serial_printf("[\x1b[1;33mATA\x1b[0;0m]\tBytes per Track %d\n", ident.track_bytes);
            serial_printf("[\x1b[1;33mATA\x1b[0;0m]\tSerial No: %s\n", (char*)ident.serial_no);
        }
    } else {
        outb(0x1F7,0xB0);
        _sleep(10);
        outb(0x1F2,0);
        outb(0x1F3,0);
        outb(0x1F4,0);
        outb(0x1F5,0);
        outb(0x1F7,0xEC);
        _sleep(10);

        if(inb(0x1F7)&&!(inb(0x1F7)&0x01)) {
            serial_printf("[\x1b[1;33mATA\x1b[0;0m] Drive 0xB0 exists\n");
            for(int i = 0; (((inb(0x1F7)) & (1 << 7)) != 0) && (inb(0x1F7)&0x01); i++)
                if(i>=1000)
                    return;

            if(inb(0x1F5)||inb(0x1F3)) {
                serial_printf("[\x1b[1;33mATA\x1b[0;0m] Drive 0xB0 not compatible with ATA SPECS ");
                return;
            }

            if ((inb(0x1F7) & 0x08)) {
                unsigned short* identdata = (unsigned short*) &ident;
                for(int idx = 0; idx < 255; idx++)
                    identdata[idx] = inw( 0x1F0 );
                
                HDD='S';
                outb(0x1F0+ATA_REG_CONTROL,0x02);
                serial_printf("[\x1b[1;33mATA\x1b[0;0m] Hard Disk Initialized\n");
                serial_printf("[\x1b[1;33mATA\x1b[0;0m]\tPATA Info, Heads: %d\n",  ident.heads);
                serial_printf("[\x1b[1;33mATA\x1b[0;0m]\tSectors: %d\n",  ident.sectors);
                serial_printf("[\x1b[1;33mATA\x1b[0;0m]\tCylinders: %d\n", ident.cyls);
                serial_printf("[\x1b[1;33mATA\x1b[0;0m]\tBytes per Sector %d\n", ident.sector_bytes);
                serial_printf("[\x1b[1;33mATA\x1b[0;0m]\tBytes per Track %d\n", ident.track_bytes);
                serial_printf("[\x1b[1;33mATA\x1b[0;0m]\tSerial No: %s\n", (char*)ident.serial_no);
                printf((char*)ident.serial_no);
            }
        } else {
            kpanic("No harddisk found, system can't work with out it");
            return;
        }
    }
}

void read_ata(unsigned int addr, unsigned char *buffer) {
    read_sector(addr);
    while (!(inb(0x1F7) & 0x08)) {}
    unsigned char tmpword;
    for (int idx = 0; idx < 256; idx++) {
        tmpword = inw(0x1F0);
        buffer[idx * 2] = (unsigned char)tmpword;
        buffer[idx * 2 + 1] = (unsigned char)(tmpword >> 8);
    }
}

void write_ata(char *buffer, unsigned int addr) {
    write_sector(addr);
    while (!(inb(0x1F7) & 0x08)) {}
    unsigned char tmpword;
    for (int idx = 0; idx < 256; idx++) {
        tmpword = buffer[8 + idx * 2] | (buffer[8 + idx * 2 + 1] << 8);
        outw(0x1F0, tmpword);
    }
}

mbr_t mbr;

int read_partition_map() {
	read_ata(0, (unsigned char*)&mbr);

	if (mbr.signature[0] == 0x55 && mbr.signature[1] == 0xAA) {
		printf("Partition table found.");

		for (int i = 0; i < 4; ++i) {
			if (mbr.partitions[i].status & 0x80) {
				printf("Partition #%d: @%d+%d");
			} else {
				printf("Partition #%d: inactive");
			}
		}

		return 0;
	} else {
		printf("Did not find partition table ");
		printf("%d\n",  mbr.signature[0]);
		printf("\t");
		printf("%d\n",  mbr.signature[1]);

		printf("Parsing anyone yields:");

		for (int i = 0; i < 4; ++i) {
			if (mbr.partitions[i].status & 0x80) {
				printf("\tPartition ");
                printf("%d\n",  i+1);
                printf("\t: ");
                printf("%d\n",  mbr.partitions[i].lba_first_sector);
                printf("\t");
                printf("%d\n",  mbr.partitions[i].sector_count);
			} else {
				printf("Partition inactive:");
                printf("%d\n",  i+1);
                printf("\t");
			}
		}
	}

	return 1;
}