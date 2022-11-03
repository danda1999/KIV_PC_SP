/**
 * @file veretx.h
 * @author Daniel Cífka (dcifka20@students.zcu.cz)
 * @brief Hlavičkový soubor "přepravky" pro uzel grafu.
 * @version 1.0
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _VERTEX_H
#define _VERTEX_H

/** Standartní knihovny jazyka C. */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Struktura popisující vrchol grafu, její id a reálné souřadnice vrcholu.
 * 
 */
typedef struct _vertex
{
    int id; /**< Id vrcholu. */
    char *WKT; /**< Reálné souřadnice vrcholu (dynamicky alokováno). */
} vertex;

/**
 * @brief Funkce tvořící nový vrchol grafu.
 * 
 * @param id Id vrcholu.
 * @param WKT  Reálné souřadnice vrcholu.
 * @return vertex* Ukazatel na nově dynamicky alokovanou instanci struktury vertex.
 */
vertex *veretx_create(const int id, const char *WKT);

/**
 * @brief  Funkce pro uvolnění instance vrcholu.
 * 
 * @param poor Uvolňovaná instance vrcholu.
 */
void vertex_destroy(vertex **poor);

#endif
