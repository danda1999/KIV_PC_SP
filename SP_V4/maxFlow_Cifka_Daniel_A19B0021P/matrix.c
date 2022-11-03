/**
 * \file matrix.c
 * \brief Soubor obsahující implementace operací se strukturou matrix.
 */

#include "matrix.h"

matrix *matrix_create(const size_t rows, const size_t cols, const mat_num_t i_val) {
    matrix *new_mat;

    if (rows == 0 || cols == 0) {
        return NULL;
    }

    new_mat = (matrix *)malloc(sizeof(matrix));
    if (!new_mat) {
        return NULL;
    }

    new_mat->rows = rows;
    new_mat->cols = cols;

    new_mat->items = (mat_num_t *)malloc(rows * cols * sizeof(mat_num_t));
    if (!new_mat->items) {
        free(new_mat);
        return NULL;
    }

    matrix_fill(new_mat, i_val);
    return new_mat;
}

void matrix_fill(matrix *mat, const mat_num_t val) {
    size_t i;

    if (!mat || !mat->items) {
        return;
    }

    for (i = 0; i < mat->cols * mat->rows; ++i) {
        mat->items[i] = val;
    }
}

void matrix_print(const matrix *mat) {
    size_t r, c;

    if (!mat || !mat->items) {
        printf("| NULL |\n\n");
        return;
    }

    for (r = 0; r < mat->rows; ++r) {
        printf("| ");

        for (c = 0; c < mat->cols; ++c)
            printf(MAT_NUMBER_FORMAT, matrix_get(mat, r, c));

        printf("|\n");
    }

    printf("\n");
}

void matrix_free(matrix **poor) {
    if (!poor || !*poor)
        return;

    (*poor)->cols = 0;
    (*poor)->rows = 0;

    free((*poor)->items);
    (*poor)->items = NULL;

    free(*poor);
    *poor = NULL;
}

mat_num_t matrix_get(const matrix *mat, const size_t row, const size_t col) {
    return mat->items[row * mat->cols + col];
}

void matrix_set(matrix *mat, const size_t row, const size_t col, mat_num_t val) {
    if (!mat || !mat->items) {
        return;
    }

    mat->items[row * mat->cols + col] = val;
}

matrix *matrix_add(const matrix *a, const matrix *b) {
    matrix *temp;
    size_t i;

    if (!a || !a->items || !b || !b->items) {
        return NULL;
    }

    if (a->rows != b->rows || a->cols != b->cols) {
        return NULL;
    }

    temp = matrix_create(a->rows, a->cols, 0);
    if (!temp) {
        return NULL;
    }

    for (i = 0; i < a->rows * a->cols; ++i) {
        temp->items[i] = a->items[i] + b->items[i];
    }

    return temp;
}

matrix *matrix_mul(const matrix *a, const matrix *b) {
    matrix *temp;
    size_t ar, bc, ac;
    mat_num_t mult_temp;

    if (!a || !a->items || !b || !b->items) {
        return NULL;
    }

    if (a->cols != b->rows) {
        return NULL;
    }

    temp = matrix_create(a->rows, b->cols, 0.0);
    if (!temp) {
        return NULL;
    }

    for (ar = 0; ar < a->rows; ++ar) {
        for (bc = 0; bc < b->cols; ++bc) {
            mult_temp = 0;

            for (ac = 0; ac < a->cols; ++ac)
                mult_temp += matrix_get(a, ar, ac) * matrix_get(b, ac, bc);

            matrix_set(temp, ar, bc, mult_temp);
        }
    }

    return temp;
}

void matrix_mul_scal(matrix *mat, const mat_num_t scal) {
    size_t i;

    if (!mat || !mat->items) {
        return;
    }

    for (i = 0; i < mat->cols * mat->rows; ++i)
        mat->items[i] *= scal;
}

void matrix_move(matrix **target, matrix **source) {
    if (!target || !source || !*source || !(*source)->items) {
        return;
    }

    if (*target && (*target)->items) {
        matrix_free(target);
    }

    *target = *source;
    *source = NULL;
}
