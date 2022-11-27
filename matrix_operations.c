//
// Created by Zear on 11/13/2022.
//
#include "matrix_operations.h"
#include "line_operations.h"
#include "matrix_lib.h"
#include "debugmalloc.h"
#include <math.h>
#include "value_check.h"

// a paraméterként kapott mátrixot megszorozza a paraméterként kapott skalárral, !megváltoztatja a paraméterként kapott mátrixot!
void m_scalar_multip(matrix m, double skalar) {
    for (int i = 0; i < m.height; i++) {
        for (int j = 0; j < m.width; j++) {
            m.rows[i][j] *= skalar;
        }
    }
}

//megcsereli a matrix 2 sorat
void swap_lines(matrix m, int index1, int index2) {
    double *temp = m.rows[index1];
    m.rows[index1] = m.rows[index2];
    m.rows[index2] = temp;
}

//the two matrices has to be the same size
//free a hívó felelőssége
matrix m_addition(matrix m1, matrix m2) {
    if (m1.height != m2.height || m1.width != m2.width) {
        printf("a dimenziok nem megfeleloek a muvelet nem elvegzheto");
        return m_create(0, 0);
    } else {
        matrix result = m_create(m1.height, m1.width);
        for (int i = 0; i < result.height; i++) {
            free(result.rows[i]);
            result.rows[i] = add_lines(m1.rows[i], m2.rows[i], result.width);
        }
        return result;
    }

}



//matrixszorzast vegez a 2 parameterkent kapott matrixon, uj memoriateruletet foglal az eredmenynek
//free a hivo felelossege
matrix m_multip(matrix left, matrix right)      {
    //teszteljük hogy a szorzás végrehajtható-e
    if (left.width != right.height) {
        printf("szorzas nem elvegezheto mert a magadott matrixok meretei nem megfeleloek");
        return m_create(0, 0);
    }
    //uj matrix letrehozasa a megfelelo dimenziokkal
    matrix result = m_create(left.height, right.width);
    //iteraljunk vegig az eredmeny sorain fentrol lefele
    for (int i = 0; i < result.height; i++) {
        //sorokon bellul balrol jobbra
        for (int j = 0; j < result.width; j++) {
            //inicializaljuk hogy ne memoriaszemet legyen benne
            double current = 0;
            for (int k = 0; k < left.width; k++) {
                current += left.rows[i][k] * right.rows[k][j];
            }
            result.rows[i][j] = current;
        }
    }
    return result;
}

//megkeresi a matrixban levo abszolutertekben legnagyobb elemet
double find_biggest_abs_in_matrix(matrix m) {
    double biggest = fabs(m.rows[0][0]);
    for (int i = 0; i < m.height; i++){
        for (int j = 0; j<m.width; j++) {
            if (fabs(m.rows[i][j]) > biggest) {
                biggest = fabs(m.rows[i][j]);
            }
        }
    }
    return biggest;
}

//free a hivo kotelessege
matrix gauss_elimination(matrix m) {
    matrix result = m_cpy(m);
    //elkezdünk végigmenni a mátrix főátlóján, ha lehetséges
    //szélesség-1ig megyünk mivel ott az egyenletrendszerhez egyenleteinek megoldásai vannak
    for (int i = 0, j = 0; i < result.height && j < (result.width - 1); i++, j++) {
        double current = result.rows[i][j];
        //ha egyes akkor kész vagyunk mehetünk a következő sorra
        if (fabs(current - 1) < 0.0000001) {
        }
            //ha nulla akkor nem oszthatunk le vele, ilyenkor sort kell cserélni egy alatta lévő sorral ami ebben az oszlopban nem nulla
        else if (fabs(current) < 0.0000001) {
            //egy flag a csere sikerességét jelzi
            bool swap_success = false;
            //addig megyünk amíg nem találunk egy olyan sort ahol nem nulla az elem, vagy a mátrix aljáig
            for (int k = i; k < result.height && !swap_success; k++) {
                if (fabs((result.rows[k][j])) > 0.0000001) {
                    swap_lines(result, i, k);
                    swap_success = true;
                    i--, j--; //ha sikeres volt, csökkentjük egyel visszábbmegyünk az átlón,
                    // mivel az új ciklus iterációnál egyel tovább fog menni, de ezen a soron mégegyszer futtatni kell, hogy létrahozzuk a vezéregyest
                }
            }
            //ha nem volt nulla alatta és nem tudtuk felcserélni akkor mozgassuk a pointert 1-el balra
            if (!swap_success) {
                if (j < m.width - 1) {
                    //ezzel egyel felfelé megyünk de a következő ciklus iterációnál egyel jobbra lefelé megyünk majd, így összeségében jobbra megyünk
                    i--;
                    continue;
                }
            }
        }
            //ha nem 1 és nem nulla akkor beszorozzuk az 1/current-tel
        else {
            double *temp = skalar_multip_line(result.rows[i], result.width, 1 / result.rows[i][j]);
            free(result.rows[i]);
            result.rows[i] = temp;
        }
        //a jelenlegi sorban így már vezéregyes van
        //az alatta lévő sorokból kivonjuk ezt a sort (megfelelő skalárral szorozva), hogy kinullázzuk a vezéregyes alatti számokat
        for (int k = i + 1; k < result.height; k++) {
            //megszorozzuk a legutóbbi vezéregyest tartalmazó sort az alatta levő sor ugyanazon oszlop elemének -1szeresével
            double *temp = skalar_multip_line(result.rows[i], result.width, -1 * result.rows[k][j]);
            //ezt adjuk hozzá az alatta lévő sorhoz
            double *new_line = add_lines(temp, result.rows[k], result.width);
            //felszabadítjuk a segédtömböket és beállítjuk a result tömb sorát
            free(result.rows[k]);
            result.rows[k] = new_line;
            free(temp);
        }
        //kikommentelve, hasznalhato, hogy lepesenkent lathassuk a gauss-eliminaciot
        /*
        printf("\n******************\n");
        mprint(result);
         */
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
        if(fabs(result.rows[i][j]-1)<0.0000001) {
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

//kiszamitja a matrix rangjat (gauss eliminacio segitsegevel)
int matrix_rank(matrix m) {
    matrix result = m_cpy(m);
    //elkezdünk végigmenni a mátrix főátlóján, ha lehetséges
    for (int i = 0, j = 0; i < result.height && j < (result.width ); i++, j++) {
        double current = result.rows[i][j];
        //ha egyes akkor kész vagyunk mehetünk a következő sorra
        if (fabs(current - 1) < 0.0000001) {

        }
            //ha nulla akkor nem oszthatunk le vele, ilyenkor sort kell cserélni egy alatta lévő sorral ami ebben az oszlopban nem nulla
        else if (fabs(current) < 0.0000001) {
            //egy flag a csere sikerességét jelzi
            bool swap_success = false;
            //addig megyünk amíg nem találunk egy olyan sort ahol nem nulla az elem, vagy a mátrix aljáig
            for (int k = i; k < result.height && !swap_success; k++) {
                if (fabs((result.rows[k][j])) > 0.0000001) {
                    swap_lines(result, i, k);
                    swap_success = true;
                    i--, j--; //ha sikeres volt, csökkentjük egyel visszábbmegyünk az átlón,
                    // mivel az új ciklus iterációnál egyel tovább fog menni, de ezen a soron mégegyszer futtatni kell, hogy létrahozzuk a vezéregyest
                }
            }
            //ha nem volt nulla alatta és nem tudtuk felcserélni akkor mozgassuk a pointert 1-el balra
            if (!swap_success) {
                if (j < m.width - 1) {
                    //ezzel egyel felfelé megyünk de a következő ciklus iterációnál egyel jobbra lefelé megyünk majd, így összeségében jobbra megyünk
                    i--;
                    continue;
                }
            }
        }
            //ha nem 1 és nem nulla akkor beszorozzuk az 1/current-tel
        else {
            double *temp = skalar_multip_line(result.rows[i], result.width, 1 / result.rows[i][j]);
            free(result.rows[i]);
            result.rows[i] = temp;
        }
        //a jelenlegi sorban így már vezéregyes van
        //az alatta lévő sorokból kivonjuk ezt a sort (megfelelő skalárral szorozva), hogy kinullázzuk a vezéregyes alatti számokat
        for (int k = i + 1; k < result.height; k++) {
            //megszorozzuk a legutóbbi vezéregyest tartalmazó sort az alatta levő sor ugyanazon oszlop elemének -1szeresével
            double *temp = skalar_multip_line(result.rows[i], result.width, -1 * result.rows[k][j]);
            //ezt adjuk hozzá az alatta lévő sorhoz
            double *new_line = add_lines(temp, result.rows[k], result.width);
            //felszabadítjuk a segédtömböket és beállítjuk a result tömb sorát
            free(result.rows[k]);
            result.rows[k] = new_line;
            free(temp);
        }
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
    int to_return = result.height;
    free_matrix(result);
    return to_return;
}






