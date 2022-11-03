#include "output.h"

int write_file(const char *output_file, const vector_t *minimal_cut) {
    FILE *file = NULL;
    edge *element;
    int *array;

    size_t i = 0, j = 0;

    /* Kontrola vstupních argumentů funkce. */
    if(!output_file || strlen(output_file) == 0 || !minimal_cut) {
        printf("Input arguments to write to file are not valid.\n");
        return EXIT_FAILURE; /* Pokud je nějaký vstupní argument nevalidní, je vracena hodnota EXIT_FAILURE. */
    }

    array = (int *)malloc(sizeof(int) * vector_count(minimal_cut)); /* Dynamická alokace pole celých čísel, kde budou uloženy id hran minimálního řezu pro seřazení. */
    if(!array) { /*Kontrola zdali byla alokace úspěšná */
        printf("The minimum slice edge id field allocation was not created successfully.\n");
        return EXIT_FAILURE; /* Pokud alokace není úspěšná vratíme hodnotu NULL. */
    }

    for(i = 0; i < vector_count(minimal_cut); ++i) {
        element = *(edge **)vector_at(minimal_cut, i);
        array[i] = element->id; /* Do dynamicky alokovaného pole jsou vloženy id hran minimálního řezu, získaného z vectoru minimálního řezu. */
    }

    qsort(array, vector_count(minimal_cut), sizeof(int), cmpfunc); /* Využití knihovní funkce qsort pro seřazení pole id vzestupně. */

    file = fopen(output_file, "w+"); /*Kontrola otevření souboru pro zápis. */
    if(!file) {
        printf("Could not open file\n");
        return EXIT_FAILURE; /* Pokud se nepodaří otevřít soubor, vracím hodnotu EXIT_FAILURE. */
    }

    fprintf(file, "id,source,target,capacity,isvalid,WKT\n"); /* Zapis hlavičky do souboru. */
    for(j = 0; j < vector_count(minimal_cut); ++j) {
        for (i = 0; i < vector_count(minimal_cut); ++i) {
            element = *(edge **)vector_at(minimal_cut, i); /* Získání hrany z vectoru minimálního řezu. */
            if(element->id == array[j]) { /* Kontrola shody id a při shodě daná hrana je zapsána do souboru. */
                fprintf(file,"%d,%d,%d,%d,%s,%s\n", element->id, element->source, element->target, element->capacity, element->isvalid, element->WKT);
            }
        }
    }

    fclose(file); /*Uzavření souboru. */
    free(array); /*Uvolnění dynamicky alokovaného pole celých čísel. */
    
    return EXIT_SUCCESS;
}

int cmpfunc(const void * a, const void * b) {

    return ( *(int*)a - *(int*)b ); /*Zde pobíhá přerovnání prvku pole vzestupně podle id hran. */
}