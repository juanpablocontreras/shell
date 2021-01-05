
#include "shell.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]){

    if(argc == 1){
        //prompt user mode

        bool quit = false;

        char cmds_str[MAX_NUM_ARGS_PER_CMD*MAX_INPUT_LEN];
        while(!quit){
            //prompt the user for commands
            printf("enter shell commands \n");
            gets(cmds_str);

            quit = parse_and_execute_comands(cmds_str);
        }

        printf("quit has been reached \n");
    }

    return 0;
}