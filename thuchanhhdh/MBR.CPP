
#include <bios.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <iostream.h>


typedef unsigned char byte;
typedef unsigned int word;

struct PT
{
	byte activedisk;
	byte fstHead;
	word fstCySector;
	byte type;
	byte endHead;
	word endCySector;
	unsigned long frontSect; //So sector giua MBR va sector dau tien trong PT
	unsigned long NoOfSector;
};

struct MBR
{
	char CTmoi[446];
	PT PartTbl[4];
	word signature;
};


void main()
{
	FILE *f;
	MBR MBR1;

	printf("\n Kich thuoc PT: %d byte", sizeof(PT));
	printf("\n Kich thuoc MBR: %d byte", sizeof(MBR));

	if ((f=fopen("MBR.dat", "r")) ==NULL)
	{
		printf("\n Loi doc file");
		getch();
		return;
	}

	fread(&MBR1, sizeof(MBR), 1, f);

	cout<<endl<<"Chuong trinh moi:"<<endl;
	for (int i=0; i<446; i++) printf("%c", MBR1.CTmoi[i]);

	for(i=0; i<4; i++)
	{
		printf("\n PT %d", i+1);
		if(MBR1.PartTbl[i].activedisk ==80) printf("\n Dia tuong ung chua HDH");
		else printf("\n Dia khong chua HDH");

		printf("\n Mat dau: %p", MBR1.PartTbl[i].fstHead);
		unsigned int a = MBR1.PartTbl[i].fstCySector;
		printf("\n Cylinder dau: %p", a>>6);
		printf("\n Sector dau tien: %p", (MBR1.PartTbl[i].fstCySector<<10)>>10);
		printf("\n Kieu dia: %p", MBR1.PartTbl[i].type);
		printf("\n Mat cuoi: %p", MBR1.PartTbl[i].endHead);
		printf("\n Cylinder cuoi: %p", MBR1.PartTbl[i].endCySector>>6);
		printf("\n Sector cuoi: %p", (MBR1.PartTbl[i].endCySector<<10)>>10);
		printf("\n So sector giua MBR va dia logic: %lu",MBR1.PartTbl[i].frontSect);
		printf("\n So sector cua dia: %lu", MBR1.PartTbl[i].NoOfSector);
	}
	printf("\n Gia tri 2 byte cuoi: %p", MBR1.signature);
	fclose(f);
	getch();
}








