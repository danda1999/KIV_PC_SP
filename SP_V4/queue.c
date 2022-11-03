#include "queue.h"

queue_item *new_item(int data) {
    queue_item *temp = NULL;

    /* Kontrola vstupního argumentu funkce. */
    if(data < 0) {
        printf("The input argument for creating an element to be added to the queue is invalid.\n");
        return NULL; /* Pokud je vstupní argument nevalidní, je vracena hodnota NULL. */
    }

    temp = (queue_item *)malloc(sizeof(queue_item)); /* Dynamická alokace struktury queue_item představující prvek přidaný do fronty. */
    if(!temp) { /*Kontrola zdali byla alokace úspěšná */
        printf("The memory required to allocate the queue_item structure was not obtained.\n");
        return NULL; /* Pokud alokace není úspěšná vratíme hodnotu NULL. */
    }

    temp->data = data; /* Atributu data pridávaného prvku přiřadíme předanou číselnou hodnotu. */
    temp->next = NULL; /* Ukazatel na další prvek je nasten na NULL, jelikož není další prvek přiřazen. */

    return temp; /*Vracíme nově vytvořený prvek přidávaný do fronty. */
}

queue *queue_create() {
    queue *q = NULL;

    q = (queue *)malloc(sizeof(queue)); /* Dynamická alokace struktury queue představující abstraktní datovou strukturu fronty. */
    if(!q) { /*Kontrola zdali byla alokace úspěšná */
        printf("The memory required to allocate the queue structure was not obtained.\n");
        return NULL; /* Pokud alokace není úspěšná vratíme hodnotu NULL. */
    }
    q->front = q->rear = NULL; /* Čelo a konec fronty nastaven na NULL, jelikož neobsahuje žádný přidaný prvek. */

    return q;
}

queue *enQueue(queue *q, int data) {
    queue_item *temp = NULL;

    /* Kontrola vstupních argumentů funkce. */
    if(!q || data < 0) {
        printf("Input arguments for adding an element to the queue are not valid.\n");
        return NULL; /* Pokud jsou vstupní argumenty nevalidní, je vracena hodnota NULL. */
    }

    temp = new_item(data); /* Vytvoření nového prvku přidáváaného na konec fronty. */
    if(!temp) { /* Kontrola zdali tvorba nového prvku proběhla úspěšně. */
        return NULL; /* Pokud neproběhla vracím hodnotu NULL. */
    }

    if(q->rear == NULL) { /* Pokud je fronta prázdná vložím prvek, a nastavím ho jako čelo a konec fronty. */
        q->front = q->rear = temp;
        return q;
    }

    /*Pokud se prvek ve frontě nachází, nově přidaný prvek bude nastven jako následující prvek koncového prvku fronty. */
    q->rear->next = temp;
    q->rear = temp;

    return q; /* Vracím ukazatel na dynamicky alokovanou strukturu queue s nově přidaným prvkem. */
}

queue *deQueue(queue *q) {
    queue_item *temp;

    /* Kontrola vstupního argumentu funkce. */
    if(!q) {
        printf("The input argument to remove an element from the queue is not valid.\n");
        return NULL; /* Pokud je vstupní argument nevalidní, je vracena hodnota NULL. */
    }

    if(q->front == NULL) {
        return q;
    }

    temp = q->front; /* Prvek z čela fronty si uložím do pomocné proměnné, kterou na konci funkce uvolním. */
    q->front = q->front->next;  
    if(q->front == NULL) { /* Pokud je čelo fronty prázdné nastavím konec fronty na hodnotu NULL, představující prázdný konec fronty. */
        q->rear = NULL;
    }

    temp->next = NULL; /* Další prvek pomocné proměnné temp nastavim na NULL. */
    temp->data = 0; /* Data pomocné proměnné temp nastavim na nulu. */
    free(temp); /* Uvolním alokovanou paměť odebraného prvku z čela fronty, který je uložen v pomocné proměnné temp. */
    return q;
}

queue *clean_queue(queue *q) {

    /* Kontrola vstupního argumentu funkce. */
    if(!q) {
        printf("The queue cleanup input argument is invalid.\n");
        return NULL; /* Pokud je vstupní argument nevalidní, je vracena hodnota NULL. */
    }

    while (q->front != NULL) { /* Odebírám zbývající prvky ve frontě, dokud není čelo fronty prázdné. */
        deQueue(q);
    }

    return q; /* Po skončení cyklu vrátim ukazatel na prazdnou instaci struktury fronty. */
}

int get_front_element(queue *q) {

    /* Kontrola vstupního argumentu funkce. */
    if(!q) { 
        printf("The input argument for getting an element from the queue head is not valid.\n");
        return -1; /* Pokud je vstupní argument nevalidní, je vracena hodnota -1. */
    }

    return q->front->data; /* Funkce vrací hodnotu prvku na čele fronty. */
}