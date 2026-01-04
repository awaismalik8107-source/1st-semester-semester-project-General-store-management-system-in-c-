#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "COLORS.c"
#include "Align.h"
#define LIST 1800

struct User {
    char temp[200];
    char name[30];
    char password[30];
    char authority[20];
    char perform[20];
};

struct User Userp[LIST];

void SortingU(int count) {
    struct User Temp;
    int flag1;

    for (int i = 0; i < count - 1; i++) {
        flag1 = 0;
        for (int j = 0; j < count - 1 - i; j++) {
            if (atoi(Userp[j].perform) < atoi(Userp[j + 1].perform)) {
                Temp = Userp[j];
                Userp[j] = Userp[j + 1];
                Userp[j + 1] = Temp;
                flag1 = 1;
            }
        }
        if (flag1 == 0) break;
    }
}

void Filterer() {
    int count = 0;
    FILE *Userlist = fopen("Userlist.csv", "r");
    if (!Userlist) {
        printf(RED "Userlist.csv not found!\n" reset);
        return;
    }

    struct User a1;
    char line[1024];

    while (fgets(line, sizeof(line), Userlist)) {
        line[strcspn(line, "\n")] = 0;
        char *tok = strtok(line, ",");
        if (!tok) continue;

        strncpy(a1.name, tok, sizeof(a1.name)-1); a1.name[sizeof(a1.name)-1]='\0';
        tok = strtok(NULL, ",");
        strncpy(a1.password, tok ? tok : "", sizeof(a1.password)-1); a1.password[sizeof(a1.password)-1]='\0';
        tok = strtok(NULL, ",");
        strncpy(a1.authority, tok ? tok : "", sizeof(a1.authority)-1); a1.authority[sizeof(a1.authority)-1]='\0';
        tok = strtok(NULL, ",");
        strncpy(a1.perform, tok ? tok : "", sizeof(a1.perform)-1); a1.perform[sizeof(a1.perform)-1]='\0';

        Userp[count++] = a1;
    }

    fclose(Userlist);

    SortingU(count);

    printf(MAG "+%-5s +%-25s +%-20s +%-15s +%-10s+\n" reset, "No.", "Username", "Password", "Authority", "Profit");

    for (int i = 0; i < count; i++) {
        printf("%-5d %-25s %-20s %-15s %-10s\n", i + 1, Userp[i].name, Userp[i].password, Userp[i].authority, Userp[i].perform);
    }

   
   


void wait_for_enter() {
    int c;
    
    while ((c = getchar()) != '\n' && c != EOF);

    
    printf(BLU "\nPress Enter to continue..." reset);

    
    getchar();
}



}
