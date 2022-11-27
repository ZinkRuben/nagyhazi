#include <stdio.h>
#include <math.h>
#include "debugmalloc.h"
#include "matrix_io.h"
#include "matrix_operations.h"
#include "matrix_lib.h"
#include "matrix_list.h"
#include <string.h>


void remove_new_line(char *string) {
    int i = 0;
    while (string[i] != '\n' && string[i] != '\0') {
        i++;
    }
    if (string[i] == '\n') {
        string[i] = '\0';
    }
}

void main_menu(m_list *strazsa) {
    char menu_szoveg[] = "ird be a parancs melletti szamot a parancs vegrehajtasahoz\n"
                         " 0:ezen lista ujbol kiirasa\n"
                         " 1:matrix beolvasasa \n"
                         " 2:matrix fajlba irasa \n"
                         " 3:tarolt matrixok neveinek listazasa \n"
                         " 4:tarolt matrixok kiirasa\n"
                         " 5:muveletvegzes matrixokkal\n"
                         " 6:matrix masolasa\n"
                         " 7:matrix torlese\n"
                         " 9:kilepes\n";
    printf("Udv a matrix konyvtar programban!");
    int command;
    char name1[31];
    char name2[31];
    char buffer[201];
    printf("%s", menu_szoveg);
    while (1) {

        scanf("%d", &command);
        while (getchar() != '\n');
        switch (command) {
            case 0:
                printf("%s", menu_szoveg);
                break;
            case 1:
                printf("ird be a beolvasando fajl helyet es nevet (max 200 karakter)");
                scanf("%s", buffer);
                while (getchar() != '\n') {}
                matrix new_matrix = read_matrix_f(buffer);
                if (new_matrix.height == 0) {
                    printf("hiba tortent, a megadott matrix nem beolvashato\n");
                    free_matrix(new_matrix);
                    break;
                }
                printf("ird be a matrix nevet (ahogy a programon bellul hivatkozni szeretnel ra (max 200 karakter)");
                fgets(name1, 31, stdin);
                remove_new_line(name1);
                mprint(new_matrix);
                m_list_append(&strazsa, new_matrix, name1);
                break;
            case 2:
                printf("add meg a fajla irando matrix nevet");
                matrix m_to_write_to_file = find_user_named_matrix(strazsa);
                printf("add meg a fajl nevet kiterjeszteset es utvonalat\n"
                       " (ha nem adsz meg utvonalat a programmal megegyezo mappaba tortenik a mentes)");
                scanf("%s", buffer);
                while (getchar() != '\n') {}
                write_matrix_f(buffer, m_to_write_to_file);
                break;
            case 3:
                list_all_matrices(strazsa);
                break;
            case 4:
                print_all_matrices(strazsa);
                break;
            case 5:
                printf("Milyen muveletet szeretnel vegezni?\n"
                       "0: vissza\n"
                       "1: matrixok osszeadasa\n"
                       "2: matrix szorzasa egy skalarral, !az adott matrixot valtoztja meg!\n"
                       "3: matrixok szorzasa\n"
                       "4: gauss-eliminacio\n"
                       "5: matrix rang szamolas\n"
                       "");
                scanf("%d", &command);
                switch (command) {
                    case 0:
                        break;
                        //matrixok osszeadasa
                    case 1:
                        printf("a matrixok megadasanal figyelj a sorrendre, a muvelet csak akkor elvegezheto\n"
                               "ha az elso matrix szelessege megegyezik a masodik matrix magassagaval");
                        printf("add meg az elso matrix nevet (max 30 karakter)");
                        matrix m1 = find_user_named_matrix(strazsa);
                        printf("add meg a masodik matrix nevet (max 30 karakter)");
                        matrix m2 = find_user_named_matrix(strazsa);
                        matrix result = m_addition(m1, m2);
                        if (result.height == 0) {
                            free_matrix(result);
                            // az 2 megadott matrix dimenzio nem megfeleloek igy az osszeadas nem hajthato vegre
                            printf("muvelet megszakitva");
                            break;
                        }
                        printf("add meg az uj osszeg matrix nevet, ahogy a programon bellul hivatkozni szeretnel ra");
                        scanf("%s", name1);
                        while (getchar() != '\n') {}
                        m_list_append(&strazsa, result, name1);
                        break;

                        //matrix szorzasa skalarral
                    case 2:
                        printf("add meg a szorzando matrix nevet (max 30 karakter)");
                        matrix m_skalar_m = find_user_named_matrix(strazsa);
                        printf("add meg a skalart amivel meg szeretned szorozni a matrixot");
                        double skalar;
                        scanf("%lf", &skalar);
                        m_scalar_multip(m_skalar_m, skalar);
                        break;

                        //matrix szorzas
                    case 3:
                        printf("add meg az elso matrix nevet (max 30 karakter)");
                        matrix left_matrix = find_user_named_matrix(strazsa);
                        printf("add meg a masodik matrix nevet (max 30 karakter)");
                        matrix right_matrix = find_user_named_matrix(strazsa);
                        matrix multip_result = m_multip(left_matrix, right_matrix);
                        if (multip_result.height == 0) {
                            free_matrix(multip_result);
                            // az 2 megadott matrix dimenzio nem megfeleloek igy az osszeadas nem hajthato vegre
                            printf("muvelet megszakitva");
                            break;
                        }
                        printf("add meg az uj szorzat matrix nevet, ahogy a programon bellul hivatkozni szeretnel ra");
                        scanf("%s", name1);
                        while (getchar() != '\n') {}
                        m_list_append(&strazsa, multip_result, name1);
                        break;
                        //gauss eliminacio
                    case 4:
                        printf("add meg a Gauss-eliminalni valo matrix nevet");
                        matrix m_to_gauss = find_user_named_matrix(strazsa);
                        matrix gauss_result = gauss_elimination(m_to_gauss);
                        printf("add meg az uj gauss eliminalt matrix nevet, ahogy a programon bellul hivatkozni szeretnel ra");
                        scanf("%s", name1);
                        while (getchar() != '\n') {}
                        m_list_append(&strazsa, gauss_result, name1);
                        break;
                    case 5:
                        printf("add meg a matrixot aminek kivancsi vagy a rangjara");
                        printf("A matrix rangja: %d\n", matrix_rank(find_user_named_matrix(strazsa)));
                        break;
                    default:
                        break;
                }
                break;
                //matrix duplikalsa
            case 6:
                printf("ird be a matrix nevet, amelyikbol szeretnel megegy peldanyt");
                matrix copied = m_cpy(find_user_named_matrix(strazsa));
                printf("add meg az uj masolat matrix nevet, ahogy a programon bellul hivatkozni szeretnel ra");
                scanf("%s", name1);
                while (getchar() != '\n') {}
                m_list_append(&strazsa, copied, name1);
                break;
                //matrix torlese a memoriabol
            case 7:
                printf("ird be a matrix nevet amit szeretnel torolni a programbol\n");

                fgets(name1, 31, stdin);
                remove_new_line(name1);
                remove_list_item(strazsa, name1);
                printf("sikeresen torolve");
                break;
                //kilepes
            case 9:
                free_list(strazsa);
                printf("Remelem tetszett a program! Szia!");
                return;
                //hibas parancskod eseten default
            default:
                printf("nem ismert parancskod, kerlek progalkozz ujra");
                break;
        }
    }
}


int main() {


    m_list *strazsa = (m_list *) (malloc(sizeof(m_list)));
    strcpy(strazsa->name, "strazsa");
    strazsa->next = NULL;
    strazsa->data = m_create(0, 0);
    main_menu(strazsa);


//    matrix matrix1 = read_matrix_f("..\\matrix2.txt");
//    matrix matrix2 = read_matrix_f("..\\matrix2.txt");
//    m_list_append(&strazsa, matrix1, "m1");
//    m_list_append(&strazsa, matrix2, "m2");
//    list_all_matrices(strazsa);
//    remove_list_item(strazsa, "m2");
//    printf("ADASDSADASDSADSDA");
//    list_all_matrices(strazsa);
//    free_list(strazsa);

//    char* masolat = "..\\matrix1.txt";
//    matrix matrix1 = read_matrix_f(masolat);
//    matrix matrix2 = read_matrix_f("..\\matrix2.txt");
//    mprint(matrix2);
//    mprint(matrix1);
//    matrix osszeg = m_addition(matrix1,matrix1);
//    printf("%d", osszeg.width);
//    printf("%d", osszeg.height);
//    mprint(osszeg);
//    //matrix eliminated = gauss_elimination(matrix1);
//    //matrix eliminated2 = gauss_elimination(matrix2);
//    //printf("\n");
//    //mprint(eliminated);
//    //printf("\n\n");
//    //mprint(eliminated2);
//    //free_matrix(eliminated);
//
//
//
//
//    matrix multiplied = m_multip(matrix1, matrix2);
//    printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n");
//    mprint(multiplied);
//    write_matrix_f("..\\m1m2multiplied.txt", multiplied);
//
//    m_list *first = (m_list*)malloc(sizeof(m_list));
//    first->data = multiplied;
//    strcpy(first->name,"test_m");
//    first->next = NULL;
//
//    m_list_append(&first, matrix1, "matrix1");
//    m_list_append(&first, matrix2, "matrix2");
//    list_all_matrices(first);
//
//    print_all_matrices(first);
//
//    remove_list_item(first, "matrix2");
//    remove_list_item(first, "matrix1");
//    remove_list_item(first, "test_m");
//
//    //free_matrix(multiplied);
//    //free_matrix(matrix1);
//    //free_matrix(eliminated2);
}
