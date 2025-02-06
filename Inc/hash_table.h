#ifndef HASHTABLE_H
#define HASHTABLE_H

#define MAX_ACTION_NAME_LENGTH 10
#define HASH_TABLE_SIZE 14


typedef struct Action{
    int (*action_handler)(void);
    char action_name[MAX_ACTION_NAME_LENGTH];
    int (*action_helper)(void);
}Action;

extern Action * hash_table[HASH_TABLE_SIZE];

int init_hash_table(void);
int hash_table_insert(Action* p);
Action* hash_table_lookup(char* action_name);

#endif