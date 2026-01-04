#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "COLORS.c"
#include "login.h"
#include "Selling.h"

struct Userlist
{
    char temp[200];
    char username[45];
    char password[60];
    char authority[20];
    char performance[10];
};

void userlist()
{
    FILE *fp = fopen("Userlist.csv", "r");
    if (!fp) return;

    struct Userlist u;
    printf(BMAG"%-20s | %-20s | %-10s | %-5s\n"reset,
           "Username", "Password", "Authority", "Perf");

    while (fgets(u.temp, sizeof(u.temp), fp))
    {
        if (strlen(u.temp) <= 1) continue;
        u.temp[strcspn(u.temp, "\n")] = 0;

        char *t = strtok(u.temp, ",");
        if (t) strcpy(u.username, t);

        t = strtok(NULL, ",");
        if (t) strcpy(u.password, t);

        t = strtok(NULL, ",");
        if (t) strcpy(u.authority, t);

        t = strtok(NULL, ",");
        if (t) strcpy(u.performance, t);

        if (!strcasecmp(login_usernames, u.username))
            printf(BHCYN"%-20s"reset" | ", u.username);
        else
            printf(BLU"%-20s"reset" | ", u.username);

        for (int i = 0; i < strlen(u.password); i++) printf("*");
        printf(" | %-10s | %-5s\n", u.authority, u.performance);
    }
    fclose(fp);
}

void Add_user()
{
    struct Userlist u;
    char line[200];

    for (;;)
    {
        system("clear");
        printf(BLU"Home>Manager>"RED"Add-User\n\n"reset);
        printf("Username: ");
        getchar();
        fgets(u.username, sizeof(u.username), stdin);
        u.username[strcspn(u.username, "\n")] = 0;

        FILE *fp = fopen("Userlist.csv", "r");
        if (!fp) return;

        int exists = 0;
        while (fgets(line, sizeof(line), fp))
        {
            char *t = strtok(line, ",");
            if (t && !strcasecmp(t, u.username))
            {
                exists = 1;
                break;
            }
        }
        fclose(fp);

        if (exists)
        {
            printf(RED"\nUser already exists!\n"reset);
            sleep(1);
            continue;
        }

        printf("Password: ");
        scanf("%s", u.password);

        strcpy(u.authority, "Staff");
        strcpy(u.performance, "0");

        fp = fopen("Userlist.csv", "a");
        if (!fp) return;

        fprintf(fp, "%s,%s,%s,%s\n",
                u.username, u.password,
                u.authority, u.performance);

        fclose(fp);
        printf(GRN"\nUser Added Successfully\n"reset);
        break;
    }
}

void UserManager()
{
    struct Userlist cur, tmp;
    char search[50];
    int found = 0, admin_lock = 0, del = 0;

    FILE *fp = fopen("Userlist.csv", "r");
    FILE *out = fopen("temp.csv", "w");
    if (!fp || !out) return;

    printf("\nEnter Username: ");
    scanf("%s", search);

    rewind(fp);
    while (fgets(cur.temp, sizeof(cur.temp), fp))
    {
        cur.temp[strcspn(cur.temp, "\n")] = 0;

        char *t = strtok(cur.temp, ",");
        strcpy(cur.username, t);
        strcpy(cur.password, strtok(NULL, ","));
        strcpy(cur.authority, strtok(NULL, ","));
        strcpy(cur.performance, strtok(NULL, ","));

        if (!strcasecmp(cur.username, search))
        {
            found = 1;
            if (!strcasecmp(cur.authority, "Admin") ||
               (!strcasecmp(cur.authority, "Manager")
                && strcasecmp(cur.username, login_usernames)))
                admin_lock = 1;
            break;
        }
    }

    if (!found || admin_lock)
    {
        fclose(fp);
        fclose(out);
        remove("temp.csv");
        printf(RED"Access denied\n"reset);
        return;
    }

    for (;;)
    {
        system("clear");
        printf("USER: %s\nAuthority: %s\n", cur.username, cur.authority);
        printf("1.Show\n2.Edit Username\n3.Edit Password\n4.Delete\n5.Save & Exit\n");

        int ch;
        scanf("%d", &ch);

        if (ch == 1)
        {
            printf("%s %s %s %s\n",
                   cur.username, cur.password,
                   cur.authority, cur.performance);
            sleep(2);
        }
        else if (ch == 2)
            scanf("%s", cur.username);
        else if (ch == 3)
            scanf("%s", cur.password);
        else if (ch == 4)
            del = 1;
        else if (ch == 5)
            break;
    }

    rewind(fp);
    while (fgets(tmp.temp, sizeof(tmp.temp), fp))
    {
        tmp.temp[strcspn(tmp.temp, "\n")] = 0;

        char *t = strtok(tmp.temp, ",");
        strcpy(tmp.username, t);
        strcpy(tmp.password, strtok(NULL, ","));
        strcpy(tmp.authority, strtok(NULL, ","));
        strcpy(tmp.performance, strtok(NULL, ","));

        if (!strcasecmp(tmp.username, search))
        {
            if (!del)
                fprintf(out, "%s,%s,%s,%s\n",
                        cur.username, cur.password,
                        cur.authority, cur.performance);
        }
        else
        {
            fprintf(out, "%s,%s,%s,%s\n",
                    tmp.username, tmp.password,
                    tmp.authority, tmp.performance);
        }
    }

    fclose(fp);
    fclose(out);
    remove("Userlist.csv");
    rename("temp.csv", "Userlist.csv");
}

int Manage_function()
{
    int op;
    for (;;)
    {
        printf(BLU"Home>"reset RED"Manager>\n\n"reset);
        printf("1.Userlist\n2.Manage User\n3.Add User\n4.Counter\n5.Exit\n");
        scanf("%d", &op);

        if (op == 1) userlist();
        else if (op == 2) UserManager();
        else if (op == 3) Add_user();
        else if (op == 4) SELLINGmain();
        else if (op == 5) return 0;
    }
}
