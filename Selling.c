#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "COLORS.c"
#include "Align.h"
#include <ctype.h>
#include "Selling.h"
#include "login.h"



#include <time.h>

#define MAX_ITEMS 50
#define Errormargin 1
#define MAX_SUGGESTIONS 50

struct product 
{
    char temp[400];
    char itemcode[20];
    char itemname[30];
    char sitemprice[10];
    char itemcat[20];
    int itemprice;
    char itemamountr[10];
    char itemsaled[10];
    char bitemprice[10];
    char percentageofprofit[10];
    char totalsaled[10];
};


struct User
{
    char temp[200];
    char name[30];
    char password[30];
    char authority[20];
    char perform[20];
};

//------------------------------------------//



void User_update(int sales)
{
    struct User a1;
    
    FILE *User_update=fopen("Userlist.csv","r");
    FILE *User_update_temp=fopen("Userlisttemp.csv","w");

    while(fgets(a1.temp,sizeof(a1.temp),User_update)!=NULL)
    {
        a1.temp[strcspn(a1.temp,"\n")]='\0';
        char *tok;
        tok=strtok(a1.temp,",");
        if(tok)
        {
            strcpy(a1.name,tok);
        } 


        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.password,tok);
        } 

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.authority,tok);
        } 

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a1.perform,tok);
        } 


        if(strcasecmp(login_usernames,a1.name)==0)
        {
            fprintf(User_update_temp,"%s,%s,%s,%d\n",a1.name,a1.password,a1.authority,atoi(a1.perform)+sales);
            continue;
        }


        fprintf(User_update_temp,"%s,%s,%s,%s\n",a1.name,a1.password,a1.authority,a1.perform);


    }

    fclose(User_update);
    fclose(User_update_temp);


    remove("Userlist.csv");
    rename("Userlisttemp.csv","Userlist.csv");


}




void updateBudgetLeft(int total) {
    FILE *fp = fopen("bugdet.csv", "r");
    if (!fp) {
        printf("Could not open file %s\n", "bugdet.csv");
        return;
    }

    FILE *temp = fopen("temp.csv", "w");
    if (!temp) {
        printf("Could not create temporary file\n");
        fclose(fp);
        return;
    }

    int budgetLeft, budgetAllotted, sales;

    while (fscanf(fp, "%d,%d,%d", &budgetLeft, &budgetAllotted, &sales) == 3) {
        budgetLeft += sales;  
        fprintf(temp, "%d,%d,%d\n", budgetLeft, budgetAllotted, sales+total);
    }

    fclose(fp);
    fclose(temp);

    
    remove("bugdet.csv");
    rename("temp.csv", "bugdet.csv");
}




struct ReceiptItem {
    char code[20];
    char name[30];
    char cat[20];
    int price;
    int quantity;
    int total;
};

struct error_Itemname
{
    char name[30];
};

struct ReceiptItem receipt[MAX_ITEMS];
int item_count = 0;

void changing_stock(char *item_name_Stock,int quantity)
{
    struct product a2;
    int percentage_profit;
    int flag1=0;
   
    FILE *product_list=fopen("Productlist.csv","r");
    FILE *product_list_temp=fopen("Temp_plist.csv","w");

    while (fgets(a2.temp,sizeof(a2.temp),product_list)!=0)
    {
        char *tok;
        tok=strtok(a2.temp,",");
        
        if(tok)
        {
            strcpy(a2.itemcode,tok);
        }
        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a2.itemname,tok);
        }
        
        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a2.itemcat,tok);
        }



         tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a2.itemamountr,tok);
        }
        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a2.itemsaled,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a2.bitemprice,tok);
        }
        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a2.sitemprice,tok);
        }
        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a2.percentageofprofit,tok);
        }
         tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a2.totalsaled,tok);
        }
        if(strcmp(a2.itemname,item_name_Stock)==0)
        {
            flag1=1;
            break;
            
        }
        percentage_profit=(atoi(a2.sitemprice)-atoi(a2.bitemprice))*100/atoi(a2.bitemprice);
        fprintf(product_list_temp,"%s,%s,%s,%s,%s,%s,%s,%d%%,%s",a2.itemcode,a2.itemname,a2.itemcat,a2.itemamountr,a2.itemsaled,a2.bitemprice,a2.sitemprice,percentage_profit,a2.totalsaled);

    
    }
    if(flag1==1)
    {
        int increased;
        int new_quantity;
        
        increased=atoi(a2.totalsaled)+(quantity*atoi(a2.sitemprice));

        new_quantity=atoi(a2.itemamountr)-quantity;
        percentage_profit=(atoi(a2.sitemprice)-atoi(a2.bitemprice))*100/atoi(a2.bitemprice);
        
        fprintf(product_list_temp,"%s,%s,%s,%d,%d,%s,%s,%d%%,%d\n",a2.itemcode,a2.itemname,a2.itemcat,new_quantity,quantity,a2.bitemprice,a2.sitemprice,percentage_profit,increased);

        while(fgets(a2.temp,sizeof(a2.temp),product_list)!=NULL)
        {
               char *tok;
        tok=strtok(a2.temp,",");
        
        if(tok)
        {
            strcpy(a2.itemcode,tok);
        }
        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a2.itemname,tok);
        }
        
        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a2.itemcat,tok);
        }



         tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a2.itemamountr,tok);
        }
        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a2.itemsaled,tok);
        }

        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a2.bitemprice,tok);
        }
        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a2.sitemprice,tok);
        }
        tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a2.percentageofprofit,tok);
        }
         tok=strtok(NULL,",");
        if(tok)
        {
            strcpy(a2.totalsaled,tok);
        }

        percentage_profit=(atoi(a2.sitemprice)-atoi(a2.bitemprice))*100/atoi(a2.bitemprice);
        fprintf(product_list_temp,"%s,%s,%s,%s,%s,%s,%s,%d%%,%s",a2.itemcode,a2.itemname,a2.itemcat,a2.itemamountr,a2.itemsaled,a2.bitemprice,a2.sitemprice,percentage_profit,a2.totalsaled);

        }


    }

    fclose(product_list);
    fclose(product_list_temp);

    remove("Productlist.csv");
    rename("Temp_plist.csv","Productlist.csv");
    

    
}

struct product suggestions[MAX_ITEMS];
int suggestion_count = 0;



void error_margin(char *falsename)
{
    suggestion_count = 0;
    struct product a3;
    FILE *productlist = fopen("Productlist.csv", "r");
    if (!productlist) return;

    printf("Did you mean:\n");

    while (fgets(a3.temp, sizeof(a3.temp), productlist) != NULL)
    {
        char *tok = strtok(a3.temp, ","); // use  case seperation based on a 
        if (tok) strcpy(a3.itemcode, tok);

        tok = strtok(NULL, ",");
        if (tok) strcpy(a3.itemname, tok);

        tok = strtok(NULL, ",");
        if (tok) strcpy(a3.itemcat, tok);

        
        char tempname[100];
        strcpy(tempname, a3.itemname);

        char *word = strtok(tempname, " ");
        int matched = 0;

        while (word != NULL)
        {
            int len = strlen(word) < strlen(falsename) ? strlen(word) : strlen(falsename); 
            int correct = 0;

            for (int j = 0; j < len; j++)
            {
                if (tolower(word[j]) == tolower(falsename[j]))
                    correct++;
            }

            int errors = strlen(falsename) - correct;

           
            if ((strlen(falsename) >= 4 && errors <= Errormargin) ||(strlen(falsename) < 4 && errors <= (Errormargin - 1)))
            {
                matched = 1;
                break;
            }

            word = strtok(NULL, " ");
        }

        if (matched && suggestion_count < MAX_SUGGESTIONS)
        {
            suggestions[suggestion_count++] = a3;
            printf("%30s%2d. %-10s %-30s %-30s\n"," ",suggestion_count, a3.itemcode, a3.itemname, a3.itemcat);
        }
    }

    fclose(productlist);

    
    if (suggestion_count > 0)
    {
        int choice;
        printf("\nEnter item number to select: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= suggestion_count)
        {
            strcpy(falsename, suggestions[choice - 1].itemname); // set chosen item by array
        }
        
     
    }
    else
    {
        printf("\nNo matching items found.\n");
    }

    if(suggestion_count == 0)
    {
        return ;
    }
}

int find_and_storeprice(char *searchitemname) {
    struct product a1;
    int flagsofflags=0;
    FILE *productlist = fopen("Productlist.csv", "r");
    if (!productlist) {
        printf("File not found\n");
        return -1;
    }
    for(;;)
    {
    while (fgets(a1.temp, sizeof(a1.temp), productlist)) {
        char *tok;

        tok = strtok(a1.temp, ","); 
        if (tok) strcpy(a1.itemcode, tok);
        tok = strtok(NULL, ","); 
        if (tok) strcpy(a1.itemname, tok);
        tok = strtok(NULL, ","); 
        if (tok) strcpy(a1.itemcat, tok);
        tok = strtok(NULL, ","); 
        if(tok!=NULL)
        {
            strcpy(a1.itemamountr,tok);
        }
        tok = strtok(NULL, ","); 
        tok = strtok(NULL, ","); 
        tok = strtok(NULL, ","); 
        if (tok) 
        strcpy(a1.sitemprice, tok);

        if (strcasecmp(searchitemname, a1.itemname) == 0 || strcasecmp(searchitemname, a1.itemcode) == 0) {
            int quantity;
char buffer[50];
getchar();
for (;;) {
    
    move_to_hcenter("Enter Quantity: ");
    if (fgets(buffer, sizeof(buffer), stdin)==NULL) {
       
        continue;
    }

    
    buffer[strcspn(buffer, "\n")] = 0;

   
    if (sscanf(buffer, "%d", &quantity) != 1 || (long long int)quantity>10000||(long long int)quantity<0) 
    {
        printf(RED"\nInvalid input, enter a number\n"reset);
        
        continue;
    }

    if (quantity > atoi(a1.itemamountr) ) {
        printf(RED"\nThe quantity is greater than stocks\n"reset);
        continue;
    }
    if (quantity==0)
    {
        printf("\n");
        system("clear");
        return 0;
    }
    

    break;
}

            int tprice = atoi(a1.sitemprice) * quantity;

            
            strcpy(receipt[item_count].code, a1.itemcode);
            strcpy(receipt[item_count].name, a1.itemname);
            strcpy(receipt[item_count].cat, a1.itemcat);
            receipt[item_count].price = atoi(a1.sitemprice);
            receipt[item_count].quantity = quantity;
            receipt[item_count].total = tprice;
            item_count++;

            changing_stock(a1.itemname,quantity);
            fclose(productlist);
            return tprice;
        }

    }
    if(flagsofflags==0)
    {
    error_margin(searchitemname);
    rewind(productlist);
    flagsofflags ++;
    continue;
    }
    else
    {
        printf(RED,"\nItem Not found"reset);
        break;
    }
    }
    fclose(productlist);
    return 0;
}


void print_receipt() {
    
    

    printf(BLU "===========RECEIPT ========\n" reset);
    printf("%-10s | %-20s | %-15s | %-10s | %-8s | %-10s\n",
           "Code", "Item", "Category", "Price", "Qty", "Total");
    printf("-----------------------------------------------------------------------------\n");

    int grand_total = 0;
    for (int i = 0; i < item_count; i++) {
        printf("%-10s | %-20s | %-15s | %-10d | %-8d | %-10d\n",
               receipt[i].code, receipt[i].name, receipt[i].cat,
               receipt[i].price, receipt[i].quantity, receipt[i].total);
        grand_total += receipt[i].total;
    }
    printf("-----------------------------------------------------------------------------\n");
    printf("%55s %10d\n", "Grand Total:", grand_total);
}

void recipt_file()
{
    time_t now=time(NULL);

    struct tm *t=localtime(&now);
    char filename[100];
    strftime(filename,sizeof(filename),"RECIPTS/Recipt_%I:%M:%S.%p_%a-%m-%Y.txt",t);//11:30:39.am_Day
    FILE *recipt=fopen(filename,"w");
    
    fprintf(recipt,BLU "====================RECEIPT ================\n" reset);
    fprintf(recipt,"%-10s | %-20s | %-15s | %-10s | %-8s | %-10s\n","Code", "Item", "Category", "Price", "Qty", "Total");
    fprintf(recipt,"-----------------------------------------------------------------------------\n");

    int grand_total = 0;
    for (int i = 0; i < item_count; i++) {
    fprintf(recipt,"%-10s | %-20s | %-15s | %-10d | %-8d | %-10d\n",receipt[i].code, receipt[i].name, receipt[i].cat,receipt[i].price, receipt[i].quantity, receipt[i].total);grand_total += receipt[i].total;
    }
    fprintf(recipt,"-----------------------------------------------------------------------------\n");
    fprintf(recipt,"%55s %10d\n", "Grand Total:", grand_total);
    User_update(grand_total);
    updateBudgetLeft(grand_total);





    
}

void clear_receipt_items() {
    for (int i = 0; i < MAX_ITEMS; i++) {
        memset(&receipt[i], 0, sizeof(struct ReceiptItem));
    }
    item_count = 0;
}

void save_sale_history() 
{
    FILE *hist = fopen("SalesHistory.csv", "a");
    if (!hist) {
        printf("Error opening SalesHistory.csv\n");
        return;
    }

    
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    char date[20], timebuf[20];
    strftime(date, sizeof(date), "%Y-%m-%d", t);
    strftime(timebuf, sizeof(timebuf), "%H:%M:%S", t);

    
    for (int i = 0; i < item_count; i++) 
    {
        fprintf(hist, "%s,%s,%s,%s,%d,%d,%d,%s,%s\n",date,timebuf,receipt[i].code,receipt[i].name,receipt[i].price,receipt[i].quantity,receipt[i].total,receipt[i].cat,"SALE"   );
    }

    fclose(hist);
}

int SELLINGmain() {
    system("clear");
    char itemdetails[30];
    for(;;)
    {
    

    while (1) {
        
        moving_to_vcenter();
        move_to_hcenter(BLU "Enter item name (or type 'done' to finish): " reset);
        scanf(" %[^\n]", itemdetails);

        if (strcasecmp(itemdetails, "done") == 0) 
        break;
        
        
        find_and_storeprice(itemdetails);
        system("clear");
        print_receipt(); 
    }
        system("clear");
        moving_to_vcenter();
        char ex_option[10];
        int exit_flag=0;

        for(;;)
        {
        move_to_hcenter(RED"Do you want to save the list(Yes/no):-\t\t\t"reset);
        scanf(" %[^\n]",ex_option);

        if(strcasecmp(ex_option,"yes")==0||strcasecmp(ex_option,"No")==0||strcasecmp(ex_option,"y")==0||strcasecmp(ex_option,"n")==0)
        {
            if(strcasecmp(ex_option,"yes")==0||strcasecmp(ex_option,"y")==0)
            {
            exit_flag=1;
            break;
            }
            else
            {
                break;
            }
           
        }
        else
        {
            system("clear");
            moving_to_vcenter();
            move_to_hcenter(RED"invalid option"reset);
            continue;
            

        }

    }
    if(exit_flag!=0)
    {
        recipt_file();
        save_sale_history();
        system("clear");
        moving_to_vcenter();

        move_to_hcenter(GRN"Recipt saved\n"reset);
        int restart_option=0;
       
        for(;;)
        {
            move_to_hcenter(MAG"-----------------------------------Options--------------------------------\n"reset);
            
            move_to_hcenter("1:-New Recipt\n");
            
            move_to_hcenter("2:-Exit\n\n");
            
            move_to_hcenter(BLU"Option:-\t"reset);
            scanf("%d",&restart_option);
            if(restart_option==1)
            {   
              clear_receipt_items();
              system("clear");
                break;
            }
            if(restart_option==2)
            {
                return 0;
            }
            if(restart_option!=1 || restart_option!=2)
            {
                system("clear");
                moving_to_vcenter();
                move_c_hcenter();
                printf(RED"Invalid Option\n"reset);
                continue;
            }
           
        }

        
    }
    else
    {
        system("clear");
        continue;
    }
        
}
    

    return 0;
}





