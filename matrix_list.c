//
// Created by Zear on 11/22/2022.
//

#include "matrix_list.h"
//name max 30 karakter lehet
void m_list_append(m_list** first, matrix m, char* name) {
    m_list* new = (m_list*)malloc(sizeof(m_list));
    new->data = m;
    new->next = NULL;
    strcpy(new->name, name);
    m_list* temp = *first;
    if(*first == NULL) {
        *first = new;
    }
    while(temp->next!=NULL){
        temp = temp->next;
    }
    (temp)->next = new;
}

void list_all_matrices(m_list* first) {
    first=first->next;
    while(first!=NULL){
        puts(first->name);
        first = first->next;
    }
}

void print_all_matrices(m_list* first) {
    first=first->next;
    while(first!=NULL) {
        puts(first->name);
        mprint(first->data);
        printf("\n");
        first = first->next;
    }
}
//megkeresi a parameterkent kapott nev-nek megfelelo matrixot
m_list* find_matrix(m_list* first, char* to_find) {
    while(first!= NULL && strcmp(first->name, to_find) != 0) {
        first = first->next;
    }
    //ha nem talalhato akkor first null pointer lesz
    return first;
}
//kitorli a parameterkent kapott nevnek megfelelo matrixot
void remove_list_item(m_list* first, char* name) {
    //strazsa nem torolheto ilyen modon
    if(strcmp(name, "strazsa")==0){
        printf("strazsa elem nem torolheto");
        return;
    }
    m_list* mover = first;
    //addig megyunk amig a kovekezo(mover) nem lesz null vagy a keresett nev
    //strcmp 0-t ad vissza ha a ket sztring megegyezik
    while(mover!=NULL && strcmp(mover->name, name) != 0){
        first = mover;
        mover = mover->next;
    }
    //ket lehetoseg, ha null volt akkor a nev nem talalhato
    if(mover==NULL) {
        printf("Az elem nem talalhato, igy nem torolheto %s", name);
        return;
    }
    //eloszor a matrixot szabaditjuk fel
    free_matrix(mover->data);
    //atallitjuk a kovekezo pointert
    first->next = mover->next;
    //felszabaditjuk a listaelemet
    free(mover);
}

//felszabaditjuk az osszes matrixot es a hozzajuk tartozo listaelemeket
//csak a program bezarasanal fut le
void free_list(m_list *first) {
    //addig megyunk ameddig a kovetkezo nem lesz null, tehat a vegeig
    while(first!=NULL){
        //felszabaditjuk az ebben a listaelemben levo matrixot
        free_matrix(first->data);
        //letrehozunk egy ideiglenes valtozot a kovetkezonek
        m_list *next = first->next;
        //igy mar felszabadithatjuk a matrixot
        free(first);
        //atallitjuk az iteralot a kovetkezo elemre
        first = next;
    }
}

matrix find_user_named_matrix(m_list *strazsa) {
    char name1[30+1];
    scanf("%s", name1);
    while (getchar() != '\n') {}
    m_list *m1 = find_matrix(strazsa, name1);
    if (m1 == NULL) {
        printf("nem talalhato ilyen nevu matrix, probalkozz ujra");
        return find_user_named_matrix(strazsa);
    }
    return m1->data;
}
