#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"
#include "hash_table.h"

Command* hash_table[HASH_TABLE_SIZE];

int hash(const char* command_name)
{
    int length = strlen(command_name);
    int hash_value = 0;
    for (int i = 0; i < length; i++)
    {
        hash_value += command_name[i];
        hash_value = (hash_value * command_name[i]) % HASH_TABLE_SIZE;
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

int hash_table_insert(const Command* p)
{
    if (p == NULL)
    {
        printf("Null pointer as argument!");
        return 0;
    }
    else
    {
        int index = hash(p->command_name);

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

Command* hash_table_lookup(char* command_name)
{
    int index = hash(command_name);

    // Return the pointer of the struct if the command exists in the table
    if (hash_table[index] != NULL && strcmp(command_name, hash_table[index]->command_name) == 0)
    {
        return hash_table[index];
    }
    // Return NULL if doesn't
    else
    {
        return NULL;
    }
}