//
// Created by Zear on 11/13/2022.
//

#ifndef NAGYHAZI_MATRIX_OPERATIONS_H
#define NAGYHAZI_MATRIX_OPERATIONS_H
#include "struct.h"
void m_scalar_multip(matrix m, double skalar);

matrix m_multip(matrix left, matrix right);

matrix m_addition(matrix m1, matrix m2);

void swap_lines(matrix m, int index1, int index2);

double find_biggest_abs_in_matrix(matrix m);
//uj matrixot foglal, free a hivo felelossege
matrix gauss_elimination(matrix m);

int matrix_rank(matrix m);
#endif //NAGYHAZI_MATRIX_OPERATIONS_H
