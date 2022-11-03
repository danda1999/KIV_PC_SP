#include "Stack.h"

Stack *create_stack(const size_t width) {

    Stack *s;

    if(!width) {
        return NULL;
    }

    s = (Stack *)malloc(sizeof(Stack));
    if(!s) {
        return NULL;
    }

    s->nelement = 0;
    s->top = NULL;
    s->width = width;

    return s;
}

void stack_push(Stack *s, const void *data) {
    Node *new_node;
    if(!s || !data) {
        return;
    }

    new_node = malloc(sizeof(Node));
    if(!new_node) {
        return;
    }
    new_node->data = malloc(s->width);
    if(!new_node->data) {
        return;
    }

    memcpy(&new_node->data, &data, s->width);

    new_node->next = s->top;
    s->top = new_node;
    s->nelement ++;
}

void *stack_pop(Stack *s) {
    Node *n;
    void *f;

    if (!s || s->nelement == 0) {
        return NULL;
    }

    n = s->top;
    s->top = n->next;

    
    memcpy(&f, &n->data, s->width);

    free(n);
    n = NULL;
    s->nelement--;
    return f;
}

void *stack_get_head(Stack *s) {
    Node *n;
    void *f;
    
    if (!s || s->nelement == 0) {
        return NULL;
    }

    n = s->top;
    
    memcpy(&f, &n->data, s->width);
    return f;
}

int stack_nelement(Stack *s) {
    return s->nelement;
}