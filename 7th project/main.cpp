#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

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
    return 1;
}

template <typename T>
int isempty(Stack<T> *st){
    if(st->sp == -1)
        return 0;
    return 1;
}

int Prec(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;
 
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    }
    return -1;
}

int isOperator(char c)
{
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='^')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int main() {
    char infix[256];
    gets(infix);
    Stack<char> operators;
    Stack<double> res;
    initStack<char>(&operators, strlen(infix));
    initStack<double>(&res, strlen(infix));
    char postfix[256];
    int pfIndex = 0;
    for (int i = 0; i < strlen(infix); i++) {
        if (isdigit(infix[i])) {
            postfix[pfIndex++] = infix[i];
        }
        else if (infix[i] == '(') {
            push<char>(&operators, infix[i]);
        }
        else if (infix[i] == ')') {
            char val;
            top<char>(&operators, &val);
            while (val != '(') {
                postfix[pfIndex++] = val;
                pop<char>(&operators, &val);
                top<char>(&operators, &val);
            }
            pop<char>(&operators, &val);
        }
        else {
            char val;
            top<char>(&operators, &val);
            while (!isempty(&operators) && Prec(infix[i]) <= Prec(val)) {
                postfix[pfIndex++] = val;
                pop<char>(&operators, &val);
                top<char>(&operators, &val);
            }
            push<char>(&operators, infix[i]);
        }
    }
    char val;
    while (pop<char>(&operators, &val)) {
        postfix[pfIndex++] = val;
    }

    postfix[pfIndex] = '\0';
    printf("%s\n", postfix);

    for (int i = 0; i < strlen(postfix); i++) {
        if (isdigit(postfix[i])) {
            push<double>(&res, postfix[i]-'0');
        }
        else {
            if (postfix[i] == '+') {
                double a, b;
                pop<double>(&res, &a);
                pop<double>(&res, &b);
                push<double>(&res, a+b);
            }
            else if (postfix[i] == '-') {
                double a, b;
                pop<double>(&res, &a);
                pop<double>(&res, &b);
                push<double>(&res, a-b);
            }
            else if (postfix[i] == '*') {
                double a, b;
                pop<double>(&res, &a);
                pop<double>(&res, &b);
                push<double>(&res, a*b);
            }
            else if (postfix[i] == '/') {
                double a, b;
                pop<double>(&res, &a);
                pop<double>(&res, &b);
                push<double>(&res, b/a);
            }
            else if (postfix[i] == '^') {
                double a, b;
                pop<double>(&res, &a);
                pop<double>(&res, &b);
                push<double>(&res, pow(b,a));
            }
        }
    }
    double result;
    pop(&res, &result);
    printf("%lf", result);
    return 0;
}
