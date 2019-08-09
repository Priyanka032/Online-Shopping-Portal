// FINAL DSC Project ISC 3B

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>

struct Product
{
	int id;
	char name[20];
	int price;
	int qty;
};

struct Bill
{
	int pid;
	char pname[20];
	int pprice;
};

int getID();
int billFileNo();
void manageProduct();
void purchaseProduct();
void generateBill();
void addProduct();
void displayAllProduct();
struct Product findProduct(int id);
void updateProduct(int id,int qty);

char fproduct[]={"product.dat"};
char fbill[]={"bill.dat"};
int total=0;

int main()
{
	FILE *fp;
	int ch;
	clrscr();
	while(1)
	{
		clrscr();
		printf("==============================================================================================\n\n");
		printf("\t\t Welcome Product Mnagement System\n\n");
		printf("==============================================================================================\n\n");
		printf("1. Manage Product\n\n");
		printf("2. Purchase Product\n\n");
		printf("3. Generate Bill\n\n");
		printf("0. Exit\n\n");
		printf("==============================================================================================\n\n");
		printf("\n please enter your choice:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: manageProduct();
				break;
			case 2: purchaseProduct();
				break;
			case 3: generateBill();
				break;
			case 0: exit(0);
		}

	}
	return 0;
	getch();
}

int getID()
{
	FILE *fp;
	int value=0;
	fp=fopen("prodid.txt","r");
	if(fp==NULL)
	{
		fp=fopen("prodid.txt","w");
		fprintf(fp,"%d",0);
		fclose(fp);
		fp=fopen("prodid.txt","r");
	}
	fscanf(fp,"%d",&value);
	fclose(fp);
	fp=fopen("prodid.txt","w");
	fprintf(fp,"%d",value+1);
	fclose(fp);
	return value+1;
}

void manageProduct()
{
	int ch;
	int back=0;
	while(1)
	{
		clrscr();
		printf("==========================================\n\n");
		printf("\t\t Welcome Product Management System\n\n");
		printf("==========================================\n\n");
		printf("1.Add new product\n\n");
		printf("2. display all product\n\n");
		printf("0. Back\n\n");
		printf("===========================================\n\n");
		printf("\n please enter your choice:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: addProduct();
				break;
			case 2: displayAllProduct();
				break;
			case 0: back=1;
				break;
		}
		if(back==1)
		{
			break;
		}
		else
		{
			getch();
		}
	}
}

void addProduct()
{
	FILE *fp;
	struct Product t1;
	fp=fopen(fproduct,"ab");
	t1.id=getID();
	printf("\n enter product name:");
	scanf("%s",t1.name);
	printf("\n enter product price:");
	scanf("%d",&t1.price);
	printf("\n Enter product qty:");
	scanf("%d",&t1.qty);
	fwrite(&t1,sizeof(t1),1,fp);
	fclose(fp);
}

void displayAllProduct()
{
	FILE *fp;
	struct Product t;
	int id,found=0;
	clrscr();
	fp=fopen(fproduct,"rb");
	printf("\n=========================================\n\n");
	printf("\t\t Product Details \n\n");
	printf("===========================================\n\n");
	printf("ID\tname\tQty.\tPrice\n\n");
	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		if(feof(fp))
		{
			break;
		}
		printf("%d\t",t.id);
		printf("%s\t",t.name);
		printf("%d\t",t.qty);
		printf("%d\t\t\n",t.price);
	}
	printf("============================================\n\n");
	fclose(fp);
}

void purchaseProduct()
{
	char ch1,ch2;
	int id;
	clrscr();
	printf("=====================\n\n");
	printf("\t\t welcome product management system\n\n");
	printf("=====================\n\n");
	while(1)
	{
		displayAllProduct();
		fflush(stdin);
		printf("\n\ndo you want to purchase[y/n]:");
		scanf("%c",&ch1);
	if(ch1=='y')
	{
		FILE *fp;
		struct Bill t1;
		struct Product t2;
		fp=fopen(fbill,"ab");
		printf("\n\n enter the product ID to purchase:");
		scanf("%d",&id);
		t2=findProduct(id);
		t1.pid=t2.id;
		strcpy(t1.pname,t2.name);
		t1.pprice=t2.price;
		fwrite(&t1,sizeof(t1),1,fp);
		fclose(fp);
	}
		fflush(stdin);
		printf("\n\n do you want to continue[y/n]:");
		scanf("%c",&ch2);
		if(ch2=='n')
		{
			break;
		}
		getch();
	}
}
struct Product findProduct(int id)
{
	FILE *fp;
	struct Product t;
	fp=fopen(fproduct,"rb");
	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		if(feof(fp))
		{
			break;
		}
		if(t.id==id)
		{
			updateProduct(id,t.qty-1);
			break;
		}
	}
	fclose(fp);
	return t;
}
void updateProduct(int id,int qty)
{
	FILE *fp,*fp1;
	struct Product t,t1;
	int found=0;
	fp=fopen(fproduct,"rb");
	fp1=fopen("temp.dat","wb");
	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		if(feof(fp))
		{
			break;
		}
		if(t.id==id)
		{
			found=1;
			t.qty=qty;
			fwrite(&t,sizeof(t),1,fp1);
		}
		else
		{
			fwrite(&t,sizeof(t),1,fp1);
		}
		}
		fclose(fp);
		fclose(fp1);

	if(found==0)
	{
		printf("sorry no record found\n\n");
	}
	else
	{
		fp=fopen(fproduct,"wb");
		fp1=fopen("temp.dat","rb");
		while(1)
		{
			fread(&t,sizeof(t),1,fp1);
			if(feof(fp1))
			{
			break;
			}
			fwrite(&t,sizeof(t),1,fp);
		}
	}
	fclose(fp);
	fclose(fp1);
}

void generateBill()
{
	FILE *fp,*fp1;
	struct Bill t;
	int id, found=0;
	char ch1;
	int brel=0;
	char billname[20];

	clrscr();

	fp=fopen(fbill,"rb");

	printf("\n==================================================\n\n");
	printf("\t\tBill Details\n\n");
	printf("==================================================\n\n");

	printf("Pro-ID\tPro-Name\tPro-Price\n\n");

	while(1)
	{
		fread(&t,sizeof(t),1,fp);

		if(feof(fp))
		{
			break;
		}

		printf("%d\t",t.pid);
		printf("%s\t",t.pname);
		printf("%d\t\t\t\n",t.pprice);
		total=total+t.pprice;
	}

	printf("\n\n===============>>>>Total Bill Amount [Rs: %d]\n\n",total);

	fclose(fp);

	if(total!=0)
	{
		fflush(stdin);
		printf("\n\n\nDo you want to go back? [Y/N]:");
		scanf("%c",&ch1);

		if(ch1=='Y')
		{
			brel=billFileNo();
			sprintf(billname,"%s%d","",brel);
			strcat(billname,"dat");

			fp=fopen(fbill,"rb");
			fp1=fopen(billname,"wb");

			while(1)
			{
				fread(&t,sizeof(t),1,fp);

				if(feof(fp))
				{
					break;
				}
				fwrite(&t,sizeof(t),1,fp1);
			}
			fclose(fp);
			fclose(fp1);

			fp=fopen(fbill,"wb");
			fclose(fp);
			total=0;
		}
	}
	else
	{
		printf("\n\nSorry item selected\n\n");
	}
}

int billFileNo()
{
	FILE *fp;
	int value=0;
	fp=fopen("billno.txt","r");
	if(fp==NULL)
	{
		fp=fopen("billno.txt","w");
		fprintf(fp,"%d",0);
		fclose(fp);
		fp=fopen("billno.txt","r");
	}
	fscanf(fp,"%d",&value);
	fclose(fp);
	fp=fopen("billno.txt","w");
	fprintf(fp,"%d",value+1);
	fclose(fp);
	return value+1;
}





