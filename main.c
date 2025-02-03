/*
    Name: Vamsi Krishna
    Description: To implement Inverted search using Hashing & Single Linked List Data structures. which stores data by indexing, which increases speed and performance 
    of adding,storing data into databases.
    Date: 01/02/2025.
*/

#include"is.h"

slist *head = NULL;
int created_database = 0;
int updated_database = 0;
int main(int argc,char *argv[])
{
    if(cla_validation(argc,argv) != success)
    {
        printf("INFO : CLA Failed\n");
        return failure;
    }
    printf("INFO : CLA Passed\n");

    hash_t HT[27];
    initialize_HT(HT);
    int choice;
    char user_word[50];
    char file_name[50];
    while(1)
    {
        printf("\n---Menu---\n");
        printf("1.Create HT\n");
        printf("2.Display HT\n");
        printf("3.Update HT\n"); 
        printf("4.Search HT\n"); 
        printf("5.Save HT\n"); 
        printf("6.Exit\n");

        printf("Enter Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
            // create HT
                if(created_database == 1)
                {
                    //printf("Already database is present, Can't create new database\n");
                    printf("INFO: Database is already created,so create is not possible\n");
                }
                // else if(updated_database == 1)
                // {
                //     printf("INFO: Database is already updated,so update is not possible\n");
                // }
                else
                {
                    if(create_DB(HT) == success)
                    {
                        created_database = 1;
                        printf("INFO: successful : creation of DATABASE :");
                        
                        //print the file name linked list.
                        slist *temp = head;
                        while(temp != NULL)
                        {
                            printf(" %s",temp->string);
                            temp = temp->link;
                        }
                        printf("\n");
                    }
                    else
                    {
                        printf("INFO: DATABASE creation Failed\n");
                    }
                }
                break;
            case 2:
            // display HT
                if(created_database == 1 || updated_database == 1)
                {
                    display_HT(HT);
                }
                else
                {
                    printf("INFO: DataBase created or updated\n");
                    break;
                }
                break;
            case 3:
            // update HT
                if(created_database == 1 )
                {   
                    printf("INFO: Database is already created, update is not possible\n");
                }
                else if(updated_database == 1)
                {
                    printf("INFO: Database is already updated, update is not possible\n");
                }
                else
                {
                    //read file from user "".txt" --> .
                    printf("Enter the Database file name in \".txt\" extension : ");
                    scanf("%s",file_name);
                    if(file_name_validation(file_name) == success)
                    {
                        if(valid_hash_file(file_name) == success)
                        {
                            update_HT(HT,file_name);
                            printf("INFO: Update Database Successful\n");
                            updated_database = 1;
                            //print the file name linked list.
                            slist *temp = head;
                            if(head == NULL)
                            {
                                printf("->NULL\n");
                            }
                            else
                            {
                                while(temp != NULL)
                                {
                                    printf("->");
                                    printf(" %s",temp->string);
                                    temp = temp->link;
                                }
                                printf("\n");
                            }
                        }
                        else
                        {
                            printf("INFO: Invalid Input Database File, Try Again\n");
                        }
                    }
                    else
                    {
                        printf("INFO: \"%s\" => This file not a \".txt\" file\n",file_name);
                    }
                }
                break;
            case 4:
            // search HT
                if(created_database == 1 || updated_database == 1)
                {
                    printf("Enter word to search : ");
                    scanf(" %s",user_word);

                    if(search_HT(HT,user_word) == success)
                    {
                        //printf("Search word completed\n");
                    }
                    else
                    {
                        printf("INFO: Word is not found in the Database\n");
                    }
                }
                else
                {
                    printf("No Database created/updated to search\n");
                    break;
                }
                break;
            case 5:  
            //save HT
                if(created_database == 1 || updated_database == 1)
                {   //read file from user "".txt".
                    printf("To save, Enter the file name with \".txt\" extension : ");
                    scanf("%s",file_name);
                    if(file_name_validation(file_name) == success)
                    {
                        save_HT(HT,file_name);
                        printf("INFO: Database saved\n");
                    }
                    else
                    {
                        printf("Incorrect file format, Please try again\n");
                    }
                }
                else
                {
                    printf("No Database created/updated to save\n");
                    break;
                }
                break;
            case 6:
            //exit
                return success;
                break;
        }
    }

    return success;
}