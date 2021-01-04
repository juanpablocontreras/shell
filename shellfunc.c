#include "shell.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>


void print_args(int argc, char *argv[]){

    printf("number of arguments: %d \n", argc);

    for(int i=0; i< argc; i++ ){
        printf("argument at %d is: %s \n", i, argv[i]);
    }
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

    print_args(cmds_idx, cmds);
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
