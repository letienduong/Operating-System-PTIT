
#include <bios.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <iostream.h>


typedef unsigned char byte;
typedef unsigned int word;

struct BOOT32
{
	byte jmpBoot[3];
	char OEMName[8];  //ten hang
	word BytePerSec;
	byte SecPerClus;
	word RsvdSec;
	byte NumFATs;
	word RootEnt;
	word TotSec16;
	byte Media;
	word FATSz16;
	word SecPerTrk;
	word NumHeads;
	unsigned long HiddSec;
	unsigned long TotSec32;
	unsigned long FATSz32;
	word ExtFlags;
	word FSVer;
	unsigned long RootClus;
	word FSInfo;
	word BkBootSec;
	byte Reserved[12];
	byte DrvNum;
	byte Reserved1;
	byte BootSig;
	unsigned long VolID;
	byte VolLab[11];
	byte FilSysType[8];

};

void main()
{
	FILE *f;
	BOOT32 B;

	printf("\n Kich thuoc BOOT: %d byte", sizeof(BOOT32));

	if ((f=fopen("BOOT32.dat", "r")) ==NULL)
	{
		printf("\n Loi doc file");
		getch();
		return;
	}

	fread(&B, sizeof(BOOT32), 1, f);

	printf("\n Lenh nhay: %p"," %p "," %p", B.jmpBoot[0], B.jmpBoot[1], B.jmpBoot[2]);
	printf("\n Ten hang: %s", B.OEMName);
	printf("\n So luong byte/Sector: %d", B.BytePerSec);
	printf("\n So luong sector/Cluster: %p", B.SecPerClus);
	printf("\n SO luong sector du tru trong vung du tru cua dia: %du", B.RsvdSec);
	printf("\n So luong bang FAT: %p", B.NumFATs);
	printf("\n So luong toi da khoan muc trong ROOT: %d", B.RootEnt);
	printf("\n So luong Sector trong dia (fat12,16): %d", B.TotSec16);
	printf("\n Kieu dia: %p", B.Media);
	printf("\n Kich thuoc FAT 12/16: %d", B.FATSz16);
	printf("\n So sector/track: %d", B.SecPerTrk);
	printf("\n So luong dau tu: %d", B.NumHeads);
	printf("\n So sector an truoc partiotion: %lu", B.HiddSec);
	printf("\n Tong so sector: %lu", B.TotSec32);
	printf("\n Kich thuoc FAT theo sector: %lu", B.FATSz32);
	printf("\n Flag: %d", B.ExtFlags);
	printf("\n version: %d", B.FSVer);
	printf("\n Cluster dau tien cua thu muc goc: %lu", B.RootClus);
	printf("\n Sector trong vung du tru dia copy boot: %d", B.BkBootSec);
	printf("\n Du tru: %s", B.Reserved);
	printf("\n So thu tu dia: %p", B.DrvNum);
	printf("\n Du tru 1: %p", B.Reserved1);
	printf("\n Dau hieu: %p", B.BootSig);
	printf("\n Volume ID: %lu", B.VolID);
	printf("\n Volume lable: %s", B.VolLab);
	printf("\n FAT 32: %s", B.FilSysType);

	fclose(f);
	getch();
}