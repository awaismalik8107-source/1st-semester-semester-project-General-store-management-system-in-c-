#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include "Align.h"

void moving_to_vcenter()
{
    struct winsize w;

    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
    {
        
        for(int i = 0; i < 10; i++)
            printf("\n");
        return;
    }

    int rows = w.ws_row;
    int newrows = (rows > 30) ? (rows - 30)/2 : 0;

    for(int i = 0; i < newrows; i++)
        printf("\n");
}


void move_to_hcenter(const char *text)
{
    struct winsize w;
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
    {
        printf("%s", text);  
        return;
    }

    int cols = w.ws_col;
    int ncol= (cols > (int)strlen(text)) ? (cols - strlen(text))/2 : 0;

    for(int i = 0; i < ncol; i++)
        printf(" ");  

    printf("%s", text);  
}


void move_c_hcenter()
{
    struct winsize w;
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
    {
        
        return;
    }

    int cols = w.ws_col;
    int ncol= (cols-10)/2;

    for(int i = 0; i < ncol; i++)
        printf(" ");  

    
}

void move_c_hcenter2()
{
    struct winsize w;
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
    {
        
        return;
    }

    int cols = w.ws_col;
    int ncol= (cols-30)/2;

    for(int i = 0; i < ncol; i++)
        printf(" ");  

    
}