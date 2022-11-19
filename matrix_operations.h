//
// Created by Zear on 11/13/2022.
//

#ifndef NAGYHAZI_MATRIX_OPERATIONS_H
#define NAGYHAZI_MATRIX_OPERATIONS_H
#include "struct.h"
void m_skalar_multip(matrix m, double skalar);

matrix m_addition(matrix m1, matrix m2);

matrix swap_lines(matrix m, int index1, int index2);
#endif //NAGYHAZI_MATRIX_OPERATIONS_H
