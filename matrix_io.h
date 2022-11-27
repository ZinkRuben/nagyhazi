//
// Created by Zear on 11/13/2022.
//
#ifndef NAGYHAZI_MATRIX_IO_H
#define NAGYHAZI_MATRIX_IO_H
#include "struct.h"
void mprint(matrix m);
matrix read_matrix_f(char *filename);
void write_matrix_f(char *filename, matrix m);
#endif //NAGYHAZI_MATRIX_IO_H
