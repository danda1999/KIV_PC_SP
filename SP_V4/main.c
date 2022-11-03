/**
 * @file main.c
 * @author Daniel Cífka (dcifka20@students.zcu.cz)
 * @brief Hlavní soubor, kde se volají přslušené metody pro vykonání Edmonds–Karpova algoritmu, který řeší problém s maximálním tokem.
 * @version 1.0
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Standartní knihovny jazyka C. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Importované hlavičkové soubory pro práci s příslušnými datovými strukturami a potřebnými výpočetními funkcemi. */
#include "input.h"
#include "vertex.h"
#include "edge.h"
#include "vector.h"
#include "graph.h"
#include "matrix.h"
#include "maxflow.h"
#include "output.h"



int main(int argc, char** argv) {
    vector_t *vector_vertexs = NULL, *vector_edges = NULL, *real_vector = NULL, *image_vector = NULL, *minimal_cut = NULL;
    matrix *capacity = NULL;
    int source = -1, target = -1, isvalid_a = 0;
    int i = 0;
    char *input_edges_file = NULL, *input_vertex_file = NULL, *output_file = NULL;

    /* Kontrola počtu vstupních argumentů */
    if(8 < argc  && argc < 13)  {
        for (i = 1; i < argc; ++i) /* Průchod vstupními argumenty a nastavování příslušných proměných vstupními argumenty. */
        {
            if(strcmp(argv[i], "-v") == 0) {
                input_vertex_file = argv[i + 1];
            } else if(strcmp(argv[i], "-e") == 0) {
                input_edges_file = argv[i + 1];
            } else if(strcmp(argv[i], "-s") == 0) {
                source = atoi(argv[i + 1]);
            } else if(strcmp(argv[i], "-t") == 0) {
                target = atoi(argv[i + 1]);
            } else if(strcmp(argv[i], "-a") == 0) {
                isvalid_a = 1;
            } else if(strcmp(argv[i], "-out") == 0) {
                output_file = argv[i + 1];
            }
        }

        if(!input_edges_file || !input_vertex_file || source == -1 || target == -1) { /* Kontrla zdali byli zadány povinné vstupní argumenty. */
            printf("Not all required input arguments are specified.\n");
            return EXIT_FAILURE;
        }

    } else {
        printf("The number of input arguments is not within the allowed range.\n");
        return EXIT_FAILURE;
    }

    vector_vertexs = vertex_loader(input_vertex_file);
    if(!vector_vertexs) {
        printf("Invalid vertex file.\n");
        return 1;
    }

    vector_edges = edge_loader(input_edges_file, isvalid_a);
    if(!vector_edges) {
        printf("Invalid edge file.\n");
        vector_destroy(&vector_vertexs);
        return 2;
    }

    if(check_vertex_in_graph(vector_vertexs, source) == 1) {
        printf("Invalid source vertex.\n");
        vector_destroy(&vector_edges);
        vector_destroy(&vector_vertexs);
        return 3;
    }

    if(check_vertex_in_graph(vector_vertexs, target) == 1 || source == target) {
        printf("Invalid sink vertex.\n");
        vector_destroy(&vector_edges);
        vector_destroy(&vector_vertexs);
        return 4;
    }

    real_vector = get_real_vector(vector_vertexs);
    if(!real_vector) {
        printf("A helper vector for parsing real id to imaginary could not be created.\n");
        vector_destroy(&vector_edges);
        vector_destroy(&vector_vertexs);
        return EXIT_FAILURE;
    }

    image_vector = get_image_vector(vector_vertexs);
    if(!image_vector) {
        printf("A helper vector for parsing real id to imaginary could not be created.\n");
        vector_destroy(&real_vector);
        vector_destroy(&vector_edges);
        vector_destroy(&vector_vertexs);
        return EXIT_FAILURE;
    }

    capacity = capacity_matrix(real_vector, image_vector, vector_edges);
    if(!capacity) {
        printf("Capacity matrix not created.\n");
        vector_destroy(&real_vector);
        vector_destroy(&vector_edges);
        vector_destroy(&vector_vertexs);
        return EXIT_FAILURE;
    }

    minimal_cut = max_flow(capacity, real_vector, image_vector, vector_vertexs, vector_edges, get_image_id_from_real(real_vector, image_vector, source), get_image_id_from_real(real_vector, image_vector, target));
    if(!minimal_cut) {
        printf("Minimal section vector was not created.\n");
        matrix_free(&capacity);
        vector_destroy(&image_vector);
        vector_destroy(&real_vector);
        vector_destroy(&vector_edges);
        vector_destroy(&vector_vertexs);
        return 6;
    
    }
    
    if(output_file != NULL && write_file(output_file, minimal_cut) == 1)
    {
        printf("Invalid output file.\n");
        vector_destroy(&minimal_cut);
        matrix_free(&capacity);
        vector_destroy(&image_vector);
        vector_destroy(&real_vector);
        vector_destroy(&vector_edges);
        vector_destroy(&vector_vertexs);
        return 5;
    }

    vector_destroy(&minimal_cut);
    matrix_free(&capacity);
    vector_destroy(&image_vector);
    vector_destroy(&real_vector);
    vector_destroy(&vector_edges);
    vector_destroy(&vector_vertexs);
    return EXIT_SUCCESS;
}