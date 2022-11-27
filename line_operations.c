//
// Created by Zear on 11/13/2022.
//

#include "line_operations.h"
#include "debugmalloc.h"

// a mátrix egy sorát paraméterként kapja és visszatér annak a paraméterként kapott valós szám szorosával
// a free a meghívó feladata
double *skalar_multip_line(double *line, int length, double scalar) {
    //új memoriaterulet foglalasa az szorzatnak
    double *result = (double *) malloc(length * sizeof(double));
    //minden elemet megszoroz a skalarral es ertekul adja az uj tomb megfelelo elemenek
    for (int i = 0; i < length; i++) {
        result[i] = line[i] * scalar;
    }
    return result;
}

//ket double tipusu tomb ertekeit adja ossze
//the length of the 2 arrays has to be the same
//free a hívó kötelessége
double *add_lines(double *line1, double *line2, int length) {
    double *result = (double *) malloc(length * sizeof(double));
    for (int i = 0; i < length; i++) {
        result[i] = line1[i] + line2[i];
    }
    return result;
}



