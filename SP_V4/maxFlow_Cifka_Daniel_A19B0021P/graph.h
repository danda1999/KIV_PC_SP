/**
 * @file graph.h
 * @author Daniel Cífka (dcifka20@students.zcu.cz)
 * @brief Hlavičkový soubor pro tvorbu a práci s grafem.
 * @version 1.0
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _GRAPH_H
#define _GRAPH_H

/** Standartní knihovny jazyka C. */
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

/** Importované hlavičkové soubory pro práci s příslušnými datovými strukturami. */
#include "vector.h"
#include "matrix.h"
#include "edge.h"
#include "vertex.h"

/**
 * @brief Funkce pro tvorbu vectoru obsahující skutečný id hran.
 * 
 * @param vector_vertexs Vector vrcholů grafu.
 * @return vector_t* Ukazatel na dynamicky alokovanou strukturu vector_t, obsahující skutečný id hran.
 */
vector_t *get_real_vector(const vector_t *vector_vertexs);

/**
 * @brief Funkce pro tvorbu vectoru obsahující imaginární id hran.
 * 
 * @param vector_vertexs Vector vrcholů grafu.
 * @return vector_t* Ukazatel na dynamicky alokovanou strukturu vector_t, obsahující imaginární id hran.
 */
vector_t *get_image_vector(const vector_t *vector_vertexs);

/**
 * @brief Funkce pro tvorbu matice kapacit.
 * 
 * @param real_vector Vector skutečných id hran.
 * @param image_vector Vector imaginárních id hran.
 * @param vector_edges Vector načtených hran grafu.
 * @return matrix* Ukazatel na dynamicky alokovanou strukturu matrix, která obsahuje kapacity hran.
 */
matrix *capacity_matrix(const vector_t *real_vector, const vector_t *image_vector, const vector_t *vector_edges);

/**
 * @brief Funkce vrací imaginární id skutečné hrany, kde id sktečné hrany je shodné s předaným id.
 * 
 * @param real_vector Vector reálných id hran.
 * @param image_vector Vector imaginárních id hran.
 * @param id Id hrany kterou hledám.
 * @return int Imaginární id hledáný hrany.
 */
int get_image_id_from_real(const vector_t *real_vector, const vector_t *image_vector, const int id);

/**
 * @brief Funkce vrací skutečný id imaginární hrany, kde id imaginární hrany je shodné s předaným id.
 * 
 * @param real_vector Vector reálných id hran.
 * @param image_vector Vector imaginárních id hran.
 * @param id Id hrany kterou hledám.
 * @return int Skutečný id hledáný hrany.
 */
int get_real_id_from_image(const vector_t *real_vector, const vector_t *image_vector, const int id);

/**
 * @brief Funkce vrátí hranu, která obsahuje předaný parametry v argumentech.
 * 
 * @param vector_edges Vector načtených hran.
 * @param source Počátečná vrchol.
 * @param target Koncový vrchol.
 * @param capacity Kapacita hrany.
 * @return edge* Ukazatel na dynamicky alokovanou strukturu edge, představující hranu grafu.
 */
edge *get_edge(const vector_t *vector_edges, const int source, const int target, const int capacity);

#endif