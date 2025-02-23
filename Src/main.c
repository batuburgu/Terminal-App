#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> 
#include <stdbool.h>
#include <conio.h>
#include "main.h"
#include "hash_table.h"
#include "command_handler.h"

#define CTRLC_ASCII 3
#define BACKSPACE_ASCII 8
#define TAB_ASCII 9
#define ENTER_ASCII 13
#define SPACE_ASCII 32
#define HELP_WORD_LENGTH 6

#define DEBUG_ENABLE 1
#if (DEBUG_ENABLE == 1)
    #define printD(str) do{ \
        printf("\nFile:%s->", __FILE__);        \
        printf("Line:%d->", __LINE__);           \
        printf("Func:%s->", __func__);            \
        printf("Log:%s\n", str);              \
    }while(0)
#else
    #define printD(str) do{} while(0)
#endif

#define COMMAND_CREATOR( handler_function, name, helper_function )      \
    {                                                                    \
     .command_handler = handler_function,                                 \
     .command_name = name,                                                 \
     .command_helper = helper_function                                      \
    };

// Declaration of commands
const Command add = COMMAND_CREATOR(&add_function, "add", &add_helper_function);
const Command addition = COMMAND_CREATOR(&add_function, "addition", &add_helper_function);
const Command subs = COMMAND_CREATOR(&subs_function, "subs", &subs_helper_function);
const Command substract = COMMAND_CREATOR(&subs_function, "substract", &subs_helper_function);
const Command multi = COMMAND_CREATOR(&multi_function, "multi", &multi_helper_function);
const Command multiple = COMMAND_CREATOR(&multi_function, "multiple", &multi_helper_function);
const Command multiplication = COMMAND_CREATOR(&multi_function, "multiplication", &multi_helper_function);
const Command divd = COMMAND_CREATOR(&div_function, "divd", &div_helper_function);
const Command divide = COMMAND_CREATOR(&div_function, "divide", &div_helper_function);
const Command division = COMMAND_CREATOR(&div_function, "division", &div_helper_function);
const Command clear = COMMAND_CREATOR(&clear_function, "clear", &clear_helper_function);
const Command help = COMMAND_CREATOR(&help_function, "help", &clear_helper_function);

const Command* commands [] = {&add, &addition, &subs, &substract, &multi, &multiple, &multiplication, &divd, &divide, &division, &clear, &help};

// Global Variables
char input_array[MAX_INPUT_SIZE];
const char help_command [] = "--help";
const int NUMBER_OF_COMMANDS = sizeof(commands) / sizeof(Command*);

terminal_data* add_new_data(char* pointer)
{
    terminal_data *new_data = (terminal_data *) malloc(sizeof(terminal_data));
    
    new_data->data_pointer = pointer;
    new_data->word_length = 0;
    return new_data;
}

char* list_possible_commands(char input_array[MAX_INPUT_SIZE], const Command* command_list[NUMBER_OF_COMMANDS], int* arg_count)
{
    int possible_commands [NUMBER_OF_COMMANDS];
    for (int i = 0; i < (int) NUMBER_OF_COMMANDS; i++)
    {
        possible_commands[i] = 1;
    }
     
    int sum = 0;
    int indexes [NUMBER_OF_COMMANDS];

    printf("\nPossible commands:\n");   
    for (int j = 0; j < (int) NUMBER_OF_COMMANDS; j++)
    {
        for (int k = 0; k < (int) strlen(input_array); k++)
        {
            if (k > (int) strlen(command_list[j]->command_name) && possible_commands[j] == 1) // input is longer than command
            {
                printD("Input is longer than command");
                possible_commands[j] = 0;
            }
            else if (input_array[k] != command_list[j]->command_name[k] && possible_commands[j] == 1) // check for letter difference
            {   
                printD("Letter difference");
                possible_commands[j] = 0;
            }
        }
        if (possible_commands[j] == 1) // Displays the possible commands and saves their indexes
        {
            indexes[sum] = j;
            sum++;
            printf("%s ",command_list[j]->command_name);
        }           
    }

    if (sum == 0) // No possible commands found 
    {
        printf("No possible commands found!\n");
        printf("\n->");
        for (int i = 0; i < (int) strlen(input_array); i++)
        {
            printf("%c",input_array[i]);
        }
        
    } 
    else if (sum == 1) // There is only one possible command, save the possible command to input_array and display it again
    {
        int index = indexes[0];
        int wordlength = strlen(command_list[index]->command_name);
        printD("One command found");
        printf("\n->");
        for (int i = 0; i < wordlength; i++)
        {
            input_array[i] = command_list[index]->command_name[i];
            printf("%c",input_array[i]); 
        }
        *arg_count = wordlength;
        
    } 
    else // More than one possible commands, display the current input to screen
    {
        printf("\n->");
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

    terminal_data* pointer_array[MAX_INPUT_SIZE];
    pointer_array[0] = add_new_data(&input_array[0]);

    int i = 1;
    int command_flag = 0;
    int length = 1;
    int number_of_inputs = 1;

    // Parsing console input and taking the pointers of the letters after spaces
    while (input_array[i] != '\0')
    {
        if (input_array[i] == SPACE_ASCII && input_array[i+1] != SPACE_ASCII)
        {   
            pointer_array[number_of_inputs - 1]->word_length = length;
            length = 1;

            pointer_array[number_of_inputs] = add_new_data(&input_array[++i]);
            number_of_inputs++;
            
        }
        else if (input_array[i] != SPACE_ASCII)
        {
            i++;
            length++;
        }
        else
        {
            i++;
        }
        
    }
    pointer_array[number_of_inputs-1]->word_length = length; // assigning final input length

    // Command only and incorrect inputs
    if (number_of_inputs == 1) 
    {
        int command_length = pointer_array[0]->word_length;
        char tmp_array [command_length];
        for (int j = 0; j < command_length; j++)
        {
            tmp_array[j] = input_array[j];
        }

        printf("Input arr:%s", tmp_array);
        pointer_to_command = hash_table_lookup(tmp_array);
        if (pointer_to_command != NULL)
        {
            pointer_to_command->command_handler(pointer_array);
        }
        else printf("\nNo such command found!\n");
        
        return 0;
    }
    else
    {
        printD("Else");
        int j = 0;
        int command_word_length = pointer_array[0]->word_length;
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
            printD("Given command");
            i = 0; 
            return 0;
        }
        else
        {
            printD("Command Found");
            command_flag = 1;    
            
        }     

        if (command_flag == 1) // Check for --help"
        {
            char tmp_array [HELP_WORD_LENGTH];
            int j = 0;
            char* start_of_help = pointer_array[1]->data_pointer;
    
            for (j = 0; j < HELP_WORD_LENGTH; j++)
            {
                tmp_array[j] = *(start_of_help + j);
            }
            tmp_array[j] = '\0';

            if (strcmp(tmp_array, "--help") == 0)
            {
                printD("Executed Helper");
                pointer_to_command->command_helper(pointer_array);
            }
            else
            {
                printD("Executed Handler");
                pointer_to_command->command_handler(pointer_array);
            }   
        }
    }
    return 0;
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
    hash_table_insert(&help);

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
                printf("\n");
                input_array[arg_count] = '\0';
                arg_count = 0;
                parse_command_data(input_array);   
            }
            
            printf("\n->");
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