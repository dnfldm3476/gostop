#include<stdio.h>
#include"set.h"
#include"play.h"
#include"gos.h"
#include"cal.h"
#include"save.h"

int main(void)
{
    game_Setting(true);
    system("clear");
    while(1){
        char *command;
        char buf[10];
        command = buf;
        draw();
        scanf("%s",command);
        command_Interface(command);
    }
    return 0;
}
