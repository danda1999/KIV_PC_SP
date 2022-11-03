/**
 * @file person.h
 * @author František Pártl (fpartl@kiv.zcu.cz)
 * @brief Hlavičkový soubor "přepravky" pro osobu.
 * @date 2021-11-25
 */

#ifndef _PERSON_H
#define _PERSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Struktura popisující osobu, její věk a velikost bot.
 */
typedef struct _person_t {
    char *name;         /**< Jméno osoby (dynamicky alokováno). */
    int age;            /**< Věk osoby. */
    int shoe_size;      /**< Velikost bot osoby. */
} person_t;

/**
 * @brief Funkce vytvoří novou osobu.
 * @param name Jméno osoby.
 * @param age Věk osoby.
 * @param shoe_size Velikost bot osoby.
 * @return person* Ukazatel na nově dynamicky alokovanou instanci struktury person.
 */
person_t *person_create(const char *name, const int age, const int shoe_size);

/**
 * @brief Funkce pro uvolnění osoby.
 * @param poor Uvolňována osoba.
 */
void person_destroy(person_t **poor);

/**
 * @brief Funkce vytiskne osobu do konzole.
 * @param p Tištěná osoba.
 */
void person_print(const person_t *p);

#endif
