#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"
#include "main.h"
#include "command_handler.h"
#include "hash_table.h"

extern Command* commands;

int add_function(char* pointer_array[])
{
    printf("Add Function\n");
    return 0;
}

int add_helper_function(char* pointer_array[])
{
    printf("Add Helper Function");
    return 0;
}

int subs_function(char* pointer_array[])
{
    printf("Subs Function");
    return 0;
}

int subs_helper_function(char* pointer_array[])
{
    printf("Subs Helper Function");
    return 0;
}

int multi_function(char* pointer_array[])
{
    printf("Multi function");
    return 0;
}

int multi_helper_function(char* pointer_array[])
{
    printf("Multi Helper Function");
    return 0;
}

int div_function(char* pointer_array[])
{
    printf("Div function");
    return 0;
}

int div_helper_function(char* pointer_array[])
{
    printf("Div Helper Function");
    return 0;
}

int clear_function(char* pointer_array[])
{
    system("cls");
    return 1;
}

int clear_helper_function(char* pointer_array[])
{
    printf("Clear Console Helper");
    return 0;
}

int help_function(char* pointer_array[])
{
    int number_of_commands = sizeof(commands);
    
    for (int i = 0; i < number_of_commands; i++)
    {
        printf("Commands: ");
        //printf("%s ", commands[i]->command_name);
    }
    printf("\n");
    
    return 0;
}