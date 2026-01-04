#include "login.h"
#include <stdio.h>
#include <string.h>
#include "Manager.h"
#include "Selling.h"
#include "Admin_Manager.h"

int main() {

    for(;;)
    {
    Login();
    
    if(strcmp(login_authority,"Manager")==0)
    {
        Manage_function();
    }

    else if(strcmp(login_authority,"Staff")==0)
    {
        SELLINGmain();
    }

    else if(strcmp(login_authority,"Admin")==0)
    {
        Admin();
    }


}

    return 0;
}
