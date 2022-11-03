#include "person.h"

person_t *person_create(const char *name, const int age, const int shoe_size) {
    person_t *new;

    if (!name || strlen(name) == 0) {
        return NULL;
    }

    new = (person_t *)malloc(sizeof(person_t));
    if (!new) {
        return NULL;
    }

    new->name = (char *)malloc(strlen(name) + 1);
    if (!new->name) {
        free(new);
        return NULL;
    }
    strcpy(new->name, name);

    new->age = age;
    new->shoe_size = shoe_size;

    return new;
}

void person_destroy(person_t **poor) {
    if (!poor || !*poor) {
        return;
    }

    free((*poor)->name);    /* Otázka pro vás! Vynulovali jsme tímto pamět?! */
    (*poor)->name = NULL;

    (*poor)->age = 0;
    (*poor)->shoe_size = 0;

    free(*poor);            /* Tady zkusíme udělat změnu a podíváme se, jak se bude valgrind chovat! */
    *poor = NULL;
}

void person_print(const person_t *p) {
    if (!p) {
        return;
    }

    printf("(\"%s\", %d, %d)\n", p->name, p->age, p->shoe_size);
}