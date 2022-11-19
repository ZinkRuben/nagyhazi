//
// Created by Zear on 11/13/2022.
//
#include "matrix_operations.h"
#include "line_operations.h"
#include "debugmalloc.h"

// a paraméterként kapott mátrixot megszorozza a paraméterként kapott skalárral, !megváltoztatja a paraméterként kapott mátrixot!
void m_skalar_multip(matrix m, double skalar) {
    for (int i = 0; i < m.height; i++) {
        for (int j = 0; j < m.width; j++) {
            m.rows[i][j] *= skalar;
        }
    }
}
//the two matrices has to be the same size
//free a hívó felelőssége
matrix m_addition(matrix m1, matrix m2) {
    matrix result;
    if (m1.height != m2.height || m1.width != m2.width) {
        result.width = 0;
        result.height = 0;
        return result;
    } else {
        result.height = m1.height;
        result.width = m1.width;
    }
    for (int i = 0; i < result.height; i++) {
        result.rows[i] = add_lines(m1.rows[i], m2.rows[i], result.width);
    }

}

matrix swap_lines(matrix m, int index1, int index2) {
    double *temp = m.rows[index1];
    m.rows[index1] = m.rows[index2];
    m.rows[index2] = temp;
}



