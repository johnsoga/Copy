/*
 * File:   LinkedList.h
 * Author: logic
 *
 * Created on January 30, 2013, 12:15 PM
 */

#ifndef Copy_LinkedList_h
#define Copy_LinkedList_h
#define data_t char *
#endif


#include <stdio.h>
#include <stdlib.h>


struct Node {
    
    struct Node *next;
    data_t data;
};

struct List {
    
    long size;
    struct Node *head;
};


int create(struct List *list);
int insertAt(data_t data, int position, struct List* list);
int isEmpty(struct List* list);
long size(struct List* list);
void removeAll(struct List* list);
int removeAt(int position, struct List* list);
data_t get(int position, struct List* list);