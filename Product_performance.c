#include<stdio.h>
#include<string.h>
#include  "COLORS.c"
#include "Align.h"
#include <stdlib.h>
#include <ctype.h>
#include "ProductPerformance.h"
#define LIST 1800
struct product
{
    char temp[200];
    char name[30];
    char code[20];
    char cat[30];
    char stock[20] ;
    char bprice[20];
    char sprice[20];
    char percent[20];
    char solditem[20];
    char profits [20];
};

//------------------------------------------//
struct product Productslist[LIST];

void Sorting(int count)
{
    struct product temp;
    int flag1;

    for (int i = 0; i < count - 1; i++)
    {
        flag1 = 0;
        for (int j = 0; j < count - 1 - i; j++)
        {
            if (atoi(Productslist[j].profits) < atoi(Productslist[j + 1].profits))
            {
                // Swap through adresss
                temp = Productslist[j];
                Productslist[j] = Productslist[j + 1];
                Productslist[j + 1] = temp;

                flag1 = 1;
            }
        }
        if (flag1 == 0)
            break; 
    }
}

void Filterer1(char *text)
{
    int i;
    int count=0;
    FILE *productlist=fopen("Productlist.csv","r");
    struct product a1;

    while (fgets(a1.temp,sizeof(a1.temp),productlist)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';

        char *tok;
        tok=strtok(a1.temp,",");
        if(tok!=NULL)
        {
            strcpy(a1.code,tok);
        }


        tok=strtok(NULL,",");
        if(tok!=NULL)
        {
            strcpy(a1.name,tok);
        }
        tok=strtok(NULL,",");
        if(tok!=NULL)
        {
            strcpy(a1.cat,tok);
        }
        if(strcmp(a1.cat,text)!=0)
        {

            continue;
        }


        tok=strtok(NULL,",");
        if(tok!=NULL)
        {
            strcpy(a1.stock,tok);

        }

        tok=strtok(NULL,",");
        if(tok!=NULL)
        {
            strcpy(a1.solditem,tok);

        }

     
        tok=strtok(NULL,",");
        if(tok!=NULL)
        {
            strcpy(a1.bprice,tok);
        }
        
        tok=strtok(NULL,",");
        if(tok!=NULL)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok!=NULL)
        {
            strcpy(a1.percent,tok);
        }

        tok=strtok(NULL,",");
        if(tok!=NULL)
        {
            strcpy(a1.profits,tok);
        }


        strcpy(Productslist[count].code,a1.code);
        strcpy(Productslist[count].name,a1.name);
        strcpy(Productslist[count].cat,a1.cat);
        strcpy(Productslist[count].stock,a1.stock);
        strcpy(Productslist[count].solditem,a1.solditem);
        strcpy(Productslist[count].bprice,a1.bprice);
        strcpy(Productslist[count].sprice,a1.sprice);
        strcpy(Productslist[count].percent,a1.percent);
        strcpy(Productslist[count].profits,a1.profits);

        count +=1;




    }
    
 fclose(productlist);
    Sorting(count);
    printf("+%-10s +%-25s+%-30s+%-30s+%-20s+%-20s+%-20s+%-20s+%-20s+\t\t%-20s+\n","count", "Item code", "item name", "Category", "Stock", "Sold Item","Buying price", "Selling price", "Profit Percentage", "Sales");

    
   for(i = 0; i < count; i++)
{
    printf("%-10d \t%-20s %-30s %-35s %-20s %-20s %-20s %-20s %-20s \t%20s\n",i + 1,Productslist[i].code,Productslist[i].name,Productslist[i].cat,Productslist[i].stock,Productslist[i].solditem,Productslist[i].bprice,Productslist[i].sprice,Productslist[i].percent,Productslist[i].profits
    );

    
}

    printf(BLU"\n Enter to continue\n"reset);
    getchar();


}

void Stationary_performance()
{
    Filterer1("Stationary");

}

void Kitchen_Utills_performance()
{
    Filterer1("Kitchen Utills");

}

void Beverage_performance()
{
    Filterer1("Beverage");

}

void Hygiene_performance()
{
    Filterer1("Hygiene");

}

void Washroom_Utils_performance()
{
    Filterer1("Washroom Utils");

}

void Tools_performance()
{
    Filterer1("Tools");

}


void performance_all()
{
    int i;
    int count=0;
    FILE *productlist=fopen("Productlist.csv","r");
    struct product a1;

    while (fgets(a1.temp,sizeof(a1.temp),productlist)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';

        char *tok;
        tok=strtok(a1.temp,",");
        if(tok!=NULL)
        {
            strcpy(a1.code,tok);
        }


        tok=strtok(NULL,",");
        if(tok!=NULL)
        {
            strcpy(a1.name,tok);
        }
        tok=strtok(NULL,",");
        if(tok!=NULL)
        {
            strcpy(a1.cat,tok);
        }
     
        tok=strtok(NULL,",");
        if(tok!=NULL)
        {
            strcpy(a1.stock,tok);

        }

        tok=strtok(NULL,",");
        if(tok!=NULL)
        {
            strcpy(a1.solditem,tok);

        }

     
        tok=strtok(NULL,",");
        if(tok!=NULL)
        {
            strcpy(a1.bprice,tok);
        }
        
        tok=strtok(NULL,",");
        if(tok!=NULL)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok!=NULL)
        {
            strcpy(a1.percent,tok);
        }

        tok=strtok(NULL,",");
        if(tok!=NULL)
        {
            strcpy(a1.profits,tok);
        }


        strcpy(Productslist[count].code,a1.code);
        strcpy(Productslist[count].name,a1.name);
        strcpy(Productslist[count].cat,a1.cat);
        strcpy(Productslist[count].stock,a1.stock);
        strcpy(Productslist[count].solditem,a1.solditem);
        strcpy(Productslist[count].bprice,a1.bprice);
        strcpy(Productslist[count].sprice,a1.sprice);
        strcpy(Productslist[count].percent,a1.percent);
        strcpy(Productslist[count].profits,a1.profits);

        count +=1;




    }
    
 fclose(productlist);
    Sorting(count);
    printf("+%-10s +%-25s+%-30s+%-30s+%-20s+%-20s+%-20s+%-20s+%-20s+\t\t%-20s+\n","count", "Item code", "item name", "Category", "Stock", "Sold Item","Buying price", "Selling price", "Profit Percentage", "Sales");

    
   for(i = 0; i < count; i++)
{
    printf("%-10d \t%-20s %-30s %-35s %-20s %-20s %-20s %-20s %-20s \t%20s\n",i + 1,Productslist[i].code,Productslist[i].name,Productslist[i].cat,Productslist[i].stock,Productslist[i].solditem,Productslist[i].bprice,Productslist[i].sprice,Productslist[i].percent,Productslist[i].profits
    );
}

    printf(GRN"\nEnter to Continue"reset);
    getchar();


}


void Printing_performance()
{   
    
    for(;;)
    {
        
    
    system("clear");
    printf("Location\n");
    move_c_hcenter();
    moving_to_vcenter();
    move_c_hcenter();
    printf(MAG"----What Do you want to print----\n"reset);
    move_c_hcenter2();
    printf("1.Stationary\n");
    move_c_hcenter2();
    printf("2.Kitchen Utills\n");
    move_c_hcenter2();
    printf("3.Beverage\n");
    move_c_hcenter2();
    printf("4.Hygiene\n");
    move_c_hcenter2();
    printf("5.Washroom Utils\n");
    move_c_hcenter2();
    printf("6.Tools\n");
    move_c_hcenter2();
    printf("7.Print All\n");
    move_c_hcenter2();
    printf("8.Exit\n");

    move_c_hcenter2();
    int option;
    printf(BLU"Choice:-\t"reset);
    // scanf("%d",&option);
    // getchar();
     char temp_option[40];//will store the whole invalid input so no infinity
        // scanf("%d", &option); This will put at infinity if the asdasda or characters are enter
        // getchar();
        fgets(temp_option,sizeof(temp_option),stdin);
        temp_option[strcspn(temp_option,"\n")]='\0';

        if(sscanf(temp_option,"%d",&option)!=1)//done successfully
        {
            system("clear");
            
            printf(RED"\n\n\nCharacter cant be inputed"reset);
            continue;
        }

    
    switch (option)
    {
    case 1:
        Stationary_performance();
        break;
    case 2:
        Kitchen_Utills_performance();
        break;
    case 3:
        Beverage_performance();
        break;
    case 4:
        Hygiene_performance();
        break;

    case 5:
        Washroom_Utils_performance();
        break;
    case 6:
        Tools_performance();
        break;
    
    case 7:
        performance_all();
        break;
    case 8:
        return ;
    break;

    default:

        printf(RED"\nInvalid Input\n"reset);
        break;
    }



    }
    
}
