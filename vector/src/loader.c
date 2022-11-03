/**
 * @file loader.c
 * @author František Pártl (fpartl@kiv.zcu.cz)
 * @brief Příklad, na kterém si ukážeme načítání dat ze souborů do dynamicky realokovaného pole.
 * @version 1.0
 * @date 2020-12-07
 */

#include <stdio.h>
#include <stdlib.h>

#include "person.h"
#include "vector.h"

#define TODO(message) \
    printf(__FILE__":%d This has not been implemented yet: "#message"!\n", __LINE__);

/** @brief Používaný znak k oddělování hodnotu v CSV souboru. */
#define CSV_DELIMETER ";"

/** @brief Souboru s načítanými osobami. */
#define PERSON_FILE "../data/persons.csv"

/** @brief Soubor s načítanými integery. */
#define INTEGER_FILE "../data/integers.txt"

/** @brief Velikost načítacího bufferu. */
#define CHAR_BUFFER_SIZE 256

/**
 * @brief Ukázka načítání integerů.
 */
void integer_loader() {
    char line[CHAR_BUFFER_SIZE] = { 0 };
    vector_t *numbers;
    FILE *file;
    size_t i;
    int temp;

    file = fopen(INTEGER_FILE, "r");
    if (!file) {
        return;
    }

    numbers = vector_create(sizeof(int), NULL);
    if (!numbers) {
        goto clean_and_exit;
    }

    while (fgets(line, CHAR_BUFFER_SIZE, file)) {
        temp = atoi(line);

        if (!vector_push_back(numbers, &temp)) {
            goto clean_and_exit;
        }
    }

    for (i = 0; i < vector_count(numbers); ++i) {
        printf("%d\n", *(int *)vector_at(numbers, i));
    }

  clean_and_exit:
    vector_destroy(&numbers);
    fclose(file);
}

/**
 * @brief Ukázka načítání osob.
 */
void person_loader() {
    char line[CHAR_BUFFER_SIZE] = { 0 }, *name;
    int age, shoe_size;
    FILE *file;
    size_t i;           /* Bude se hodit. */
    vector_t *persons;
    person_t *p;

    #define clean_and_exit()        \
        vector_destroy(&persons);   \
        fclose(file);               \
        return;

    file = fopen(PERSON_FILE, "r");
    if (!file) {
        return;
    }

    persons = vector_create(sizeof(person_t *), (vec_it_dealloc_t)person_destroy);
    if (!persons) {
        return;
    }

    while (fgets(line, CHAR_BUFFER_SIZE, file)) {
        if (strlen(line) == 0) {
            continue;
        }

        age = atoi(strtok(line, CSV_DELIMETER));
        shoe_size = atoi(strtok(NULL, CSV_DELIMETER));
        name = strtok(NULL, CSV_DELIMETER);
        name[strcspn(name, "\r\n")] = 0;

        p = person_create(name, age, shoe_size);
        if (!p) {
            clean_and_exit();
        }

        vector_push_back(persons, &p);
    }

    TODO("Vypis vektoru instanci struktury person_t!");
    /* 
     * Uvědomte si, co přesně je uloženo ve vektoru persons (přesný datový typ).
     * Prvek z vektoru vyberte pomocí funkce vector_at a opět se důkladně zamyslete nad tím, co tato funkce vrací.
     * Instanci struktury person_t je možné vypsat pomocí funkce person_print, která je deklarována v person.h.
     */

    clean_and_exit();
    #undef clean_and_exit
}

/**
 * @brief Hlavní přístupový bod aplikace.
 * @return int Vždy vrací hodnotu EXIT_SUCCESS.
 */
int main() {
    integer_loader();
    person_loader();

    return EXIT_SUCCESS;
}