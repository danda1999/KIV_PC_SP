#include "graph.h"


vector_t *get_real_vector(const vector_t *vector_vertexs) {
    size_t i = 0;
    vector_t *real_vector = NULL;
    vertex *element = NULL;

    /* Kontrola vstupních argumentů funkce. */
    if(!vector_vertexs) {
        printf("The input argument for creating the real id auxiliary vector is not valid.\n");
        return NULL; /* Pokud je vstupní argument nevalidní, je vracena hodnota NULL. */
    }

    real_vector = vector_create(sizeof(int), NULL); /* Dynamická alokace vectoru celých čísel, kde budou uloženy skutečné id načtených hran. */
    if(!real_vector) { /*Kontrola zdali byla alokace úspěšná */
        printf ("Real id helper vector allocation not obtained successfully.");
        return NULL; /* Pokud alokace není úspěšná vratíme hodnotu NULL. */
    }


    for ( i = 0; i < vector_count(vector_vertexs); ++i) { /* Uložení skutečných a imaginaárních id do příslušných vectorů. */
        element = *(vertex**)vector_at(vector_vertexs, i);
        if(vector_push_back(real_vector, &element->id) == 0) { /* Pokud je vložení prvku do vectoru neúspěšné vytořené vectory uvolním a vratím hodnotu NULL. */
            printf("Inserting an element into a real_vector was not successful.\n");
            vector_destroy(&real_vector);
            real_vector = NULL;
            return NULL; /* Pokud alokace není úspěšná vratíme hodnotu NULL. */
        }
    }

    return real_vector;
}

vector_t *get_image_vector(const vector_t *vector_vertexs) {
    size_t i = 0;
    vector_t *image_vector = NULL;

    /* Kontrola vstupních argumentů funkce. */
    if(!vector_vertexs) {
        printf("The input argument for creating the imaginary id auxiliary vector is not valid.\n");
        return NULL; /* Pokud je vstupní argument nevalidní, je vracena hodnota NULL. */
    }

    image_vector = vector_create(sizeof(int), NULL); /* Dynamická alokace vectoru celých čísel, kde budou uloženy imaginární id načtených hran. */
    if(!image_vector) { /*Kontrola zdali byla alokace úspěšná */
        printf ("Auxiliary vector imaginary id allocation was not obtained successfully.");
        return NULL; /* Pokud alokace není úspěšná vratíme hodnotu NULL. */
    }

    for ( i = 0; i < vector_count(vector_vertexs); ++i) { /* Uložení skutečných a imaginaárních id do příslušných vectorů. */
        if(vector_push_back(image_vector, &i) == 0) {  /* Pokud je vložení prvku do vectoru neúspěšné vytořené vectory uvolním a vratím hodnotu NULL. */
            printf("Inserting an element into a image_vector was not successful.\n");
            vector_destroy(&image_vector);
            image_vector = NULL;
            return NULL; /* Pokud alokace není úspěšná vratíme hodnotu NULL. */
        }

    }

    return image_vector;

}

matrix *capacity_matrix(const vector_t *real_vector, const vector_t *image_vector, const vector_t *vector_edges) {
    matrix *capacity = NULL;
    size_t i = 0;
    int row = 0, col = 0;
    edge *element;

    /* Kontrola vstupních argumentů funkce. */
    if(!real_vector || !vector_edges) {
        printf("The input arguments for creating the capacity matrix are not valid.\n");
        return NULL; /* Pokud je nějaký vstupní argument nevalidní, je vracena hodnota NULL. */
    }

    capacity = matrix_create(vector_count(real_vector), vector_count(real_vector), 0); /* Dynamická alokoace datové struktury matrix, která reprezentuje matici kapacit hran. */
    if(!capacity) { /*Kontrola zdali byla alokace úspěšná */
        printf("Memory acquisition for capacity matrix allocation was not successful.\n");
        return NULL; /* Pokud alokace není úspěšná vratíme hodnotu NULL. */
    }

    for(i = 0; i < vector_count(vector_edges); ++i) { /* Naplnění matice kapacit příslušnými kapacity získaných hran */
        element = *(edge **)vector_at(vector_edges, i);
        row = get_image_id_from_real(real_vector, image_vector, element->source);
        if(row == -1) { /* Pokud není pro zadanou hranu nalezený počáteční vrchol, uvolníme alokovanou matici kapacit */
            printf("No edge with capacity is found for the initial vertex.\n");
            matrix_free(&capacity);
            return NULL;
        }
        col = get_image_id_from_real(real_vector, image_vector, element->target);
        if(col == -1) { /* Pokud není pro zadanou hranu nalezený koncový vrchol, uvolníme alokovanou matici kapacit */
            printf("No edge with capacity is found for the end vertex.\n");
            matrix_free(&capacity);
        }

        matrix_set(capacity, row, col, element->capacity); /* Nastavení kapacity na příslušnou hranu */
    }

    return capacity;
}

int get_image_id_from_real(const vector_t *real_vector, const vector_t *image_vector, const int id) {
    size_t i = 0;
    int position = 0;

    /* Kontrola vstupních argumentů funkce. */
    if(!real_vector || id < 0) {
        printf("The input arguments for obtaining the imaginary id are not valid.\n");
        return -1; /* Pokud je nějaký vstupní argument nevalidní, je vracena hodnota -1. */
    }

    for(i = 0; i < vector_count(real_vector); ++i) { /* Nahrazení skutečného id hrany za imaginární id hrany, které je následně vráceno. */
        position = *(int *)vector_at(real_vector, i);
        if(id == position) {
            return *(int *)vector_at(image_vector, i); /* Vracíme imaginární id skutečné hrany grafu. */
        }
    }
    printf("The method did not find any matching IDs.\n");
    return -1; /* Pokud není shoda nalezena je vrácena hodnota -1. */
}

int get_real_id_from_image(const vector_t *real_vector, const vector_t *image_vector, const int id) {
    size_t i = 0;
    int position = 0;

    /* Kontrola vstupních argumentů funkce. */
    if(!real_vector || id < 0) {
        printf("The input arguments for obtaining the real id are not valid.\n");
        return -1; /* Pokud je nějaký vstupní argument nevalidní, je vracena hodnota -1. */
    }

    for(i = 0; i < vector_count(image_vector); ++i) { /* Zjistení z imaginárního id hrany jeho skutečné id, které je následně vráceno. */
        position = *(int *)vector_at(image_vector, i);
        if(position == id) {
            return *(int *)vector_at(real_vector, i); /* Vracíme skutečné id hrany grafu. */
        }
    }
     printf("The method did not find any matching Vertexs.\n");
    return -1; /* Pokud není shoda nalezena je vrácena hodnota -1. */
}

edge *get_edge(const vector_t *vector_edges, const int source, const int target, const int capacity) {
    size_t i = 0;
    edge *element = NULL;

    /* Kontrola vstupních argumentů funkce. */
    if(!vector_edges || source < 0 || target < 0 || capacity < 0) {
        printf("The input arguments for obtaining the edge with the passed parameters are not valid.\n");
        return NULL; /* Pokud je nějaký vstupní argument nevalidní, je vracena hodnota NULL. */
    }

    for(i = 0; i < vector_count(vector_edges); ++i) { /* Nalezení příslušné hrany splňující předané parametry počátčního vrcholu, koncové vrcholu a kapacity. */
        element = *(edge **)vector_at(vector_edges, i);
        if(element->source == source && element->target == target && element->capacity == capacity) {
            return element; /* Vracíme nalezenou hranu splňující předané specifikace. */
        }
    }

    return NULL; /* Pokud není nalezená příslušná hrana tak vracím hodnotu NULL. */
}