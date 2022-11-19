#include <stdio.h>
#include <math.h>
#include "debugmalloc.h"
#include "matrix_io.h"
#include "line_operations.h"
#include "matrix_operations.h"
#include "matrix_lib.h"
#include "value_check.h"

/*
double row1[] = {1, 2, 3, 4};
double row2[] = {1, 2, 3, 4};
double row3[] = {1, 2, 3, 4};
double row4[] = {1, 2, 3, 4};

double* rows[] = {row1, row2, row3, row4};
matrix m = {4, 3, rows};
*/

















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
            for (int k = i; k < result.height && !swap_success; k++) {
                if (fabs((result.rows[k][j])) > 0.00001) {
                    swap_lines(result, i, k);
                    swap_success = true;
                    i--, j--; //because we need to run the algorithm on this line one more time, before we can go to the next line
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
        printf("\n******************\n");
        mprint(result);
    }


    //teszteljünk hogy van e csak 0
    for (int i = result.height-1; i >= 0 ; i--) {
        //ha van csupa 0 sor, hagyjuk el (módosítsuk a magasságát is)
        // csupa nulla sor csak a végén lehet
        if (check_all_zero_line(result.rows[i], result.width)) {
            result.height -= 1;
            free(result.rows[i]);
        }
        //mivel az összes csupa nulla sor az aljára koncentrálodik, ha van 1 nem csupa nulla sor, utána már nem lehet több
        else{
            break;
        }
    }


    //teszteljük hogy van e tilos sor
    for (int i = result.height; i > 0 ; i--) {
        if(check_invalid_line(result.rows[i],result.width)) {
            printf("Nincs megoldása az egyenletrendszernek");
            return result;
            //itt az algoritmus visszatér visszaadjuk olyan formában ahol látható hogy nincs megoldása az egyenletrendszernek
        }
    }

            //második fázis: a vezéregyesek felett álló számokat is nullázzuk ki
    int i = result.height-1;
    int j = result.width-2;
    while (j>=0 && i >=0) {
        printf("\n**********************\n");
        mprint(result);
        if(fabs(result.rows[i][j]-1)<0.00001) {
            for(int k = i-1; k>=0; k--){
                double* temp = result.rows[k];
                double* kivonando = skalar_multip_line(result.rows[i], result.width, -1*result.rows[k][j]);
                result.rows[k] = add_lines(temp, kivonando, result.width);
                free(temp);
                free(kivonando);
            }
            i--; j--;
        }
        else{
            j--;
        }
    }


    return result;


}
//if it's a zero, try to swap this line, with one line lower than it
//if there are only zero's below this, go to the right
//if it's neither a one nor a zero, devide this row with current number to get a one





int main() {
    matrix matrix1 = read_matrix_f("..\\matrix1.txt");
    matrix matrix2 = read_matrix_f("..\\matrix2.txt");
    mprint(matrix2);
    mprint(matrix1);
    //matrix eliminated = gauss_elimination(matrix1);
    matrix eliminated2 = gauss_elimination(matrix2);
    printf("\n");
    //mprint(eliminated);
    printf("\n\n");
    mprint(eliminated2);
    //free_matrix(eliminated);
    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(eliminated2);


}
