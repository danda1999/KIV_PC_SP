#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Node_s
{
    void *data;
    struct Node_s *next;
} Node;

typedef struct Stack_s
{
    Node *top;
    size_t width;
    size_t nelement;
}Stack;

Stack *create_stack(size_t width);

void stack_push(Stack *s, const void *data);

void  *stack_pop(Stack *s);

void  *stack_get_head(Stack *s);

int stack_nelement(Stack *s);

#endif

