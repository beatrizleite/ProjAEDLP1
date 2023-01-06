//
// Created by Bea on 29/11/2022.
//

#include "../headers/bipolarChars.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "../headers/bipolarInts.h"
#include "../headers/structs.h"

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
        store_key_char(matrix_kpub, i+1, num);
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
    char * found = calloc(1,sizeof(short));
    char * partialpubkey_arr = key_long_2_digits_char(partialpubkey);
    char ** found_priv = NULL;
    int digit_cnt = count_digits(partialpubkey);
    int n = 0, cnt, k = 0;
    for (int i = 0; i < lines; ++i) {
        cnt = count_digits(key_digits_2_long_char(matrix_kpub[i]));
        for (int j = 0; j < cnt; ++j) {
            if (partialpubkey_arr[j] == matrix_kpub[i][j]) {
                k++;
            } else {
                k = 0;
            }
            if(k == digit_cnt) {
                found[n] = (char)i;
                n++;
            }
        }
    }
    if(n != 0) {
        found_priv = alloc_matrix_char(n+1, 10);
        found_priv[0][0] = n;
        unsigned long long privkey, pubkey;
        for (int i = 0; i < n; ++i) {
            pubkey = key_digits_2_long_char(matrix_kpub[found[i]]);
            privkey = get_private_key_char(matrix_kpub, matrix_kpriv, found[i], pubkey);
            store_key_char(found_priv, n+1, privkey);
        }
        return found_priv;
    } else {
        return 0;
    }
}

unsigned long long *create_keys_array_char(char **matrix, int lines){
    unsigned long long *keys = (unsigned long long *) malloc(lines * sizeof(unsigned long long));
    for (int i = 0; i < lines; ++i) {
        keys[i] = key_digits_2_long_char(matrix[i]);
    }
    return keys;
}

void sort_matrix_char(char **matrix, int lines, int order){
    unsigned long long *keys = create_keys_array_char(matrix, lines);
    quicksort(keys, 0, lines-1, order);
    for (int i = 0; i < lines; ++i) {
        char *copy = key_long_2_digits_char(keys[i]);
        for (int j = 0; j < COLUMNS; ++j) {
            matrix[i][j] = copy[j];
        }
    }
}

void sort_all_matrices_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, int order){
    sort_matrix_char(matrix_kpub, lines, order);
    sort_matrix_char(matrix_kpriv, lines, order);
    sort_matrix_char(matrix_kcod, lines, order);
}

void list_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, int order){
    sort_matrix_char(matrix_kpub, lines, order);
    for (int i = 0; i < lines; ++i) {
        printf("\nkey #%d\n",i+1);
        printf("%llu\n", key_digits_2_long_char(matrix_kpub[i]));
        printf("%llu\n", key_digits_2_long_char(matrix_kpriv[i]));
        printf("%llu\n", key_digits_2_long_char(matrix_kcod[i]));
    }
}

void save_txt_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]){
    FILE *fp;
    unsigned long long pub, priv, cod;
    fp = fopen(filename, "w");

    if(fp == NULL){
        printf("Can't create file.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < lines; ++i) {
        pub = key_digits_2_long_char(matrix_kpub[i]);
        fprintf(fp,"%llu",pub);
        fprintf(fp,",");
        priv = key_digits_2_long_char(matrix_kpriv[i]);
        fprintf(fp,"%llu",priv);
        fprintf(fp,",");
        cod = key_digits_2_long_char(matrix_kcod[i]);
        fprintf(fp,"%llu",cod);
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void load_txt_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]){
    FILE *fp;
    char line[255];
    int aux1=0, aux2=0, aux3=0;
    unsigned long long pub = 0;
    unsigned long long priv = 0;
    unsigned long long cod = 0;
    fp = fopen(filename, "r");

    if(fp == NULL){
        printf("Can't open/read file.\n");
        exit(EXIT_FAILURE);
    }
    int k = 0;
    while(fgets(line, sizeof(line), fp)) {

        int i = 0;
        char *token;
        token = strtok(line, ",");

        while (token != NULL) {
            if (i == 0) {
                pub = atoll(token);
                token = strtok(NULL, ",");
                i++;
            } else if (i == 1) {
                priv = atoll(token);
                token = strtok(NULL, ",");
                i++;

            } else {
                cod = atoll(token);
                token = strtok(NULL, ",");
            }
        }

        store_key_char(matrix_kpub, k + 1, pub);
        store_key_char(matrix_kpriv, k + 1, priv);
        store_key_char(matrix_kcod, k + 1, cod);
        k++;
    }
}

void save_bin_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]){

    num_t number[lines];
    FILE *fp;
    fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Can't create file.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < lines; ++i) {
        number[i].pub = key_digits_2_long_char(matrix_kpub[i]);
        number[i].priv = key_digits_2_long_char(matrix_kpriv[i]);
        number[i].cod = key_digits_2_long_char(matrix_kcod[i]);
    }
    fwrite(number, sizeof(num_t), lines, fp);
    fclose(fp);
}

void load_bin_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]){
    num_t number[lines];
    FILE *fp;
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Can't create file.\n");
        exit(EXIT_FAILURE);
    }
    fread(number, sizeof(num_t), lines, fp);
    for (int i = 0; i < lines; ++i) {
        store_key_char(matrix_kpub, i+1, number[i].pub);
        store_key_char(matrix_kpriv, i+1, number[i].priv);
        store_key_char(matrix_kcod, i+1, number[i].cod);
    }
    fclose(fp);
}
