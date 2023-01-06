//
// Created by Bea on 08/11/2022.
//

#ifndef NUMEROSBIPOLARES_STRUCTS_H
#define NUMEROSBIPOLARES_STRUCTS_H

#define LINES 10
#define COLUMNS 20

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

typedef struct key_holders_list{
    KEY_HOLDERS *phead;
    KEY_HOLDERS *ptail;
    int nkey_holder;
}KEY_HOLDERS_LIST;

typedef struct user{
    char name[100];
    char email[100];
    KEY_HOLDERS *porta_chaves;
    struct user *next;
}USER;

typedef struct user_list{
    USER *phead;
    USER *ptail;
    int nusers;
}USER_LIST;

#endif //NUMEROSBIPOLARES_STRUCTS_H
