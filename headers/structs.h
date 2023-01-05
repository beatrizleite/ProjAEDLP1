//
// Created by Bea on 08/11/2022.
//

#ifndef NUMEROSBIPOLARES_STRUCTS_H
#define NUMEROSBIPOLARES_STRUCTS_H

typedef struct date{
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int second;
}DATE;

typedef struct key_holder{
    int lines;
    short **INT_matrix_kpub;
    short **INT_matrix_kpriv;
    short **INT_matrix_kcod;
    char **CHAR_matrix_kpub;
    char **CHAR_matrix_kpriv;
    char **CHAR_matrix_kcod;
}KEY_HOLDER;

typedef struct key_holders{
    KEY_HOLDER *porta_chave;
    DATE created;
    DATE updated;
    struct key_holders *next;
}KEY_HOLDERS;

typedef struct user{
    char name[100];
    char email[100];
    KEY_HOLDERS *porta_chaves;
    struct user *next;
}USER;

#endif //NUMEROSBIPOLARES_STRUCTS_H
