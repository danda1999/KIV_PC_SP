/**
 * \file matrix.h
 * \brief Hlavičkový dokument struktury matice.
 *
 * Soubor obsahuje definici struktury matrix, která představuje obecnou dvourozměrnou matici
 * s položkami typu mat_num_t. Obsahuje rovněž definice operací sčítání a násobení nad maticemi.
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

/**< Definice formátu pro výpis položek matice. */
#define MAT_NUMBER_FORMAT "%05.2f "

/**< Definice typu pro položky obsažené v matici. */
typedef double mat_num_t;

/**
 * \struct matrix
 * \brief Struktura představující matici s položkami typu mat_num_t.
 */
typedef struct _matrix {
    size_t rows;            /**< Počet řádků matice. */
    size_t cols;            /**< Počet sloupců matice. */
    mat_num_t *items;       /**< Ukazatel na data matice. */
} matrix;

/**
 * \brief matrix_create Funkce dynamicky alokuje novou matici o daných rozměrech
 *                      a jejích položky nastaví na hodnotu i_val.
 * \param rows Počet řádků nové matice.
 * \param cols Počet soupců nové matice.
 * \param i_val Hodnota položek nové matice.
 * \return Ukazatel na nově vytvořenou matici nebo NULL při chybě.
 */
matrix *matrix_create(const size_t rows, const size_t cols, const mat_num_t i_val);

/**
 * \brief matrix_fill Funkce nastaví položky zadané matice mat na hodnotu val.
 * \param mat Ukazatel na matici, jejíž položky budou nastaveny.
 * \param val Nová hodnota položek matice.
 */
void matrix_fill(matrix *mat, const mat_num_t val);

/**
 * \brief matrix_print Funkce vytiskne matici do standardního výstupu.
 * \param mat Ukazatel na vypisovanou matici.
 */
void matrix_print(const matrix *mat);

/**
 * \brief matrix_free Funkce provede uvolnění dynamicky alokované matice.
 * \param poor Ukazatel na ukazatel na matici určenou k uvolnění.
 */
void matrix_free(matrix **poor);

/**
 * \brief matrix_at Funkce vrací hodnotu prvku matice na daných souřadnicích. Funkce nekontroluje
 *                  rozsah zadaného řádku a sloupce -- při nesprávném použití může dojít k segmentační
 *                  chybě.
 * \param mat Ukazatel na matici z níž bude prvek vybírán.
 * \param row Řádek matice.
 * \param col Sloupec matice.
 * \return Hodnota prvku matice na daných souřadnicích.
 */
mat_num_t matrix_get(const matrix *mat, const size_t row, const size_t col);

/**
 * \brief matrix_set Funkce nastaví hodnotu prvku matice na daných souřadnicích na hodnotu val.
 * \param mat Ukazatel na matici, jejíž prvek bude nastavován.
 * \param row Řádek matice.
 * \param col Sloupec matice.
 * \param val Nová hodnotu prvku na daných souřadnicích.
 */
void matrix_set(matrix *mat, const size_t row, const size_t col, mat_num_t val);

/**
 * \brief matrix_add Funkce provede sečtení dvou zadaných matic. Vstupní matice musí mít stejné rozměry.
 *                   Výsledek operace bude dynamicky alokován a vráce v podobě ukazatele.
 * \param a První sčítanec.
 * \param b Druhý sčítanec.
 * \return Ukazatel součet matic, nebo NULL při chybě.
 */
matrix *matrix_add(const matrix *a, const matrix *b);

/**
 * \brief matrix_mul Funkce provede vynásobení zadaných matic. Počet sloupců matice a musí být stejný
 *                   jako počet řádků matice b.
 * \param a První činitel.
 * \param b Druhý činitel.
 * \return Ukazatel na součin matic, nebo NULL při chybě.
 */
matrix *matrix_mul(const matrix *a, const matrix *b);

/**
 * \brief matrix_mul_scal Fukce vynásobí položky matice mat skalárem scal.
 * \param mat Ukazatel na matici, jejíž položky budou násobeny.
 * \param scal Skalár, kterým se bude násobit.
 */
void matrix_mul_scal(matrix *mat, const mat_num_t scal);

/**
 * \brief matrix_move Funkce přesune matici source do matice target. Pokud již matice target
 *                    obsahuje nějaká data, budou automaticky uvolněna. Dereferencovaný ukazatel
 *                    source bude nastaven na hodnotu NULL.
 * \param target Cílová matice.
 * \param source Zdrojová matice.
 */
void matrix_move(matrix **target, matrix **source);

#endif
