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

struct root_entry
{
	char file_name[8];
	char file_ext[3];
	char attribute;
	char reserved;
	char created_time_ms;
	int created_time;
	int created_date;
	int accessed_date;
	int first_clu_fat32;
	int modified_time;
	int modified_date;
	int first_cluster;
	long file_size;
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

void rootEntryPrint(root_entry e)
{


	if (e.file_name[0] =='\0' || e.file_size < 0) return;

	int a = (int) e.file_name[0];
	if (a == 0xe5) return;


	int i;
	for(i=0; i<8; i++) {
		printf("%c", e.file_name[i]);
	}
	printf("  ");
	for(i=0; i<3; i++) {
		printf("%c", e.file_ext[i]);
	}
	printf("   ");
	if(e.attribute == 0x10) {
		printf("<<DIR>>");
	} else {
		printf("%ld", e.file_size);
	}

	printf("   ");
	printf("%d", (e.created_date <<11)>>11);


	printf("/%d", (e.created_date<<7)>>12);


	printf("/%d", (e.created_date>>9)+1980);
	printf("   ");

	printf ("  %d", e.first_cluster);

	printf("\n");
}

void main()
{
	int i;

	bootsector *bs= new bootsector();

	absread(2,1,0,bs);

	root_entry* rootEn = new root_entry[bs->root_entries];


	int NoOfClusInRoot = (bs->root_entries) * 32/ (bs->bytes_per_sector);
	int firstClusInRoot = bs->reserved_sectors + bs->number_of_fats * bs->sectors_per_fat;
	absread(2,NoOfClusInRoot, firstClusInRoot, rootEn);

//	for (i=0; i<bs->root_entries; i++) rootEntryPrint(rootEn[i]);

	getch();

	int firstClusInFat = bs->reserved_sectors;
	int NoOfClusInFat = bs->sectors_per_fat;

	char *fatBuf = new char[bs->sectors_per_fat *bs->bytes_per_sector];

	absread(2,NoOfClusInFat, firstClusInFat, fatBuf);

	for (i=2; i<500; i++) printf(" _ %x", (int) (fatBuf + i*2));

//	getch();

 /*	int condition=0;

	for (i=0; i<bs->root_entries; i++)
	{
	  //	if (strcmp(rootEn[i].file_name, "bootsect") ==0)
	  if(  (rootEn[i].file_name[0]=='b') && (rootEn[i].file_name[1]=='o') && (rootEn[i].file_name[2]=='o')
	  && (rootEn[i].file_name[3]=='t') && (rootEn[i].file_name[4]=='s') && (rootEn[i].file_name[5]=='e')
	  && (rootEn[i].file_name[6]=='c') && (rootEn[i].file_name[7]=='t') )
		{
			condition=1;
			long clus = rootEn[i].first_cluster;
			long size =0;
			while(clus < 0xfff8 && size <rootEn[i].file_size )
			{
				printf("__%d", clus);
				size = size + bs->bytes_per_sector * bs->sector_per_cluster;
				clus = fatBuf[clus];
			}
		}
	}
	if (condition==0)  printf("\n file nay khong co trong thu muc goc");

	*/
	getch();


}
