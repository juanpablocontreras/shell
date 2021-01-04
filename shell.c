
#include "shell.h"

#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    //one command
    //
    
    //prompt the user for commands
    char cmds_str[MAX_NUM_ARGS_PER_CMD*MAX_INPUT_LEN];
    printf("enter shell commands \n");
    scanf("%[^\n]",cmds_str);

    //fork to create a child process that will take care of command
    pid_t cpid; 
    int status;

    cpid = fork();

    if(cpid < 0){
        fprintf(stderr, "error: fork could not create a child");
    }else if(cpid == 0){
        //child process

        //parse input
        char* cmd_argv[MAX_NUM_ARGS_PER_CMD + 1];
        parse_cmd(cmds_str, cmd_argv);

        //execute command
        execvp(cmd_argv[0], cmd_argv);

    }else{
        //parent
        //waitpid(cpid, &status, 0);
        //printf("child process finished\n");
        sleep(2);
    }
    
    return 0;
}