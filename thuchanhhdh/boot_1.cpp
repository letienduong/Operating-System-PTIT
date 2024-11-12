#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<string.h>

struct bootsector
{
	char jump_instruction[3];
	char OEM_ID[8];
	int bytes_per_sector;
	char sector_per_cluster;
	int reserved_sectors;
	char number_of_fats;
	int root_entries;
	int small_sectors;
	char media_descriptor;
	int sectors_per_fat;
	int sectors_per_track;
	int number_of_heads;
	long hidden_sectors;
	long large_sectors;
	char physical_drive_number;
	char reserved;
	char extended_boot_signature;
	char volume_serial_number[4];
	char volume_lable[11];
	char file_system_type[8];
	char bootstrap_code[448];
	char end_of_sector_marker[2];

};


void bootsectorPrint (bootsector *bs)
{
	printf("OEM ID: %s \n", bs->OEM_ID);
	printf("bytes per sector: %d \n", bs->bytes_per_sector);
	printf("sectors per cluster: %d \n", bs->sector_per_cluster);
	printf("number of fat table: %d \n", bs->number_of_fats);
	printf("root entries: %d \n", bs->root_entries);
	printf("total sectors: %d \n", bs->small_sectors);
	printf(" media descriptor: %x \n", bs->media_descriptor	);
	printf("sectors per fat: %d \n", bs->sectors_per_fat);
	printf("sectors per track: %d \n", bs->sectors_per_track);
	printf("number of heads: %d \n", bs->number_of_heads);
	printf("hidden sectors: %ld \n", bs->hidden_sectors);
	printf("total sectors: %ld \n", bs->large_sectors);
	printf("physical drive number: %x \n", bs->physical_drive_number);
	printf("volume serial number: %s \n", bs->volume_serial_number);
	printf("volume lable: %s \n", bs->volume_lable);
	printf("file system type: %s \n", bs->file_system_type);

}


void main()
{
	int i;

	bootsector *bs= new bootsector();

	absread(2,1,0,bs);

	bootsectorPrint(bs);


	getch();


}
