#include"is.h"

/* Function definitions */
status cla_validation(int argc,char *argv[])
{
    if(argc > 1)
    {
        for(int i=1;i<argc;i++)
        {       
            //if present in current directory then check for extension
            if(strstr(argv[i],".txt") == NULL)
            {
                printf("INFO: \"%s\" FIle is without \".txt\" \n",argv[i]);
            }
            //if it is present then check whether it is empty or not. 
            else
            {
                //check if file is present or not
                FILE *fptr = fopen(argv[i],"r");
                if(fptr == NULL)
                {
                    printf("ERROR : \"%s\" File is not present in current directory\n",argv[i]);
                    continue;
                }
                else
                {
                    fseek(fptr,0,SEEK_END);
                    if(ftell(fptr) == 0)
                    {
                        printf("INFO: \"%s\" This File is Empty\n",argv[i]);
                        continue;   //to next argument validation.
                    }
                    else
                    {
                        //store it into list.
                        //before that traverse and validate if it is already present or not.
                        struct S_LIST *temp = head; 
                        if(head == NULL)
                        {
                            slist *new = malloc(sizeof(slist));
                            if(new == NULL)
                            {
                                printf("ERROR : Node creation failed\n");
                            }
                            new->string = argv[i];
                            new->link = NULL;
                            head = new;
                            printf("INFO: Successful: Inserting file name \"%s\" into File List\n",argv[i]);
                            continue; 
                        }
                        else
                        {
                            int flag =0;
                            while(temp != NULL)
                            {
                                if(strcmp(temp->string,argv[i]) == 0)
                                {
                                    printf("INFO: \"%s\" This File is repeated, So it will not store into LINKED LIST\n",argv[i]);
                                    //return failure;
                                    flag = 1;
                                    break;
                                }
                                temp = temp->link;
                            }
                            if(flag == 1)
                            {
                                //reset the flag and continue the outer loop
                                flag = 0;
                                continue;
                            }
                            if(temp == NULL)
                            {
                                //create new node and update argv[i]
                                slist *new = malloc(sizeof(slist));
                                if(new == NULL)
                                {
                                    printf("ERROR : Node creation failed\n");
                                }
                                //update newly created node string and link part.
                                new->link = NULL;
                                new->string = argv[i];

                                //travers to insert at last 
                                temp = head;
                                while(temp->link !=  NULL)
                                {
                                    temp = temp->link;
                                }
                                temp->link = new;
                                printf("INFO: Successful: Inserting file name \"%s\" into File List\n",argv[i]);
                                continue;
                            }
                        }
                        fclose(fptr);
                    }
                }
            }
        }
    }
    else
    {
        printf("Invalid Arguments\n");
        return failure;
    }
    
    //after preparing list of file names print list.
    if(head == NULL)
    {
        printf("->NUL\n");
    }
    else
    {
        slist *print_list = head;
        while(print_list != NULL)
        {
            printf("->");
            printf("%s",print_list->string);
            print_list = print_list->link;
        }
        printf("\n");
    }
    return success;
}

status initialize_HT(hash_t HT[])
{
    //initialliaize Hash Table with index and NULL for the first time. 
    for(int i=0; i<27; i++)
    {
        HT[i].index = i;
        HT[i].h_link = NULL;
    }
    return success;
}

main_node* is_word_already_present(char temp_word[], hash_t HT[], int index)
{
    main_node *temp = HT[index].h_link;
    while(temp != NULL)
    {
        //compare every word of main node with temp_word
        if(strcmp(temp_word,temp->word) == 0)
        {
            //if matching return success;
            return temp;
        }
        temp = temp->m_link;
    }
    //if word is not matched and temp reaches NULL then return word not found
    return NULL;
}

status is_file_name_matching(sub_node *found_sub_node, char file_name[])
{
    while(found_sub_node != NULL)
    {
        if(strcmp(found_sub_node->file_name,file_name) == success)
        {
            //increment word count here only & exit by returning success
            found_sub_node->word_count += 1;
            return success; 
        }
        found_sub_node = found_sub_node->s_link;
    }    
    return failure;
}

void display_HT(hash_t HT[])
{
    main_node *m_temp = NULL;
    sub_node *s_temp = NULL;
    printf("Index     word      File count\n");
    printf("------------------------------\n");
    for(int i = 0; i < 27; i++)
    {
        m_temp = HT[i].h_link;
        while(m_temp != NULL)
        {
            // printf("Index[%d]-\t", i);
            // printf(" ->Word : %-7s\t",m_temp->word);
            // printf(" ->File Count : %d\t",m_temp->file_count);
            printf("[%d]-\t", i);
            printf("%-9s\t",m_temp->word);
            printf("%-5d\t",m_temp->file_count);
            //intialize sub node link.
            s_temp = m_temp->s_link;
            while(s_temp != NULL)
            {
                printf(" ->Word Count : %-5d",s_temp->word_count);
                printf(" ->File Name : %-5s\t",s_temp->file_name);
                s_temp = s_temp->s_link;
            }
            m_temp = m_temp->m_link;
        printf("\n");
        }
    }
    printf("------------------------------\n");
}

status create_DB(hash_t HT[])
{
    //check if head == NULL or not
    if(head == NULL)
    {
        printf("INFO: File list is empty\n");
        return failure;
    }

    //take temp variable for traverseing list of file names.
    slist *temp = head;
    
    //again reinitializse temp with head
    temp = head;

    while(temp != NULL)
    {
        //first get the file name from the list and open the file.
        FILE *fp = fopen(temp->string,"r");

        //error handling. 
        if(fp == NULL)
        {   
            printf("ERROR :  %s File opening failed\n",temp->string);
            return failure;
        }   

        //start reading from the file
        char *temp_word = malloc(100);
        while(fscanf(fp,"%s",temp_word) > 0)
        {
            //now find the index for first alphabet in word i.e extracted.
            int index;
            //tolower(temp_word[0]);
            if(temp_word[0] >= 'A' && temp_word[0] <= 'Z')
            {
                index = temp_word[0] - 65;
            }
            else if(temp_word[0] >= 'a' && temp_word[0] <= 'z')
            {
                index = temp_word[0] - 'a';
            }
            else
            {
                index = 26;
            }

            //case - 1
            //if index is available i.e == NULL
            if(HT[index].h_link == NULL)  
            {
                //then create a new main node 
                main_node *new_m_node = malloc(sizeof(main_node));

                //error handling
                if(new_m_node == NULL)
                {
                    printf("ERROR : Creating new Main node Failed\n");
                    return failure;
                }
                //create sub-node
                sub_node *new_s_node = malloc(sizeof(sub_node));

                //error handling for memory created or not
                if(new_s_node == NULL)
                {
                    printf("ERROR : Creating new sub node failed\n");
                    return failure;
                }

                //first update sub-node
                new_s_node->word_count  = 1;
                // new_s_node->file_name  = temp->string;
                strcpy(new_s_node->file_name, temp->string);
                new_s_node->s_link  = NULL;

                //now update main node parts which is created priviously.
                new_m_node->file_count = 1;
                strcpy(new_m_node->word,temp_word);
                new_m_node->m_link = NULL;
                new_m_node->s_link = new_s_node;

                //now establish link with hash table and main node.
                HT[index].h_link = new_m_node; 
            }
            //case - 2
            //Hash table link != NULL i.e already some data(words) are present
            else
            {
                main_node *found_main_node = NULL;
                //case - 1
                //check for word already present or not in the main node
                if( (found_main_node = is_word_already_present(temp_word, HT, index) ) != NULL)
                {
                    //if already present --> check for file_name matching or not
                    //if filename matching increment the word count
                    if(is_file_name_matching(found_main_node->s_link,temp->string) == success)
                    {
                        
                    }
                    //else if file name not matched 
                    //create new subnode update that file name , word_count, link part
                    //also incremnt the file count in main node.
                    else
                    {
                        //creating a new sub-node
                        sub_node *new_sub_node = malloc(sizeof(sub_node));

                        //error handling
                        if(new_sub_node == NULL)
                        {
                            printf("ERROR : creating new sub_node failed\n");
                            return failure;
                        } 

                        new_sub_node->word_count = 1;
                        strcpy(new_sub_node->file_name,temp->string);
                        new_sub_node->s_link = NULL;

                        //traverse to insert the sub_node at last
                        sub_node *traverse_sub_node = found_main_node->s_link;
                        
                        while(traverse_sub_node->s_link != NULL)
                        {
                            traverse_sub_node = traverse_sub_node->s_link;
                        }
                        //now update the newly created sub_node to establish link at the end of same index
                        traverse_sub_node->s_link = new_sub_node;

                        //also incrementing file count on main_node
                        found_main_node->file_count += 1;  
                    }

                }
                //if word is not present then create a new_main_node & sub_node
                else
                {   
                    //then create a new main node 
                    main_node *new_m_node = malloc(sizeof(main_node));

                    //error handling
                    if(new_m_node == NULL)
                    {
                        printf("ERROR : Creating new Main node Failed\n");
                        return failure;
                    }
                    //create sub-node
                    sub_node *new_s_node = malloc(sizeof(sub_node));

                    //error handling for memory created or not
                    if(new_s_node == NULL)
                    {
                        printf("ERROR : Creating new sub node failed\n");
                        return failure;
                    }

                    //first update sub-node
                    new_s_node->word_count  = 1;
                    //new_s_node->file_name  = temp->string;
                    strcpy(new_s_node->file_name, temp->string);
                    new_s_node->s_link  = NULL;

                    //now update main node parts which is created priviously.
                    new_m_node->file_count = 1;
                    strcpy(new_m_node->word,temp_word);
                    new_m_node->m_link = NULL;
                    new_m_node->s_link = new_s_node;

                    //now establish link with  newly created main node and previous main node..
                    //HT[index].link = new_m_node;
                    main_node* insert_main_at_last = HT[index].h_link;
                    
                    //traverse upto last main node and establish the link for new word.
                    while(insert_main_at_last->m_link != NULL)
                    {
                        //update for traversig till last node
                        insert_main_at_last = insert_main_at_last->m_link;
                    } 
                    //now update the new main node address in m_link of already present previous main node
                    insert_main_at_last->m_link = new_m_node;
                }
            }
        }
        temp = temp->link;
    }
    created_database = 1;
    return success;
}

status save_HT(hash_t HT[],char file_name[])
{
    FILE *save_file = fopen(file_name,"w");
    
    //error handling
    if(save_file == NULL)
    {
        printf("Opening save_file failed\n");
        return failure;
    }
    main_node *m_temp = NULL;
    sub_node *s_temp = NULL;
    for(int i = 0; i < 27; i++)
    {
        m_temp = HT[i].h_link;
        while(m_temp != NULL)
        {
            fprintf(save_file,"#%d;%s;%d;",i,m_temp->word,m_temp->file_count);
            // fprintf(save_file,"%s\n",m_temp->word);
            // fprintf(save_file,"#->File Count : %d\n",m_temp->file_count);
            //intialize sub node link.
            s_temp = m_temp->s_link;
            while(s_temp != NULL)
            {
                fprintf(save_file,"%d;%s;",s_temp->word_count,s_temp->file_name);
                // printf(save_file,"#->File Name : - %s\n",s_temp->file_name);
                s_temp = s_temp->s_link;
            }
            m_temp = m_temp->m_link;
            fprintf(save_file,"#\n");
        }
    }
    fclose(save_file);
}

status search_HT(hash_t HT[],char word[])
{   
    int index;
    //find the index 
    if(word[0] >= 'A' && word[0] <= 'Z')
    {
        index = word[0] - 'A';
    }
    else if(word[0] >= 'a' && word[0] <= 'z')
    {
        index = word[0] - 'a';
    }
    else
    {
        index = 26;
    }
    //check index ->link
    main_node *main_node_traverse = HT[index].h_link;

    //traverse trough main nodes.
    while(main_node_traverse != NULL)
    {
        //->word present 
        if(strcmp(main_node_traverse->word,word) == success)
        {
            //initiallise with subnode link of matched main node and start traversing
            printf("word \"%s\" is present in \"%d\" file/files\n",main_node_traverse->word,main_node_traverse->file_count);
            sub_node *sub_node_traverse = main_node_traverse->s_link;
            while(sub_node_traverse != NULL)
            {
                printf("In \"%s\" : the word is present \"%d\" times\n",sub_node_traverse->file_name,sub_node_traverse->word_count);
                sub_node_traverse = sub_node_traverse->s_link;
            }
            return success;
        }
        main_node_traverse = main_node_traverse->m_link;
    }
    //word not present 
    return word_not_found;
}

status file_name_validation(char file_name[])
{
    if(strstr(file_name,".txt") == NULL)
    {
        return  failure;
    }
    return success;
}

status valid_hash_file(char filename[])
{
    FILE *fptr = fopen(filename,"r");

    //error handling 
    if(fptr == NULL)
    {
        printf("ERROR : File opening Failed!\n");
        return failure;
    }

    char ch = getc(fptr);
    if(ch == '#')
    {
        //seek to EOF -1 position to read whether last character is ending with '#' or not. 
        fseek(fptr,-2,SEEK_END);
        ch = getc(fptr);
        if(ch == '#')
        {
            fclose(fptr);
            return success;
        }
        else
        {
            printf("ERROR : File not ending with \'#\' \n");
            return failure;
        }
    }
    else
    {
        printf("ERROR : File not starting with \'#\'\n");
        return failure;
    }
}

void update_HT(hash_t HT[],char file_name[])
{
    FILE *read_file = fopen(file_name,"r");
    //error handling 
    if(read_file == NULL)
    {
        printf("ERROR : File opening Failed!\n");
        return;
    }

    //for main node
    int extracted_index;    //to store index from file
    char extracted_word[50];    //to store word from file
    int extracted_file_count;   //to store file count
    
    //for subnode
    int extracted_word_count;   //to store word count
    char extracted_file_name[50];   //to store file name
    //read from file only --> main node content --> index,word,filecount.  
    while(fscanf(read_file,"#%d;%[^;];%d;",&extracted_index,extracted_word,&extracted_file_count) == 3)
    {
        //check hash table link part is null or not.
        if(HT[extracted_index].h_link == NULL)
        {
            //create a main node and establish link between hash table and created new main node.
            main_node *new_main_node = malloc(sizeof(main_node));

            //validate != Null or not
            if(new_main_node == NULL)
            {
                printf("ERROR: Creating New Main Node Failed\n");
                // return failure;
                return;
            }

            //if memory allocated then update extracted main node data.
            new_main_node->file_count = extracted_file_count;
            strcpy(new_main_node->word,extracted_word); //copy the extracted word.
            new_main_node->m_link = NULL;
            new_main_node->s_link = NULL;
            HT[extracted_index].h_link = new_main_node;

            //now create the subnode based on file count
            while(extracted_file_count)
            {   
                fscanf(read_file,"%d;%[^;];",&extracted_word_count,extracted_file_name);

                delete_list_if_file_already_present(extracted_file_name);

                //create subnode 
                sub_node* new_sub_node = malloc(sizeof(sub_node));
                //error handling
                if(new_sub_node == NULL)
                {
                    printf("ERROR : Createing new sub node failed\n");
                    // return failure;
                    return;
                }
                //if memory allocated update the sub node parts --> wordcount, filename,link part
                new_sub_node->word_count = extracted_word_count;
                strcpy(new_sub_node->file_name,extracted_file_name);
                new_sub_node->s_link = NULL; 
                //check if new_main_node of s_link == NULL or not
                //if = NULL? 
                if(new_main_node->s_link == NULL)
                {   
                    //then update.
                    new_main_node->s_link = new_sub_node;
                }
                else
                {
                    //if not equal to NULL 
                    // then traverse through the subnode and insert them.
                    sub_node *travserse_sub_node = new_main_node->s_link;

                    while(travserse_sub_node->s_link != NULL)
                    {
                        travserse_sub_node = travserse_sub_node->s_link;
                    }
                    //after coming out of the loop insert the new_sub_node created.
                    travserse_sub_node->s_link = new_sub_node;
                }
                extracted_file_count--;
            }
        }
        else
        {
            //if main_node link is not empty then create a main node and establish the link between previous main node.
            
            //create main node
            main_node *new_main_node = malloc(sizeof(main_node));

            //validate != Null or not
            if(new_main_node == NULL)
            {
                printf("ERROR : Creating New Main Node Failed\n");
                return;
            }

            //if memory allocated then update extracted main node data.
            new_main_node->file_count = extracted_file_count;
            strcpy(new_main_node->word,extracted_word); //copy the extracted word.
            new_main_node->m_link = NULL;   //initially update m_link with NULL
            new_main_node->s_link = NULL;   //initiall update s_link with NULL

            //as we know h_link is not empty so traverse till reaching NULL and update the new_main_node.
            main_node *traverse_main_node = HT[extracted_index].h_link; 
            while(traverse_main_node->m_link != NULL)
            {
                traverse_main_node = traverse_main_node->m_link;
            }
            //after terminating loop i.e we reached last main node now update the new_main_node.
            traverse_main_node->m_link = new_main_node;

            //now create sub_node 
            //now create the subnode based on file count
            if(extracted_file_count)
            {   
                //read all sub node datas.
                fscanf(read_file, "%d;%[^;];", &extracted_word_count, extracted_file_name);

                //create subnode 
                sub_node* new_sub_node = malloc(sizeof(sub_node));
                
                //error handling
                if(new_sub_node == NULL)
                {
                    printf("ERROR : Createing new sub node failed\n");
                    return;
                }
                
                //if memory allocated update the sub node parts --> wordcount, filename,link part
                new_sub_node->word_count = extracted_word_count;
                strcpy(new_sub_node->file_name,extracted_file_name);
                new_sub_node->s_link = NULL; 
                //check if new_main_node of s_link == NULL or not
                //if = NULL? 
                if(new_main_node->s_link == NULL)
                {   
                    //then update.
                    new_main_node->s_link = new_sub_node;
                }
                else
                {
                    //if not equal to NULL 
                    // then traverse through the subnode and insert them.
                    sub_node *travserse_sub_node = new_main_node->s_link;

                    while(travserse_sub_node->s_link != NULL)
                    {
                        travserse_sub_node = travserse_sub_node->s_link;
                    }
                    //after coming out of the loop insert the new_sub_node created.
                    travserse_sub_node->s_link = new_sub_node;
                }
                extracted_file_count--;
            }
        }
        getc(read_file); //for character '#'
        getc(read_file); //for new line character '\n'
    }
    fclose(read_file);
}

void delete_list_if_file_already_present(char extracted_file_name[])
{
    //inistiallise the traverse main for traversing through single linked list(list with file names)
    slist *traverse_slist = head;
    slist *prev_traverse_slist = NULL;

    //traversing for only deleting.
    while(traverse_slist != NULL)
    {
        if(strcmp(traverse_slist->string,extracted_file_name) == 0)
        {
            //if file names matched then delete that particular node and establish the link.

            //check if traverse_slist ->link having NULL or not
            if(head == traverse_slist)
            {
                head = traverse_slist->link;
                free(traverse_slist);
                return;
            }
            prev_traverse_slist->link = traverse_slist->link;
            free(traverse_slist);
            return;
        }
        prev_traverse_slist = traverse_slist;
        traverse_slist = traverse_slist->link;
    }
}