#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "command_handler.h"
#include "hash_table.h"

extern const Command* commands[];
extern const int NUMBER_OF_COMMANDS;

#define HYPHEN 45
#define MINUS 109

#define EIGHT_BIT_IDENTIFIER "-q"  // ASCII value for 'q'
#define SHORT_IDENTIFIER "-s"     // ASCII value for 's'
#define DEFAULT_IDENTIFIER "-d"   // ASCII value for 'd'
#define LONG_IDENTIFIER "-l"      // ASCII value for 'l'
#define FLOAT_IDENTIFIER "-f"     // ASCII value for 'f'
#define UNSIGNED_IDENTIFIER "-u"  // ASCII value for 'u'

#define DEFAULT_CASE 0
#define EIGHT_BIT_CASE 1
#define SHORT_INT_CASE 2
#define LONG_INT_CASE 3
#define FLOAT_CASE 4

int add_function(terminal_data* pointer_array[])
{
    int i = 1;
    long long int new_input = 0;
    int unsigned_flag = 0;
    int datatype = 0;
    int datatype_flag = 0;

    int64_t int_result = 0;
    uint64_t uint_result = 0;
    float float_result = 0;

    while (pointer_array[i]->data_pointer !=  NULL)
    {
        int wordlength = pointer_array[i]->word_length;
        char tmp_array [wordlength + 1];

        // check for signed unsigned 
        if (*(pointer_array[i]->data_pointer) == HYPHEN && *(pointer_array[i]->data_pointer + 1) == UNSIGNED_IDENTIFIER && (i == 1 || i == 2))
        {
            unsigned_flag = 1;
        }
       
        // check for data type
        else if (*(pointer_array[i]->data_pointer) == HYPHEN && (i == 1 || i == 2) && !datatype_flag)
        {
            for (int j = 0; j < wordlength; j++)
            {
                tmp_array[j] = *(pointer_array[i]->data_pointer + j);
            }
            tmp_array[wordlength] = '\0';
            if (strcmp(tmp_array, DEFAULT_IDENTIFIER) == 0) 
            {
                datatype = 0;
            } 
            else if (strcmp(tmp_array, EIGHT_BIT_IDENTIFIER) == 0) 
            {
                datatype = 1;
            } 
            else if (strcmp(tmp_array, SHORT_IDENTIFIER) == 0) 
            {
                datatype = 2;
            } 
            else if (strcmp(tmp_array, LONG_IDENTIFIER) == 0) 
            {
                datatype = 3;
            } 
            else if (strcmp(tmp_array, FLOAT_IDENTIFIER) == 0) 
            {
                datatype = 4;
            } 
            else {
                printf("Unexpected Identifier\n");
            }
            datatype_flag = 1;
        }
        // Process numbers
        else
        {
            for (int j = 0; j < wordlength; j++)
            {
                tmp_array[j] = *(pointer_array[i]->data_pointer + j);
            }
            tmp_array[wordlength] = '\0';

            if (!unsigned_flag) // signed integer
            {
                switch (datatype)
                {
                case DEFAULT_CASE:
                    new_input = strtol(tmp_array, NULL, 10);
                    
                    if (int_result + new_input >= INT32_MAX) int_result = INT32_MAX - 1;
                    else if(int_result + new_input <= INT32_MIN) int_result = INT32_MIN + 1;
                    else int_result += new_input;

                    if (pointer_array[i+1]->data_pointer == NULL)
                    {
                        printf("Result:%lld",int_result);
                    }
                    
                    break;
                case EIGHT_BIT_CASE:
                    new_input = strtol(tmp_array, NULL, 10);
                    if (int_result + new_input >= INT8_MAX) int_result = INT8_MAX - 1;
                    else if(int_result + new_input <= INT8_MIN) int_result = INT8_MIN;
                    else int_result += (int8_t) new_input;

                    if (pointer_array[i+1]->data_pointer == NULL)
                    {
                        printf("Result:%lld",int_result);
                    }

                    break;
                case SHORT_INT_CASE:
                    new_input = strtol(tmp_array, NULL, 10);
                    
                    if (int_result + new_input >= INT16_MAX) int_result = INT16_MAX - 1;
                    else if(int_result + new_input <= INT16_MIN) int_result = INT16_MIN;
                    else int_result += (int16_t) new_input;

                    if (pointer_array[i+1]->data_pointer == NULL)
                    {
                        printf("Result:%lld",int_result);
                    }

                    break;
                case LONG_INT_CASE:
                    new_input = strtol(tmp_array, NULL, 10);
                    int_result += new_input;

                    if (pointer_array[i+1]->data_pointer == NULL)
                    {
                        printf("Result:%lld",int_result);
                    }

                    break;
                case FLOAT_CASE:
                    float_result += strtof(tmp_array, NULL);
                    if (pointer_array[i+1]->data_pointer == NULL)
                    {
                        printf("Result:%f",float_result);
                    }
                default:
                    break;
                }
            }
            else // unsigned integer
            {
                switch (datatype_flag)
                {
                case DEFAULT_CASE:
                    new_input = strtoul(tmp_array, NULL, 10);
                    uint_result += (uint8_t) new_input;
                    if (uint_result + new_input >= UINT32_MAX) uint_result = UINT32_MAX - 1;
                    
                    if (pointer_array[i+1]->data_pointer == NULL)
                    {
                        printf("Result:%lld",uint_result);
                    }
                    
                    break;
                case EIGHT_BIT_CASE:
                    new_input = strtoul(tmp_array, NULL, 10);
                    uint_result += (uint8_t) new_input;
                    if (uint_result + new_input>= UINT8_MAX) uint_result = UINT8_MAX - 1;

                
                    if (pointer_array[i+1]->data_pointer == NULL)
                    {
                        printf("Result:%lld",uint_result);
                    }

                    break;
                case SHORT_INT_CASE:
                    new_input = strtoul(tmp_array, NULL, 10);
                    uint_result += (uint16_t) new_input;
                    if (uint_result +new_input >= UINT16_MAX) uint_result = UINT16_MAX - 1;

                    if (pointer_array[i+1]->data_pointer == NULL)
                    {
                        printf("Result:%lld",uint_result);
                    }

                    break;
                case LONG_INT_CASE:
                    uint_result += strtoul(tmp_array, NULL, 10);

                    if (pointer_array[i+1]->data_pointer == NULL)
                    {
                        printf("Result:%lld",uint_result);
                    }

                    break;
                case FLOAT_CASE:
                    float_result += strtof(tmp_array, NULL);
                    if (pointer_array[i+1]->data_pointer == NULL)
                    {
                        printf("Result:%f",float_result);
                    }
                default:
                    break;
                } 
            }
        }
        i++;
    }  
    return 0;
}

int add_helper_function(terminal_data* pointer_array[])
{
    printf("Add Helper Function");
    return 0;
}

int subs_function(terminal_data* pointer_array[])
{
    printf("Subs Function");
    return 0;
}

int subs_helper_function(terminal_data* pointer_array[])
{
    printf("Subs Helper Function");
    return 0;
}

int multi_function(terminal_data* pointer_array[])
{
    printf("Multi function");
    return 0;
}

int multi_helper_function(terminal_data* pointer_array[])
{
    printf("Multi Helper Function");
    return 0;
}

int div_function(terminal_data* pointer_array[])
{
    printf("Div function");
    return 0;
}

int div_helper_function(terminal_data* pointer_array[])
{
    printf("Div Helper Function");
    return 0;
}

int clear_function(terminal_data* pointer_array[])
{
    system("cls");
    return 1;
}

int clear_helper_function(terminal_data* pointer_array[])
{
    printf("Clear Console Helper");
    return 0;
}

int help_function(terminal_data* pointer_array[])
{
    for (int i = 0; i < NUMBER_OF_COMMANDS; i++)
    {
        printf("%s ", commands[i]->command_name);
    }
    
    return 0;
}