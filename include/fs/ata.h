#pragma once

#define ATA_SR_BSY     0x80
#define ATA_SR_DRDY    0x40
#define ATA_SR_DF      0x20
#define ATA_SR_DSC     0x10
#define ATA_SR_DRQ     0x08
#define ATA_SR_CORR    0x04
#define ATA_SR_IDX     0x02
#define ATA_SR_ERR     0x01

#define ATA_ER_BBK      0x80
#define ATA_ER_UNC      0x40
#define ATA_ER_MC       0x20
#define ATA_ER_IDNF     0x10
#define ATA_ER_MCR      0x08
#define ATA_ER_ABRT     0x04
#define ATA_ER_TK0NF    0x02
#define ATA_ER_AMNF     0x01

#define ATA_CMD_READ_PIO          0x20
#define ATA_CMD_READ_PIO_EXT      0x24
#define ATA_CMD_READ_DMA_EXT      0x25
#define ATA_CMD_WRITE_PIO         0x30
#define ATA_CMD_WRITE_PIO_EXT     0x34
#define ATA_CMD_CACHE_FLUSH       0xE7
#define ATA_CMD_CACHE_FLUSH_EXT   0xEA
#define ATA_CMD_IDENTIFY_PACKET   0xA1
#define ATA_CMD_IDENTIFY          0xEC

#define ATAPI_CMD_READ       0xA8
#define ATAPI_CMD_EJECT      0x1B

#define IDE_ATA        0x00
#define IDE_ATAPI      0x01

#define ATA_MASTER     0x00
#define ATA_SLAVE      0x01

#define ATA_REG_DATA       0x00
#define ATA_REG_ERROR      0x01
#define ATA_REG_FEATURES   0x01
#define ATA_REG_SECCOUNT0  0x02
#define ATA_REG_LBA0       0x03
#define ATA_REG_LBA1       0x04
#define ATA_REG_LBA2       0x05
#define ATA_REG_HDDEVSEL   0x06
#define ATA_REG_COMMAND    0x07
#define ATA_REG_STATUS     0x07
#define ATA_REG_SECCOUNT1  0x08
#define ATA_REG_LBA3       0x09
#define ATA_REG_LBA4       0x0A
#define ATA_REG_LBA5       0x0B
#define ATA_REG_CONTROL    0x0C
#define ATA_REG_ALTSTATUS  0x0C
#define ATA_REG_DEVADDRESS 0x0D

#define ATA_PRIMARY      0x00
#define ATA_SECONDARY    0x01

#define ATA_READ      0x00
#define ATA_WRITE     0x01

typedef enum AtaCommand {
	ATA_CMD_NOP = 0x00,
	ATA_CMD_CFA_REQUEST_EXTENDED_ERROR = 0x03,
	ATA_CMD_DEVICE_RESET = 0x08,
	ATA_CMD_READ_SECTORS = 0x20,
	ATA_CMD_READ_SECTORS_EXT = 0x24,
	ATA_CMD_READ_DMA_QUEUED_EXT = 0x26,
	ATA_CMD_READ_NATIVE_MAX_ADDRESS_EXT = 0x27,
	ATA_CMD_READ_MULTIPLE_EXT = 0x29,
	ATA_CMD_READ_STREAM_DMA_EXT = 0x2a,
	ATA_CMD_READ_STREAM_EXT = 0x2b,
	ATA_CMD_READ_LOG_EXT = 0x2f,
	ATA_CMD_WRITE_SECTORS = 0x30,
	ATA_CMD_WRITE_SECTORS_EXT = 0x34,
	ATA_CMD_WRITE_DMA_EXT = 0x35,
	ATA_CMD_WRITE_DMA_QUEUED_EXT = 0x36,
	ATA_CMD_SET_MAX_ADDRESS_EXT = 0x37,
	ATA_CMD_CFA_WRITE_SECTORS_WITHOUT_ERASE = 0x38,
	ATA_CMD_WRITE_MULTIPLE_EXT = 0x39,
	ATA_CMD_WRITE_STREAM_DMA_EXT = 0x3a,
	ATA_CMD_WRITE_STREAM_EXT = 0x3b,
	ATA_CMD_WRITE_DMA_FUA_EXT = 0x3d,
	ATA_CMD_WRITE_DMA_QUEUED_FUA_EXT = 0x3e,
	ATA_CMD_WRITE_LOG_EXT = 0x3f,
	ATA_CMD_READ_VERIFY_SECTORS = 0x40,
	ATA_CMD_READ_VERIFY_SECTORS_EXT = 0x42,
	ATA_CMD_WRITE_UNCORRECTABLE_EXT = 0x45,
	ATA_CMD_READ_LOG_DMA_EXT = 0x47,
	ATA_CMD_CONFIGURE_STREAM = 0x51,
	ATA_CMD_WRITE_LOG_DMA_EXT = 0x57,
	ATA_CMD_TRUSTED_RECEIVE = 0x5c,
	ATA_CMD_TRUSTED_RECEIVE_DMA = 0x5d,
	ATA_CMD_TRUSTED_SEND = 0x5e,
	ATA_CMD_TRUSTED_SEND_DMA = 0x5f,
	ATA_CMD_CFA_TRANSLATE_SECTOR = 0x87,
	ATA_CMD_EXECUTE_DEVICE_DIAGNOSTIC = 0x90,
	ATA_CMD_DOWNLOAD_MICROCODE = 0x92,
	ATA_CMD_PACKET = 0xa0,
	ATA_CMD_IDENTIFY_PACKET_DEVICE = 0xa1,
	ATA_CMD_SERVICE = 0xa2,
	ATA_CMD_SMART = 0xb0,
	ATA_CMD_DEVICE_CONFIGURATION_OVERLAY = 0xb1,
	ATA_CMD_NV_CACHE = 0xb6,
	ATA_CMD_CFA_ERASE_SECTORS = 0xc0,
	ATA_CMD_READ_MULTIPLE = 0xc4,
	ATA_CMD_WRITE_MULTIPLE = 0xc5,
	ATA_CMD_SET_MULTIPLE_MODE = 0xc6,
	ATA_CMD_READ_DMA_QUEUED = 0xc7,
	ATA_CMD_READ_DMA = 0xc8,
	ATA_CMD_WRITE_DMA = 0xca,
	ATA_CMD_WRITE_DMA_QUEUED = 0xcc,
	ATA_CMD_CFA_WRITE_MULTIPLE_WITHOUT_ERASE = 0xcd,
	ATA_CMD_WRITE_MULTIPLE_FUA_EXT = 0xce,
	ATA_CMD_CHECK_MEDIA_CARD_TYPE = 0xd1,
	ATA_CMD_STANDBY_IMMEDIATE = 0xe0,
	ATA_CMD_IDLE_IMMEDIATE = 0xe1,
	ATA_CMD_STANDBY = 0xe2,
	ATA_CMD_IDLE = 0xe3,
	ATA_CMD_READ_BUFFER = 0xe4,
	ATA_CMD_CHECK_POWER_MODE = 0xe5,
	ATA_CMD_SLEEP = 0xe6,
	ATA_CMD_FLUSH_CACHE = 0xe7,
	ATA_CMD_WRITE_BUFFER = 0xe8,
	ATA_CMD_FLUSH_CACHE_EXT = 0xea,
	ATA_CMD_IDENTIFY_DEVICE = 0xec,
	ATA_CMD_SET_FEATURES = 0xef,
	ATA_CMD_SECURITY_SET_PASSWORD = 0xf1,
	ATA_CMD_SECURITY_UNLOCK = 0xf2,
	ATA_CMD_SECURITY_EARASE_PREPARE = 0xf3,
	ATA_CMD_SECURITY_ERASE_UNIT = 0xf4,
	ATA_CMD_SECURITY_FREEZE_LOCK = 0xf5,
	ATA_CMD_SECURITY_DISABLE_PASSWORD = 0xf6,
	ATA_CMD_READ_NATIVE_MAX_ADDRESS = 0xf8,
	ATA_CMD_SET_MAX_ADDRESS = 0xf9
} AtaCommand;

typedef enum AtaStatus {
	ATA_STAT_BUSY = 0x80,
	ATA_STAT_READY = 0x40,
	ATA_STAT_FAULT = 0x20,
	ATA_STAT_SEEK = 0x10,
	ATA_STAT_DRQ = 0x08,
	ATA_STAT_CORR = 0x04,
	ATA_STAT_INDEX = 0x02,
	ATA_STAT_ERR = 0x01,
} AtaStatus;


typedef struct ident_device_t {
	unsigned short	config;		
	unsigned short	cyls;		
	unsigned short	reserved2;	
	unsigned short	heads;		
	unsigned short	track_bytes;	
	unsigned short	sector_bytes;	
	unsigned short	sectors;	
	unsigned short	vendor0;	
	unsigned short	vendor1;	
	unsigned short	vendor2;	
	unsigned char	serial_no[20];	
	unsigned short	buf_type;
	unsigned short	buf_size;	
	unsigned short	ecc_bytes;	
	unsigned char	fw_rev[8];	
	unsigned char	model[40];	
	unsigned char	max_multsect;	
	unsigned char	vendor3;	
	unsigned short	dword_io;	
	unsigned char	vendor4;	
	unsigned char	capability;	
	unsigned short	reserved50;	
	unsigned char	vendor5;	
	unsigned char	tPIO;	
	unsigned char	vendor6;	
	unsigned char	tDMA;		
	unsigned short	field_valid;	
	unsigned short	cur_cyls;	
	unsigned short	cur_heads;	
	unsigned short	cur_sectors;	
	unsigned short	cur_capacity0;	
	unsigned short	cur_capacity1;	
	unsigned char	multsect;	
	unsigned char	multsect_valid;	
	unsigned int	lba_capacity;	
	unsigned short	dma_1word;	
	unsigned short	dma_mword;	
	unsigned short  eide_pio_modes; 
	unsigned short  eide_dma_min;	
	unsigned short  eide_dma_time;	
	unsigned short  eide_pio;      
	unsigned short  eide_pio_iordy; 
	unsigned short	words69_70[2];	
	unsigned short	words71_74[4];	
	unsigned short  queue_depth;	
	unsigned short  words76_79[4];	
	unsigned short  major_rev_num;	
	unsigned short  minor_rev_num;	
	unsigned short  command_set_1;	
	unsigned short  command_set_2;	
	unsigned short  cfsse;		
	unsigned short  cfs_enable_1;	
	unsigned short  cfs_enable_2;	
	unsigned short  csf_default;	
	unsigned short  dma_ultra;	
	unsigned short	word89;		
	unsigned short	word90;		
	unsigned short	CurAPMvalues;	
	unsigned short	word92;		
	unsigned short	hw_config;	
	unsigned short  words94_125[32];
	unsigned short	last_lun;	
	unsigned short	word127;	
	unsigned short	dlf;		
	unsigned short  csfo;		
	unsigned short	words130_155[26];
	unsigned short	word156;
	unsigned short	words157_159[3];
	unsigned short	words160_255[95];
} identify_device_t;

#define SECTORSIZE		512
#define DISK_PORT		0x1F0

typedef struct {
	unsigned char  status;
	unsigned char  chs_first_sector[3];
	unsigned char  type;
	unsigned char  chs_last_sector[3];
	unsigned int   lba_first_sector;
	unsigned int   sector_count;
} partition_t;

typedef struct {
	unsigned short  flags;
	unsigned short  unused1[9];
	char            serial[20];
	unsigned short  unused2[3];
	char            firmware[8];
	char            model[40];
	unsigned short  sectors_per_int;
	unsigned short  unused3;
	unsigned short  capabilities[2];
	unsigned short  unused4[2];
	unsigned short  valid_ext_data;
	unsigned short  unused5[5];
	unsigned short  size_of_rw_mult;
	unsigned int    sectors_28;
	unsigned short  unused6[38];
	unsigned long   sectors_48;
	unsigned short  unused7[152];
} __attribute__((packed)) ata_identify_t;

typedef struct {
	unsigned char     boostrap[446];
	partition_t 	  partitions[4];
	unsigned char     signature[2];
} __attribute__((packed)) mbr_t;

void init_ata();

void _sleep(int ms);

void write_sector(unsigned int addr);

void read_sector(unsigned int addr);

void read_ata(unsigned int addr, unsigned char *buffer);

void write_ata(char *buffer, unsigned int addr);

int read_partition_map();