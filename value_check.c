//
// Created by Zear on 11/13/2022.
//
#include <stdbool.h>
#include "value_check.h"
#include <math.h>
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

