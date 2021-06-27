#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>

#define NS 15
#define CS 4

/*this is global variable*/
COORD coord= {0,0};

/*Handle Screen handling*/ 
void moveToXY(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

/*declaration of checking functions*/
void check_code(char[]);
int check_value(char[]);

/* declaration of type*/
typedef struct
{
    char name[NS],code[CS];
    float rate;
    int quantity;
} rec;
rec item;

/*declaration of display functions*/
void choices(int);
void display_mainmenu();
void display_bill();
void window(int,int,int,int);
void highlight(int,int);
void display_items(rec *,int,int);
void dis_con();
void display_search();

/*declaration of business logic*/
void calculate_bill();
void add_items();
void edit_items();
void del_items();
void exit();

/*declaration of display functions*/
void display_code();
void display_rate();
void display_quantity();
void display_all();

/*start of main*/
int main()
{
    display_mainmenu();
    return 0;
}

void display_mainmenu()
{
    int i;
    char ch;
    const char *menu[]= {"   Calculate Bill","   Add Goods","   Edit Goods","   Display All ","   Search", "   Delete Goods","   Exit"};
    system("cls");

//textbackground(11);
//textcolor(0);
//_setcursortype(_NOCURSOR);
    window(40,90,20,40);
    moveToXY(84,10);

    printf("MAIN MENU");
    choices(7);
}


/*function for cursor movement*/
void choices(int no)
{
    int count=1;
    char ch='0';
    moveToXY(100,8);
    while(1)
    {
        switch(ch)
        {
	        case 80:
	            count++;
	            if (count==no+1) count=1;
	            break;
	        case 72:
	            count--;
	            if(count==0) count=no;
	            break;
        }
        highlight(no,count);

        ch=getch();
        
        if(ch=='\r')
        {
            if(no==7)
            {
                if (count==1) calculate_bill() ;
                else if(count==2) add_items();
                else if(count==3) edit_items();
                else if (count==4) display_all();
                else if (count==5) display_search();
                else if (count==6) del_items();
                else   exit(0);
            
            }
            if(no==4)
            {
                if (count==1) display_code();
                else if (count==2)display_rate();
                else if (count==3) display_quantity();
                else display_mainmenu();
            }
        }
    }
}

void calculate_bill()
{
	char x[4] = {0};
    int j=15,q=0,size=0,i=1;
    float total=0,gtotal=0;

    FILE *file;
    file=fopen("record.txt","r+b");
    rewind(file);

	system("cls");
	window(40,100,20,35);
	display_bill();
	moveToXY(80,30);
    printf("enter  \"end\" to finish input");

    while(1)
    {
        moveToXY(15,18);
        printf("                    ");
        moveToXY(15,19);
        printf("                    ");
        moveToXY(15,18);
        printf("Enter item code:");
        scanf("%s",x);
        if(strcmp(x,"end")==0)
            break;
        moveToXY(15,19);
        printf("Enter quantity:");
        scanf("%d",&q);
        rewind(file);
        while(fread(&item,sizeof(item),1,file))
        {
            if((strcmp(item.code,x)==0))
            {
 				if(item.quantity-q < 0)
                {
                    moveToXY(10,22);
                    printf("Don't have enough items in store for item name:%s",item.name);
                    break;
                }

                total=item.rate*q;
                moveToXY(65,j);
                printf("%4d",i);
                printf("%9s",item.name);
                printf("%13d",q);
                printf("%15.2f",item.rate);
                printf("%13.2f",total);
                gtotal=gtotal+total;
                size=sizeof(item);
                item.quantity=item.quantity-q;
                j+=2;
                i++;
                fseek(file,-size,SEEK_CUR);
                fwrite(&item,sizeof(item),1,file);
                break;
            }
        }
    }
    if(gtotal!=0)
    {
        moveToXY(75,j+5);
        printf("TOTAL AMOUNT = NRs. %6.2f",gtotal);
    }
    getch();
    display_mainmenu();

}

/*function to display bill window*/
void display_bill()
{
    int i;
    moveToXY(65,8);

    for (i=1; i<=10; i++)
        printf("*");
    printf(" * Storage Management System * ");
    for (i=1; i<=10; i++)
        printf("*");
    printf("\n\n");

    moveToXY(80,10);
    printf("CUSTOMER'S BILL") ;

    moveToXY(67 ,13);
    printf("SN.   Item Name     Quantity     Rate          Total");

}

void highlight(int no,int count)
{
    if (no==4)
    {
       
        moveToXY(75,15);
        printf("   By Code          ");
        moveToXY(75,17);
        printf("   By Rate          ");
        moveToXY(75,19);
        printf("   By Quantity      ");
        moveToXY(75,21);
        printf("   Back to main menu");
        switch (count)
        {
            case 1:
                moveToXY(75,15);
                printf(" - By Code          ");
                break;
            case 2:
                moveToXY(75,17);
                printf(" - By Rate          ");
                break;
            case 3:
                moveToXY(75,19);
                printf(" - By Quantity      ");
                break;
            case 4:
                moveToXY(75,21);
                printf(" - Back to main menu");
                break;
        }
    }

    if(no==7)
    {
        moveToXY (75,15);
        printf("   Calculate Final Bill ");
        moveToXY (75,17);
        printf("   Add Items      ");
        moveToXY (75,19);
        printf("   Edit Items     ");
        moveToXY (75,21);
        printf("   Display All Items    ");
        moveToXY (75,23);
        printf("   Search Items        ");
        moveToXY (75,25);
        printf("   Delete Items   ");
        moveToXY (75,27);
        printf("   Exit           ");
       
        switch(count)
        {
            case 1:
                moveToXY (75,15);
                printf(" - Calculate Final Bill ");
                break;
            case 2:
                moveToXY (75,17);
                printf(" - Add Items      ");
                break;
            case 3:
                moveToXY (75,19);
                printf(" - Edit Items     ");
                break;
            case 4:
                moveToXY (75,21);
                printf(" - Display All Items   ");
                break;
            case 5:
                moveToXY (75,23);
                printf(" - Search Items       ");
                break;
            case 6:
                moveToXY (75,25);
                printf(" - Delete Items   ");
                break;
            case 7:
                moveToXY (75,27);
                printf(" - Exit           ");
                break;
        }
    }
}

/*function to display box*/
void window(int a,int b,int c,int d)
{
    int i;
    system("cls");
    moveToXY(75,5);	

    for (i=1; i<=10; i++)
        printf("*");
    printf(" *  * ");
    for (i=1; i<=10; i++)
        printf("*");
    printf("\n\n");
    moveToXY(70,6);
    printf("Storage Management System By Jainish Dabhi");

    for (i=a; i<=b; i++)
    {
        moveToXY(i+22,9);
        printf("\xcd");
        moveToXY(i+22,11);
        printf("\xcd");
        moveToXY(i+22,c-7);
        printf("\xcd");
        moveToXY(i+22,d-7);
        printf("\xcd");
    }

    moveToXY(a+22,9);
    printf("\xc9");
    moveToXY(a+22,10);
    printf("\xba");
    moveToXY(a+22,11);
    printf("\xc8");
    moveToXY(b+22,9);
    printf("\xbb");
    moveToXY(b+22,10);
    printf("\xba");
    moveToXY(b+22,11);
    printf("\xbc");

    for(i=c; i<=d; i++)
    {
        moveToXY(a+22,i-7);
        printf("\xba");
        moveToXY(b+22,i-7);
        printf("\xba");
    }

    moveToXY(a+22,c-7);
    printf("\xc9");
    moveToXY(a+22,d-7);
    printf("\xc8");
    moveToXY(b+22,c-7);
    printf("\xbb");
    moveToXY(b+22,d-7);
    printf("\xbc");

}


/*function to add records*/
void add_items()
{
    FILE *file;
    
    char y[CS],x[12];
    
    system("cls");
    
    moveToXY(75,5);
    printf("Enter new record(Y/N)?");
    while(toupper(getche())=='Y')
    {
        system("cls");
        file=fopen("record.txt","ab");
        check_code(y);
        strcpy(item.code,y);
        moveToXY(70,16);
        printf("Enter rate of the item:");
        scanf("%f",&item.rate);
        moveToXY(70,18);
        printf("Enter quantity of the item:");
        scanf("%d",&item.quantity);
        moveToXY(70,20);
        printf("Enter name of the item:");
        scanf("%s",item.name);
        fseek(file,0,SEEK_END);
        fwrite(&item,sizeof(item),1,file);
        fclose(file);
        moveToXY(70,22);
        printf("Enter new record(Y/N)?");

    }
    display_mainmenu();
}

/*function to check availability of code*/
void check_code(char y[])
{
    int flag;
    FILE *file;
    file=fopen("record.txt","rb");
    while(1)
    {
        system("cls");
        window(40,100,20,35);
        moveToXY(75,10);
        printf(" ADD Items ")  ;
        flag=1;
        rewind(file);
        moveToXY(70	,14);
        printf("Enter new code of the item:");
        scanf(" %[^\n]",y);
        while(fread(&item,sizeof(item),1,file)==1)
        {
            if (strcmp(y,item.code)==0)
            {
                flag=0;
                moveToXY(70,25);
                printf("code already exists");
                moveToXY(70,27);
                printf("enter again");
                getch();
                break;
            }
        }
        if (flag==1)
            break;
    }
}

/*function to check validity of code while editing and deleting*/
int check_value(char x[NS])
{
    FILE *file;
    int flag=1;
    file=fopen("record.txt","rb");
    rewind(file);
    while (fread(&item,sizeof (item),1,file))
    {
        if(strcmp(item.code,x)==0)
        {
            flag=0;
            break;
        }
    }
    fclose(file);
    return flag;
}



/*function for editing*/
void edit_items()
{
    int flag=0,choice;
    char x[CS],y[CS];
    FILE *file;
    int size;
    system("cls");

    window(40,100,20,45);
    moveToXY(80,10);
    printf("EDIT ITEMS");

    moveToXY(75,14);
    printf("enter item code: ");
    scanf("%s",x);
    flag = check_value(x);
    if(flag==0)
    {
        file=fopen("record.txt","r+b");
        rewind(file);
        while (fread(&item,sizeof (item),1,file))
        {
            if(strcmp(item.code,x)==0)
            {
                moveToXY(75,16);
                printf("name       = %s",item.name);
                moveToXY(75,18);
                printf("code       = %s",item.code);
                moveToXY(75,20);
                printf("rate       = %g",item.rate);
                moveToXY(75,22);
                printf("quantity   = %d",item.quantity);
                moveToXY(75,24);;
                printf("Do you want to edit this record?(y/n):");
                fflush(file);

                if(toupper(getche())=='Y')
                {
                    moveToXY(75,26);
                    printf("1- edit name ");
                    moveToXY(75,27);
                    printf("2- edit code ");
                    moveToXY(75,28);
                    printf("3- edit rate ");
                    moveToXY(75,29);
                    printf("4- edit quantity ");
                    moveToXY(75,30);  ;
                    printf(" enter your choice(1, 2, 3, 4) ");
                    scanf("%d",&choice);
                    switch(choice)
                    {
	                    case 1:
	                        system("cls");
	                        window(40,100,20,35);
	                        moveToXY(70,18);
	                        printf("EDIT RECORDS");
	                        moveToXY(75,24);
	                        printf(" enter new name: ");
	                        scanf("%s",item.name);
	                        size=sizeof(item);
	                        fseek(file,-size,SEEK_CUR);
	                        fwrite(&item,sizeof(item),1,file);
	                        break;
	                    case 2:
	                        system("cls");
	                        window(40,100,20,35);
	                        moveToXY(70,18);
	                        printf("EDIT RECORDS");
	                        moveToXY(75,24);
	                        check_code(y);
	                        strcpy(item.code,y);
	                        size=sizeof(item);
	                        fseek(file,-size,SEEK_CUR);
	                        fwrite(&item,sizeof(item),1,file);
	                        break;
	                    case 3:
	                        system("cls");
	                        window(40,100,20,35);
	                        moveToXY(70,18);
	                        printf("EDIT RECORDS");
	                        moveToXY(75,24);
	                        printf(" enter new rate: ");
	                        scanf("%f",&item.rate);
	                        size=sizeof(item);
	                        fseek(file,-size,SEEK_CUR);
	                        fwrite(&item,sizeof(item),1,file);
	                        break;
	                    case 4:
	                        system("cls");
	                        window(40,100,20,35);
	                        moveToXY(70,18);
	                        printf("EDIT RECORDS");
	                        moveToXY(75,24);
	                        printf(" enter new quantity: ");
	                        scanf("%d",&item.quantity);
	                        size=sizeof(item);
	                        fseek(file,-size,1);
	                        fwrite(&item,sizeof(item),1,file);
	                        break;
                    }
                    moveToXY(75,30);
                    printf("--- item edited---");
                    break;
                }
            }
        }
    }
    if (flag==1)
    {
        moveToXY(75,30);
        printf("Item does not exist.");
        moveToXY(75,32);
        printf("TRY ABGAIN");
    }
    getch();
    fclose(file);
    display_mainmenu();
}

/*function to display all records*/
void display_all()
{
    int i,j=1;
    FILE *file;
    dis_con();
    file=fopen("record.txt","rb");
    rewind(file);
    i=15;
    fflush(file);
    
    while(fread(&item,sizeof(item),1,file))
    {
        display_items(&item,i,j);
        i++;
        j++;
        if ((j%20)==0)
        {
            moveToXY(70,10);
            printf("Press any key to see more...........");
            getch();
            system("cls");
            dis_con();
            i=15;
            continue;
        }
    }
    getch();
    if (i==26)
    {
        moveToXY(75,25);
        printf("-- no articles found --");
    }
    getch();
    fclose(file);
    display_mainmenu();
}

/*function to display window for item display*/
void dis_con()
{
    int i;
    system("cls");
    window(40,100,20,35);
   
    moveToXY(85,10);
    printf("RECORDS") ;
//textcolor(8);
    moveToXY(68,13);
    printf ("SN   Item Name   Item Code      Rate     Quantity");
}


/*function to display in screen*/
void display_items(rec *item,int i,int j)
{
    moveToXY(65,i);//textcolor(13);
    printf("%4d",j);
    printf("%9s",item->name);
    printf("%12s",item->code);
    printf("%14.2f",item->rate);
    printf("%11d",item->quantity);
}


void display_search()
{
    char ch;
    int i;
    const char *menu[]= {"   By Code","   By Rate","   By Quantity","   Back to main menu"};
    system("cls");
    window(40,100,20,35);
    moveToXY(80,10);
    printf("SEARCH MENU");
    choices(4);
}

/*function to display by quantity*/
void display_quantity()
{
    int i,j=1;
    int a,b;
    FILE *file;
    dis_con();
    file=fopen("record.txt","rb");
    rewind(file);
    i=15;
    moveToXY(30,15);;
    printf("Enter lower range: ");
    scanf("%d",&a);
    moveToXY(30,17);
    printf("Enter upper range:");
    scanf("%d",&b);
    fflush(file);
    
    while(fread(&item,sizeof(item),1,file))
    {
        if((item.quantity>=a)&&(item.quantity<=b))
        {
            display_items(&item,i,j);
            i++;
            j++;
            if ((j%20)==0)
            {
                moveToXY(70,25);
                printf("Press any key to see more...........");
                getch();
                system("cls");
                dis_con();
                i=26;
                continue;
            }
        }
    }

    getch();
    if (i==15)
    {
        moveToXY(70,20);
        printf(" No items found.");
    }
    getch();
    display_search();
    fclose(file);
}

/*function to display by rate*/
void display_rate()
{
    int i,j=1;
    float a,b;
    FILE *file;
    dis_con();
    file=fopen("record.txt","rb");
    rewind(file);
    i=15;
    moveToXY(30,15);;
    printf("enter lower range: ");
    scanf("%f",&a);
    moveToXY(30,17);
    printf("enter upper range: ");
    scanf("%f",&b);
    fflush(file);
    
    while(fread(&item,sizeof(item),1,file))
    {
        if((item.rate>=a)&&(item.rate<=b))
        {
            display_items(&item,i,j);
            i++;
            j++;
            if ((j%20)==0)
            {
                moveToXY(75,20);
                printf("press any key to see more...........");
                getch();
                system("cls");
                dis_con();
                i=26;
                continue;
            }
        }
    }
    
    getch();
    if (i==15)
    {
        moveToXY(75,20);
        printf(" no item found ");
    }
    getch();
    fclose(file);
    display_search();
}

/*function to display by code*/
void display_code()
{
    int i,j=1;
    char x[4]= {0};
    FILE *file;
    dis_con();
    file=fopen("record.txt","rb");
    rewind(file);
    i=15;
    moveToXY(30,15);;
    printf("enter item code: ");
    scanf("%s",x);
    fflush(file);
    while(fread(&item,sizeof(item),1,file))
    {
        if((strcmp(item.code,x)==0))
        {
            display_items(&item,i,j);
            i++;
            j++;
            break;
        }
    }
    if (i==15)
    {
        moveToXY(75,15);
        printf("no item found");
    }
    getch();
    fclose(file);
    display_search();
}


/*function to delete records*/
void del_items()
{
    int flag;
    char x[NS];
    FILE *file,*file1;
    system("cls");

    window(40,100,20,35);
    moveToXY(80,10);
    printf("DELETE ITEMS");
    moveToXY(75,15);
    printf("enter item code: ");
    scanf("%s",x);

    flag=check_value(x);
   
    if(flag==0)
    {
    	printf("inside flag 0");
        file1=fopen("record1.txt","ab");
        file=fopen("record.txt","rb");
        rewind(file);
        while (fread(&item,sizeof (item),1,file))
        {
            if(strcmp(item.code,x)!=0)
                fwrite(&item,sizeof(item),1,file1);
        }
        moveToXY(75,17);
        printf("---item deleted---");
        fclose(file);
        fclose(file1);
        int del = remove("record.txt");
        rename("record1.txt","record.txt");
    }
   
    if (flag==1)
    {
        moveToXY(75,17);
        printf("---item does not exist---");
        moveToXY(75,19);
        printf("TRY AGAIN");
        getch();
        display_mainmenu();	
    }
    fclose(file1);
    fclose(file);
    getch();
    display_mainmenu();
}