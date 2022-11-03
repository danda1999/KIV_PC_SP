/**
 * @file input.h
 * @author Daniel Cífka (dcifka20@students.zcu.cz)
 * @brief Hlavičkový soubor knihovny pro načítání dat z csv souboru.
 * @version 1.0
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _INPUT_H
#define _INPUT_H

/** Standartní knihovny jazyka C. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Importované hlavičkové soubory pro ukládání načtených dat. */
#include "vertex.h"
#include "edge.h"
#include "vector.h"

/** @brief Používaný znak pro k oddělování hodnot v CSV souboru. */
#define CSV_DELIMETER ","

/** @brief Velikost načítacího bufferu. */
#define CHAR_BUFFER_SIZE 10000

/** @brief Hodnota pro kontrolu hlavičky CSV souboru hran. */
#define EDGE_HEADER 1

/** @brief Hodnota pro kontrolu hlavičky CSV souboru vrcholů. */
#define VERTEX_HEADER 0

/**
 * @brief Metoda pro načítání vrcholů ze zadaného CSV souboru.
 * 
 * @param input_vertex_file Cesta k souboru pro načtení vrcholů.
 * @return vector_t* Ukazatel na nově dynamicky alokovanou instanci struktury vector_t, který uchovává načtené vrcholy grafu.
 */
vector_t *vertex_loader(const char *input_vertex_file);

/**
 * @brief Metoda pro načítání hran ze zadaného CSV souboru.
 * 
 * @param input_edge_file Cesta k souboru pro načtení hran.
 * @param isvalid_a Hodnota, která určí načítaní pouze hran s hodnotou isvalid = True nebo i s hodnotou isvalid = False.
 * @return vector_t*  Ukazatel na nově dynamicky alokovanou instanci struktury vector_t, který uchovává načtené hrany grafu.
 */
vector_t *edge_loader(const char *input_edge_file, const int isvalid_a);

/**
 * @brief Metoda pro kontrolu duplicit v souboru vrcholů.
 * 
 * @param vector_vertex Vector uchovávající doposud načtené vrcholy.
 * @param id Id načteného vrcholu.
 * @return int Hodnotu 0 pokud byla nalezena duplicita nebo neplatný vstupní argument, hodnotu 1 pokud duplicita nebyla nalezena.
 */
int duplicity_check_vertex(const vector_t * vector_vertex, const int id);

/**
 * @brief Metoda pro kontrolu duplicit v souboru hran.
 * 
 * @param vector_edge Vector uchovávající doposud načtené hrany.
 * @param id Id načtené hrany.
 * @return int Hodnotu 0 pokud byla nalezena duplicita nebo neplatný vstupní argument, hodnotu 1 pokud duplicita nebyla nalezena.
 */
int duplicity_check_edge(const vector_t * vector_edge, const int id);

/**
 * @brief Metoda kontrolující správnost hlavičky CSV souboru.
 * 
 * @param header Načtená hlavička CSV souboru.
 * @param v_e_check číselná hodnota pro volbu kontroly hlavičky CSV souboru.
 * @return int Číselná hodnota 0 pokud je hlavička rovna definované hlavičce, -1 pokud hlavička neni definována.
 */
int header_check(char *header, const int v_e_check);

/**
 * @brief Metoda kontrulující zdali zadaný zdrojový nebo cílový vrchol se nachazí ve vectoru vrcholů.
 * 
 * @param vector_vertex Vectoru načtených vrcholů.
 * @param id Id zdrojového nebo cílového vrcholu.
 * @return int Hodnota 0 pokud se vrchol nachází ve vectoru vrcholů, hodnota 1 pokud se vrchol nenachází ve vectoru vrcholů.
 */
int check_vertex_in_graph(const vector_t *vector_vertex, const int id);

#endif

