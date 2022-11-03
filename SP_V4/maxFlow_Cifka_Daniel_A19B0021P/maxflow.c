#include "maxflow.h"

int *BFS (matrix *residual, const size_t  source, const size_t  target, int *parents, const vector_t *vector_vertex) {
    size_t i = 0;
    int u = 0;
    int *visiter = NULL;
    queue *q = NULL;

    /* Kontrola vstupních argumentů funkce. */
    if(!residual || !parents || !vector_vertex) {
        printf("Not all required input arguments are specified.");
        return NULL; /* Pokud jsou vstupní argumenty nevalidní, je vracena hodnota NULL. */
    }

    visiter = (int *)malloc(vector_count(vector_vertex) * sizeof(int)); /* Dynamická alokace pole celých čísel, která reprezentuje číselnou hodnotou navštívenost vrcholu. */
    if(!visiter) { /*Kontrola zdali byla alokace úspěšná */
        printf("The visiter array has not been created.\n");
        return NULL; /* Pokud alokace není úspěšná vratíme hodnotu NULL. */
    }

    for(i = 0; i < vector_count(vector_vertex); ++i) { /* Prvky alokovaného pole budou nastaveny na hodnotu 0. */
        visiter[i] = 0;
    }

    q = queue_create(); /* Vytvoříme abstraktní datovou struktůru frontu. */
    if(!q) { /* Kontrola zdali tvorba fronty proběhla úspěšně. */
        printf("The queue data structure allocation memory was not retrieved.\n");
        free(visiter);
        visiter = NULL; /* Pokud tvorba fronty není úspěšná vratíme hodnotu NULL. */
    }

    q = enQueue(q, source); /* Přidám do fronty počáteční vrchol. */

    visiter[source] = 1; /* Navštívenost počátečního uzlu nastavím na 1, čímž identifikuji, že byl navštíven. */
    parents[source] = -1; /* Předem počátečního uzlu nastaven na -1, který značí žádného předka. */

    while (q->front != NULL) { /* Samostatný algoritmus BFS. BFS končí pokud je nalezený cílový vrchol nebo pokud je prohledaný celá graf bez úspěšného nalezení. */
        u = get_front_element(q); /* Získam prvek z čela fronty. */
        if(u == -1) { /* Kontrola zdali prvek byl získán úspěšně, pokud funkce vrátí -1 alokované paměti jsou uvolněny a vratíme hodnotu NULL. */
            q = clean_queue(q);
            free(q);
            q = NULL;
            free(visiter);
            visiter = NULL;
            free(parents);
            parents = NULL;
            return NULL;
        }
        
        q = deQueue(q); /* Odeberu prvek z čela fronty. */

        for(i = 0; i < vector_count(vector_vertex); ++i) { /* Zjištování, zdali nalezený vrchol není cílovým vrcholem. */
            if(visiter[i] == 0 &&  0 < matrix_get(residual, u, i)) {
                if(i == target) { /* Pokud je nalezen cilový vrchol je v poli parents nastaven předek, alokovaná paměť je uvolněna a vracíme ukaztel na alokované pole parents. */
                    parents[i] = u;
                    q = clean_queue(q);
                    free(q);
                    q = NULL;
                    free(visiter);
                    visiter = NULL;
                    return parents;
                }

                q = enQueue(q, i); /* Pokud není nalezena shoda přidáme daný prvek do fronty a pokračujem dalším vrcholem. */
                parents[i] = u;
                visiter[i] = 1;
            }
        }
    }

    q = clean_queue(q); /* Po prohledání grafu a nenalezení shody s cílovým vrcholem je alokovaná paměť uvolněná včetně alokace pole parents a vratíme hodnotu NULL. */
    free(q);
    q = NULL;
    free(visiter);
    visiter = NULL;
    free(parents);
    parents = NULL;
    return NULL;
}

int min_flow(int current, int last) {

    /* Kontrola vstupních argumentů funkce. */
    if(current < 0 || last < 0) {
        printf("The input arguments for obtaining the minimum flow are not valid.\n");
        return -1; /* Pokud jsou vstupní argumenty nevalidní, je vracena hodnota -1. */
    }

    if(current > last) { /* Pokud je aktuální hodnota výšší než hodnota minulá, tak je vrácena hodnota minulého toku. */
        return last;
    } else { /* Pokud je hodnota aktuální menší než hodnota minulá, tak vrátíme aktuální získanou hodnotu toku. */
        return current;
    }
}

vector_t *max_flow(matrix *capacity, const vector_t *real_vector, const vector_t *image_vector, const vector_t *vector_vertex, const vector_t *vector_edge, const size_t source, const size_t target) {
    matrix *residual = NULL;
    vector_t *minimal_cut = NULL;
    edge *minimal_edge = NULL, *help_edge = NULL;
    size_t i = 0, u = 0, v = 0;
    int path = 0, maxFlow = 0, residual_capacity = 0, *parents = NULL, help_capacity = 0;

    /* Kontrola vstupních argumentů funkce. */
    if(!capacity || !real_vector || !vector_vertex || !vector_edge) {
        printf("Not all required input arguments are specified.");
        return NULL; /* Pokud jsou vstupní argumenty nevalidní, je vracena hodnota NULL. */
    }

    residual = matrix_create(vector_count(vector_vertex), vector_count(vector_vertex), 0); /* Dynamická alokoace datové struktury matrix, která reprezentuje měnící se matici kapacit hran. */
    if(!residual) { /*Kontrola zdali byla alokace úspěšná */
        printf("Residual matrix allocation memory was not obtained.\n");
        return NULL; /* Pokud alokace není úspěšná vratíme hodnotu NULL. */
    }

    parents = (int *)malloc(vector_count(vector_vertex) * sizeof(int)); /* Dynamická alokace pole celých čísel, které uchovává předka s minimální kapacitou hrany do příslušného vrcholu. */
    if(!parents) { /*Kontrola zdali byla alokace úspěšná */
        printf("Ancestor array allocation memory not retrieved.\n");
        matrix_free(&residual);
        return NULL; /* Pokud alokace není úspěšná uvolním alokovanou pameť a vratím hodnotu NULL. */
    }

    minimal_cut = vector_create(sizeof(edge *), NULL); /* Dynamická alokace vectoru, který bude uchovávat hrany minimálního řezu. */
    if(!minimal_cut) { /*Kontrola zdali byla alokace úspěšná */
        printf("Memory for minimum slice vector allocation was not obtained.\n");
        matrix_free(&residual);
        free(parents);
        return NULL; /* Pokud alokace není úspěšná uvolním alokovanou pameť a vratím hodnotu NULL. */
    }

    /* Inicializace měnící se matice kapacit příslušnými načtenými kapacitami uložených v matici kapacit. */
    for(i = 0; i < vector_count(vector_vertex); ++i) {
        for(v = 0; v < vector_count(vector_vertex); ++v) {
            matrix_set(residual, i, v, matrix_get(capacity, i, v));
        } 
    }

    maxFlow = 0; /* Maximální tok nastaven na 0. */
    parents = BFS(residual, source, target, parents, vector_vertex); /* Prohledaní grafu algoritmem BFS, která násleně vratí modifikované alokované pole parents. */ 

    while (parents != NULL) { /* Pokud v ukazateli parents je uložena hodnota NULL, smyčka končí pro výpočet maximálního toku končí. */
        path = __INT_MAX__;
        help_capacity = __INT_MAX__; /* Pomocná proměná pro uložení aktuálního maximálního toku. */
        for(i = target; i != source; i = parents[i]) {
            u = parents[i];
            residual_capacity = matrix_get(residual, u, i);
            path = min_flow(path, residual_capacity);
            if(path == -1) { /* Pokud funkce min_flow() vrátí -1 nastala chyba ve vstupních argumentech a program bude ukončen navratovou hodnotou NULL. */
                matrix_free(&residual);
                free(parents);
                vector_destroy(&minimal_cut);
                return NULL; /* Pokud alokace není úspěšná uvolním alokovanou pameť a vratím hodnotu NULL. */
            }

            if(residual_capacity == path) { /* Kontrola zdali bylo změněno minimum. */
                help_edge = get_edge(vector_edge, get_real_id_from_image(real_vector, image_vector, u), get_real_id_from_image(real_vector, image_vector, i), path);
                if(residual_capacity <= help_capacity && help_edge != NULL) { /* Podmínka pro zjištení zdali je aktuálně nalezený minimální tok menší než předchozí a získaná hrana nemá hodnotu NULL. */
                    minimal_edge = help_edge; /* Pokud je podmínka splněná, vložíme získanou hranu do proměný minimál_edge. */
                    help_capacity = minimal_edge->capacity; /* Pokud je splněná podmíka proměnou help_capacity nahradíme capacituou nově nalezené minimální hrany. */
                }
            }
        }

        for (i = target; i != source; i = parents[i]) { /* Aktualizace měnící se matice kapacit a obrat hran podle délky cesty. */
            u = parents[i];
            matrix_set(residual, u, i, matrix_get(residual, u, i) - path);
            matrix_set(residual, i, u, matrix_get(residual, i, u) + path);
        }
        maxFlow += path;
        vector_push_back(minimal_cut, &minimal_edge); /* Vložení nalezené minimální hrany do vectoru minimálního řezu. */
        parents = BFS(residual, source, target, parents, vector_vertex); /* Prohledaní grafu algoritmem BFS, která násleně vratí modifikované alokované pole parents. */ 
    }

    printf("Max network flow is |x| = %d.\n", maxFlow);
    if(maxFlow == 0) { /* Pokud je maximální tok roven nule, tak je alokovaná paměť struktur této funkce uvolněná a vrácena je hodnota NULL. */
        matrix_free(&residual);
        vector_destroy(&minimal_cut);
        return NULL;
    }
    matrix_free(&residual); /* Maximální tok neni nulový, tak uvolníme alokovanou paměť měnící se matice a vratíme vector minimálního řezu. */
    return minimal_cut;
    
}