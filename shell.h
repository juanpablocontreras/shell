//Global constants
extern const int MAX_NUM_COMMANDS; //maximum of commands per entry
extern const int MAX_NUM_ARGS_PER_CMD; //maximum 8 arguments for each command. this includes the command name
extern const int MAX_INPUT_LEN; //maximum 32 characters in an input 

//function declarations
void print_args(int argc, char *argv[]);
void parse_cmd(char* cmd_str, char** argv);
