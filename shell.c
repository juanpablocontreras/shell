
#include "shell.h"

#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    
    //prompt the user for commands
    char cmds_str[MAX_NUM_ARGS_PER_CMD*MAX_INPUT_LEN];
    printf("enter shell commands \n");
    scanf("%[^\n]",cmds_str);

    //get all parallel commands
    char* parllel_cmds[MAX_NUM_COMMANDS];
    parse_separate_cmds(cmds_str, parllel_cmds);

    char* cmd;
    int cmd_idx = 0;

    cmd = parllel_cmds[cmd_idx++];
    while(cmd!=NULL){
        //create a child to handle the command
        pid_t cpid; 
        int status;

        cpid = fork();
        if(cpid < 0){
            fprintf(stderr, "error: fork could not create a child");
        }else if(cpid == 0){
            //child process

            //sleep(1);
            //printf("child executing: %s\n", cmd);

            //parse command
            char* cmd_argv[MAX_NUM_ARGS_PER_CMD + 1];
            parse_cmd(cmd, cmd_argv);

            //execute command and replace child context
            execvp(cmd_argv[0], cmd_argv);

        }else{
            //parent
            //printf("child created to execute command; %s\n", cmd);
            cmd = parllel_cmds[cmd_idx++];
        }
    }

    //wait for all parralel commands to finish execution
    while(wait(NULL)>0){}

    return 0;
}