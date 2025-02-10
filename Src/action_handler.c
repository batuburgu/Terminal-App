#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"
#include "main.h"
#include "hash_table.h"

int add_function(Node *head)
{
    Node* temp = head;
    printf("Add Function\n");
    while (temp->next != NULL)
    {
        printf("%c", temp->data);
        temp = temp->next;
    }
    return 0;
}

int add_helper_function()
{
    printf("Add Helper Function");
    return 0;
}

int subs_function(Node *head)
{
    printf("Subs Function");
    return 0;
}

int subs_helper_function()
{
    printf("Subs Helper Function");
    return 0;
}

int multi_function(Node *head)
{
    printf("Multi function");
    return 0;
}

int multi_helper_function()
{
    printf("Multi Helper Function");
    return 0;
}

int div_function(Node *head)
{
    printf("Div function");
    return 0;
}

int div_helper_function()
{
    printf("Div Helper Function");
    return 0;
}


