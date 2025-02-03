#ifndef IS_h
#define IS_h

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>

//struct for list storing file names.
typedef struct S_LIST
{
    char *string;
    struct S_LIST *link;
}slist;


//for sub_node
typedef struct SUB_NODE
{
    int word_count;     //for storing word_count
    char file_name[50];  //for storing filename
    struct SUB_NODE *s_link;  //for subnode
}sub_node;

//for main node
typedef struct MAIN_NODE
{
    int file_count;
    char word[50];
    struct MAIN_NODE *m_link; //main node link
    sub_node *s_link; //sub node link.
}main_node;

//struct for Hash table
typedef struct HASH_T
{
    int index;
    main_node *h_link; //main_node *link;
}hash_t;

typedef enum 
{
    success,
    failure,
    list_empty,
    word_not_found,
    file_name_not_found
}status;

extern int created_database;
extern int updated_database;

//head pointer.
extern struct S_LIST *head;

/* Functions */
status cla_validation(int argc, char *arv[]);

status create_DB(hash_t HT[]);

status initialize_HT();

main_node* is_word_already_present(char temp_word[], hash_t HT[], int index);

// //then create a new main node 
// main_node* main_node_generator();

void display_HT(hash_t HT[]);

status is_file_name_matching(sub_node *found_sub_node, char file_name[]);

status save_HT(hash_t HT[],char file_name[]);

status file_name_validation(char file_name[]);

status search_HT(hash_t HT[],char word[]);

status valid_hash_file(char filename[]);

void update_HT(hash_t HT[],char file_name[]);

void delete_list_if_file_already_present(char extracted_file_name[]);

#endif
