#include "input.h"

vector_t *vertex_loader(const char *input_vertex_file) {
    char line[CHAR_BUFFER_SIZE] = { 0 }, *WKT = NULL;
    int id = 0;
    FILE *file;
    vector_t *vertexs = NULL;
    vertex *v = NULL;

    /* Kontrola vstupních argumentů funkce. */
    if(!input_vertex_file || strlen(input_vertex_file) == 0) {
        printf("The input argument for retrieving graph vertices is not valid.\n");
        return NULL; /* Pokud je vstupní argument nevalidní, je vracena hodnota NULL. */
    }

    file = fopen(input_vertex_file, "r");
    if(!file) { /*Kontrola otevření souboru pro čtení. */
        printf("Could not open file\n");
        return NULL; /* Pokud se nepodaří otevřít soubor, vracím hodnotu NULL. */
    }

    vertexs = vector_create(sizeof(vertex *), (vec_it_dealloc_t)vertex_destroy); /* Vytvoření instance vectoru vrcholů */
    if(!vertexs) { /*Kontrola zdali byla alokace úspěšná */
        printf("The required memory for allocating the vertex structure was not obtained.\n");
        return NULL;
        fclose(file);
    }

    fgets(line, CHAR_BUFFER_SIZE, file); /* Přečtení první řádky CSV souboru, kde je uložena hlavička */
    if(header_check(line, VERTEX_HEADER) == -1) { /* Kontrola hlavičky CSV souboru vrcholů */
        printf("Incorrect head of csv file\n");
        vector_destroy(&vertexs);
        vertexs = NULL;
        fclose(file);
        return NULL;
    }
    while (fgets(line, CHAR_BUFFER_SIZE, file)) { /* Čtení CSV souboru po řádkách */
        if(strlen(line) == 0 || strlen(line) == 1) {
            continue;
        }

        /* Rozdelení CSV souboru na příslušné hodnoty vrcholu */
        id = atoi(strtok(line, CSV_DELIMETER));
        WKT = strtok(NULL, CSV_DELIMETER);
        WKT[strcspn(WKT, "\r\n")] = 0;
        if(duplicity_check_vertex(vertexs, id) == 1) { /* Kontrola doplicity vrcholů v CSV souboru */
            v = veretx_create(id, WKT); /* Vytvoření instance načteného vrcholu */
            if(!v) {
                printf("The required memory for allocating the vertex structure was not obtained.\n");
                vector_destroy(&vertexs);
                vertexs = NULL;
                fclose(file);
                return NULL;
            }

            if(vector_push_back(vertexs, &v) == 0) { /* Vložení ukazatele na nově vytvořenou instanci do vectoru */
                printf("Inserting an element into a vertex vector was not successful.\n");
                vertex_destroy(&v);
                v = NULL;
                vector_destroy(&vertexs);
                vertexs = NULL;
                fclose(file);
                return NULL;
            } 
        }
    }

    fclose(file);
    return vertexs;
}

vector_t *edge_loader(const char *input_edge_file, const int isvalid_a) {
    char line[CHAR_BUFFER_SIZE] = { 0 }, *isvalid = NULL, *WKT = NULL;
    int id = 0, source = 0, target = 0, capacity = 0;
    FILE *file;
    vector_t *edges = NULL;
    edge *e = NULL;

    /* Kontrola vstupních argumentů funkce. */
    if(!input_edge_file || strlen(input_edge_file) == 0) {
        printf("The input argument for retrieving graph edges is not valid.\n");
        return NULL; /* Pokud je vstupní argument nevalidní, je vracena hodnota NULL */
    }

    file = fopen(input_edge_file, "r");
    if(!file) { /*Kontrola otevření souboru pro čtení. */
        printf("Could not open file\n");
        return NULL;  /* Pokud se nepodaří otevřít soubor, vracím hodnotu NULL. */
    }

    edges = vector_create(sizeof( edge *), (vec_it_dealloc_t)edge_destroy); /* Dynamická alokace instance vectoru hran */
    if(!edges) { /*Kontrola zdali byla alokace úspěšná */
        printf("The required memory for allocating the edge structure was not obtained.\n");
        fclose(file);
        return NULL; /* Pokud alokace není úspěšná vratíme hodnotu NULL. */
    }

    fgets(line, CHAR_BUFFER_SIZE, file); /* Přečtení první řádky CSV souboru, kde je uložena hlavička. */
    if(header_check(line, EDGE_HEADER) == -1) { /* Kontrola hlavičky CSV souboru hran. */
        printf("Incorrect head of csv file\n");
        vector_destroy(&edges);
        edges = NULL;
        fclose(file);
        return NULL;
    }

    while (fgets(line, CHAR_BUFFER_SIZE, file)) { /* Čtení CSV souboru po řádkách. */
        if(strlen(line) == 0 || strlen(line) == 1) {
            continue;
        }

        /* Rozdelení CSV souboru na příslušné hodnoty hrany. */
        id = atoi(strtok(line, CSV_DELIMETER));
        source = atoi(strtok(NULL, CSV_DELIMETER));
        target = atoi(strtok(NULL, CSV_DELIMETER));
        capacity = atoi(strtok(NULL, CSV_DELIMETER));
        isvalid = strtok(NULL, CSV_DELIMETER);
        isvalid[strcspn(isvalid, "\r\n")] = 0;
        WKT = strtok(NULL, "\n");
        WKT[strcspn(WKT, "\r\n")] = 0;

        if(duplicity_check_edge(edges, id) == 1) { /* Kontrola doplicity hran v CSV souboru. */
            e = edge_create(id, source, target, capacity, isvalid, WKT); /* Vytvoření instance načtené hrany. */
            if(!e) {
                printf("The required memory for allocating the edge structure was not obtained.\n");
                vector_destroy(&edges);
                edges = NULL;
                fclose(file);
            }

            if(!isvalid_a && strcmp(isvalid, "True")) { /* Pokud není zadaná přepínač '-a' hrany s hodnotou isvalid = False jsou přeskočeny. */
                edge_destroy(&e);
                e = NULL;
                continue;
            }

            if(vector_push_back(edges, &e) == 0) { /* Vložení ukazatele na nově vytvořenou instanci do vectoru. */
                printf("Inserting an element into a edge vector was not successful.\n");
                edge_destroy(&e);
                vector_destroy(&edges);
                edges = NULL;
                fclose(file);
                return NULL;
            }
        }
    }
    
    fclose(file);
    return edges;
}

int duplicity_check_vertex(const vector_t * vector_vertex, const int id) {
    size_t i = 0;
    vertex *element = NULL;

    /* Kontrola vstupních argumentů funkce. */
    if(!vector_vertex || id < 0) {
        printf("Input arguments for duplication are not valid.\n");
        return EXIT_SUCCESS; /* Pokud je nějaký vstupní argument nevalidní, je vracena hodnota EXIT_SUCCESS. */
    }

    for(i = 0; i < vector_count(vector_vertex); ++i) {
        element = *(vertex **)vector_at(vector_vertex, i); /* Získání vrcholu z vectoru na požadované pozici. */
        if(element->id == id) {     /* Zjisštění zdali se id neshoduje s id získaného prvku. */
            return EXIT_SUCCESS;
        }
    }

    return EXIT_FAILURE;
}

int duplicity_check_edge(const vector_t * vector_edge, const int id) {
    size_t i = 0;
    edge *element = NULL;

    /* Kontrola vstupních argumentů funkce. */
    if(!vector_edge || id < 0) {
        printf("Input arguments for duplication are not valid.\n");
        return EXIT_SUCCESS; /* Pokud je nějaký vstupní argument nevalidní, je vracena hodnota EXIT_SUCCESS. */
    }

    for(i = 0; i < vector_count(vector_edge); ++i) {
        element = *(edge **)vector_at(vector_edge, i); /* Získání vrcholu z vectoru na požadované pozici. */
        if(element->id == id) {     /* Zjisštění zdali se id neshoduje s id získaného prvku. */
            return EXIT_SUCCESS;
        }
    }

    return EXIT_FAILURE;
}

int header_check(char *header, const int v_e_check) {
    char *header_this = NULL;

    /* Kontrola vstupních argumentů funkce. */
    if(!header || strlen(header) == 0) {
        printf("Input arguments to verify the correctness of the csv file header.\n");
        return -1; /* Pokud je vstupní argument nevalidní, je vracena hodnota -1. */
    }

    if(v_e_check == VERTEX_HEADER) {
        header_this = "id,WKT\n";
        if(strcmp(header_this, header) == 0) { /* Pokud je hlavička rovna definované hlavičce tak metoda strcmp vrátí 0. */
            return strcmp(header_this, header); 
        } 
    }

    if(v_e_check == EDGE_HEADER) {
        header_this = "id,source,target,capacity,isvalid,WKT\n";
        if(strcmp(header_this, header) == 0) { /* Pokud je hlavička rovna definované hlavičce tak metoda strcmp vrátí 0. */
            return strcmp(header_this, header);
        }
    }

    return -1;
}

int check_vertex_in_graph(const vector_t *vector_vertex, const int id) {
    size_t i = 0;
    vertex *element = NULL;

    /* Kontrola vstupních argumentů funkce. */
    if(!vector_vertex || id < 0) {
        printf("Input arguments to verify that the vertex is the vertex of the graph.\n");
        return EXIT_SUCCESS; /* Pokud je nějaký vstupní argument nevalidní, je vracena hodnota EXIT_SUCCESS */
    }

    for(i = 0; i < vector_count(vector_vertex); ++i) {
        element = *(vertex **) vector_at(vector_vertex, i); /* Získání vrcholu z vectoru na požadované pozici */
        if(element->id == id) {     /* Zjisštění zdali se id neshoduje s id získaného prvku */
            return EXIT_SUCCESS;
        }
    }

    return EXIT_FAILURE;
}
