//Need to fix
//add product 
//change of prices


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "COLORS.c"
#include "Align.h"
#include "Product_Management.h"
#include <ctype.h>
struct product
{
    char name[30];
    char code[20];
    char cat[30];
    int stock ;
    int bprice;
    int sprice;
    int percent;
    
   

};
struct productlist
{
    char temp[200];
    char name[30];
    char code[20];
    char cat[30];
    int stock ;
    int bprice;
    int sprice;
    int percent;
};
struct rproductlist
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
#define MAX_Item 1800   //300+300+300+300+300+300
struct rproductlist productlist[MAX_Item];

int count=0;
void *Putting_new_itemcode(char *itemcat,char *itemname,char *itemcode)
{
   
    char part1[20];
    char part2[4];
    char part3[10];
    
    {
    if(strcmp(itemcat,"Stationary")==0)
    {
        strcpy(part1,"STA-");
    }
     if(strcmp(itemcat,"Kitchen Utills")==0)
    {
        strcpy(part1,"KIT-");
    }
    if(strcmp(itemcat,"Beverage")==0)
    {
        strcpy(part1,"BEV-");
    }
    if(strcmp(itemcat,"Hygiene")==0)
    {
        strcpy(part1,"HYG-");
    }
    if(strcmp(itemcat,"Washroom Utils")==0)
    {
        strcpy(part1,"WAS-");
    }

    if(strcmp(itemcat,"Tools")==0)
    {
        strcpy(part1,"TLS-");
    }

    }

    //part 2
    for(int i=0;i<3;i++)
    {
        part2[i]=itemname[i];
    }
    for(int i=0;i<strlen(part2);i++)
    {
        part2[i]=toupper(part2[i]);
    }
    part2[3]='\0';

    //part 3
    int x = (rand() % 900);//taking rad to 999 
    sprintf(part3, "-%d",x);

    strcpy(itemcode, part1);
    strcat(itemcode, part2);
    strcat(itemcode, part3);
    return itemcode;


}

int Adding_A_Item()
{
    struct product ADDProduct;
    struct productlist a3;
    FILE *productlist = fopen("Productlist.csv", "a");
    FILE *productlistread = fopen("Productlist.csv", "r");
    FILE *budget = fopen("bugdet.csv", "r");
    FILE *budgettemp = fopen("budgettemp.csv", "w");

    if (!productlist || !productlistread || !budget || !budgettemp)
    {
        printf("Error opening one or more files!\n");
        if (productlist) fclose(productlist);
        if (productlistread) fclose(productlistread);
        if (budget) fclose(budget);
        if (budgettemp) fclose(budgettemp);
        return 0;
    }

    char temp[300], b1[100], b2[100], b3[100];
    int leftover;

    if (fgets(temp, sizeof(temp), budget))
    {
        char *tok = strtok(temp, ",");
        if (tok) strcpy(b1, tok);

        tok = strtok(NULL, ",");
        if (tok) strcpy(b2, tok);

        tok = strtok(NULL, ",");
        if (tok) strcpy(b3, tok);
    }
    else
    {
        printf("Budget file is empty!\n");
        fclose(productlist);
        fclose(productlistread);
        fclose(budget);
        fclose(budgettemp);
        return 0;
    }

    while (1)
    {
        system("clear");
        moving_to_vcenter();
        move_c_hcenter2();
        printf(MAGHB "Select the type of the product\n" reset);
        move_to_hcenter("1.Stationary\n");
        move_to_hcenter("2.Kitchen Utills\n");
        move_to_hcenter("3.Beverage\n");
        move_to_hcenter("4.Hygiene\n");
        move_to_hcenter("5.Washroom Utils\n");
        move_to_hcenter("6.Tools\n");
        move_to_hcenter("7.Return\n");
        printf(BLU "%50s" reset, "Choice:-\t");

        int option = 0;
        char input[20];
        while (1)
        {
            fgets(input, sizeof(input), stdin);
            if (sscanf(input, "%d", &option) != 1 || option < 1 || option > 7)
            {
                printf(RED "Invalid choice, try again.\n" reset);
            }
            else
            {
                break;
            }
        }

        if (option == 7)
            break;

        switch (option)
        {
        case 1: strcpy(ADDProduct.cat, "Stationary"); break;
        case 2: strcpy(ADDProduct.cat, "Kitchen Utills"); break;
        case 3: strcpy(ADDProduct.cat, "Beverage"); break;
        case 4: strcpy(ADDProduct.cat, "Hygiene"); break;
        case 5: strcpy(ADDProduct.cat, "Washroom Utils"); break;
        case 6: strcpy(ADDProduct.cat, "Tools"); break;
        }

        system("clear");
        moving_to_vcenter();

        while (1)
        {
            int exists = 0;
            rewind(productlistread);
            move_c_hcenter2();
            printf(BLU "Enter Product Name:-\t" reset);
            fgets(ADDProduct.name, sizeof(ADDProduct.name), stdin);
            ADDProduct.name[strcspn(ADDProduct.name, "\n")] = '\0';

            if (strlen(ADDProduct.name) < 2 || strlen(ADDProduct.name) >= 30)
            {
                printf(RED "Invalid Name\n" reset);
                continue;
            }

            while (fgets(a3.temp, sizeof(a3.temp), productlistread))
            {
                char *tok = strtok(a3.temp, ",");
                if (tok) strcpy(a3.code, tok);
                tok = strtok(NULL, ",");
                if (tok) strcpy(a3.name, tok);

                if (strcasecmp(a3.name, ADDProduct.name) == 0)
                {
                    exists = 1;
                    break;
                }
            }

            if (exists)
            {
                move_c_hcenter2();
                printf(RED "\nThe product already exists\n" reset);
                continue;
            }
            break;
        }

        while (1)
        {
            move_c_hcenter2();
            printf(BLU "Enter Product Original price:-\t" reset);
            fgets(input, sizeof(input), stdin);
            if (sscanf(input, "%d", &ADDProduct.bprice) != 1 || ADDProduct.bprice <= 0)
            {
                printf(RED "Invalid price\n" reset);
                continue;
            }
            break;
        }

        while (1)
        {
            move_c_hcenter2();
            printf(BLU "Enter Product Selling price:-\t" reset);
            fgets(input, sizeof(input), stdin);
            if (sscanf(input, "%d", &ADDProduct.sprice) != 1 || ADDProduct.sprice <= ADDProduct.bprice)
            {
                printf(RED "Selling price must be higher than original price\n" reset);
                continue;
            }
            break;
        }

        while (1)
        {
            move_c_hcenter2();
            printf(BLU "Enter Product Stock:-\t" reset);
            fgets(input, sizeof(input), stdin);
            if (sscanf(input, "%d", &ADDProduct.stock) != 1 || ADDProduct.stock <= 0 || ADDProduct.stock > 2000)
            {
                printf(RED "Invalid stock\n" reset);
                continue;
            }

            if ((long long)ADDProduct.stock * ADDProduct.bprice > atoi(b1) - 10000)
            {
                printf(RED "Not enough budget\n" reset);
                continue;
            }
            break;
        }

        ADDProduct.percent = ((ADDProduct.sprice - ADDProduct.bprice) * 100) / ADDProduct.bprice;

        strcpy(ADDProduct.code, Putting_new_itemcode(ADDProduct.cat, ADDProduct.name, ADDProduct.code));

        system("clear");
        moving_to_vcenter();
        move_c_hcenter2();
        printf("|%-15s %-20s %-15s %-10s %-10s %-10s %-10s\n", "Code", "Name", "Category", "Buy", "Sell", "Stock", "%%age");
        move_c_hcenter2();
        printf("|%-15s %-20s %-15s %-10d %-10d %-10d %-10d\n\n", ADDProduct.code, ADDProduct.name, ADDProduct.cat, ADDProduct.bprice, ADDProduct.sprice, ADDProduct.stock, ADDProduct.percent);

        char option2[10];
        while (1)
        {
            move_c_hcenter();
            printf("yes:-Confirm it\n");
            move_c_hcenter();
            printf("no:-Retry\n");
            move_c_hcenter();
            printf(BLU "Option:-\t" reset);
            fgets(option2, sizeof(option2), stdin);
            option2[strcspn(option2, "\n")] = '\0';

            if (strcasecmp(option2, "yes") == 0 || strcasecmp(option2, "y") == 0)
            {
                leftover = atoi(b1) - (ADDProduct.stock * ADDProduct.bprice);
                fprintf(budgettemp, "%d,%s,%s", leftover, b2, b3);
                fprintf(productlist, "%s,%s,%s,%d,0,%d,%d,%d,0\n",ADDProduct.code, ADDProduct.name, ADDProduct.cat,ADDProduct.stock, ADDProduct.bprice, ADDProduct.sprice, ADDProduct.percent);

                fclose(productlist);
                fclose(productlistread);
                fclose(budget);
                fclose(budgettemp);

                remove("bugdet.csv");
                rename("budgettemp.csv", "bugdet.csv");

                return 0;
            }
            else if (strcasecmp(option2, "no") == 0 || strcasecmp(option2, "n") == 0)
            {
                break;
            }
            else
            {
                move_c_hcenter();
                printf(RED "Invalid option! Please type yes/y or no/n\n" reset);
            }
        }
    }

    return 0;
}

void Print_Satationary()
{
    count=0;
    struct rproductlist a1;
    FILE *Stationary=fopen("Productlist.csv","r");
    if(Stationary==NULL)
    {
        printf("\nProductlist Not Found\n");
        return ;
    }


    while(fgets(a1.temp,sizeof(a1.temp),Stationary)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';
        char *tok;
        tok=strtok(a1.temp,",");
        if(tok)
        {
            strcpy(a1.code,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.name,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.cat,tok);
        }
        if(strcmp(a1.cat,"Stationary")!=0)
        {
            continue;
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.stock,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.solditem,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.bprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.percent,tok);
        }


        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.profits,tok);
        }


        strcpy(productlist[count].code,a1.code);
        strcpy(productlist[count].name,a1.name);
        strcpy(productlist[count].cat,a1.cat);
        strcpy(productlist[count].stock,a1.stock);
        strcpy(productlist[count].solditem,a1.solditem);
        strcpy(productlist[count].bprice,a1.bprice);
        strcpy(productlist[count].sprice,a1.sprice);
        strcpy(productlist[count].percent,a1.percent);
        strcpy(productlist[count].profits,a1.profits);
        count +=1;
    }

    moving_to_vcenter();

    printf("+%-10s +%-25s+%-30s+%-30s+%-20s+%-20s+%-20s+%-20s+%-20s+\t\t%-20s+\n","count", "Item code", "item name", "Category", "Stock", "Sold Item","Buying price", "Selling price", "Profit Percentage", "Sales");



    for(int i=0;i<count;i++)
    {
        
      
        printf("%-10d \t%-20s %-30s %-35s %-20s %-20s %-20s %-20s %-20s \t%20s\n",i+1,productlist[i].code,productlist[i].name,productlist[i].cat,productlist[i].stock,productlist[i].solditem,productlist[i].bprice,productlist[i].sprice,productlist[i].percent,productlist[i].profits);
    
    
    }

    printf(BLU"\n\nPress Enter to continue"reset);
        getchar();
    fclose(Stationary);
    return;

}


void Print_Satationary1()
{
    count=0;
    struct rproductlist a1;
    FILE *Stationary=fopen("Productlist.csv","r");
    if(Stationary==NULL)
    {
        printf("\nProductlist Not Found\n");
        return ;
    }


    while(fgets(a1.temp,sizeof(a1.temp),Stationary)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';
        char *tok;
        tok=strtok(a1.temp,",");
        if(tok)
        {
            strcpy(a1.code,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.name,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.cat,tok);
        }
        if(strcmp(a1.cat,"Stationary")!=0)
        {
            continue;
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.stock,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.solditem,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.bprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.percent,tok);
        }


        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.profits,tok);
        }


        strcpy(productlist[count].code,a1.code);
        strcpy(productlist[count].name,a1.name);
        strcpy(productlist[count].cat,a1.cat);
        strcpy(productlist[count].stock,a1.stock);
        strcpy(productlist[count].solditem,a1.solditem);
        strcpy(productlist[count].bprice,a1.bprice);
        strcpy(productlist[count].sprice,a1.sprice);
        strcpy(productlist[count].percent,a1.percent);
        strcpy(productlist[count].profits,a1.profits);
        count +=1;
    }

      moving_to_vcenter();

    printf("+%-10s +%-25s+%-30s+%-30s+%-20s+%-20s+%-20s+%-20s+%-20s+\t\t%-20s+\n","count", "Item code", "item name", "Category", "Stock", "Sold Item","Buying price", "Selling price", "Profit Percentage", "Sales");



    for(int i=0;i<count;i++)
    {
        
        printf("%-10d \t%-20s %-30s %-35s %-20s %-20s %-20s %-20s %-20s \t%20s\n",i+1,productlist[i].code,productlist[i].name,productlist[i].cat,productlist[i].stock,productlist[i].solditem,productlist[i].bprice,productlist[i].sprice,productlist[i].percent,productlist[i].profits);
    }

    fclose(Stationary);
    return;

}


void Print_Satationaryr()
{
    count=0;
    struct rproductlist a1;
    FILE *Stationary=fopen("Productlist.csv","r");
    if(Stationary==NULL)
    {
        printf("\nProductlist Not Found\n");
        return ;
    }


    while(fgets(a1.temp,sizeof(a1.temp),Stationary)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';
        char *tok;
        tok=strtok(a1.temp,",");
        if(tok)
        {
            strcpy(a1.code,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.name,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.cat,tok);
        }
        if(strcmp(a1.cat,"Stationary")!=0)
        {
            continue;
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.stock,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.solditem,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.bprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.percent,tok);
        }


        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.profits,tok);
        }


        strcpy(productlist[count].code,a1.code);
        strcpy(productlist[count].name,a1.name);
        strcpy(productlist[count].cat,a1.cat);
        strcpy(productlist[count].stock,a1.stock);
        strcpy(productlist[count].solditem,a1.solditem);
        strcpy(productlist[count].bprice,a1.bprice);
        strcpy(productlist[count].sprice,a1.sprice);
        strcpy(productlist[count].percent,a1.percent);
        strcpy(productlist[count].profits,a1.profits);
        count +=1;
    }

    fclose(Stationary);
    return;

}




void Print_Kitchen_Utills()
{
    count=0;
    struct rproductlist a1;
    FILE *Stationary=fopen("Productlist.csv","r");
    if(Stationary==NULL)
    {
        printf("\nProductlist Not Found\n");
        return ;
    }


    while(fgets(a1.temp,sizeof(a1.temp),Stationary)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';
        char *tok;
        tok=strtok(a1.temp,",");
        if(tok)
        {
            strcpy(a1.code,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.name,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.cat,tok);
        }
        if(strcmp(a1.cat,"Kitchen Utills")!=0)
        {
            continue;
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.stock,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.solditem,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.bprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.percent,tok);
        }


        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.profits,tok);
        }


        strcpy(productlist[count].code,a1.code);
        strcpy(productlist[count].name,a1.name);
        strcpy(productlist[count].cat,a1.cat);
        strcpy(productlist[count].stock,a1.stock);
        strcpy(productlist[count].solditem,a1.solditem);
        strcpy(productlist[count].bprice,a1.bprice);
        strcpy(productlist[count].sprice,a1.sprice);
        strcpy(productlist[count].percent,a1.percent);
        strcpy(productlist[count].profits,a1.profits);
        count +=1;
    }

    moving_to_vcenter();

    printf("+%-10s +%-25s+%-30s+%-30s+%-20s+%-20s+%-20s+%-20s+%-20s+\t\t%20s+\n","count", "Item code", "item name", "Category", "Stock", "Sold Item","Buying price", "Selling price", "Profit Percentage", "Sales");



    for(int i=0;i<count;i++)
    {
        
        printf("%-10d \t%-20s %-30s %-35s %-20s %-20s %-20s %-20s %-20s \t%20s\n",i+1,productlist[i].code,productlist[i].name,productlist[i].cat,productlist[i].stock,productlist[i].solditem,productlist[i].bprice,productlist[i].sprice,productlist[i].percent,productlist[i].profits);
    }

    printf(BLU"\n\nPress Enter to continue"reset);
        getchar();
    fclose(Stationary);
    return;

}


void Print_Kitchen_Utills1()
{
    count=0;
    struct rproductlist a1;
    FILE *Stationary=fopen("Productlist.csv","r");
    if(Stationary==NULL)
    {
        printf("\nProductlist Not Found\n");
        return ;
    }


    while(fgets(a1.temp,sizeof(a1.temp),Stationary)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';
        char *tok;
        tok=strtok(a1.temp,",");
        if(tok)
        {
            strcpy(a1.code,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.name,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.cat,tok);
        }
        if(strcmp(a1.cat,"Kitchen Utills")!=0)
        {
            continue;
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.stock,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.solditem,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.bprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.percent,tok);
        }


        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.profits,tok);
        }


        strcpy(productlist[count].code,a1.code);
        strcpy(productlist[count].name,a1.name);
        strcpy(productlist[count].cat,a1.cat);
        strcpy(productlist[count].stock,a1.stock);
        strcpy(productlist[count].solditem,a1.solditem);
        strcpy(productlist[count].bprice,a1.bprice);
        strcpy(productlist[count].sprice,a1.sprice);
        strcpy(productlist[count].percent,a1.percent);
        strcpy(productlist[count].profits,a1.profits);
        count +=1;
    }

      moving_to_vcenter();

    printf("+%-10s +%-25s+%-30s+%-30s+%-20s+%-20s+%-20s+%-20s+%-20s+\t\t%-20s+\n","count", "Item code", "item name", "Category", "Stock", "Sold Item","Buying price", "Selling price", "Profit Percentage", "Sales");



    for(int i=0;i<count;i++)
    {
        
        printf("%-10d \t%-20s %-30s %-35s %-20s %-20s %-20s %-20s %-20s \t%20s\n",i+1,productlist[i].code,productlist[i].name,productlist[i].cat,productlist[i].stock,productlist[i].solditem,productlist[i].bprice,productlist[i].sprice,productlist[i].percent,productlist[i].profits);
    }
    fclose(Stationary);
    return;

}


void Print_Kitchen_Utillsr()
{
    count=0;
    struct rproductlist a1;
    FILE *Stationary=fopen("Productlist.csv","r");
    if(Stationary==NULL)
    {
        printf("\nProductlist Not Found\n");
        return ;
    }


    while(fgets(a1.temp,sizeof(a1.temp),Stationary)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';
        char *tok;
        tok=strtok(a1.temp,",");
        if(tok)
        {
            strcpy(a1.code,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.name,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.cat,tok);
        }
        if(strcmp(a1.cat,"Kitchen Utills")!=0)
        {
            continue;
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.stock,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.solditem,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.bprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.percent,tok);
        }


        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.profits,tok);
        }


        strcpy(productlist[count].code,a1.code);
        strcpy(productlist[count].name,a1.name);
        strcpy(productlist[count].cat,a1.cat);
        strcpy(productlist[count].stock,a1.stock);
        strcpy(productlist[count].solditem,a1.solditem);
        strcpy(productlist[count].bprice,a1.bprice);
        strcpy(productlist[count].sprice,a1.sprice);
        strcpy(productlist[count].percent,a1.percent);
        strcpy(productlist[count].profits,a1.profits);
        count +=1;
    }

   
    fclose(Stationary);
    return;

}




void Print_Beverage()
{
    
    count=0;
    struct rproductlist a1;
    FILE *Stationary=fopen("Productlist.csv","r");
    if(Stationary==NULL)
    {
        printf("\nProductlist Not Found\n");
        return ;
    }


    while(fgets(a1.temp,sizeof(a1.temp),Stationary)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';
        char *tok;
        tok=strtok(a1.temp,",");
        if(tok)
        {
            strcpy(a1.code,tok);
        }
        
        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.name,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.cat,tok);
        }
        if(strcmp(a1.cat,"Beverage")!=0)
        {
            continue;
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.stock,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.solditem,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.bprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.percent,tok);
        }


        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.profits,tok);
        }


        strcpy(productlist[count].code,a1.code);
        strcpy(productlist[count].name,a1.name);
        strcpy(productlist[count].cat,a1.cat);
        strcpy(productlist[count].stock,a1.stock);
        strcpy(productlist[count].solditem,a1.solditem);
        strcpy(productlist[count].bprice,a1.bprice);
        strcpy(productlist[count].sprice,a1.sprice);
        strcpy(productlist[count].percent,a1.percent);
        strcpy(productlist[count].profits,a1.profits);
        count +=1;
    }

    moving_to_vcenter();

    printf("+%-10s +%-25s+%-30s+%-30s+%-20s+%-20s+%-20s+%-20s+%-20s+\t\t%20s+\n","count", "Item code", "item name", "Category", "Stock", "Sold Item","Buying price", "Selling price", "Profit Percentage", "Sales");



    for(int i=0;i<count;i++)
    {
        
        printf("%-10d \t%-20s %-30s %-35s %-20s %-20s %-20s %-20s %-20s \t%20s\n",i+1,productlist[i].code,productlist[i].name,productlist[i].cat,productlist[i].stock,productlist[i].solditem,productlist[i].bprice,productlist[i].sprice,productlist[i].percent,productlist[i].profits);
    }

    printf(BLU"\n\nPress Enter to continue"reset);
    getchar();
    fclose(Stationary);
    return;

}


void Print_Beverage1()
{
    count=0;
    struct rproductlist a1;
    FILE *Stationary=fopen("Productlist.csv","r");
    if(Stationary==NULL)
    {
        printf("\nProductlist Not Found\n");
        return ;
    }


    while(fgets(a1.temp,sizeof(a1.temp),Stationary)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';
        char *tok;
        tok=strtok(a1.temp,",");
        if(tok)
        {
            strcpy(a1.code,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.name,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.cat,tok);
        }
        if(strcmp(a1.cat,"Beverage")!=0)
        {
            continue;
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.stock,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.solditem,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.bprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.percent,tok);
        }


        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.profits,tok);
        }


        strcpy(productlist[count].code,a1.code);
        strcpy(productlist[count].name,a1.name);
        strcpy(productlist[count].cat,a1.cat);
        strcpy(productlist[count].stock,a1.stock);
        strcpy(productlist[count].solditem,a1.solditem);
        strcpy(productlist[count].bprice,a1.bprice);
        strcpy(productlist[count].sprice,a1.sprice);
        strcpy(productlist[count].percent,a1.percent);
        strcpy(productlist[count].profits,a1.profits);
        count +=1;
    }

      moving_to_vcenter();

    printf("+%-10s +%-25s+%-30s+%-30s+%-20s+%-20s+%-20s+%-20s+%-20s+\t\t%-20s+\n","count", "Item code", "item name", "Category", "Stock", "Sold Item","Buying price", "Selling price", "Profit Percentage", "Sales");



    for(int i=0;i<count;i++)
    {
        
        printf("%-10d \t%-20s %-30s %-35s %-20s %-20s %-20s %-20s %-20s \t%20s\n",i+1,productlist[i].code,productlist[i].name,productlist[i].cat,productlist[i].stock,productlist[i].solditem,productlist[i].bprice,productlist[i].sprice,productlist[i].percent,productlist[i].profits);
    }

    fclose(Stationary);
    return;

}



void Print_Beverager()
{
    count=0;
    struct rproductlist a1;
    FILE *Stationary=fopen("Productlist.csv","r");
    if(Stationary==NULL)
    {
        printf("\nProductlist Not Found\n");
        return ;
    }


    while(fgets(a1.temp,sizeof(a1.temp),Stationary)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';
        char *tok;
        tok=strtok(a1.temp,",");
        if(tok)
        {
            strcpy(a1.code,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.name,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.cat,tok);
        }
        if(strcmp(a1.cat,"Beverage")!=0)
        {
            continue;
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.stock,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.solditem,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.bprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.percent,tok);
        }


        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.profits,tok);
        }


        strcpy(productlist[count].code,a1.code);
        strcpy(productlist[count].name,a1.name);
        strcpy(productlist[count].cat,a1.cat);
        strcpy(productlist[count].stock,a1.stock);
        strcpy(productlist[count].solditem,a1.solditem);
        strcpy(productlist[count].bprice,a1.bprice);
        strcpy(productlist[count].sprice,a1.sprice);
        strcpy(productlist[count].percent,a1.percent);
        strcpy(productlist[count].profits,a1.profits);
        count +=1;
    }

     
    fclose(Stationary);
    return;

}



void Print_Hygiene()
{
    count=0;
    struct rproductlist a1;
    FILE *Stationary=fopen("Productlist.csv","r");
    if(Stationary==NULL)
    {
        printf("\nProductlist Not Found\n");
        return ;
    }


    while(fgets(a1.temp,sizeof(a1.temp),Stationary)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';
        char *tok;
        tok=strtok(a1.temp,",");
        if(tok)
        {
            strcpy(a1.code,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.name,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.cat,tok);
        }
        if(strcmp(a1.cat,"Hygiene")!=0)
        {
            continue;
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.stock,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.solditem,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.bprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.percent,tok);
        }


        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.profits,tok);
        }


        strcpy(productlist[count].code,a1.code);
        strcpy(productlist[count].name,a1.name);
        strcpy(productlist[count].cat,a1.cat);
        strcpy(productlist[count].stock,a1.stock);
        strcpy(productlist[count].solditem,a1.solditem);
        strcpy(productlist[count].bprice,a1.bprice);
        strcpy(productlist[count].sprice,a1.sprice);
        strcpy(productlist[count].percent,a1.percent);
        strcpy(productlist[count].profits,a1.profits);
        count +=1;
    }

    moving_to_vcenter();

    printf("+%-10s +%-25s+%-30s+%-30s+%-20s+%-20s+%-20s+%-20s+%-20s+\t\t%20s+\n","count", "Item code", "item name", "Category", "Stock", "Sold Item","Buying price", "Selling price", "Profit Percentage", "Sales");



    for(int i=0;i<count;i++)
    {
        
        printf("%-10d \t%-20s %-30s %-35s %-20s %-20s %-20s %-20s %-20s \t%20s\n",i+1,productlist[i].code,productlist[i].name,productlist[i].cat,productlist[i].stock,productlist[i].solditem,productlist[i].bprice,productlist[i].sprice,productlist[i].percent,productlist[i].profits);
    }

    printf(BLU"\n\nPress Enter to continue"reset);
        getchar();
    fclose(Stationary);
    return;

}


void Print_Hygiene1()
{
    count=0;
    struct rproductlist a1;
    FILE *Stationary=fopen("Productlist.csv","r");
    if(Stationary==NULL)
    {
        printf("\nProductlist Not Found\n");
        return ;
    }


    while(fgets(a1.temp,sizeof(a1.temp),Stationary)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';
        char *tok;
        tok=strtok(a1.temp,",");
        if(tok)
        {
            strcpy(a1.code,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.name,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.cat,tok);
        }
        if(strcmp(a1.cat,"Hygiene")!=0)
        {
            continue;
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.stock,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.solditem,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.bprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.percent,tok);
        }


        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.profits,tok);
        }


        strcpy(productlist[count].code,a1.code);
        strcpy(productlist[count].name,a1.name);
        strcpy(productlist[count].cat,a1.cat);
        strcpy(productlist[count].stock,a1.stock);
        strcpy(productlist[count].solditem,a1.solditem);
        strcpy(productlist[count].bprice,a1.bprice);
        strcpy(productlist[count].sprice,a1.sprice);
        strcpy(productlist[count].percent,a1.percent);
        strcpy(productlist[count].profits,a1.profits);
        count +=1;
    }

      moving_to_vcenter();

    printf("+%-10s +%-25s+%-30s+%-30s+%-20s+%-20s+%-20s+%-20s+%-20s+\t\t%-20s+\n","count", "Item code", "item name", "Category", "Stock", "Sold Item","Buying price", "Selling price", "Profit Percentage", "Sales");



    for(int i=0;i<count;i++)
    {
        
        printf("%-10d \t%-20s %-30s %-35s %-20s %-20s %-20s %-20s %-20s \t%20s\n",i+1,productlist[i].code,productlist[i].name,productlist[i].cat,productlist[i].stock,productlist[i].solditem,productlist[i].bprice,productlist[i].sprice,productlist[i].percent,productlist[i].profits);
    }
    fclose(Stationary);
    return;

}


void Print_Hygiener()
{
    count=0;
    struct rproductlist a1;
    FILE *Stationary=fopen("Productlist.csv","r");
    if(Stationary==NULL)
    {
        printf("\nProductlist Not Found\n");
        return ;
    }


    while(fgets(a1.temp,sizeof(a1.temp),Stationary)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';
        char *tok;
        tok=strtok(a1.temp,",");
        if(tok)
        {
            strcpy(a1.code,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.name,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.cat,tok);
        }
        if(strcmp(a1.cat,"Hygiene")!=0)
        {
            continue;
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.stock,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.solditem,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.bprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.percent,tok);
        }


        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.profits,tok);
        }


        strcpy(productlist[count].code,a1.code);
        strcpy(productlist[count].name,a1.name);
        strcpy(productlist[count].cat,a1.cat);
        strcpy(productlist[count].stock,a1.stock);
        strcpy(productlist[count].solditem,a1.solditem);
        strcpy(productlist[count].bprice,a1.bprice);
        strcpy(productlist[count].sprice,a1.sprice);
        strcpy(productlist[count].percent,a1.percent);
        strcpy(productlist[count].profits,a1.profits);
        count +=1;
    }

     
    fclose(Stationary);
    return;

}




void Print_Washroom_Utils()
{
    count=0;
    struct rproductlist a1;
    FILE *Stationary=fopen("Productlist.csv","r");
    if(Stationary==NULL)
    {
        printf("\nProductlist Not Found\n");
        return ;
    }


    while(fgets(a1.temp,sizeof(a1.temp),Stationary)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';
        char *tok;
        tok=strtok(a1.temp,",");
        if(tok)
        {
            strcpy(a1.code,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.name,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.cat,tok);
        }
        if(strcmp(a1.cat,"Washroom Utils")!=0)
        {
            continue;
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.stock,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.solditem,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.bprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.percent,tok);
        }


        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.profits,tok);
        }


        strcpy(productlist[count].code,a1.code);
        strcpy(productlist[count].name,a1.name);
        strcpy(productlist[count].cat,a1.cat);
        strcpy(productlist[count].stock,a1.stock);
        strcpy(productlist[count].solditem,a1.solditem);
        strcpy(productlist[count].bprice,a1.bprice);
        strcpy(productlist[count].sprice,a1.sprice);
        strcpy(productlist[count].percent,a1.percent);
        strcpy(productlist[count].profits,a1.profits);
        count +=1;
    }

    moving_to_vcenter();

    printf("+%-10s +%-25s+%-30s+%-30s+%-20s+%-20s+%-20s+%-20s+%-20s+\t\t%20s+\n","count", "Item code", "item name", "Category", "Stock", "Sold Item","Buying price", "Selling price", "Profit Percentage", "Sales");



    for(int i=0;i<count;i++)
    {
        
        printf("%-10d \t%-20s %-30s %-35s %-20s %-20s %-20s %-20s %-20s \t%20s\n",i+1,productlist[i].code,productlist[i].name,productlist[i].cat,productlist[i].stock,productlist[i].solditem,productlist[i].bprice,productlist[i].sprice,productlist[i].percent,productlist[i].profits);
    }

    printf(BLU"\n\nPress Enter to continue"reset);
    getchar();
    fclose(Stationary);
    return;

}


void Print_Washroom_Utilsr()
{
    count=0;
    struct rproductlist a1;
    FILE *Stationary=fopen("Productlist.csv","r");
    if(Stationary==NULL)
    {
        printf("\nProductlist Not Found\n");
        return ;
    }


    while(fgets(a1.temp,sizeof(a1.temp),Stationary)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';
        char *tok;
        tok=strtok(a1.temp,",");
        if(tok)
        {
            strcpy(a1.code,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.name,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.cat,tok);
        }
        if(strcmp(a1.cat,"Washroom Utils")!=0)
        {
            continue;
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.stock,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.solditem,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.bprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.percent,tok);
        }


        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.profits,tok);
        }


        strcpy(productlist[count].code,a1.code);
        strcpy(productlist[count].name,a1.name);
        strcpy(productlist[count].cat,a1.cat);
        strcpy(productlist[count].stock,a1.stock);
        strcpy(productlist[count].solditem,a1.solditem);
        strcpy(productlist[count].bprice,a1.bprice);
        strcpy(productlist[count].sprice,a1.sprice);
        strcpy(productlist[count].percent,a1.percent);
        strcpy(productlist[count].profits,a1.profits);
        count +=1;
    }

    
    fclose(Stationary);
    return;

}




void Print_Washroom_Utils1()
{
    count=0;
    struct rproductlist a1;
    FILE *Stationary=fopen("Productlist.csv","r");
    if(Stationary==NULL)
    {
        printf("\nProductlist Not Found\n");
        return ;
    }


    while(fgets(a1.temp,sizeof(a1.temp),Stationary)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';
        char *tok;
        tok=strtok(a1.temp,",");
        if(tok)
        {
            strcpy(a1.code,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.name,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.cat,tok);
        }
        if(strcmp(a1.cat,"Washroom Utils")!=0)
        {
            continue;
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.stock,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.solditem,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.bprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.percent,tok);
        }


        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.profits,tok);
        }


        strcpy(productlist[count].code,a1.code);
        strcpy(productlist[count].name,a1.name);
        strcpy(productlist[count].cat,a1.cat);
        strcpy(productlist[count].stock,a1.stock);
        strcpy(productlist[count].solditem,a1.solditem);
        strcpy(productlist[count].bprice,a1.bprice);
        strcpy(productlist[count].sprice,a1.sprice);
        strcpy(productlist[count].percent,a1.percent);
        strcpy(productlist[count].profits,a1.profits);
        count +=1;
    }

      moving_to_vcenter();

    printf("+%-10s +%-25s+%-30s+%-30s+%-20s+%-20s+%-20s+%-20s+%-20s+\t\t%-20s+\n","count", "Item code", "item name", "Category", "Stock", "Sold Item","Buying price", "Selling price", "Profit Percentage", "Sales");



    for(int i=0;i<count;i++)
    {
        
        printf("%-10d \t%-20s %-30s %-35s %-20s %-20s %-20s %-20s %-20s \t%20s\n",i+1,productlist[i].code,productlist[i].name,productlist[i].cat,productlist[i].stock,productlist[i].solditem,productlist[i].bprice,productlist[i].sprice,productlist[i].percent,productlist[i].profits);
    }

    fclose(Stationary);
    return;

}






void Print_Tools()
{
    count=0;
    struct rproductlist a1;
    FILE *Stationary=fopen("Productlist.csv","r");
    if(Stationary==NULL)
    {
        printf("\nProductlist Not Found\n");
        return ;
    }


    while(fgets(a1.temp,sizeof(a1.temp),Stationary)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';
        char *tok;
        tok=strtok(a1.temp,",");
        if(tok)
        {
            strcpy(a1.code,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.name,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.cat,tok);
        }
        if(strcmp(a1.cat,"Tools")!=0)
        {
            continue;
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.stock,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.solditem,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.bprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.percent,tok);
        }


        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.profits,tok);
        }


        strcpy(productlist[count].code,a1.code);
        strcpy(productlist[count].name,a1.name);
        strcpy(productlist[count].cat,a1.cat);
        strcpy(productlist[count].stock,a1.stock);
        strcpy(productlist[count].solditem,a1.solditem);
        strcpy(productlist[count].bprice,a1.bprice);
        strcpy(productlist[count].sprice,a1.sprice);
        strcpy(productlist[count].percent,a1.percent);
        strcpy(productlist[count].profits,a1.profits);
        count +=1;
    }

    moving_to_vcenter();

    printf("+%-10s +%-25s+%-30s+%-30s+%-20s+%-20s+%-20s+%-20s+%-20s+\t\t%20s+\n","count", "Item code", "item name", "Category", "Stock", "Sold Item","Buying price", "Selling price", "Profit Percentage", "Sales");



    for(int i=0;i<count;i++)
    {
        
        printf("%-10d \t%-20s %-30s %-35s %-20s %-20s %-20s %-20s %-20s \t%20s\n",i+1,productlist[i].code,productlist[i].name,productlist[i].cat,productlist[i].stock,productlist[i].solditem,productlist[i].bprice,productlist[i].sprice,productlist[i].percent,productlist[i].profits);
    }

    printf(BLU"\n\nPress Enter to continue"reset);
    getchar();
    fclose(Stationary);
    return;

}




void Print_Toolsr()
{
    count=0;
    struct rproductlist a1;
    FILE *Stationary=fopen("Productlist.csv","r");
    if(Stationary==NULL)
    {
        printf("\nProductlist Not Found\n");
        return ;
    }


    while(fgets(a1.temp,sizeof(a1.temp),Stationary)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';
        char *tok;
        tok=strtok(a1.temp,",");
        if(tok)
        {
            strcpy(a1.code,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.name,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.cat,tok);
        }
        if(strcmp(a1.cat,"Tools")!=0)
        {
            continue;
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.stock,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.solditem,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.bprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.percent,tok);
        }


        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.profits,tok);
        }


        strcpy(productlist[count].code,a1.code);
        strcpy(productlist[count].name,a1.name);
        strcpy(productlist[count].cat,a1.cat);
        strcpy(productlist[count].stock,a1.stock);
        strcpy(productlist[count].solditem,a1.solditem);
        strcpy(productlist[count].bprice,a1.bprice);
        strcpy(productlist[count].sprice,a1.sprice);
        strcpy(productlist[count].percent,a1.percent);
        strcpy(productlist[count].profits,a1.profits);
        count +=1;
    }


    fclose(Stationary);
    return;

}




void Print_Tools1()
{
    count=0;
    struct rproductlist a1;
    FILE *Stationary=fopen("Productlist.csv","r");
    if(Stationary==NULL)
    {
        printf("\nProductlist Not Found\n");
        return ;
    }


    while(fgets(a1.temp,sizeof(a1.temp),Stationary)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';
        char *tok;
        tok=strtok(a1.temp,",");
        if(tok)
        {
            strcpy(a1.code,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.name,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.cat,tok);
        }
        if(strcmp(a1.cat,"Tools")!=0)
        {
            continue;
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.stock,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.solditem,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.bprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.percent,tok);
        }


        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.profits,tok);
        }


        strcpy(productlist[count].code,a1.code);
        strcpy(productlist[count].name,a1.name);
        strcpy(productlist[count].cat,a1.cat);
        strcpy(productlist[count].stock,a1.stock);
        strcpy(productlist[count].solditem,a1.solditem);
        strcpy(productlist[count].bprice,a1.bprice);
        strcpy(productlist[count].sprice,a1.sprice);
        strcpy(productlist[count].percent,a1.percent);
        strcpy(productlist[count].profits,a1.profits);
        count +=1;
    }
      moving_to_vcenter();

    printf("+%-10s +%-25s+%-30s+%-30s+%-20s+%-20s+%-20s+%-20s+%-20s+\t\t%-20s+\n","count", "Item code", "item name", "Category", "Stock", "Sold Item","Buying price", "Selling price", "Profit Percentage", "Sales");



    for(int i=0;i<count;i++)
    {
        
        printf("%-10d \t%-20s %-30s %-35s %-20s %-20s %-20s %-20s %-20s \t%20s\n",i+1,productlist[i].code,productlist[i].name,productlist[i].cat,productlist[i].stock,productlist[i].solditem,productlist[i].bprice,productlist[i].sprice,productlist[i].percent,productlist[i].profits);
    }


    fclose(Stationary);
    return;

}


int find_index(const char *code)
{
 for (int i = 0; i < count; i++)
    {
        if (strcmp(productlist[i].code, code) == 0)
            return i;
    }   
}




int resetValues(int oldIndex)
{
    char code[20];
    strcpy(code, productlist[oldIndex].code);

    if (strcasecmp(productlist[oldIndex].cat,"Stationary")==0)
        Print_Satationaryr();
    else if (strcasecmp(productlist[oldIndex].cat,"Kitchen Utills")==0)
        Print_Kitchen_Utillsr();
    else if (strcasecmp(productlist[oldIndex].cat,"Beverage")==0)
        Print_Beverager();
    else if (strcasecmp(productlist[oldIndex].cat,"Hygiene")==0)
        Print_Hygiener();
    else if (strcasecmp(productlist[oldIndex].cat,"Washroom Utils")==0)
        Print_Washroom_Utilsr();
    else if (strcasecmp(productlist[oldIndex].cat,"Tools")==0)
        Print_Toolsr();

    return find_index(code);
}








void Printing_The_Selecting2(int option,char*text)
{   








    system("clear");

   option = resetValues(option);
    if (option == -1)
    {
    return;
    }



    printf("");
    moving_to_vcenter();
    move_c_hcenter2();
    for(int i=0;i<70;i++)
    {
        printf("-");
    }
    printf("\n");
    move_c_hcenter2();
    printf(BLU"%-30s"reset"\t\t\t%s\n","ItemName:-",productlist[option].name);
    move_c_hcenter2();
    printf(BLU"%-30s"reset"\t\t\t%s\n","ItemCode:-",productlist[option].code);

    move_c_hcenter2();
    printf(BLU"%-30s"reset"\t\t\t%s\n","Category:-",productlist[option].cat);
    move_c_hcenter2();
    printf(BLU"%-30s"reset"\t\t\t%s\n","Stock:-",productlist[option].stock);

    move_c_hcenter2();
    printf(BLU"%-30s"reset"\t\t\t%s\n","Sold:-",productlist[option].solditem);

    move_c_hcenter2();
    printf(BLU"%-30s"reset"\t\t\t%s\n","Original Price:-",productlist[option].bprice);
    move_c_hcenter2();
    printf(BLU"%-30s"reset"\t\t\t%s\n","Selling Price:-",productlist[option].sprice);
    
    move_c_hcenter2();
    printf(BLU"%-30s"reset"\t\t\t%s\n","Profit Percentage:-",productlist[option].percent);
    move_c_hcenter2();
    printf(BLU"%-30s"reset"\t\t\t%s\n","Sales:-",productlist[option].profits);
    printf("\n\n\n");
    move_c_hcenter2();
    printf(MAG"--------------------------%s------------------------------\n"reset,text);
   
}



void Print_all()
{
    
   count=0;
    struct rproductlist a1;
    FILE *Stationary=fopen("Productlist.csv","r");
    if(Stationary==NULL)
    {
        printf("\nProductlist Not Found\n");
        return ;
    }


    while(fgets(a1.temp,sizeof(a1.temp),Stationary)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';
        char *tok;
        tok=strtok(a1.temp,",");
        if(tok)
        {
            strcpy(a1.code,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.name,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.cat,tok);
        }
        

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.stock,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.solditem,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.bprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.percent,tok);
        }


        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.profits,tok);
        }


        strcpy(productlist[count].code,a1.code);
        strcpy(productlist[count].name,a1.name);
        strcpy(productlist[count].cat,a1.cat);
        strcpy(productlist[count].stock,a1.stock);
        strcpy(productlist[count].solditem,a1.solditem);
        strcpy(productlist[count].bprice,a1.bprice);
        strcpy(productlist[count].sprice,a1.sprice);
        strcpy(productlist[count].percent,a1.percent);
        strcpy(productlist[count].profits,a1.profits);
        count +=1;
    }

    moving_to_vcenter();

    printf("+%-10s +%-25s+%-30s+%-30s+%-20s+%-20s+%-20s+%-20s+%-20s+\t\t%20s+\n","count", "Item code", "item name", "Category", "Stock", "Sold Item","Buying price", "Selling price", "Profit Percentage", "Sales");



    for(int i=0;i<count;i++)
    {
        
        printf("%-10d \t%-20s %-30s %-35s %-20s %-20s %-20s %-20s %-20s \t%20s\n",i+1,productlist[i].code,productlist[i].name,productlist[i].cat,productlist[i].stock,productlist[i].solditem,productlist[i].bprice,productlist[i].sprice,productlist[i].percent,productlist[i].profits);
    }

    printf(BLU"\n\nPress Enter to continue"reset);
     getchar();
    fclose(Stationary);
    return;

}

void Print_call()
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
        Print_Satationary();
        break;
    case 2:
        Print_Kitchen_Utills();
        break;
    case 3:
        Print_Beverage();
        break;
    case 4:
        Print_Hygiene();
        break;

    case 5:
        Print_Washroom_Utils();
        break;
    case 6:
        Print_Tools();
        break;
    
    case 7:
        Print_all();
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

int Edit_call()
{
    int option;
    system("clear");
    for(;;)
    {
        move_c_hcenter();
        printf("Location\n");
        moving_to_vcenter();
        move_c_hcenter();
        printf(MAG"----What Do you want to Edit From----\n"reset);
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
        printf("7.All\n");
        move_c_hcenter2();
        printf("8.Exit\n");

        move_c_hcenter2();
        
        printf(BLU"Choice:-\t"reset);
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
                Print_Satationary1();
                return option;
            case 2:
                Print_Kitchen_Utills1();
                return option;
            case 3:
                Print_Beverage1();
                return option;
            case 4:
                Print_Hygiene1();
                return option;
            case 5:
                Print_Washroom_Utils1();
                return option;
            case 6:
                Print_Tools1();
                return option;
            case 7:
                Print_all();
                return option;
            case 8:
                return option;
            default:
                system("clear");
                printf(RED"\nInvalid Input\n"reset);
                break;
        }
    }
   return option;
}

void Edit_Itemname(int option)
{
    FILE *productlists = fopen("Productlist.csv", "r");
    FILE *tempfile    = fopen("Temp_productlist.csv", "w");

    if (productlists == NULL || tempfile == NULL)
    {
        printf("Product List not found\n");
        return;
    }

    struct rproductlist a1;
    char newname[30];

    Printing_The_Selecting2(option, "Edit itemName");
    printf("\n\n\n");

    for (;;)
    {
        move_c_hcenter2();
        printf(BLU"NewName :-\t\t"reset);

        fgets(newname, sizeof(newname), stdin);
        newname[strcspn(newname, "\n")] = '\0';

        if (strlen(newname) >= 25 || strlen(newname) < 3)
            printf(RED"\nError---invalid length\n"reset);
        else
            break;
    }

    while (fgets(a1.temp, sizeof(a1.temp), productlists))
    {
        a1.temp[strcspn(a1.temp, "\n")] = '\0';

        char *tok = strtok(a1.temp, ",");
        if (!tok) continue;
        strcpy(a1.code, tok);

        tok = strtok(NULL, ",");  strcpy(a1.name, tok ? tok : "");
        tok = strtok(NULL, ",");  strcpy(a1.cat, tok ? tok : "");
        tok = strtok(NULL, ",");  strcpy(a1.stock, tok ? tok : "");
        tok = strtok(NULL, ",");  strcpy(a1.solditem, tok ? tok : "");
        tok = strtok(NULL, ",");  strcpy(a1.bprice, tok ? tok : "");
        tok = strtok(NULL, ",");  strcpy(a1.sprice, tok ? tok : "");
        tok = strtok(NULL, ",");  strcpy(a1.percent, tok ? tok : "");
        tok = strtok(NULL, ",");  strcpy(a1.profits, tok ? tok : "");

        /* ✅ If selected item → modify name */
        if (strcmp(productlist[option].name, a1.name) == 0)
            strcpy(a1.name, newname);

        fprintf(
            tempfile,
            "%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
            a1.code,
            a1.name,
            a1.cat,
            a1.stock,
            a1.solditem,
            a1.bprice,
            a1.sprice,
            a1.percent,
            a1.profits
        );
    }

    fclose(productlists);
    fclose(tempfile);

    remove("Productlist.csv");
    rename("Temp_productlist.csv", "Productlist.csv");
}

void Edit_ItemBuying(int option)
{
    FILE *productlists = fopen("Productlist.csv", "r");
    FILE *tempfile = fopen("Temp_productlist.csv", "w");
    if (productlists == NULL || tempfile == NULL)
    {
        printf("Product List not found");
        return;
    }

    struct rproductlist a1;
    int newprice = 0;
    int newsaleprice = 0;

    Printing_The_Selecting2(option, "Edit Original Price");
    printf("\n\n\n");

    while (fgets(a1.temp, sizeof(a1.temp), productlists) != NULL)
    {
        a1.temp[strcspn(a1.temp, "\n")] = '\0';

        char *tok = strtok(a1.temp, ",");
        if (tok) strcpy(a1.code, tok);
        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.name, tok);
        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.cat, tok);
        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.stock, tok);
        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.solditem, tok);
        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.bprice, tok);
        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.sprice, tok);
        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.percent, tok);
        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.profits, tok);

        if (strcmp(productlist[option].code, a1.code) == 0)
        {
            for (;;)
            {
                move_c_hcenter2();
                printf(BLU"Newprice :-\t\t"reset);
                scanf("%d", &newprice);
                getchar();
                int diff;
                diff = ((long long)newprice - atoll(a1.bprice)) / 100;

                if (diff >= 200 ||diff <= -50)
                {
                    printf(RED"\nYou are enter a Huge change compared to Original Price try doing one by one or error"reset);
                }

                if (diff <= 200)
                {
                    break;
                }
            }

            newsaleprice = (int)(newprice + (newprice * atoi(a1.percent)) / 100);

            fprintf(tempfile, "%s,%s,%s,%s,%s,%d,%d,%s,%s\n",a1.code, a1.name, a1.cat, a1.stock, a1.solditem,newprice, newsaleprice, a1.percent, a1.profits);
            continue;
        }

        fprintf(tempfile, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n",a1.code, a1.name, a1.cat, a1.stock, a1.solditem,a1.bprice, a1.sprice, a1.percent, a1.profits);
    }

    fclose(productlists);
    fclose(tempfile);
    remove("Productlist.csv");
    rename("Temp_productlist.csv", "Productlist.csv");
}

void Edit_Profit(int option)
{
    FILE *productlists = fopen("Productlist.csv", "r");
    FILE *tempfile = fopen("Temp_productlist.csv", "w");
    if (productlists == NULL || tempfile == NULL)
    {
        printf("Product List not found");
        return;
    }

    struct rproductlist a1;
    int newprice = 0;
    int newpercentage = 0;

    Printing_The_Selecting2(option, "Edit Sale Price");
    printf("\n\n\n");

    while (fgets(a1.temp, sizeof(a1.temp), productlists) != NULL)
    {
        a1.temp[strcspn(a1.temp, "\n")] = '\0';

        char *tok = strtok(a1.temp, ",");
        if (tok) strcpy(a1.code, tok);
        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.name, tok);
        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.cat, tok);
        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.stock, tok);
        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.solditem, tok);
        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.bprice, tok);
        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.sprice, tok);
        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.percent, tok);
        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.profits, tok);

        if (strcmp(productlist[option].code, a1.code) == 0)
        {
            for (;;)
            {
                move_c_hcenter2();
                printf(BLU"Newprice :-\t\t"reset);
                scanf("%d", &newprice);
                getchar();

                if (((long long int)((long long int)newprice - atoi(a1.bprice)) / 100) >= 200 || ((long long int)((long long int)newprice - atoi(a1.bprice)) / 100 < 0))
                {
                    printf(RED"\nExtortion Error"reset);
                }

                if (((long long int)((long long int)newprice - atoi(a1.bprice)) / 100) <= 200)
                {
                    break;
                }
            }

                newpercentage = (int)(((newprice - atoi(a1.bprice)) * 100) / atoi(a1.bprice));

            fprintf(tempfile, "%s,%s,%s,%s,%s,%s,%d,%d,%s\n",a1.code, a1.name, a1.cat, a1.stock, a1.solditem,a1.bprice, newprice, newpercentage, a1.profits);
            continue;
        }

        fprintf(tempfile, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n",a1.code, a1.name, a1.cat, a1.stock, a1.solditem,a1.bprice, a1.sprice, a1.percent, a1.profits);
    }

    fclose(productlists);
    fclose(tempfile);
    remove("Productlist.csv");
    rename("Temp_productlist.csv", "Productlist.csv");
}

void Edit_Percentage(int option)
{
    FILE *productlists = fopen("Productlist.csv", "r");
    FILE *tempfile = fopen("Temp_productlist.csv", "w");
    if(productlists == NULL)
    {
        printf("Product List not found");
        return;
    }

    struct rproductlist a1;
    int newprice = 0;
    int newpercentage = 0;

    Printing_The_Selecting2(option, "Edit Percentage Profit");
    printf("\n\n\n");

    while(fgets(a1.temp, sizeof(a1.temp), productlists) != NULL)
    {
        a1.temp[strcspn(a1.temp, "\n")] = '\0';
        char *tok = strtok(a1.temp, ",");
        if(tok) strcpy(a1.code, tok);

        tok = strtok(NULL, ",");
        if(tok) strcpy(a1.name, tok);

        tok = strtok(NULL, ",");
        if(tok) strcpy(a1.cat, tok);

        tok = strtok(NULL, ",");
        if(tok) strcpy(a1.stock, tok);

        tok = strtok(NULL, ",");
        if(tok) strcpy(a1.solditem, tok);

        tok = strtok(NULL, ",");
        if(tok) strcpy(a1.bprice, tok);

        tok = strtok(NULL, ",");
        if(tok) strcpy(a1.sprice, tok);

        tok = strtok(NULL, ",");
        if(tok) strcpy(a1.percent, tok);

        tok = strtok(NULL, ",");
        if(tok) strcpy(a1.profits, tok);

        if(strcmp(productlist[option].code, a1.code) == 0)
        {
            for(;;)
            {
                move_c_hcenter();
                printf(BLU"Newpercentage of profit :-\t\t");
                scanf("%d", &newpercentage);
                getchar();

                if((long long int)newpercentage >= 200 || (long long int)newpercentage < 0)
                {
                    printf(RED"\nExtortion Error Or No profit Error"reset);
                }
                if((long long int)newpercentage <= 200)
                {
                    break;
                }
            }
                newprice = atoi(a1.bprice) * (1 + (float)newpercentage / 100.0);
           

            fprintf(tempfile, "%s,%s,%s,%s,%s,%s,%d,%d,%s\n",a1.code, a1.name, a1.cat, a1.stock, a1.solditem,a1.bprice, newprice, newpercentage, a1.profits);
            continue;
        }

        fprintf(tempfile, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n",a1.code, a1.name, a1.cat, a1.stock, a1.solditem,a1.bprice, a1.sprice, a1.percent, a1.profits);
    }

    fclose(productlists);
    fclose(tempfile);
    remove("Productlist.csv");
    rename("Temp_productlist.csv", "Productlist.csv");
}


void Edit_ADDStock(int option)
{
    FILE *productlists = fopen("Productlist.csv", "r");
    FILE *tempfile = fopen("Temp_productlist.csv", "w");
    FILE *bugdet = fopen("bugdet.csv", "r");
    FILE *temp_bugdet = fopen("bugdettemp.csv", "w");

    if(productlists == NULL)
    {
        printf(RED"Product List not found\n"reset);
        return;
    }

    if(bugdet == NULL)
    {
        printf(RED"Bugdet.csv not found\n"reset);
        return;
    }

    char temp[50], bugdett[50];
    int bugdet1;

    fgets(temp, sizeof(temp), bugdet);
    temp[strcspn(temp, "\n")] = '\0';
    char *tok1 = strtok(temp, ",");
    strcpy(bugdett, tok1);
    char b1[20];
    tok1 = strtok(NULL, ",");
    strcpy(b1, tok1);
    char b2[20];
    tok1 = strtok(NULL, ",");
    strcpy(b2, tok1);

    bugdet1 = atoi(bugdett);

    struct rproductlist a1;
    int add_stock;

    Printing_The_Selecting2(option, "Add Stock");
    printf("\n\n\n");

    while(fgets(a1.temp, sizeof(a1.temp), productlists) != NULL)
    {
        a1.temp[strcspn(a1.temp, "\n")] = '\0';
        char *tok = strtok(a1.temp, ",");
        if(tok) strcpy(a1.code, tok);

        tok = strtok(NULL, ",");
        if(tok) strcpy(a1.name, tok);

        tok = strtok(NULL, ",");
        if(tok) strcpy(a1.cat, tok);

        tok = strtok(NULL, ",");
        if(tok) strcpy(a1.stock, tok);

        tok = strtok(NULL, ",");
        if(tok) strcpy(a1.solditem, tok);

        tok = strtok(NULL, ",");
        if(tok) strcpy(a1.bprice, tok);

        tok = strtok(NULL, ",");
        if(tok) strcpy(a1.sprice, tok);

        tok = strtok(NULL, ",");
        if(tok) strcpy(a1.percent, tok);

        tok = strtok(NULL, ",");
        if(tok) strcpy(a1.profits, tok);

        if(strcmp(productlist[option].code, a1.code) == 0)
        {
            for(;;)
            {
                move_c_hcenter2();
                printf("Add Stock:-\t\t");
                scanf("%d", &add_stock);
                getchar();

                if((atoi(a1.bprice) * add_stock) > bugdet1 - 10000)
                {
                    printf(RED"\nBudget Error\n"reset);
                }
                else
                {
                    break;
                }
            }

            add_stock += atoi(a1.stock);
            bugdet1 -= atoi(a1.bprice) * (add_stock - atoi(a1.stock));

            fprintf(tempfile, "%s,%s,%s,%d,%s,%s,%s,%s,%s\n",a1.code, a1.name, a1.cat, add_stock, a1.solditem,a1.bprice, a1.sprice, a1.percent, a1.profits);
            continue;
        }

        fprintf(tempfile, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n",a1.code, a1.name, a1.cat, a1.stock, a1.solditem,a1.bprice, a1.sprice, a1.percent, a1.profits);
    }

    fprintf(temp_bugdet, "%d,%s,%s", bugdet1, b1, b2);

    fclose(productlists);
    fclose(tempfile);
    fclose(bugdet);
    fclose(temp_bugdet);

    remove("Productlist.csv");
    rename("Temp_productlist.csv", "Productlist.csv");
    remove("bugdet.csv");
    rename("bugdettemp.csv", "bugdet.csv");
}

void Edit_Cat(int option)
{
    
    FILE *productlists = fopen("Productlist.csv", "r");
    FILE *tempfile = fopen("Temp_productlist.csv", "w");
    if (productlists == NULL)
    {
        printf("Product List not found");
        return;
    }

    struct rproductlist a1;

    Printing_The_Selecting2(option, "Edit Category");
    printf("\n\n\n");
    move_c_hcenter2();
    printf(MAGHB"Select the type of the product\n"reset);

    move_c_hcenter();
    printf("1.Stationary\n");
    move_c_hcenter();
    printf("2.Kitchen Utills\n");
    move_c_hcenter();
    printf("3.Beverage\n");
    move_c_hcenter();
    printf("4.Hygiene\n");
    move_c_hcenter();
    printf("5.Washroom Utils\n");
    move_c_hcenter();
    printf("6.Tools\n");
    move_c_hcenter();
    printf("7.Return\n");
   

    int option1 = 0;

    while (fgets(a1.temp, sizeof(a1.temp), productlists) != NULL)
    {
        a1.temp[strcspn(a1.temp, "\n")] = '\0';
        char *tok;

        tok = strtok(a1.temp, ",");
        if (tok) strcpy(a1.code, tok);

        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.name, tok);

        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.cat, tok);

        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.stock, tok);

        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.solditem, tok);

        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.bprice, tok);

        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.sprice, tok);

        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.percent, tok);

        tok = strtok(NULL, ",");
        if (tok) strcpy(a1.profits, tok);

        if (strcmp(productlist[option].code, a1.code) == 0)
        {
            while (1)
            {
                move_c_hcenter2();
                printf(BLU"%10s"reset, "Choice:-\t");

                char temp[50];
                if (fgets(temp, sizeof(temp), stdin) == NULL) continue;
                temp[strcspn(temp, "\n")] = '\0';

                if (sscanf(temp, "%d", &option1) != 1)
                {
                    printf(RED"Invalid input\n"reset);
                    continue;
                }

                switch (option1)
                {
                    case 1: 
                    strcpy(a1.cat, "Stationary"); 
                    break;
                    case 2: 
                    strcpy(a1.cat, "Kitchen Utills"); 
                    break;
                    case 3: 
                    strcpy(a1.cat, "Beverage"); 
                    break;
                    case 4: 
                    strcpy(a1.cat, "Hygiene");
                     break;
                    case 5: 
                    strcpy(a1.cat, "Washroom Utils"); 
                    break;
                    case 6: 
                    strcpy(a1.cat, "Tools"); 
                    break;
                    case 7: break;
                    default:
                        printf(RED"Invalid choice\n"reset);
                        continue;
                }

                break;
            }

            fprintf(tempfile, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
                    a1.code, a1.name, a1.cat, a1.stock, a1.solditem, a1.bprice, a1.sprice, a1.percent, a1.profits);
            continue;
        }

        fprintf(tempfile, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
                a1.code, a1.name, a1.cat, a1.stock, a1.solditem, a1.bprice, a1.sprice, a1.percent, a1.profits);
    }

    fclose(productlists);
    fclose(tempfile);
    remove("Productlist.csv");
    rename("Temp_productlist.csv", "Productlist.csv");
}


void Edit_Delete(int option)
{
    FILE *productlists=fopen("Productlist.csv","r");
    FILE *tempfile=fopen("Temp_productlist.csv","w");
    if(productlists==NULL);
    {
        printf("Product List not found");
    }
    struct rproductlist a1;

    
    
    Printing_The_Selecting2(option,"Delete");
    printf("\n\n\n");
    char confirmation [100];
    for(;;)
    {
    printf("\n");
    move_c_hcenter2();
    printf("Confirmation (Yes/No):-");
    fgets(confirmation,sizeof(confirmation),stdin);
    confirmation[strcspn(confirmation,"\n")]='\0';
    
    if(strcasecmp(confirmation,"yes")==0||strcasecmp(confirmation,"y")==0||strcasecmp(confirmation,"No")==0||strcasecmp(confirmation,"n")==0)
    {
        if(strcasecmp(confirmation,"yes")==0||strcasecmp(confirmation,"y")==0)
        {
            break;
        }
        if(strcasecmp(confirmation,"No")==0||strcasecmp(confirmation,"n")==0)
        {
            return;
        }


    }
    else
    {
        continue;
    }

    }


    




    while(fgets(a1.temp,sizeof(a1.temp),productlists)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';
        char *tok;
        tok=strtok(a1.temp,",");
        if(tok)
        {
            strcpy(a1.code,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.name,tok);
        }

        if(strcmp(productlist[option].name,a1.name)==0)
        {
            
            continue;
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.cat,tok);
        }
       
        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.stock,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.solditem,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.bprice,tok);
        }
        

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.sprice,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.percent,tok);
        }
        


        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.profits,tok);
        }

       fprintf(tempfile,"%s,%s,%s,%s,%s,%s,%s,%s,%s\n",a1.code,a1.name,a1.cat,a1.stock,a1.solditem,a1.bprice,a1.sprice,a1.percent,a1.profits);
    }
    fclose(productlists);
    fclose(tempfile);
    remove("Productlist.csv");
    rename("Temp_productlist.csv","Productlist.csv");


}



void Pinting_The_Selecting(int option)
{

   
    for(;;)
    {

    option = resetValues(option);
    if (option == -1)
    {
    return;
    }



    system("clear");
    printf("");
    moving_to_vcenter();
    move_c_hcenter2();
    for(int i=0;i<70;i++)
    {
        printf("-");
    }
    printf("\n");
    move_c_hcenter2();
    printf(BLU"%-30s"reset"\t\t\t%s\n","ItemName:-",productlist[option].name);
    move_c_hcenter2();
    printf(BLU"%-30s"reset"\t\t\t%s\n","ItemCode:-",productlist[option].code);

    move_c_hcenter2();
    printf(BLU"%-30s"reset"\t\t\t%s\n","Category:-",productlist[option].cat);
    move_c_hcenter2();
    printf(BLU"%-30s"reset"\t\t\t%s\n","Stock:-",productlist[option].stock);

    move_c_hcenter2();
    printf(BLU"%-30s"reset"\t\t\t%s\n","Sold:-",productlist[option].solditem);

    move_c_hcenter2();
    printf(BLU"%-30s"reset"\t\t\t%s\n","Original Price:-",productlist[option].bprice);
    move_c_hcenter2();
    printf(BLU"%-30s"reset"\t\t\t%s\n","Selling Price:-",productlist[option].sprice);
    
    move_c_hcenter2();
    printf(BLU"%-30s"reset"\t\t\t%s\n","Profit Percentage:-",productlist[option].percent);
    move_c_hcenter2();
    printf(BLU"%-30s"reset"\t\t\t%s\n","Sales:-",productlist[option].profits);
    printf("\n\n\n");
    move_c_hcenter2();
    printf(MAG"--------------------------Options------------------------------\n"reset);
    move_c_hcenter();
    printf("1:-Edit Itemname\n");
    move_c_hcenter();
    printf("2.Change Original price\n");
    move_c_hcenter();
    printf("3.Change The Selling price\n");
    move_c_hcenter();
    printf("4.Change profit percentage\n");
    move_c_hcenter();
    printf("5.Change Category\n");
    move_c_hcenter();
    printf("6.Delete the Product\n");
    move_c_hcenter();
    printf("7.Add stock\n");
     move_c_hcenter();
    printf("8.Return\n");
    char temp_choice[50];
    int options1;
    printf("\n\n\n\n");
    

    move_c_hcenter2();
    printf(MAG"Choice:-\t\t"reset);
    // scanf("%d",&options1);
    // getchar();
    fgets(temp_choice,sizeof(temp_choice),stdin);
    temp_choice[strcspn(temp_choice,"\n")]='\0';

    if(sscanf(temp_choice,"%d",&options1)!=1)
    {
        system("clear");
        printf(RED"\n\n\nCharacter Input Error\n"reset);
        continue;
    }



    if((long long int)options1<=8&&(long long int)options1>0)
    {
        if(options1==1)
        {
            Edit_Itemname(option);
        }
        

        if(options1==2)
        {
            Edit_ItemBuying(option);
        }

        if(options1==3)
        {
            Edit_Profit(option);
        }

        if(options1==4)
        {
           Edit_Percentage(option); 
        }

        if(options1==5)
        {
            Edit_Cat(option);
        }

        if(options1==6)
        {

            Edit_Delete(option);
        }
        if(options1==7)
        {
            Edit_ADDStock(option);
        }

        if(options1==8)
        {
            return ;
        }









    }
    else
    {
        continue;
    }




}
    

}


void Select_Item()
{
    
    for (;;)
    {
        int exit_check = Edit_call();
    if (exit_check == 8)
        return;

        int options;

        printf("\n\n");
        move_c_hcenter2();
        printf(BLU"Select_Item:-\t"reset);

        char temp_option[50];
        fgets(temp_option, sizeof(temp_option), stdin);
        
        temp_option[strcspn(temp_option, "\n")] = '\0';


        if (temp_option[0] == '\0')
        {
            system("clear");
            printf(RED"\n\nInvalid input(Character)\n"reset);
            continue;
        }

        if (sscanf(temp_option, "%d", &options) !=1)
        {
            system("clear");
            printf(RED"\n\nInvalid input(Character)\n"reset);
            continue;
        }

        options -= 1;

        if (options >= 0 && options < count)
        {
            system("clear");
            Pinting_The_Selecting(options);
            break;
        }
        else
        {
            system("clear");
            printf(RED"Invalid Input\n"reset);
        }
    }
}


void Product_Management()
{   
    for(;;)
   {
    system("clear");
    moving_to_vcenter();
    move_c_hcenter2();
    printf(MAG"------------------------Product Managment----------------------------\n"reset);
    move_c_hcenter();
    printf("1:-Printing Products\n");
    move_c_hcenter();
    printf("2:-Adding Product\n");
    move_c_hcenter();
    printf("3:-Manage Item\n");
    move_c_hcenter();
    printf("4:-Return\n");
   
   

    printf("\n");
    move_c_hcenter2();
    printf(BLU"Choice-\t"reset);
    int choice;
    scanf("%d",&choice);
    getchar();

    if((long long int)choice<=4 && (long long int)choice>=0)
    {
        if(choice==1)
        {
        Print_call();
        }
        if(choice==2)
        {
        Adding_A_Item();
        }
        if(choice==3)
        {
        Select_Item();
        }
        if(choice==4)
        {
        return;
        }

    }

    else
    {
        printf(RED"Invalid input"reset);
    }
   }
}