# Inverted-Search

## Overview
The **Inverted Search** project uses an efficient searching technique based on **reverse indexing** using **hash tables** and **singly linked lists**. It allows for fast lookups of words[word to document] and their occurrences in multiple files, making it useful for text-based search applications.
Actually an hash table of words are created in such a way that all words are sorted based on their specific index value using **hash function**, this helps in efficient searching and storing by reduced time complexitiy O(1) although the worst case time complexity is O(n) based on number of words in specific index compared to other techniques.
-Input Files are passed through command line arguments

## Operations:
- Create Database - Creates a Database for respectve input files. 
- Display Database - Display's content of database after creation or updation. 
- Update Database -  Updates old file database with newly passed files.
- Search Word -  Searchs entered word by index.
- Save Database -  Saves created database to a file with **#** inclusion that includes database file.
  

## Topics covered
- C Programming
- Data structures: Hashing, Single Linked List. 
- File Handling

1. **Compile Program Execution**
   ```bash
   gcc main.c is.c is.h
   ```
2. **Execution**
   ```bash
   ./a.out < ".txt" files for which we want to create a database >

   Example: ./a.out temp1.txt temp2.txt temp3.txt alpha.txt etc......
   ```
   
