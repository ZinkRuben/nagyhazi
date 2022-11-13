#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "debugmalloc.h"

typedef struct matrix {
    int height, width;
    double **rows;
} matrix;

/*
double row1[] = {1, 2, 3, 4};
double row2[] = {1, 2, 3, 4};
double row3[] = {1, 2, 3, 4};
double row4[] = {1, 2, 3, 4};

double* rows[] = {row1, row2, row3, row4};
matrix m = {4, 3, rows};
*/
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

// a mátrix egy sorát paraméterként kapja és visszatér annak a paraméterként kapott valós szám szorosával
// a free a meghívó feladata
double *skalar_multip_line(double *line, int length, double scalar) {
    double *result = (double *) malloc(length * sizeof(double));
    for (int i = 0; i < length; i++) {
        result[i] = line[i] * scalar;
    }
    return result;
}

//adds the values of 2 double array together
//the length of the 2 arrays has to be the same
//free a hívó kötelessége
double *add_lines(double *line1, double *line2, int length) {
    double *result = (double *) malloc(length * sizeof(double));
    for (int i = 0; i < length; i++) {
        result[i] = line1[i] + line2[i];
    }
    return result;
}

void m_skalar_multip(matrix m, double skalar);

matrix m_addition(matrix m1, matrix m2);

matrix swap_lines(matrix m, int index1, int index2);

bool check_all_zero_line(double *line, int length) {
    for (int i = 0; i < length; i++) {
        if (fabs(line[i]) > 0.00001) {
            return false;
        }
    }
    return true;
}
bool check_invalid_line(double *line, int length) {
    for (int i = 0; i < length - 1; i++) {
        if (fabs(line[i]) > 0.00001) {
            return false;
        }
    }

    if (fabs(line[length - 1]) < 0.00001) {
        return false;
    }
    else
        return true;
}

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

matrix gauss_elimination(matrix m) {
    matrix result = m_cpy(m);
    //start looping through the matrix by moving on the diagonal if possible
    for (int i = 0, j = 0; i < result.height && j < (result.width - 1); i++, j++) {
        double current = result.rows[i][j];
        //if it's a one, go to next step
        if (fabs(current - 1) < 0.00001) {

        }
            //if it's a zero, try to swap this line, with a line lower than it
        else if (fabs(current) < 0.00001) {
            bool swap_success = false;
            for (int k = i; k < result.height; k++) {
                if (fabs((result.rows[k][j])) > 0.00001) {
                    swap_lines(result, i, k);
                    swap_success = true;
                }
            }
            //ha nem volt nulla alatta és nem tudtuk felcserélni akkor mozgassuk a pointert 1-el balra
            if (!swap_success) {
                if (j < m.width - 1) {
                    i--;
                    continue;

                }


            }
        }
            //if it's not one, and it's not zero multiply current row with 1/current
        else {
            double *temp = skalar_multip_line(result.rows[i], result.width, 1 / result.rows[i][j]);
            free(result.rows[i]);
            result.rows[i] = temp;
        }
        //we made a leading one in this row, so we can move to the next step
        //we have to subtract this line (multiplied by a sutiable scalar) from the lines below to make them 0
        for (int k = i + 1; k < result.height; k++) {
            //multiplies the last row with a leading 1 by the skalar k.row current column
            double *temp = skalar_multip_line(result.rows[i], result.width, -1 * result.rows[k][j]);
            double *new_line = add_lines(temp, result.rows[k], result.width);
            free(result.rows[k]);
            result.rows[k] = new_line;
            free(temp);
        }
    }//teszteljünk hogy van e csak 0 vagy tilos sor
    for (int i = 0; i < result.height; i++) {
        //ha van csupa 0 sor, hagyjuk el (módosítsuk a magasságát is)
        if (check_all_zero_line(result.rows[i], result.width)){
            //realloc a rows és minden pointert egyel arrébb kell tenni

        }
        if(check_invalid_line(result.rows[i],result.width)) {
            printf("Nincs megoldása az egyenletrendszernek");
        }
    }

            //második fázis: a vezéregyesek felett álló számokat is nullázzuk ki



            return result;


}
//if it's a zero, try to swap this line, with one line lower than it
//if there are only zero's below this, go to the right
//if it's neither a one nor a zero, devide this row with current number to get a one


//frees up memory allocated to a matrix
void free_matrix(matrix m) {
    for (int i = 0; i < m.height; i++) {
        free(m.rows[i]);
    }
    free(m.rows);
}


int main() {
    //printf("%f", m.rows[0][2]);
    matrix matrix1 = read_matrix_f("matrix1.txt");
    mprint(matrix1);
    matrix eliminated = gauss_elimination(matrix1);
    printf("\n");
    mprint(eliminated);
    free_matrix(eliminated);
    free_matrix(matrix1);


};
