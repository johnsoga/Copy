/*
 *
 * LinkedList.c
 *
 * Created by Gary Johnson on 8/26/12.
 *
 */

#include "LinkedList.h"

int create(struct List *list) {
    
    list->size = 0;
    list->head = malloc(sizeof (struct Node));
    
    if (list->head != NULL) {
        list->head->next = NULL;
        return 0;
    }
    
    return -1;
}
int insertAt(data_t data, int position, struct List* list) {
    
    long size = list->size;
    int count = 1;
    
    if (position > size + 1 || position < 1)
        return -1;
    
    struct Node *curr = list->head;
    struct Node *new = malloc(sizeof (struct Node));
    
    if (new != NULL)
        new->data = data;
    else
        return -1;
    
    while (count < position) {
        curr = curr->next;
        count++;
    }
    
    new->next = curr->next;
    curr->next = new;
    list->size += 1;
    
    return 0;
}
int isEmpty(struct List* list) {
    
    if (list->size == 0) {
        return 1;
    }
    
    return 0;
}
long size(struct List* list) {
    
    return list->size;
}
void removeAll(struct List* list) {
    
    list->head->next = NULL;
    list->size = 0;
}
int removeAt(int position, struct List* list) {
    
    long size = list->size;
    int count = 1;
    
    if (position > size || position < 1) {
        return -1;
    }
    
    struct Node *curr = list->head;
    struct Node *old;
    
    while (count < position) {
        curr = curr->next;
        count++;
    }
    
    old = curr->next;
    curr->next = curr->next->next;
    list->size -= 1;
    free(old);
    
    return 0;
}
data_t get(int position, struct List* list) {
    
    int count = 1;
    
    if (position > list->size || position < 1) {
        return NULL;
    }
    
    struct Node *curr = list->head;
    
    while (count < position) {
        curr = curr->next;
        count++;
    }
    
    return curr->next->data;
    
}