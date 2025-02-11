#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> 
#include <stdbool.h>
#include <conio.h>
#include "main.h"
#include "command_handler.h"
#include "hash_table.h"

#define CTRLC 3
#define BACKSPACE 8
#define TAB 9
#define ENTER 13

char input_array[MAX_INPUT_SIZE];

// Command Definitions
const Command add = {.command_handler = &add_function, .command_name = "add", .command_helper = &add_helper_function};
const Command addition = {.command_handler = &add_function, .command_name = "addition", .command_helper = &add_helper_function};
const Command subs = {.command_handler = &subs_function, .command_name = "subs", .command_helper = &subs_helper_function};
const Command substrcommand = {.command_handler = &subs_function, .command_name = "substrcommand", .command_helper = &subs_helper_function};
const Command multi = {.command_handler = &multi_function, .command_name = "multi", .command_helper = &multi_helper_function};
const Command multiple = {.command_handler = &multi_function, .command_name = "multiple", .command_helper = &multi_helper_function};
const Command multiplication = {.command_handler = &multi_function, .command_name = "multiplication", .command_helper = &multi_helper_function};
const Command divd = {.command_handler = &div_function, .command_name = "divd", .command_helper = &div_helper_function};
const Command divide = {.command_handler = &div_function, .command_name = "divide", .command_helper = &div_helper_function};
const Command division = {.command_handler = &div_function, .command_name = "division", .command_helper = &div_helper_function};
const Command clear = {.command_handler = NULL, .command_name = "clear", .command_helper = &clear_console};

Command* commands [] = {&add,&addition, &subs, &substrcommand, &multi, &multiple, &multiplication, &divd, &divide, &division, &clear};

#define NUMBER_OF_COMMANDS sizeof(commands)

const char help_command [6] = "--help";

/*int list_possible_commands(char input_array[MAX_INPUT_SIZE], command* commands[NUMBER_OF_COMMANDS])
{
    Node* temp = head;
    char tmp_array[MAX_command_NAME_LENGTH];
    int flag = 1; // print command flag
    int i = 0;

    printf("\nPossible commands:\n");   

    while (temp->next != NULL)
    {
        if (temp->next->next == NULL)
        {
            tmp_array[i] = temp->data;
            tmp_array[++i] = temp->next->data;
            tmp_array[i+1] = '\0';
            temp = temp->next;
        }
        else
        {
            tmp_array[i] = temp->data;
            temp = temp->next;
            i++;
        }
    }
    for (int j = 0; j < NUMBER_OF_commandS; j++)
    {
        flag = 1; // print the command if 1 
        for (int k = 0; k < (int) strlen(tmp_array); k++)
        {
            if (k > (int) strlen(commands[j]->command_name)) // input is longer than command
            {
                flag = 0;
            }
            else if(tmp_array[k] != commands[j]->command_name[k]) // check for letter difference
            {   
                flag = 0;
            }
        }
        if (flag)
        {
            printf("%s ",commands[j]->command_name);
        }   
    }
    printf("\n"); // new input line
    return 0;     
}*/

int parse_command_data(char input_array[MAX_INPUT_SIZE])
{
    Command* pointer_to_command = NULL; 
    char* pointer_array[MAX_INPUT_SIZE];
    int pointer_index = 0;
    int i = 0;
    int command_flag = 0;

    // Parsing console input and taking the pointers of the letters after spaces
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

    if (command_flag == 0) // Check for command
    {
        int command_word_length = pointer_array[1] - pointer_array[0];
        printf("%p - %p",pointer_array[2], pointer_array[1]);
        char tmp_array [command_word_length];
        
        for (int j = 0; j < command_word_length; j++)
        {
            tmp_array[j] = input_array[j];
            printf("%c",input_array[j]);
        }
        pointer_to_command = hash_table_lookup(tmp_array);
        if (pointer_to_command == NULL)
        {
            printf("No such command found!\n");
            printf("Given Command: %s", tmp_array);
            i = 0; 
            return 0;
        }
        else
        {
            printf("Found command: %s\n", pointer_to_command->command_name);
            command_flag = 1;    
            
        }     
    }
    else if (command_flag == 1) // Check for --help
    {
        int help_word_length = pointer_array[2] - pointer_array[1];
        char tmp_array [help_word_length];
        
        for (int j = 0; j < help_word_length; j++)
        {
            tmp_array[j] = input_array[j];
        }

        if (strcmp(tmp_array, "--help") == 0)
        {
            pointer_to_command->command_helper(pointer_array);
        }
        else
        {
            pointer_to_command->command_handler(pointer_array);
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
    
    while (1)
    {
        c = getch();               
        
        if (c == BACKSPACE) // Backspace
        {   
            printf("\b \b"); 
            input_array[arg_count] = ' ';
            arg_count --;

        }
        else if (c == CTRLC) return 0; // Ctrl + C to exit
        else if (c == TAB && c_prev == TAB) // List possibilities
        {
            //list_possible_commands(input_array, commands);
            c_prev = ' ';   
        }
        else if (c == TAB) // Tab
        {
            c_prev = c;
        }  
        else if (c == ENTER) // Enter
        {
            arg_count = 0;
            parse_command_data(input_array);   
        }
        else // Save the char
        {
            input_array[arg_count] = c;
            printf("%c",input_array[arg_count]);
            arg_count++;
        }
    }  
}