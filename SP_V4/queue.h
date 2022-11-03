/**
 * @file queue.h
 * @author Daniel Cífka (dcifka20@students.zcu.cz)
 * @brief Hlavičkový soubor knihovny datové strukturý fronta.
 * @version 1.0
 * @date 2022-01-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _QUEUE_H
#define _QUEUE_H

/** Standartní knihovny jazyka C. */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** @brief Struktura queue_item Představuje celo číselný prvek přidávaný do abstraktní datové struktůry fronta. */
typedef struct _queue_item
{
    int data;
    struct _queue_item* next;
}queue_item;

/** @brief Struktůra queue Představuje obecnou definici abstratkní datové struktůry Fronta, kam je možné prvky pridávat, odebírat, získávat prvek z čela fornty a její uvolnění. */
typedef struct _queue
{
    queue_item *front, *rear;
} queue;

/**
 * @brief Funkce pro tvorbu nového prvku přidávaného do fornty.
 * 
 * @param data Celo číselná hodnota přidávaného prvku.
 * @return queue_item* Ukazatel na nově dynamicky alokovanou instanci struktury queue_item.
 */
queue_item *new_item(int data);

/**
 * @brief Funkce pro tvorbu abstraktní datové struktůry fronta.
 * 
 * @return queue* Ukazatel na nově dynamicky alokovanou instanci struktury queue.
 */
queue *queue_create();

/**
 * @brief Funkce pro přidání prvku do fronty.
 * 
 * @param q Ukazatel na datovou strukturu fronty.
 * @param data Celo číselný přidávaný prvek do fronty.
 * @return queue* Ukazatel na dynamicky alokovanou instanci struktury queue s přidaným prvkem na konec fronty.
 */
queue *enQueue(queue *q, int data);

/**
 * @brief Funkce pro odebrání prvku z čela fronty.
 * 
 * @param q Ukazatel na datovou struktůru fronty.
 * @return queue* Ukazatel na dynamicky alokovanou instanci struktury queue s odebraným prvkem z čela fronty.
 */
queue *deQueue(queue *q);

/**
 * @brief Funkce odebírající zbývající prkvy uložené ve frontě a nasledně alokovanou paměť uvolnění.
 * 
 * @param q Ukazatel na datovou struktůru fronty.
 * @return queue* Ukazatel na dynamicky alokovanou instanci struktury queue, kde počet uložených prvku je nula.
 */
queue *clean_queue(queue *q);

/**
 * @brief Funkce vrací hodnotu prvku na čele fronty.
 * 
 * @param q Ukazatel na datovou struktůru fronty.
 * @return int Hodnota čelního prvku fronty.
 */
int get_front_element(queue *q);

#endif

