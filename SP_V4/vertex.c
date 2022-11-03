#include "vertex.h"

vertex *veretx_create(const int id, const char *WKT) {
    vertex *new;

    /* Kontrola vstupních argumentů funkce. */
    if(id < 0 || !WKT || strlen(WKT) == 0) {
         printf("The input arguments for creating the graph vertex are not valid.\n");
        return NULL; /* Pokud je nějaký vstupní argument nevalidní, je vracena hodnota NULL. */
    }

    new = (vertex *)malloc(sizeof(vertex)); /* Alokace paměti pro instanci vertex. */
    if(!new) { /*Kontrola zdali byla alokace úspěšná */
        printf("The required memory for allocating the vertex variable was not obtained.\n");
        return NULL; /* Pokud alokace není úspěšná vratíme hodnotu NULL. */
    }

    new->id = id;
    
    new->WKT = (char *)malloc(strlen(WKT) + 1); /* Alokace paměti pro WKT vrcholu (Textová reprezentace). */
    if(!new->WKT) { /*Kontrola zdali byla alokace úspěšná */
        printf("The required memory for allocating the WKT text size was not obtained.\n");
        free(new);
        return NULL; /* Pokud alokace není úspěšná vratíme hodnotu NULL. */
    }

    strcpy(new->WKT, WKT);

    return new; /* Vracíme vytvořenou instanci hrany */
}

void vertex_destroy(vertex **poor) {

    /* Kontrola vstupních argumentů funkce. */
    if(!poor || !*poor) {
        printf("The input arguments for freeing allocated memory are not valid.\n");
        return; /* Pokud je nějaký vstupní argument nevalidní, není nic vráceno. */
    }

    (*poor)->id = 0;
    free((*poor)->WKT); /* Uvolnění dynamicky alokované paměť pro reálné souřadnice vrcholu. */
    (*poor)->WKT = NULL;
    free(*poor);
    *poor = NULL;
}