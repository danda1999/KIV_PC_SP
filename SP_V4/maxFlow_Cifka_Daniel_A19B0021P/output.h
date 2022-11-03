/**
 * @file output.h
 * @author Daniel Cífka (dcifka20@students.zcu.cz)
 * @brief Hlavičkový soubor knihovny pro zapis dat do csv souboru.
 * @version 1.0
 * @date 2022-01-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Standartní knihovny jazyka C. */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/** Importované hlavičkové soubory pro zapis dat do souboru. */
#include "vector.h"
#include "edge.h"

/**
 * @brief Funkce pro zápis dat do CSV souboru.
 * 
 * @param output_file Cesta k výstupnímu souboru.
 * @param minimal_cut Vector uložených hran minimálních řezu. 
 * @return int Hodnotu 0 pokud vše proběhlo úspěšně, hodnotu 1 pokud nebyli validní vstupní argumenty nebo nastala nějaká chyba pri zápisu.
 */
int write_file(const char *output_file, const vector_t *minimal_cut);

/**
 * @brief Funce pro porovaní dvou prvku v poli. 
 * Funkce využita knihovní funkcí qsort.
 * 
 * @param a Ukazatel prvek v poli.
 * @param b Ukazatel prvek v poli.
 * @return int Kladná hodnota pokud má být prvek b přd prvkem a, zápornou hodnotu pokud prvek a má být před prvkem b a nula pokud jsou si rovny
 */
int cmpfunc(const void * a, const void * b);