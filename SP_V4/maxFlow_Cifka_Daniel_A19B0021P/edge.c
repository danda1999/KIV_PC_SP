#include "edge.h"
edge *edge_create(const int id, const int source, const int target, const int capacity, const char *isvalid, const char *WKT) {
    edge*new;

    /* Kontrola vstupních argumentů funkce. */
    if(id < 0 || source < 0 || target < 0|| capacity < 0 || !WKT || strlen(WKT) == 0 || !isvalid || strlen(isvalid) == 0) {
        printf("The input arguments for creating the graph edge are not valid.\n");
        return NULL; /* Pokud je nějaký vstupní argument nevalidní, je vracena hodnota NULL. */
    }

    new = (edge *)malloc(sizeof(edge)); /* Alokace paměti pro instanci edge. */
    if(!new) { /*Kontrola zdali byla alokace úspěšná */
        printf("The required memory for allocating the edge variable was not obtained.\n");
        return NULL; /* Pokud alokace není úspěšná vratíme hodnotu NULL. */
    }

    new->id = id;
    new->source = source;
    new->target = target;
    new->capacity = capacity;
    
    new->isvalid = (char *)malloc(strlen(isvalid) + 1); /* Alokace paměti pro validitu hrany (Textová reprezentace). */
    if(!new->isvalid) { /*Kontrola zdali byla alokace úspěšná */
        printf("The required memory for allocating the isvalid text size was not obtained.\n");
        free(new);
        return NULL; /* Pokud alokace není úspěšná vratíme hodnotu NULL. */
    }

    strcpy(new->isvalid, isvalid);
    
    new->WKT = (char *)malloc(strlen(WKT) + 1); /* Alokace paměti pro WKT hrany (Textová reprezentace). */
    if(!new->WKT) { /*Kontrola zdali byla alokace úspěšná */
        printf("The required memory for allocating the WKT text size was not obtained.\n");
        free(new);
        return NULL; /* Pokud alokace není úspěšná vratíme hodnotu NULL. */
    }

    strcpy(new->WKT, WKT);

    return new; /* Vracíme vytvořenou instanci hrany */
}

void edge_destroy(edge **poor) {

    /* Kontrola vstupních argumentů funkce. */
    if(!poor || !*poor) {
         printf("The input arguments for freeing allocated memory are not valid.\n");
        return; /* Pokud je nějaký vstupní argument nevalidní, není nic vráceno. */
    }

    (*poor)->id = 0;
    (*poor)->source = 0;
    (*poor)->target = 0;
    (*poor)->capacity = 0;
    free((*poor)->isvalid); /* Uvolnění dynamicky alokované paměť pro validitu hrany. */
    (*poor)->isvalid = NULL;
    free((*poor)->WKT); /* Uvolnění dynamicky alokované paměť pro reálné souřadnice hrany. */
    (*poor)->WKT = NULL;
    free(*poor);
    *poor = NULL;
}