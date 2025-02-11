#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"
#include "hash_table.h"

Action* hash_table[HASH_TABLE_SIZE];

int hash(const char* action_name)
{
    int length = strlen(action_name);
    int hash_value = 0;
    for (int i = 0; i < length; i++)
    {
        hash_value += action_name[i];
        hash_value = (hash_value * action_name[i]) % HASH_TABLE_SIZE;
    }
    return hash_value;
}

int init_hash_table(void)
{
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }
    return 1;
}

int hash_table_insert(const Action* p)
{
    if (p == NULL)
    {
        printf("Null pointer as argument!");
        return 0;
    }
    else
    {
        int index = hash(p->action_name);

        if (hash_table[index] != NULL)
        {
            printf("Index full! Index:%d",index);
            return 0;
        }
        else
        {
            printf("Inserted! Index:%d\n",index);
            hash_table[index] = p;
            return 1;
        }
    }
}

Action* hash_table_lookup(char* action_name)
{
    int index = hash(action_name);

    // Return the pointer of the struct if the action exists in the table
    if (hash_table[index] != NULL && strcmp(action_name, hash_table[index]->action_name) == 0)
    {
        return hash_table[index];
    }
    // Return NULL if doesn't
    else
    {
        return NULL;
    }
}