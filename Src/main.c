#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> 
#include <stdbool.h>
#include <conio.h>
#include "main.h"
#include "action_handler.h"
#include "hash_table.h"

const char help_command [6] = "--help";
//Linked List Creator
Node* createNode(char data)
{
    Node *new_node = (Node *) malloc(sizeof(Node));
    
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

int parse_action_data(Node* head)
{
    Node* temp = head;
    Node* start_of_input = NULL;
    Action* pointer_to_action = NULL; 
    char tmp_array[10];
    int i = 0;
    int command_flag = 0;

    // Parsing console input searching the action in the hash map
    while(temp->next != NULL)
    {   
        if (temp->data == ' ' || temp->next->next == NULL)
        {
            // End of Input Check
            if (temp->next->next == NULL)
            {
                tmp_array[i] = temp->next->data;
                tmp_array[i+1] = '\0';
            }
            else tmp_array[i] = '\0';

            // Lowercase number
            if ('a' <= tmp_array[0] && tmp_array[0] <='z' && command_flag == 0)
            {
                pointer_to_action = hash_table_lookup(tmp_array);
                if (pointer_to_action == NULL)
                {
                    printf("No such command found!\n");
                    printf("Given Command: %s", tmp_array);
                    i = 0; 
                    return 0;
                }
                else
                {
                    printf("Found command: %s\n", pointer_to_action->action_name);
                    start_of_input = temp->next;
                    i = 0; // Reading new word to tmp_array
                    temp = temp->next;
                    command_flag = 1;    
                }
            }
            // Checking for --help 
            else if (command_flag == 1)
            {
                for (int j = 0; j < i; j++)
                {
                    if (tmp_array[j] != help_command[j])
                    {
                        int function = pointer_to_action->action_handler(start_of_input);
                        return 1;
                    }       
                } 
                int function = pointer_to_action->action_helper();
                return 1;   
            }
            else
            {
                printf("Wrong Input!\n");
                return 0;
            }
        }
        else
        {
            tmp_array[i] = temp->data;
            temp = temp->next;
            i++;
        }    
    }
}

int main(void)
{
    char c;
    char c_prev = ' ';
    int arg_count = 0;
    Node* head = NULL;
    Node* temp = NULL;
    Node * prev_temp = NULL;
    
    // Action Definitions
    Action add = {.action_handler =&add_function, .action_name = "add", .action_helper = &add_helper_function};
    Action subs = {.action_handler =&subs_function, .action_name = "subs", .action_helper = &subs_helper_function};
    Action multi = {.action_handler =&multi_function, .action_name = "multi", .action_helper = &multi_helper_function};
    Action div = {.action_handler =&div_function, .action_name = "div", .action_helper = &div_helper_function};
    
    // Initializing the hash table
    init_hash_table(); 

    // Filling the hash table
    hash_table_insert(&add);
    hash_table_insert(&subs);
    hash_table_insert(&multi);
    hash_table_insert(&div);
    
    while (1)
    {
        c = getch();
        arg_count++;                

        if (c == 8) 
        {   
            printf("\b \b"); // Backspace
            temp = temp->prev;
            temp->next = NULL;

        }
        else if (c == 3) return 0; // Ctrl + C to exit
        // List possibilities
        else if (c == 9 && c_prev == 9)
        {
            printf("Tabtab");
        }
        else if (c == 9)
        {
            c_prev = c;
        }  
        else if (c == 13)
        {
            arg_count = 0;
            parse_action_data(head);   
        }
        else
        {
            if (arg_count == 1)
            {
                head = createNode(c);
                temp = head;
            }
            else
            {
                temp->next = createNode(c);
                temp->next->prev = temp;
                temp = temp->next;
            }
            printf("%c",temp->data);
        }

        
        
    }  
}