#ifndef LOGIN_H
#define LOGIN_H

extern char login_usernames[20];
extern char login_authority[20];

void Login();
int Login_username(char *login_username);
void load();
void loading_screen();
void loading();

#endif
