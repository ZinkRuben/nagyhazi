//
// Created by Zear on 11/13/2022.
//
#include "matrix_lib.h"
#include <stdlib.h>
#include "debugmalloc.h"

matrix m_cpy(matrix m) {
    double **rows = (double **) malloc(m.height * sizeof(double *));
    for (int i = 0; i < m.height; i++) {
        double *temp_ptr = (double *) malloc(m.width * sizeof(double));
        memcpy(temp_ptr, m.rows[i], sizeof(double) * m.width);
        rows[i] = temp_ptr;
    }
    matrix result = {m.height, m.width, rows};


    return result;
}


//frees up memory allocated to a matrix
void free_matrix(matrix m) {
    for (int i = 0; i < m.height; i++) {
        free(m.rows[i]);
    }
    free(m.rows);
}


