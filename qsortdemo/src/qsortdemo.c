/**
 * @file qsortdemo.c
 * @author František Pártl (fpartl@kiv.zcu.cz)
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stddef.h>

/* 
    Takhle to vychází mně:
        a) Implementace funkce swap v tomto souboru                                 ? s
        b) Impelemntace funkce swap v assembleru                                    ? s
        c) Impelementace funkce swap v tomto souboru s -O3                          ? s

    Měření byla samozřejmě prováděna bez výpisu a s NUMBER_COUNT 200000000.
*/

#define USE_DYNAMIC_ALLOCATION

/** @brief Počet generovaných čísel, která budou následně řazena algoritmem Quicksort. */
#define NUMBER_COUNT 20
/* #define NUMBER_COUNT 2090000 */
/* #define NUMBER_COUNT 200000000 */

/**
 * @brief Volíme zde konstantní seed generátoru náhodných čísel. Co to znamená a proč to děláme? 
 */
#define SRAND_SEED 42

/** @brief Při deklaraci tohoto symbolu bude proveden výpis dat před a po jejich seřazení. */
#define PRINT_INFO

/** 
 * @brief Při deklaraci tohoto symbolu budou přeloženy a spuštěny testy správnosti řešení
 *        problému. Tohle je trošku "prasárna". Testy by měly být umístěny v oddělném projektu
 *        v adresáři test! Ale jenom pro ukázku...
 */
/* #define BUILD_TESTS */

/**
 * @brief Vytvoří dynamicky alokované pole, které naplní size náhodně generovanými celými
 *        čísly ...otázka: Proč je zde použita dynamická alokace paměti, když počet prvků 
 *        v tomto případě známe už při překladu programu?
 * @param size Počet náhodných prvků generovaného pole.
 * @return Ukazatel na nově dynamicky alokované pole nebo NULL při chybě.
 */
void fill_array(int array[], const size_t size) {
    size_t i;

    if (!array || size == 0) {
        return;
    }

    srand(SRAND_SEED);        /* Inicializace generátoru náhodných čísel. */
    for (i = 0; i < size; ++i) {
        array[i] = rand();
    }
}

/**
 * @brief Vypíše size prvků pole array na standardní výstup programu. Pokud ukazatel
 *        na pole neplatný nebo má pole nulovou délku, funkce neprovede žádnou akci.
 * @param array Pole celých čísel, které bude tištěno.
 * @param size Počet tištěných prvků.
 */
void print_array(const int *array, const size_t array_size) {
    size_t i;

    if (!array || array_size == 0) {
        return;
    }

    for (i = 0; i < array_size; ++i) {
        printf("%2ld. %15d\n", i, array[i]);
    }
}

/**
 * @brief Prohodí hodnoty dvou proměnných, které jsou dány zadanými ukazateli. Pokud
 *        je některý z ukazatelů neplatný, funkce neprovede žádnou akci.
 * @param a Ukazatel na první proměnnou.
 * @param b Ukazatel na druhou proměnnou.
 */
void swap(int *a, int *b) {
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Funkci můžu samozřejmě pouze deklarovat a její tělo definovat v jiném souboru.
 *        Volací konvence __fastcall znamená, že parametry nebudou předávány prostřednicvím
 *        zásobníku, ale pomocí registrů ECX a EDX.
 */
/* extern void __fastcall swap(int *, int *); */

/**
 * @brief Rekurzivní implementace řadícího algoritmu Quicksort.
 * @param array Pole řazených prvků. 
 * @param first Index první prvku 
 * @param last Index posledního prvku.
 */
void quicksort(int *array, int first, int last){
    int fi = first, li = last;

    /* Žádný optimalizátor nám tohle nevyřeší. ;-) */
    const int pivot = first;

    if (!array || first >= last) {
        return;
    }

    while (fi < li) {
        while (array[fi] <= array[pivot] && fi < last) fi++;
        while (array[li] > array[pivot]) li--;

        if (fi < li) {
            swap(&array[fi], &array[li]);
        }
    }

    swap(&array[pivot], &array[li]);
    quicksort(array, first, li - 1);
    quicksort(array, li + 1, last);
}

/**
 * @brief Funkce pro zkontrolování správnosti výsledku řazení. Taková funkce by v ideálním případě 
 *        nebyla zde, ale byla by umístěna v samostatném spustitelném souboru v adresáři test. Vzpomínáte
 *        na standardní adresářovou strukturu v C/C++ projektech? V adresáři test by pak byl makefile, který
 *        přeloží všechny připravené testy.
 * @param numbers Pole ideálně vzestupně seřazených hodnot. 
 * @param size Počet prvků pole numbers.
 * @return int 1, pokud test dopadl dobře, jinak 0.
 */
int test_ascendess(const int *numbers, const size_t size) {
    size_t i;

    for (i = 1; i < size && numbers[i] >= numbers[i - 1]; ++i);

    return i == size;
}

/**
 * @brief Hlavní přístupový bod aplikace, která vygeneruje NUMBER_COUNT čísel, které 
 *        seřadí algoritmem QuickSort.
 * @return int Vrací EXIT_SUCCESS při úspěchu, jinak EXIT_FAILURE.
 */
int main() {
    clock_t tic, toc;

#ifdef USE_DYNAMIC_ALLOCATION
    int *numbers;

    numbers = (int *)malloc(NUMBER_COUNT * sizeof(int));
    if (!numbers) {
        printf("Tolik mista nam operacni system nechce dat...\n");
        return EXIT_FAILURE;
    }
#else
    int numbers[NUMBER_COUNT];
#endif

    printf("%ld\n", sizeof(numbers));
    fill_array(numbers, NUMBER_COUNT);

#ifdef PRINT_INFO
    printf("Vygenerovane hodnoty:\n");
    print_array(numbers, NUMBER_COUNT);
    printf("\n");
#endif

    /* Spustím algoritmus Quicksort a měřím čas. */
    tic = clock();
    quicksort(numbers, 0, NUMBER_COUNT - 1);
    toc = clock();
    printf("Quicksort razeni trvalo: %0.3f sekund.\n", (double)(toc - tic) / CLOCKS_PER_SEC);

#ifdef PRINT_INFO
    printf("\nSerazene hodnoty:\n");
    print_array(numbers, NUMBER_COUNT);
#endif

/* 
    Tohle je trošku prasárna! Testy by měly být spouštěny v rámci odděleného projektu v adresáři test! 
       V tomto projektu by pak byly includovány patřičné hlavičkové soubory s prototypy testovaných řadících 
       funkcí atd. Ale buďme realisté... tenhle náš malý projekt je sám o sobě takový test.
*/
#ifdef BUILD_TESTS 
    printf("\nVysledek testu: %s!\n", test_ascendess(numbers, NUMBER_COUNT) ? "OK" : "CHYBA");
#endif

    return EXIT_SUCCESS;
}
