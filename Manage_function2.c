#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "COLORS.c"
#include "login.h"
#include "Selling.h"
#include "Align.h"

#define USER_FILE "Userlist.csv"
#define TEMP_FILE "temp.csv"

struct Userlist {
    char temp[200];
    char username[45];
    char password[60];
    char authority[20];
    char proformanc[20];
};

static void parse_user_line(struct Userlist *user, char *line) {
    line[strcspn(line, "\n")] = 0;
    char *token = strtok(line, ",");
    if (token) strcpy(user->username, token);

    token = strtok(NULL, ",");
    if (token) strcpy(user->password, token);

    token = strtok(NULL, ",");
    if (token) strcpy(user->authority, token);

    token = strtok(NULL, ",");
    if (token) strcpy(user->proformanc, token ? token : "0");
}

static void print_masked_password(const char *password) {
    for (int i = 0; i < strlen(password); i++)
        printf("*");
}

static void userlist() {
    FILE *file = fopen(USER_FILE, "r");
    if (!file) { printf("File not found\n"); return; }

    struct Userlist u;
    printf(BMAG "%-20s | %-20s | %-20s\n" reset, "Username", "Passwords", "Authority");

    while (fgets(u.temp, sizeof(u.temp), file)) {
        if (strlen(u.temp) <= 1) continue;
        parse_user_line(&u, u.temp);

        if (strcasecmp(login_usernames, u.username) == 0)
            printf(BHCYN "%-20s" reset " | ", u.username);
        else
            printf(BLU "%-20s" reset " | ", u.username);

        print_masked_password(u.password);
        printf("\t\t\t\b\b\b\b| %-10s\n", u.authority);
    }

    fclose(file);
}

static void Add_user() {
    struct Userlist u;
    char temp[200];
    int exists;

    for (;;) {
        system("clear");
        printf(BLU "Home>Manager>" RED "Add-User\n\n" reset);
        printf(BOLD "Username: " reset);
        getchar();
        fgets(u.username, sizeof(u.username), stdin);
        u.username[strcspn(u.username, "\n")] = 0;

        FILE *file = fopen(USER_FILE, "r");
        if (!file) { printf(RED "File not found\n" reset); return; }

        exists = 0;
        while (fgets(temp, sizeof(temp), file)) {
            if (strlen(temp) <= 1) continue;
            temp[strcspn(temp, "\n")] = 0;
            char *tok = strtok(temp, ",");
            if (tok && strcasecmp(tok, u.username) == 0) {
                printf(RED "\nUser already exists!\n" reset);
                exists = 1;
                break;
            }
        }
        fclose(file);
        if (exists) continue;

        printf(BOLD "\nPassword: " reset);
        scanf("%s", u.password);
        strcpy(u.authority, "Staff");

        file = fopen(USER_FILE, "a");
        if (!file) { printf(RED "Error opening file!\n" reset); return; }
        fprintf(file, "%s,%s,%s\n", u.username, u.password, u.authority);
        fclose(file);

        printf(GRN "\nUser Added Successfully!\n" reset);
        break;
    }
}

static void ChangeAuthority(const char *target_user) {
    FILE *fp = fopen(USER_FILE, "r");
    FILE *tmp = fopen(TEMP_FILE, "w");
    if (!fp || !tmp) { printf("File error\n"); return; }

    struct Userlist u;
    int found = 0, option;

    while (fgets(u.temp, sizeof(u.temp), fp)) {
        if (strlen(u.temp) <= 1) continue;
        parse_user_line(&u, u.temp);

        if (strcasecmp(u.username, target_user) == 0) {
            found = 1;
            printf("\nChange Authority for %s\n1. Staff\n2. Manager\n3. Cancel\nChoice: ", u.username);
            scanf("%d", &option);
            if (option == 1) strcpy(u.authority, "Staff");
            else if (option == 2) strcpy(u.authority, "Manager");
        }

        fprintf(tmp, "%s,%s,%s,%s\n", u.username, u.password, u.authority, u.proformanc);
    }

    fclose(fp); fclose(tmp);
    remove(USER_FILE);
    rename(TEMP_FILE, USER_FILE);

    
    
}

static void UserManager() {
    struct Userlist u;
    char search_user[50];
    int found, delete_flag, is_admin;

    for (;;) {
        printf("\nEnter Username: ");
        scanf("%s", search_user);
        found = delete_flag = is_admin = 0;

        FILE *file = fopen(USER_FILE, "r");
        if (!file) { printf("File error\n"); return; }

        while (fgets(u.temp, sizeof(u.temp), file)) {
            if (strlen(u.temp) <= 1) continue;
            parse_user_line(&u, u.temp);
            if (strcasecmp(u.username, search_user) == 0) {
                found = 1;
                if (strcasecmp(u.authority, "Admin") == 0) is_admin = 1;
                break;
            }
        }
        fclose(file);

        if (!found) { printf("\nUser Not Found\n"); continue; }
        if (is_admin) { printf("Admin account cannot be renamed or deleted.\n"); break; }
        break;
    }

    for (;;) {
        system("clear");
        printf("\nUSER: %s\n", u.username);
        printf("Password: ");
        print_masked_password(u.password);
        printf("\nAuthority: %s\n", u.authority);

        printf("\n1.Show Password\n2.Edit Username\n3.Edit Password\n4.Delete User\n5.Change Authority\n6.Save & Search Again\n7.Save & Exit\n");

        int option;
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Username: %s\nPassword: %s\nAuthority: %s\n", u.username, u.password, u.authority);
                sleep(2);
                break;
            case 2:
                printf("New Username: ");
                scanf(" %[^\n]s", u.username);
                break;
            case 3:
                {
                    char confirm[50];
                    printf("New Password: ");
                    scanf(" %[^\n]s", u.password);
                    printf("Confirm: ");
                    scanf(" %[^\n]s", confirm);
                    if (strcmp(confirm, u.password) != 0) { printf("Password mismatch!\n"); sleep(2); }
                }
                break;
            case 4:
                delete_flag = 1;
                break;
            case 5:
                ChangeAuthority(u.username);
                break;
            case 6:
                {
                    FILE *file = fopen(USER_FILE, "r");
                    FILE *tmp = fopen(TEMP_FILE, "w");
                    struct Userlist tmp_u;
                    char line[200];

                    while (fgets(line, sizeof(line), file)) {
                        parse_user_line(&tmp_u, line);
                        if (strcasecmp(tmp_u.username, u.username) == 0) {
                            if (!delete_flag) fprintf(tmp, "%s,%s,%s,%s\n", u.username, u.password, u.authority, u.proformanc);
                        } else {
                            fprintf(tmp, "%s,%s,%s,%s\n", tmp_u.username, tmp_u.password, tmp_u.authority, tmp_u.proformanc);
                        }
                    }
                    fclose(file); fclose(tmp);
                    remove(USER_FILE);
                    rename(TEMP_FILE, USER_FILE);
                }
                if (option == 5) continue;
                return;
            case 7:
                return;
        }
    }
}

int Manage_function2() {
    int option;
    for (;;) {
        printf(BLU "Home>" reset RED "Manager>\n\n" reset);
        printf("\033[1m1:-Userlist\n2:-Manage User\n3:-Add User\n4:-Return to Menu\033[0m\n");
        fflush(stdin); fflush(stdout);
        scanf("%d", &option);

        switch (option) {
            case 1:
                system("clear");
                printf(BLU "Home>Manager>" reset RED "UserList\n" reset);
                userlist();
                printf("\n\n\nPress Enter to Exit.....");
                getchar(); getchar();
                system("clear");
                break;
            case 2:
                userlist();
                UserManager();
                getchar(); getchar();
                system("clear");
                break;
           
            case 3:
                Add_user();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice\n");
                break;
        }
    }
}
