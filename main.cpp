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
T pop(Stack<T> *st){
    if(st->arr==NULL)
        return -1;
    if(st->sp == -1)
        return -2;
    return st->arr[st->sp--];
}

template <typename T>
T top(Stack<T> *st){
    if(st->arr==NULL)
        return -1;
    if(st->sp == -1)
        return -2;
    return st->arr[st->sp];
}

template <typename T>
int isempty(Stack<T> *st){
    if(st->sp == -1)
        return 1;
    return 0;
}

int Prec(char ch)
{
    if (ch == '+' || ch == '-') {
        return 1;
    }
    else if (ch == '*' || ch == '/') {
        return 2;
    }
    else if (ch == '^') {
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
    char infix[255];
    printf("Please enter the math equation you want to calculate: ");
    gets(infix);

    Stack<char> operators;
    Stack<double> res;
    initStack<char>(&operators, strlen(infix));
    initStack<double>(&res, strlen(infix));

    char postfix[255];
    int pfIndex = 0;

    for (int i = 0; i < strlen(infix); i++) {
        if ((isdigit(infix[i]) && isdigit(infix[i+1])) || 
            (isOperator(infix[i]) && isOperator(infix[i+1])) || 
            (isOperator(infix[i]) && infix[i+1] == '\0')) {
            printf("\nInvalid input. \n");
            return 0;
        }
        else if (isspace(infix[i]))
            continue;
        else if (infix[i] == '(')
            push<char>(&operators, infix[i]);
        else {
            if (isdigit(infix[i])) 
                postfix[pfIndex++] = infix[i];
            else {
                if (infix[i] == ')') {
                    while (top<char>(&operators) != '(' && top<char>(&operators) != -2)
                        postfix[pfIndex++] = pop<char>(&operators);

                    if (top<char>(&operators) == -2) {
                        printf("\nInvalid input.\n");
                        return 0;
                    }

                    pop<char>(&operators);
                }
                else if (isOperator(infix[i])) {
                    while (Prec(top<char>(&operators)) >= Prec(infix[i]))
                        postfix[pfIndex++] = pop<char>(&operators);

                    push<char>(&operators, infix[i]);
                }
                else {
                    printf("\nInvalid input.\n");
                    return 0;
                }
            }
        }
    }

    while (!isempty(&operators)) {
        if (top<char>(&operators) != '(')
            postfix[pfIndex++] = pop<char>(&operators);
        else {
            printf("\nInvalid input.\n");
            return 0;
        }
    }

    postfix[pfIndex] = '\0';
    printf("\nPostfix Expression =  %s\n",postfix);

    for (int i = 0; i < strlen(postfix); i++) {
        if (isdigit(postfix[i])) {
            push<double>(&res, postfix[i]-'0');
        }
        else {
            if (postfix[i] == '+') {
                double a, b;
                a = pop<double>(&res);
                b = pop<double>(&res);
                push<double>(&res, a+b);
            }
            else if (postfix[i] == '-') {
                double a, b;
                a = pop<double>(&res);
                b = pop<double>(&res);
                push<double>(&res, b-a);
            }
            else if (postfix[i] == '*') {
                double a, b;
                a = pop<double>(&res);
                b = pop<double>(&res);
                push<double>(&res, a*b);
            }
            else if (postfix[i] == '/') {
                double a, b;
                a = pop<double>(&res);
                b = pop<double>(&res);
                if (a == 0) {
                    printf("\nMath Error!!!\n");
                    return 0;
                }
                push<double>(&res, b/a);
            }
            else if (postfix[i] == '^') {
                double a, b;
                a = pop<double>(&res);
                b = pop<double>(&res);
                push<double>(&res, pow(b,a));
            }
        }
    }
    
    printf("\n%s = %lf\n", infix,pop<double>(&res));

    return 0;
}
