#ifndef NAGYHAZI_STRUCT_H
#define NAGYHAZI_STRUCT_H
typedef struct matrix {
    int height, width;
    double **rows;
} matrix;

typedef struct m_list {
    matrix data;
    struct m_list* next;
    char name[31];
}m_list;




#endif
