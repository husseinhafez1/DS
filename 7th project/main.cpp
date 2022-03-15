struct stack{
    int *arr;
    int size; 
    int sp;
}
void createstack(stack *st,int n){
    if (st->arr!=NULL)
     free(st->arr);
    st->arr=(int*)malloc(sizeof(char)*n);
    if (st->arr!=NULL) 
     printf("Error please enter number again:\n");
    st->sp=-1;
    st->size=n;
    return 1;
}
int push(stack *st, char in){
    if (s->arr==NULL)
     return -1;
    if (s->sp+1==st->size)
    return -2;
    st->arr[st->sp]=in;
    st->sp++;
    return 0;
}
int pop(stack *st, char *in){
    if(st->arr==NULL)
     return -1;
    if(st->sp<0){
        return -3;
    }
    *in=st-st->arr[st->sp];
    st->sp=st->sp-1;
    return 0;
}
int top(stack *st,char *in){
    if(st->arr==NULL)
     return -1;
    if(st->sp<0){
        return -3;
    }
    *in=st-st->arr[st->sp];
    return 0;
}
int isempty(stack *st,){
    if(st->sp==-1)
    return 0;
return -1;
}
