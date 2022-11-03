/**
 * @file maxflow.h
 * @author Daniel Cífka (dcifka20@students.zcu.cz)
 * @brief Hlavičkový soubor pro knihovnu funkcí počítající maximalní tok grafu pomocí Edmondsův–Karpův algoritmus pro problém s maximálním tokem.
 * @version 1.0
 * @date 2022-01-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _MAXFLOW_H
#define _MAXFLOW_H

/** Standartní knihovny jazyka C. */
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

/** Importované hlavičkové soubory pro výpočet maximálního toku pomocí Edmondsův–Karpův algoritmus. */
#include "edge.h"
#include "vertex.h"
#include "vector.h"
#include "matrix.h"
#include "graph.h"
#include "queue.h"

/**
 * @brief Funkce pro vyhledávaní nejkratší cesty mezi počátečním a koncovým uzerl za pomoci metody BFS (Prohledávání do šířky)
 * 
 * @param residual Matice měnících se kapacit hran.
 * @param source Počáteční vrchol grafu maximálního toku.
 * @param target Koncový vrchol grafu maximálního toku.
 * @param parents Dynamicky alokované pole pro uchování svého předka.
 * @param vector_vertex Vector vrcholů grafu.
 * @return int* Ukazatel na dynamicky alokované pole, které v sobě uchovává předka daného vrcholu.
 */
int *BFS (matrix *residual, const size_t  source, const size_t  target, int *parents, const vector_t *vector_vertex);

/**
 * @brief Funkce pro porovnání aktuálního nalezeného toku a předcházející nalezeného toku.
 * 
 * @param current Nově zjištěná hodnota maximálního toku.
 * @param last Předchozí zjištěná hodnota maximálního toku.
 * @return int Vracím vybranou hodnotu maximálního toku.
 */
int min_flow(int current, int last);

/**
 * @brief Fuknce zjištující maximální tok grafem za použití Edmonds–Karpova algoritmu pro problém s maximálním tokem.
 * 
 * @param capacity Matice kapacit hran
 * @param real_vector Vector uchovávající skutečný id hran, které byli načteny.
 * @param vector_vertex Vector vrcholů grafu.
 * @param vector_edge Vector hran grafu.
 * @param source Počáteční vrchol.
 * @param target Koncový vrchol.
 * @return vector_t* Ukazatel na nově dynamicky alokovanou instanci struktury vector_t, který uchovává hrany minimálního řezu.
 */
vector_t *max_flow(matrix *capacity, const vector_t *real_vector, const vector_t *image_vector, const vector_t *vector_vertex, const vector_t *vector_edge, const size_t source, const size_t target);

#endif