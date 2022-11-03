#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Stack.h"
#include "Person.h"

int main(int argc, char const *argv[])
{
    Stack *s = create_stack(sizeof(Person *));
    size_t i = 0;
    Person *p;
    for(i = 0; i < 5; ++i) {
        p = (Person *)malloc(sizeof(Person));
        if(!p) {
            return 1;
        }
        p->age = 31;
        p->shouse = i;
        stack_push(s, p);
    }

    p = (Person *)stack_get_head(s);
    printf("%d\n", p->age);
    printf("%d\n", p->shouse);
    p = (Person *)stack_pop(s);
    
    while (p != NULL)
    {
        printf("%d\n",p->shouse);
        free(p);
        p = (Person *)stack_pop(s);
    }
    
    return 0;
}
