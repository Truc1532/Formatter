#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "fat12.h"

uint8_t sector[512] = {0};
 
void init_f12(BootSector *bs) {
	*bs = (BootSector) {
		.jump = {0xEB, 0x3C, 0x90},
		.oem_identifier = "MSWIN4.1",
		.bytes_per_sector = 512,
		.sectors_per_cluster = 1,
		.reserved_sectors = 1,
		.fat_count = 2,
		.root_dir_entries = 224,
		.total_sectors = 2880,
		.media_descriptor = 0xF0,
		.sectors_per_fat = 9,
		.sectors_per_track = 18,
		.num_heads = 2,
		.hidden_sectors = 0,
		.large_sector_count = 0,

		.drive_num = 0x00,
		.flags = 0x00,
		.signature = 0x29,
		.volume_id = 0x12345678,
		.volume_label = "NO NAME    ",
		.system_identifier = "FAT12   ",
		.boot_partition_signature = 0xAA55
	};
}

void format_f12(BootSector *bs, const char *device) {
	FILE *f = fopen(device, "rb+");
	if (!f) { perror("fopen"); return ;}
	memcpy(sector, bs, sizeof(*bs));

	uint8_t fat[512 * 9] = {0};
	fat[0] = 0xF0;
	fat[1] = 0xFF;
	fat[2] = 0xFF;

	uint8_t root_dir[224 * 32] = {0};

	fwrite(sector, 1, 512, f);

	fseek(f, 512 * 1, SEEK_SET);
	fwrite(fat, 1, sizeof(fat), f);
	
	fseek(f, 512 * 10, SEEK_SET);
	fwrite(fat, 1, sizeof(fat), f);

	fseek(f, 512 * 19, SEEK_SET);
	fwrite(root_dir, 1, sizeof(root_dir), f);

	uint8_t zero_block[512] = {0};
	for (int sector_num = 33; sector_num < 2880; sector_num++) {
		fseek(f, 512 * sector_num, SEEK_SET);
		fwrite(zero_block, 1, 512, f);
	}

	fclose(f);
}


	


