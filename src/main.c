#include <stdio.h>
#include <string.h>

#include "fat12.h"

void ask_path(char *filename) {
	printf("File to format:\n");
	
	printf(">");
	fgets(filename, 100, stdin);
	filename[strcspn(filename, "\n")] = 0;
}

int main() {
	char filename[100];
	BootSector bs;

	ask_path(filename);
	init_f12(&bs);
	format_f12(&bs, filename);	
}
