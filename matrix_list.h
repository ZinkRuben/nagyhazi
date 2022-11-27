
//
// Created by Zear on 11/22/2022.
//

#ifndef NAGYHAZI_MATRIX_LIST_H
#include "struct.h"
#include "debugmalloc.h"
#include "string.h"
#include "matrix_io.h"
#include "matrix_lib.h"

void remove_list_item(m_list* first, char* name);
void free_list(m_list* first);
m_list* find_matrix(m_list* first, char* to_find);
void m_list_append(m_list** first, matrix m, char* name);
void list_all_matrices(m_list* first);
void print_all_matrices(m_list* first);
matrix find_user_named_matrix(m_list *strazsa);
#define NAGYHAZI_MATRIX_LIST_H

#endif //NAGYHAZI_MATRIX_LIST_H
