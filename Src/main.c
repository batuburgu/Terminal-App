#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> 
#include <stdbool.h>
#include <conio.h>
#include "main.h"
#include "command_handler.h"
#include "hash_table.h"

#define CTRLC_ASCII 3
#define BACKSPACE_ASCII 8
#define TAB_ASCII 9
#define ENTER_ASCII 13
#define HELP_WORD_LENGTH 6

#define DEBUG_ENABLE 0
#if (DEBUG_ENABLE == 1)
    #define printD(str1, str2) do{ \
        printf("\nFile:%s->", __FILE__);\
        printf("Line:%d->", __LINE__);\
        printf("Func:%s->", __func__);\
        printf("%s:%s\n", str1,str2);\
    }while(0)
#else
    #define printD(str1, str2) do{} while(0)
#endif


char input_array[MAX_INPUT_SIZE];

// Command Definitions
Command add = {.command_handler = &add_function, .command_name = "add", .command_helper = &add_helper_function};
Command addition = {.command_handler = &add_function, .command_name = "addition", .command_helper = &add_helper_function};
Command subs = {.command_handler = &subs_function, .command_name = "subs", .command_helper = &subs_helper_function};
Command substract = {.command_handler = &subs_function, .command_name = "substract", .command_helper = &subs_helper_function};
Command multi = {.command_handler = &multi_function, .command_name = "multi", .command_helper = &multi_helper_function};
Command multiple = {.command_handler = &multi_function, .command_name = "multiple", .command_helper = &multi_helper_function};
Command multiplication = {.command_handler = &multi_function, .command_name = "multiplication", .command_helper = &multi_helper_function};
Command divd = {.command_handler = &div_function, .command_name = "divd", .command_helper = &div_helper_function};
Command divide = {.command_handler = &div_function, .command_name = "divide", .command_helper = &div_helper_function};
Command division = {.command_handler = &div_function, .command_name = "division", .command_helper = &div_helper_function};
Command clear = {.command_handler = &clear_function, .command_name = "clear", .command_helper = &clear_helper_function};

Command* commands [] = {&add, &addition, &subs, &substract, &multi, &multiple, &multiplication, &divd, &divide, &division, &clear};

#define NUMBER_OF_COMMANDS sizeof(commands)

const char help_command [6] = "--help";

char* list_possible_commands(char input_array[MAX_INPUT_SIZE], Command* commands[NUMBER_OF_COMMANDS], int* arg_count)
{
    int possible_commands [NUMBER_OF_COMMANDS];
    for (int i = 0; i < (int) NUMBER_OF_COMMANDS; i++)
    {
        possible_commands[i] = 1;
    }
     
    int sum = 0;
    int indexes [5];

    printf("\nPossible commands:\n");   
    for (int j = 0; j < (int) NUMBER_OF_COMMANDS; j++)
    {
        for (int k = 0; k < (int) strlen(input_array); k++)
        {
            if (k > (int) strlen(commands[j]->command_name)) // input is longer than command
            {
                printD("Input is longer than command:",commands[j]->command_name);
                possible_commands[j] = 0;
            }
            else if(input_array[k] != commands[j]->command_name[k]) // check for letter difference
            {   
                printD("Letter difference:",commands[j]->command_name);
                possible_commands[j] = 0;
            }
        }
        if (possible_commands[j] == 1)
        {
            indexes[sum] = j;
            sum++;
            printf("%s ",commands[j]->command_name);
        }           
    }

    printf("\n->");

    if (sum == 0)
    {
        printf("No possible commands found!\n");
        for (int i = 0; i < (int) strlen(input_array); i++)
        {
            printf("%c",input_array[i]);
        }
    } 
    else if (sum == 1) 
    {
        int index = indexes[0];
        int wordlength = strlen(commands[index]->command_name);
        for (int i = 0; i < wordlength; i++)
        {
            input_array[i] = commands[index]->command_name[i];
            printf("%c",input_array[i]);
            *arg_count = wordlength;
        }

    } 
    else
    {
        for (int i = 0; i < (int) strlen(input_array); i++)
        {
            printf("%c",input_array[i]);
        }
        
    }
    return input_array;     
}

int parse_command_data(char input_array[MAX_INPUT_SIZE])
{
    Command* pointer_to_command = NULL; 
    char* pointer_array[MAX_INPUT_SIZE];
    int pointer_index = 0;
    int i = 0;
    int command_flag = 0;
    pointer_array[0] = &input_array[0];

    // Parsing console input and taking the pointers of the letters after spaces
    while (input_array[i] != '\0')
    {
        if (i != 0)
        {
            if (input_array[i] == ' ')
            {
                pointer_array[pointer_index] = &input_array[++i];
                pointer_index++;
            }
            else
            {
                i++;
            }
        }
        else
        {
            pointer_array[pointer_index] = &input_array[0];
            i++;
            pointer_index++; 
        }
    }

    // Incorrect input 
    if (pointer_index == 1) 
    {
        pointer_to_command = hash_table_lookup(input_array);
        if (pointer_to_command != NULL)
        {
            pointer_to_command->command_handler(pointer_array);
        }
        else printf("\nNo such command found!\n");
        
        return 0;
    }
    else
    {
        int j = 0;
        int command_word_length = pointer_array[1] - pointer_array[0] - 1;
        char tmp_array [command_word_length];

        for (j = 0; j < command_word_length; j++)
        {
            tmp_array[j] = input_array[j];
        }
        tmp_array[j] = '\0';

        // Searching hash table
        pointer_to_command = hash_table_lookup(tmp_array);
        if (pointer_to_command == NULL)
        {
            printf("No such command found!\n");
            printD("Given command",tmp_array);
            i = 0; 
            return 0;
        }
        else
        {
            printD("Command Found",tmp_array);
            command_flag = 1;    
            
        }     

        if (command_flag == 1) // Check for --help"
        {
            char tmp_array [HELP_WORD_LENGTH];
            int j = 0;
            char* start_of_help = pointer_array[1];
    
            for (j = 0; j < HELP_WORD_LENGTH; j++)
            {
                tmp_array[j] = *(start_of_help + j);
            }
            tmp_array[j] = '\0';

            if (strcmp(tmp_array, "--help") == 0)
            {
                printD("Executed","Helper");
                pointer_to_command->command_helper(pointer_array);
            }
            else
            {
                printD("Executed","Handler");
                pointer_to_command->command_handler(pointer_array);
            }   
        }
    }
}

int main(void)
{
    char c;
    char c_prev = ' ';
    int arg_count = 0;
    
    // Initializing the hash table
    init_hash_table(); 

    // Filling the hash table
    hash_table_insert(&add);
    hash_table_insert(&subs);
    hash_table_insert(&multi);
    hash_table_insert(&divd);
    hash_table_insert(&clear);
    
    printf("->");
    while (arg_count < MAX_INPUT_SIZE)
    {
        c = getch();   
        
        if (c == BACKSPACE_ASCII) // BACKSPACE_ASCII
        {               
            if (arg_count>0) 
            {
                printf("\b \b"); 
                input_array[arg_count] = '\0';
                arg_count --;
            }
        }
        else if (c == CTRLC_ASCII) return 0; // Ctrl + C to exit
        else if (c == TAB_ASCII && c_prev == TAB_ASCII) // List possibilities
        {
            input_array[arg_count] = '\0';
            list_possible_commands(input_array, commands, &arg_count);
            c_prev = ' ';   
        }
        else if (c == TAB_ASCII) // Tab
        {
            c_prev = c;
        }  
        else if (c == ENTER_ASCII) // Enter
        {
            if (arg_count == 0) printf("\n");
            else
            {
                input_array[arg_count] = '\0';
                arg_count = 0;
                parse_command_data(input_array);   
            }
            
            printf("->");
        }
        else if (arg_count == MAX_INPUT_SIZE - 1)
        {
            if (c != BACKSPACE_ASCII || c != ENTER_ASCII)
            {
                input_array[MAX_INPUT_SIZE - 2] = c; 
            }
        }            
        else // Save the char
        {
            input_array[arg_count] = c;
            printf("%c",input_array[arg_count]);
            arg_count++;
        }
    }  
}