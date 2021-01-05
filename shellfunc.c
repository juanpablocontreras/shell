#include "shell.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


void print_args(int argc, char *argv[]){

    printf("number of arguments: %d \n", argc);

    for(int i=0; i< argc; i++ ){
        printf("argument at %d is: %s \n", i, argv[i]);
    }
}

///
//Takes a string of commands and their arguments and executes each on its own process
//cmds_str format: comand1 arg1 ... argn; comand2 arg1 ... argn; ...
//returns true if the quit command is found, false otherwise
bool parse_and_execute_comands(char* cmds_str){

    //quit comand flag
    bool quit = false;

    //parse all parallel commands
    char* parllel_cmds[MAX_NUM_COMMANDS];
    parse_separate_cmds(cmds_str, parllel_cmds);

    //execute comands in their own process
    int cmd_idx = 0;
    char* cmd = parllel_cmds[cmd_idx++];
    while(cmd!=NULL){

        if(!is_cmd_quit(cmd)){
            //create a child to handle the command
            pid_t cpid; 
            int status;

            cpid = fork();
            if(cpid < 0){
                fprintf(stderr, "error: fork could not create a child");
            }else if(cpid == 0){
                //child process

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

        }else{
            //comand is quit
            quit = true;
            cmd = parllel_cmds[cmd_idx++];
        }
    }
        
    //wait for all parralel commands to finish execution
    while(wait(NULL)>0){}

    return quit;
}

void parse_separate_cmds(char* cmds_str, char** cmds){
    //takes a string representing several commands separated by ";"
    //returns an array of strings in cmds, where each element is a command with its own arguments
    //
    //cmds must be initialized with size [MAX_NUM_COMMANDS + 1][*] to allow for null pointer termination

    char* temp_cmd;
    temp_cmd = strtok(cmds_str, ";");

    int cmds_idx = 0;
    while(temp_cmd != NULL){
        if(cmds_idx > MAX_NUM_COMMANDS){
            fprintf(stderr, "too many comands at once");
            return;
        }

        cmds[cmds_idx++] = temp_cmd;
        temp_cmd = strtok(NULL, ";");
    }

    //terminate array with null pointer
    cmds[cmds_idx++] = NULL;

    //print_args(cmds_idx, cmds);
}

void parse_cmd(char* cmd_str, char** argv){
    //takes a string representing a command and its arguments separated by " "
    //returns an array of strings in argv. the array at zero is the command name. 
    //then, each remaining element of the array is an argument to the command
    //finally, argv is terminated by putting a null pointer
    //
    //argv must be of size [MAX_NUM_ARGS_PER_CMD+1][*] to allow for the null value at the end
    //example: char* argv[MAX_NUM_ARGS_PER_CMD + 1];
    
    char* cmds_temp;
    cmds_temp = strtok(cmd_str, " ");

    //build array of cmd name and arguments
    int argv_idx = 0;
    while(cmds_temp != NULL){
        
        if(argv_idx > MAX_NUM_ARGS_PER_CMD){
            fprintf(stderr, "too many command arguments");
            return;
        }

        argv[argv_idx++] = cmds_temp;
        cmds_temp = strtok(NULL, " ");
    }

    //put a null pointer as last element of array
    argv[argv_idx++] = NULL;

    //print_args(argv_idx, argv);
}

bool is_cmd_quit(char* cmd){
    if(strstr(cmd, "quit")){
        return true;
    }
    return false;
}
