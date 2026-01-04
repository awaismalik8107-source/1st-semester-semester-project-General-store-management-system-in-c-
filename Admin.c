#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "COLORS.c"
#include "login.h"
#include "Align.h"
#include "Selling.h"
#include "Admin_Manager.h"
#include "Userlist.h"
#include "ProductPerformance.h"
#include "Product_Management.h"

void Check_Profit()
{
    long amount_left, invested;
    int profit;
    system("clear");
    move_c_hcenter2();

    FILE *fp = fopen("budget.csv", "r");
    if (!fp)
    {
        printf("File not found\n");
        return;
    }

    fscanf(fp, "%ld,%ld,%d",&amount_left,&invested,&profit);
    fclose(fp);

    profit = invested - amount_left;
    moving_to_vcenter();
    move_c_hcenter2();
    printf(BLU"Amount Invested "reset": %ld\n", invested);
    move_c_hcenter2();
    printf(BLU"Amount Left     "reset": %ld\n", amount_left);
    move_c_hcenter2();
    printf(BLU"Profit          "reset": %d\n", profit);

    printf(BLU"\nEnter to continue........\n"reset);
    getchar();
}

void Print_Sales_List()
{
    FILE *file = fopen("SalesHistory.csv", "r");
    if (!file)
    {
        printf("File %s not found!\n", "SalesHistory.csv");
        return;
    }

    system("clear");
    moving_to_vcenter();
    move_c_hcenter2();
    printf(BMAG "==================== SALES LIST ====================" reset "\n");

    moving_to_vcenter();
    move_c_hcenter2();
    printf(BMAG "Date & Time        | Item Code      | Item Name                  | Price | Qty | Total | Category        | Type" reset "\n");

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        

        char date[20], code[20], name[30], category[20], type[20];
        int price, qty, total;

        char *token = strtok(line, ",");
        if (!token) continue;
        strcpy(date, token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strcpy(code, token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strcpy(name, token);

        token = strtok(NULL, ",");
        if (!token) continue;
        price = atoi(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        qty = atoi(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        total = atoi(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strcpy(category, token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strcpy(type, token);

        char output[300];
        printf( "%-18s | %-14s | %-25s | %-5d | %-3d | %-6d | %-15s | %-5s",date, code, name, price, qty, total, category, type);
        moving_to_vcenter();
        move_c_hcenter2();
        
    }

    fclose(file);

    printf("\n");
    moving_to_vcenter();
    move_c_hcenter2();
    printf("Press Enter to continue...");
    getchar();
}

void Add_Stock()
{
    system("clear");
    moving_to_vcenter();
    char filename[] = "budget.csv";
    FILE *file = fopen(filename, "r");
    int amount_left = 100000, budget = 100000, profit = 0;

    if (file)
    {
        fscanf(file, "%d,%d,%d", &amount_left, &budget, &profit);
        fclose(file);
    }

    move_c_hcenter2();
    printf(MAG"\n================ Budget Status ================\n"reset);
    move_c_hcenter2();
    printf("Amount Left : %d\n", amount_left);
    move_c_hcenter2();
    printf("Budget      : %d\n", budget);
    move_c_hcenter2();
    printf("Profit      : %d\n", profit);
    move_c_hcenter2();
    printf("===============================================\n");

    char choice;
    printf("Do you want to add this month's profit to total and reset profit? (y/n): ");
    getchar(); // clear newline
    scanf("%c", &choice);

    if (choice == 'y' || choice == 'Y')
    {
        system("clear");
        moving_to_vcenter();
        amount_left += profit;
        profit = 0;
        move_c_hcenter2();
        printf(MAG"\n===== Profit Added! Updated Budget =====\n"reset);
        move_c_hcenter2();
        printf("Amount Left : %d\n", amount_left);
        move_c_hcenter2();
        printf("Budget      : %d\n", budget);
        move_c_hcenter2();
        printf("Profit      : %d\n", profit);
        move_c_hcenter2();
        printf("=======================================\n");
    }
    else
    {
        printf("\nNo changes made to budget.\n");
    }

    file = fopen(filename, "w");
    if (!file)
    {
        printf("Error opening file for writing!\n");
        return;
    }

    fprintf(file, "%d,%d,%d\n", amount_left, budget, profit);
    fclose(file);

    printf("\nBudget file updated successfully!\n");
}

int Admin()
{
    char temp[100];
    int option;

    for (;;)
    {
        system("clear");
        move_c_hcenter2();
        printf(BLU"Home>"YELHB"Admin\n"reset);
        moving_to_vcenter();
        move_c_hcenter2();
        printf(MAG"------------------------------------------------------Admin------------------------------------------------\n"reset);
        move_c_hcenter2(); printf(BLU"1\t"reset"|Manage Account\n");
        move_c_hcenter2(); printf(BLU"2\t"reset"|Product Managment\n");
        move_c_hcenter2(); printf(BLU"3\t"reset"|Product Performance\n");
        move_c_hcenter2(); printf(BLU"4\t"reset"|Add Stock and reset stock\n");
        move_c_hcenter2(); printf(BLU"5\t"reset"|Users_Performance\n");
        move_c_hcenter2(); printf(BLU"6\t"reset"|Selling History Combined\n");
        
        move_c_hcenter2(); printf(BLU"7\t"reset"|Counter\n");
        move_c_hcenter2(); printf(BLU"8\t"reset"|Profit This Month\n");
        move_c_hcenter2(); printf(BLU"9\t"reset"|Exit\n\n");
        move_c_hcenter2(); printf("Select Option: ");

        if (!fgets(temp, sizeof(temp), stdin))
            continue;

        if (sscanf(temp, "%d", &option) != 1)
        {
            move_c_hcenter2();
            printf("Invalid input\n");
            sleep(1);
            continue;
        }

        switch (option)
        {
            case 1:
                Manage_function2();
                break;
            case 2:
                Product_Management();
                break;
            case 3:
                Printing_performance();
                break;
            case 4:
                Add_Stock();
                break;
            case 5:
                Filterer();
                getchar();
                break;
            case 6:
                Print_Sales_List();
                break;

            case 7:
                SELLINGmain();
                break;
            case 8:
                Check_Profit();
                break;
            case 9:
                system("clear");
                return 0;
            default:
                move_c_hcenter2();
                printf("Invalid option\n");
                sleep(1);
        }
    }
}
