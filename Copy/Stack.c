#include "Stack.h"

int s_create(struct Stack* st) {
    
    st->list = NULL;
    
    st->list = malloc(sizeof(struct List));
    
    if(st->list != NULL)
        return create(st->list);
    else
        return -1;
}
int s_push(data_t data, struct Stack* st) {
    
    return insertAt(data, 1, st->list);
}
int s_isEmpty(struct Stack* st) {
    
    return isEmpty(st->list);
}
long s_size(struct Stack* st) {
    
    return size(st->list);
}
void s_popALL(struct Stack* st) {
    
    removeAll(st->list);
}
int s_pop(struct Stack* st) {
    
    return removeAt(1, st->list);
}
data_t s_peek(struct Stack* st) {
    
    return get(1, st->list);
}






