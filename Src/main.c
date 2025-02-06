#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> 
#include <stdbool.h>
#include "action_handler.h"
#include "hash_table.h"

//Linked List Structure
typedef struct Node{
    char data;
    struct Node* next;
} Node;

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
    Node * temp = head;
    char tmp_array[10];
    int i = 0;
    Action* pointer_to_action = NULL; 

    // Parsing console input searching the action in the hash map
    while(temp->next != NULL)
    {   
        if (temp->data == ' ')
        {
            char exact_input[i];
            for (int j = 0; j < i; j++)
            {
                exact_input[j] = tmp_array[j];
            }
        
            // Lowercase number
            if ('a' <= exact_input[0] && exact_input[0] <='z')
            {
                printf("%s",exact_input);
                pointer_to_action = hash_table_lookup(exact_input);
                if (pointer_to_action == NULL)
                {
                    printf("Wrong Input!");
                }
                else
                {
                    printf("Found command: %s", pointer_to_action->action_name);
                }

            }
            else
            {
                printf("Wrong Input!");
            }
            continue;
        }
        else
        {
            tmp_array[i] = temp->data;
            temp = temp->next;
            i++;
        }
       
      
    }

    return 0;
}


int main(void)
{
    char c;
    int arg_count = 0;
    Node* head = NULL;
    Node* temp = NULL;
    
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
        c = getchar();
        arg_count++;

        // Taking the terminal input to a LinkedList
        if (arg_count == 1)
        {
            head = createNode(c);
            temp = head;
        }
        else
        {
            temp->next = createNode(c);
            temp = temp->next;
        }
        
        if (c == 10)
        {
            parse_action_data(head);
        }
    } 
    
    
}