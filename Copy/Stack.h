/*
 * File:   Stack.h
 * Author: logic
 *
 * Created on January 30, 2013, 3:18 PM
 */

#ifndef Copy_Stack_h
#define Copy_Stack_h
#endif

#include "LinkedList.h"

struct Stack {
    
    struct List *list;
};

int s_create(struct Stack* st);
int s_push(data_t data, struct Stack* st);
int s_isEmpty(struct Stack* st);
long s_size(struct Stack* st);
void s_popALL(struct Stack* st);
int s_pop(struct Stack* st);
data_t s_peek(struct Stack* st);

