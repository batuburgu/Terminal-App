#ifndef HASHTABLE_H
#define HASHTABLE_H

#define MAX_COMMAND_NAME_LENGTH 20
#define HASH_TABLE_SIZE 19
#define MAX_INPUT_SIZE 200

#include "main.h"

typedef struct Command{
    int (*command_handler)(terminal_data* pointer_array[MAX_INPUT_SIZE]);
    const char command_name[MAX_COMMAND_NAME_LENGTH];
    int (*command_helper)(terminal_data* pointer_array[MAX_INPUT_SIZE]);
}Command;

extern Command * hash_table[HASH_TABLE_SIZE];

int hash(const char* Command_name);
int init_hash_table(void);
int hash_table_insert(const Command* p);
Command* hash_table_lookup(char* Command_name);

#endif