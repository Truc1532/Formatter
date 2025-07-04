#ifndef FAT_12_H
#define FAT_12_H

#include <stdint.h>

typedef struct __attribute__((packed)) {
	uint8_t jump[3];
	uint8_t oem_identifier[8];
	uint16_t bytes_per_sector;
	uint8_t sectors_per_cluster;
	uint16_t reserved_sectors;
	uint8_t fat_count;
	uint16_t root_dir_entries;
	uint16_t total_sectors;
	uint8_t media_descriptor;
	uint16_t sectors_per_fat;
	uint16_t sectors_per_track;
	uint16_t num_heads;
	uint32_t hidden_sectors;
	uint32_t large_sector_count;

	uint8_t drive_num;
	uint8_t flags;
	uint8_t signature;
	uint32_t volume_id;
	uint8_t volume_label[11];
	uint8_t system_identifier[8];
	uint8_t boot_code[448];
	uint16_t boot_partition_signature;

} BootSector;

extern void init_f12(BootSector *bs);
extern void format_f12(BootSector *bs, const char *device);

#endif
