/**
 * @file edge.h
 * @author Daniel Cífka (dcifka20@students.zcu.cz)
 * @brief Hlavičkový soubor "přepravky" pro hranu grafu. 
 * @version 1.0
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _EDGE_H
#define _EDGE_H

/** Standartní knihovny jazyka C. */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * @brief Struktura popisující hranu grafu, její id, počáteční vrchol, koncový vrchol, capacita hrany, validitu a její realné souřadnice.
 * 
 */
typedef struct _edge
{
    int id; /**< Id hrany. */
    int source; /**< Počáteční vrchol hrany. */
    int target; /**< Koncový vrchol hrany. */
    int capacity; /**< Kapacita hrany. */
    char *isvalid; /**< Validita hrany (dynamicky alokováno). */
    char *WKT; /**< Reálné souřadnice hrany (dynamicky alokováno). */
}edge;

/**
 * @brief Funkce tvořící novou hranu grafu.
 * 
 * @param id Id hrany.
 * @param source Počáteční vrchol hrany.
 * @param target Koncový vrchol hrany.
 * @param capacity Kapacita hrany.
 * @param isvalid Validita hrany.
 * @param WKT Reálné souřadnice hrany.
 * @return edge* Ukazatel na nově dynamicky alokovanou instanci struktury edge.
 */
edge *edge_create(const int id, const int source, const int target, const int capacity, const char *isvalid, const char *WKT);

/**
 * @brief Funkce pro uvolnění instance hrany.
 * 
 * @param poor Uvolňovaná instance hrany.
 */
void edge_destroy(edge **poor);

#endif

