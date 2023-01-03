//
// Created by Bea on 29/11/2022.
//

#include "../headers/bipolarChars.h"
#include <stdio.h>
#include <malloc.h>
#include "../headers/bipolarInts.h"

char* key_long_2_digits_char(unsigned long long key){
    int cnt = count_digits(key);
    unsigned long long aux;
    char * arr = calloc(cnt+1, sizeof(char));
    for (int i = cnt-1; i >= 0; i--) {
        aux = key % 10;
        arr[i] = aux + '0'; //acrescenta o '0' para transformar o int em char
        key /= 10;
    }
    arr[cnt] = '\0';
    return arr;
}

unsigned long long key_digits_2_long_char(char* keydigits){
    unsigned long long num = 0;
    for (int i = 0; keydigits[i] != '\0'; ++i) {
        num *= 10;
        num += keydigits[i] - '0';
    }
    return num;
}

unsigned long long calc_private_key_char(unsigned long long pubkey){
    unsigned long long num = calc_private_key_int(pubkey);
    return num;
}

unsigned long long calc_runlength_char(unsigned long long privkey){
    unsigned long long num = calc_runlength_int(privkey);
    return num;
}

unsigned long long private_key_from_runlength_char(unsigned long long runlengthkey){
    unsigned long long num = private_key_from_runlength_int(runlengthkey);
    return num;
}

char** alloc_matrix_char(int nlines, int ncolumns){
    char** a = (char**)calloc(nlines, sizeof(char*));
    for (int i = 0; i < nlines; i++) {
        a[i] = (char*)calloc(ncolumns, sizeof(char));
    }
    return a;
}

void store_key_char(char **matrix, int lines, unsigned long long key){
    int columns = count_digits(key);
    char * key_arr = key_long_2_digits_char(key);
    for (int i = 0; i < lines; ++i) {
        if(matrix[i][0] == 0){
            matrix[i] = realloc(matrix[i], (columns + 1) * sizeof(char));
            for (int j = 0; j < columns; ++j) {
                matrix[i][j] = key_arr[j];
            }
            matrix[i][columns] = '\0';
        }
    }
}

int exists_key_char(char **matrix, int lines, unsigned long long key){
    int columns, k = 0;
    char * key_arr = key_long_2_digits_char(key);
    unsigned long long m;
    for (int i = 0; i < lines; ++i) {
        m = key_digits_2_long_char(matrix[i]);
        columns = count_digits(m);
        for (int j = 0; j < columns; ++j) {
            if(matrix[i][j] == key_arr[j] && matrix[i][j+1] == -1){
                k++;
            }
        }
        if(k == 1) {
            return 1;
        }
    }
    return 0;
}

unsigned long long get_private_key_char(char **matrix_kpub, char **matrix_kpriv, int lines, unsigned long long pubkey){
    return exists_key_char(matrix_kpub, lines, pubkey) ? key_digits_2_long_char(matrix_kpriv[lines]) : 0;
}

unsigned long long get_runlength_char(char **matrix_kpriv, char **matrix_kcod, int lines, unsigned long long privkey) {
    return exists_key_char(matrix_kpriv, lines, privkey) ? key_digits_2_long_char(matrix_kcod[lines]) : 0;
}

unsigned long long delete_key_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char pubkey){
    char * pubkey_arr = key_long_2_digits_char(pubkey);
    unsigned long long pkey = get_private_key_char(matrix_kpub, matrix_kpriv, lines, pubkey);
    char * pkey_arr = key_long_2_digits_char(pkey);
    unsigned long long pcod = get_runlength_char(matrix_kpriv, matrix_kcod, lines, pkey);
    char * pcod_arr = key_long_2_digits_char(pcod);

    for (int i = 0; i < lines; ++i) {
        int pub_cnt = count_digits(pubkey);
        int priv_cnt = count_digits(pkey);
        int cod_count = count_digits(pcod);
        int index = -1;

        //delete key in public matrix
        for (int j = 0; j < pub_cnt; ++j) {
            if (matrix_kpub[i][j] == pubkey_arr[j]) {
                index = i;
            }
        }

        if(index != -1) {
            for (int j = index; j < lines - 1; ++j) {
                matrix_kpub[j] = matrix_kpub[j+1];
            }
            index = -1;
        }

        //delete key in priv matrix
        for (int j = 0; j < priv_cnt; ++j) {
            if (matrix_kpriv[i][j] == pkey_arr[j]) {
                index = i;
            }
        }

        if(index != -1) {
            for (int j = index; j < lines - 1; ++j) {
                matrix_kpriv[j] = matrix_kpriv[j+1];
            }
            index = -1;
        }

        //delete key in cod (run-length) matrix
        for (int j = 0; j < cod_count; ++j) {
            if (matrix_kcod[i][j] == pcod_arr[j]) {
                index = i;
            }
        }

        if(index != -1) {
            for (int j = index; j < lines - 1; ++j) {
                matrix_kcod[j] = matrix_kcod[j+1];
            }
            index = -1;
        }
    }
    return pubkey;
}

void bulk_populate_public_keys_char(char **matrix_kpub, int lines){
    for (int i = 0; i < lines; ++i) {
        unsigned long long num = new_public_key_int();
        store_key_char(matrix_kpub, lines, num);
    }
}

void bulk_compute_private_keys_char(char **matrix_kpub, char **matrix_kpriv, int lines){
    for (int i = 0; i < lines; ++i) {
        unsigned long long new_key = key_digits_2_long_char(matrix_kpub[i]);
        unsigned long long new_priv_key = calc_private_key_char(new_key);
        store_key_char(matrix_kpriv, i+1, new_priv_key);
    }
}

void bulk_compute_runlengths_char(char **matrix_kpriv, char **matrix_kcod, int lines){
    for (int i = 0; i < lines; ++i) {
        unsigned long long new_key = key_digits_2_long_char(matrix_kpriv[i]);
        unsigned long long new_cod_key = calc_runlength_char(new_key);
        store_key_char(matrix_kcod, i+1, new_cod_key);
    }
}

char** search_private_keys_char(char **matrix_kpub, char **matrix_kpriv, int lines, unsigned long long partialpubkey){

}

void sort_matrix_char(char **matrix, int lines, int order){

}

void sort_all_matrices_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, int order){

}

void list_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, int order){

}

void save_txt_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]){

}

void load_txt_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]){

}

void save_bin_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]){

}

void load_bin_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]){

}
