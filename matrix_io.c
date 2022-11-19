//
// Created by Zear on 11/13/2022.
//
#include "matrix_io.h"
#include <stdio.h>
#include "debugmalloc.h"

extern int errno;

matrix read_matrix_f(char *filename) {
    int errnum;
    FILE *ptr;
    char ch;
    ptr = fopen(filename, "r");

    if (ptr == NULL) {
        // this means file cannot be opened
        errnum = errno;
        perror("File cannot be opened || error printed by perror");
    } else {
        int magassag, szelesseg;
        fscanf(ptr, "{%d;%d}\n", &magassag, &szelesseg);
        //foglaljunk memóriát a sorok tömbjeire mutatóknak
        double **tombtomb = (double **) malloc(magassag * sizeof(double *));

        for (int i = 0; i < magassag; i++) {
            //foglaljunk memoriat az adott sornak
            double *current_row = (double *) malloc(szelesseg * sizeof(double));
            fscanf(ptr, "[%lf", &current_row[0]);
            for (int j = 1; j < szelesseg; j++) {
                fscanf(ptr, ",%lf", &current_row[j]);
            }
            fscanf(ptr, "]\n");
            tombtomb[i] = current_row;

        }
        fclose(ptr);
        matrix m = {magassag, szelesseg, tombtomb};
        return m;
    }
}


//prints out matrix
//todo check for the highest number and write that number of digits log 10
void mprint(matrix m) {
    for (int i = 0; i < m.height; i++) {
        printf("[%7.2lf", m.rows[i][0]);
        for (int j = 1; j < m.width; j++) {
            printf(",%7.2lf", m.rows[i][j]);
        }
        printf("]\n");


    }
}