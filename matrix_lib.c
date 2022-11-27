//
// Created by Zear on 11/13/2022.
//
#include "matrix_lib.h"
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
    if (m.height != 0 && m.width != 0) {
        for (int i = 0; i < m.height; i++) {
            free(m.rows[i]);
        }
        free(m.rows);
    }
}
matrix m_create(int height, int width) {
    double** rows = (double**)malloc(sizeof(double*)*height);
    for(int i = 0; i < height; i++) {
        double* curr_row = (double*)malloc(sizeof(double)*width);
        rows[i] = curr_row;
    }
    matrix result = {height, width, rows};
    return result;
}



