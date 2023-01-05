//
// Created by Bea on 29/11/2022.
//

#include "../headers/bipolarInts.h"
#include <stdio.h>
#include <string.h>

int hasZero(unsigned long long key) {
    int result = 0;
    while (key) {
        result += !(key % 10);
        key /= 10;
    }
    return result;
}

int count_digits(unsigned long long key) {
    int count = 0;
    while (key) {
        count++;
        key /= 10;
    }
    count += hasZero(key);
    return count;
}

unsigned long long new_public_key_int(void) {
    return (unsigned long long)rand() + 1;
}

short* key_long_2_digits_int(unsigned long long key) {
    int cnt = count_digits(key);
    unsigned long long aux = key;
    short * arr = calloc(cnt+1, sizeof(short));
    for (int i = cnt-1; i >= 0; i--) {
        unsigned long long digit = aux % 10;
        arr[i] = digit;
        aux /= 10;
    }
    arr[cnt] = -1;
    return arr;
}

unsigned long long key_digits_2_long_int(short* keydigits){
    unsigned long long num = 0;
    for (int i = 0; keydigits[i] != -1; ++i) {
        num *= 10;
        num += keydigits[i];
    }
    return num;
}

int isBipolar(unsigned long long key) {
    int k=0;
    if(count_digits(key) < 2) {
        return 0;
    }
    int cnt [] = {0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0};
    unsigned long long aux = key;
    short * aux_arr = key_long_2_digits_int(key);
    int n = 0;
    while(aux_arr[n] != -1) {
        int rem = aux % 10;
        cnt[rem]++;
        aux /= 10;
        n++;
    }
    for (int i = 0; i < 10; ++i) {
        if(cnt[i] != 0) k++;
    }
    if (k != 2) return 0;
    short * arr = key_long_2_digits_int(key);
    int diff = 0;
    for (int i = 1; arr[i] != -1; ++i) {
        if (arr[i] != arr[i-1]) {
            diff++;
            if(diff != 1) {
                return 0;
            }
        }
    }
    return 1;
}

unsigned long long calc_private_key_int(unsigned long long pubkey) {
    int i, j, k, n;
    unsigned long long num = 0;

    i = 1 + rand()%10;
    j = rand()%10;
    k = 1 + rand()%10;
    n = rand()%10;
    if(j != n){
        while(i) {
            num *= 10;
            num += j;
            i--;
        }
        while(k) {
            num *= 10;
            num += n;
            k--;
        }
    } else {
        calc_private_key_int(pubkey);
    }
    return isBipolar(num) ? num : calc_private_key_int(pubkey);
}

unsigned long long calc_runlength_int(unsigned long long privkey){
    int count = 1, k = 0, rl = 0;
    short * arr = key_long_2_digits_int(privkey);
    for (int i = 0; arr[i] != -1; ++i) {
        if(arr[i] == arr[i+1]) {
            count++;
            k = arr[i];
        } else {
            rl *= 10;
            rl += count;
            rl *= 10;
            rl += k;
            count = 1;
        }

    }
    return rl;
}

unsigned long long private_key_from_runlength_int(unsigned long long runlengthkey) {
    short * rl = key_long_2_digits_int(runlengthkey);
    unsigned long long privkey=0;
    for (int i = 0; i < 4; ++i) {
        if(i==0 || i==2){
            int aux = i;
            while(aux){
                privkey *= 10;
                privkey += rl[i+1];
                aux--;
            }
        }
    }
    return privkey;
}

short** alloc_matrix_int(int nlines, int ncolumns) {
    short** a = (short**)calloc(nlines, sizeof(short*));
    for (int i = 0; i < nlines; i++) {
        a[i] = (short*)calloc(ncolumns, sizeof(short));
    }
    return a;
}

void store_key_int(short **matrix, int lines, unsigned long long key){
    int columns = count_digits(key);
    short * key_arr = key_long_2_digits_int(key);
    for (int i = 0; i < lines; ++i) {
        if(matrix[i][0] == 0){
            matrix[i] = realloc(matrix[i], (columns + 1) * sizeof(short));
            for (int j = 0; j < columns; ++j) {
                matrix[i][j] = key_arr[j];
            }
            matrix[i][columns] = -1;
        }
    }
}


int exists_key_int(short **matrix, int lines, unsigned long long key) {
    int columns, k = 0, line = 0;
    short * key_arr = key_long_2_digits_int(key);
    unsigned long long m;
    for (int i = 0; i < lines; ++i) {
        m = key_digits_2_long_int(matrix[i]);
        columns = count_digits(m);
        for (int j = 0; j < columns; ++j) {
            if(matrix[i][j] == key_arr[j] && matrix[i][j+1] == -1){
                k++;
                line = i;
            }
        }
        if(k == 1) {
            return 1;
        }
    }
    return 0;
}

unsigned long long get_private_key_int(short **matrix_kpub, short **matrix_kpriv, int lines, unsigned long long pubkey) {
    return exists_key_int(matrix_kpub, lines, pubkey) ? key_digits_2_long_int(matrix_kpriv[lines]) : 0;
}

unsigned long long get_runlength_int(short **matrix_kpriv, short **matrix_kcod, int lines, unsigned long long privkey) {
    return exists_key_int(matrix_kpriv, lines, privkey) ? key_digits_2_long_int(matrix_kcod[lines]) : 0;
}

unsigned long long delete_key_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, short pubkey) {
    short * pubkey_arr = key_long_2_digits_int(pubkey);
    unsigned long long pkey = get_private_key_int(matrix_kpub, matrix_kpriv, lines, pubkey);
    short * pkey_arr = key_long_2_digits_int(pkey);
    unsigned long long pcod = get_runlength_int(matrix_kpriv, matrix_kcod, lines, pkey);
    short * pcod_arr = key_long_2_digits_int(pcod);

    for (int i = 0; i < lines; ++i) {
        int pub_cnt = count_digits(pubkey);
        int priv_cnt = count_digits(pkey);
        int cod_count = count_digits(pcod);
        int index = -1;

        //delete key in public matrix
        for (int j = 0; j < pub_cnt; ++j) {
            if (matrix_kpub[i][j] == pubkey_arr[j] && matrix_kpub[i][j + 1] == 0) {
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
            if (matrix_kpriv[i][j] == pkey_arr[j] && matrix_kpub[i][j + 1] == 0) {
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
            if (matrix_kcod[i][j] == pcod_arr[j] && matrix_kcod[i][j + 1] == 0) {
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

void bulk_populate_public_keys_int(short **matrix_kpub, int lines) {
    unsigned long long new_key;
    for (int i = 0; i < lines; ++i) {
        new_key = new_public_key_int();
        store_key_int(matrix_kpub, i+1, new_key);
    }
}


void bulk_compute_private_keys_int(short **matrix_kpub, short **matrix_kpriv, int lines) {
    for (int i = 0; i < lines; ++i) {
        unsigned long long new_key = key_digits_2_long_int(matrix_kpub[i]);
        unsigned long long new_priv_key = calc_private_key_int(new_key);
        store_key_int(matrix_kpriv, i+1, new_priv_key);
    }
}

void bulk_compute_runlengths_int(short **matrix_kpriv, short **matrix_kcod, int lines) {
    for (int i = 0; i < lines; ++i) {
        unsigned long long new_key = key_digits_2_long_int(matrix_kpriv[i]);
        unsigned long long new_cod_key = calc_runlength_int(new_key);
        store_key_int(matrix_kcod, i+1, new_cod_key);
    }
}

short** search_private_keys_int(short **matrix_kpub, short **matrix_kpriv, int lines, unsigned long long partialpubkey) {
    short * found = calloc(1,sizeof(short));
    short * partialpubkey_arr = key_long_2_digits_int(partialpubkey);
    short ** found_priv = NULL;
    int digit_cnt = count_digits(partialpubkey);
    int n = 0, cnt = 0, k = 0;
    for (int i = 0; i < lines; ++i) {
        cnt = count_digits(key_digits_2_long_int(matrix_kpub[i]));
        for (int j = 0; j < cnt; ++j) {
            if (partialpubkey_arr[j] == matrix_kpub[i][j]) {
                k++;
            } else {
                k = 0;
            }
            if(k == digit_cnt) {
                found[n] = (short)i;
                n++;
            }
        }
    }
    if(n != 0) {
        found_priv = alloc_matrix_int(n+1, 10);
        found_priv[0][0] = n;
        unsigned long long privkey, pubkey;
        for (int i = 0; i < n; ++i) {
            pubkey = key_digits_2_long_int(matrix_kpub[found[i]]);
            privkey = get_private_key_int(matrix_kpub, matrix_kpriv, found[i], pubkey);
            store_key_int(found_priv, n+1, privkey);
        }
        return found_priv;
    } else {
        return 0;
    }
}

void sort_matrix_int(short **matrix, int lines, int order){
    unsigned long long tmp, num1, num2;
    if(order == 1){ //ascending
        for (int i = 0; i < lines; ++i) {
            tmp = key_digits_2_long_int(matrix[i]);
            num1 = tmp;
            for (int j = 0; j < lines; ++j) {
                num2 = key_digits_2_long_int(matrix[j]);
                if(tmp > num2){
                    tmp = num2;
                    num2 = num1;
                    num1 = tmp;
                }
            }
        }
    } else { //descending
        for (int i = 0; i < lines; ++i) {
            tmp = key_digits_2_long_int(matrix[i]);
            num1 = tmp;
            for (int j = 0; j < lines; ++j) {
                num2 = key_digits_2_long_int(matrix[j]);
                if(tmp < num2){
                    tmp = num2;
                    num2 = num1;
                    num1 = tmp;
                }
            }
        }
    }
}

void sort_all_matrices_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, int order){
    sort_matrix_int(matrix_kpub, lines, order);
    sort_matrix_int(matrix_kpriv, lines, order);
    sort_matrix_int(matrix_kcod, lines, order);
}

void list_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, int order){
    sort_all_matrices_int(matrix_kpub, matrix_kpriv, matrix_kcod, lines, order);
    for (int i = 0; i < lines; ++i) {
        printf("\nkey #%d\n",i+1);
        printf("%llu\n", key_digits_2_long_int(matrix_kpub[i]));
        printf("%llu\n", key_digits_2_long_int(matrix_kpriv[i]));
        printf("%llu\n", key_digits_2_long_int(matrix_kcod[i]));
    }

}

void save_txt_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, char filename[]){
    FILE *fp;
    unsigned long long pub, priv, cod;
    fp = fopen(filename, "w");

    if(fp == NULL){
        printf("Can't create file.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < lines; ++i) {
        pub = key_digits_2_long_int(matrix_kpub[i]);
        fprintf(fp,"%llu",pub);
        fprintf(fp,",");
        priv = key_digits_2_long_int(matrix_kpriv[i]);
        fprintf(fp,"%llu",priv);
        fprintf(fp,",");
        cod = key_digits_2_long_int(matrix_kcod[i]);
        fprintf(fp,"%llu",cod);
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void load_txt_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, char filename[]){
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
    while(fgets(line, sizeof(line), fp)){

        int i = 0;
        char *token;
        token = strtok(line, ",");

        while(token != NULL){
            if(i == 0){
                pub = atoll(token);
                token = strtok(NULL,",");
                i++;
            }else if(i == 1){
                priv = atoll(token);
                token = strtok(NULL,",");
                i++;

            }else{
                cod = atoll(token);
                token = strtok(NULL,",");
            }
        }

        store_key_int(matrix_kpub,k+1,pub);
        store_key_int(matrix_kpriv,k+1,priv);
        store_key_int(matrix_kcod,k+1,cod);
        k++;
    }

    fclose(fp);
}

void save_bin_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, char filename[]) {
    num_t number[lines];
    FILE *fp;
    fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Can't create file.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < lines; ++i) {
        number[i].pub = key_digits_2_long_int(matrix_kpub[i]);
        number[i].priv = key_digits_2_long_int(matrix_kpriv[i]);
        number[i].cod = key_digits_2_long_int(matrix_kcod[i]);
    }
    fwrite(number, sizeof(num_t), lines, fp);
    fclose(fp);
}

void load_bin_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, char filename[]){
    num_t number[lines];
    FILE *fp;
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Can't create file.\n");
        exit(EXIT_FAILURE);
    }
    fread(number, sizeof(num_t), lines, fp);
    for (int i = 0; i < lines; ++i) {
        store_key_int(matrix_kpub, i+1, number[i].pub);
        store_key_int(matrix_kpriv, i+1, number[i].priv);
        store_key_int(matrix_kcod, i+1, number[i].cod);
    }
    fclose(fp);
}
