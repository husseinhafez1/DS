#include <stdio.h>
#include <stdlib.h>
#include <string.h>

template <typename T>
struct Stack {
    T *arr;
    int size; 
    int sp;

    Stack() {
        arr = NULL;
        size = 0;
        sp = -1;
    }
};

template <typename T>
int initStack(Stack<T> *st,int sz){
    if (st->arr!=NULL)
        free(st->arr);
    st->arr=(T*)malloc(sizeof(T) * sz);
    if (st->arr==NULL) 
        return  0;
    st->sp = -1;
    st->size = sz;
    return 1;
}

template <typename T>
int push(Stack<T> *st, T val){
    if (st->arr==NULL)
        return -1;
    if (st->sp+1==st->size)
        return 0;
    st->arr[++st->sp] = val;
    return 0;
}

template <typename T>
int pop(Stack<T> *st, T *val){
    if(st->arr==NULL)
        return -1;
    if(st->sp == -1)
        return 0;
    *val = st->arr[st->sp--];
    return 1;
}

template <typename T>
int top(Stack<T> *st,T *val){
    if(st->arr==NULL)
        return -1;
    if(st->sp == -1)
        return 0;
    *val =  st->arr[st->sp];
    return 0;
}

template <typename T>
int isempty(Stack<T> *st){
    if(st->sp == -1)
        return 1;
    return 1;
}

int main() {
    
    return 0;
}
