#ifndef HASHTABLE_H
#define HASHTABLE_H

#define MAX_Command_NAME_LENGTH 20
#define HASH_TABLE_SIZE 19
#define MAX_INPUT_SIZE 200

typedef struct Command{
    int (*command_handler)(char* pointer_array[MAX_INPUT_SIZE]);
    char command_name[MAX_Command_NAME_LENGTH];
    int (*command_helper)(char* pointer_array[MAX_INPUT_SIZE]);
}Command;

extern Command * hash_table[HASH_TABLE_SIZE];

int hash(const char* Command_name);
int init_hash_table(void);
int hash_table_insert(const Command* p);
Command* hash_table_lookup(char* Command_name);

#endif