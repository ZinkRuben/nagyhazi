//
// Created by Zear on 11/13/2022.
//
#include "matrix_io.h"
#include <stdio.h>
#include "debugmalloc.h"
#include "matrix_operations.h"
#include <math.h>
#include "matrix_list.h"


matrix read_matrix_f(char *filename) {
    FILE *ptr;
    ptr = fopen(filename, "r");

    if (ptr == NULL) {
        // this means file cannot be opened
        errno;
        perror("File cannot be opened || error printed by perror");
        return m_create(0, 0);
    } else {
        int height, width;
        fscanf(ptr, "{%d;%d}\n", &height, &width);
        //foglaljunk memóriát a sorok tömbjeire mutatóknak
        double **tombtomb = (double **) malloc(height * sizeof(double *));

        for (int i = 0; i < height; i++) {
            //foglaljunk memoriat az adott sornak
            double *current_row = (double *) malloc(width * sizeof(double));
            fscanf(ptr, "[%lf", &current_row[0]);
            for (int j = 1; j < width; j++) {
                fscanf(ptr, ",%lf", &current_row[j]);
            }
            fscanf(ptr, "]\n");
            tombtomb[i] = current_row;

        }
        fclose(ptr);
        matrix m = {height, width, tombtomb};
        return m;
    }
}


//prints out matrix
void mprint(matrix m) {
    //megkeressük a legnagyobb abszolútértékű számot, hogy tudjuk, mennyi helyet kell hagynunk a kiírásnak
    //+5=1 a logaritmus felfele kerekitese, 1 a minusz jel, 3 a tizedes pont és a 2 tizedesjegy
    int number_size = (int)log10(find_biggest_abs_in_matrix(m))+5;
    for (int i = 0; i < m.height; i++) {
        printf("[%*.2lf", number_size, m.rows[i][0]);
        for (int j = 1; j < m.width; j++) {
            printf(",%*.2lf", number_size, m.rows[i][j]);
        }
        printf("]\n");
    }
}

void write_matrix_f(char *filename, matrix m) {
    FILE *ptr;
    ptr = fopen(filename, "w");
    fprintf(ptr,"{%d;%d}\n", m.height,m.width);
    for (int i = 0; i <m.height; i++) {
        fprintf(ptr, "[%lf", m.rows[i][0]);
        for (int j = 1; j<m.width;j++) {
            fprintf(ptr, ",%lf", m.rows[i][j]);
        }
        fprintf(ptr, "]\n");
    }
    fclose(ptr);
}
