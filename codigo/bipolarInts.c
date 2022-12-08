//
// Created by Bea on 29/11/2022.
//

#include "../headers/bipolarInts.h"


int count_digits(unsigned long long key) {
    unsigned long long aux = key;
    int count=0;
    while(aux) {
        aux /= 10;
        count++;
    }
    return count;
}

unsigned long long new_public_key_int(void) {
    return (unsigned long long)(rand() % 10000) + 1;
}

short* key_long_2_digits_int(unsigned long long key) {
    int digit_num = count_digits(key);
    short aux = (short) key;
    short * arr = (short *) malloc(digit_num * sizeof(short));
    for (int i = digit_num-1; i >= 0; i--) {
        int digit = aux % 10;
        arr[i] = (short) digit;
        aux /= 10;
    }
    return arr;
}

int count_array_elements(short * arr) {

}

unsigned long long key_digits_2_long_int(short* keydigits){
    size_t digit_num = sizeof(keydigits)/sizeof(short);
    unsigned long long num = 0;
    for (int i = 0; i < digit_num; ++i) {
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
    while(aux) {
        int rem = aux % 10;
        cnt[rem]++;
        aux /= 10;
    }
    for (int i = 0; i < 10; ++i) {
        if(cnt[i] != 0) k++;
        if(k>2){
            return 0;
        }
    }
    short * arr = key_long_2_digits_int(key);
    //int size = (int)sizeof(arr)/sizeof(arr[0]);
    int size = count_digits(key);

    int diff = 0;
    for (int i = 1; i < size; ++i) {
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
    unsigned long long privkey;
    time_t t;
    srand((unsigned) time(&t));
    int k = 1;
    while(k){
        int i = 1 + rand() % 100000;
        if(pubkey % i == 0) {
            if(isBipolar(i)) {
                privkey = i;
                k = 0;
            }
        }
        i++;
    }
    return privkey;
}

unsigned long long v1_calc_private_key_int(unsigned long long pubkey) {
    int i, j, k, n;
    unsigned long long num = 0;
    time_t t;
    srand((unsigned) time(&t));

    i = 1 + rand()%8;
    j = rand()%9;
    k = 1 + rand()%8;
    n = rand()%9;
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
        v1_calc_private_key_int(pubkey);
    }

    return num;
}

unsigned long long calc_runlength_int(unsigned long long privkey){
    int cnt = count_digits(privkey);
    unsigned long long aux=privkey, digit=0;
    unsigned long long count1=0,count2=0,digit_one=0, digit_two=0;
    unsigned long long rl=0;
    while(aux) {
        digit = aux%10;
        digit_one = digit;
        count1++;
        aux /= 10;
    }

    rl += count1;
    rl *= 10;
    rl += digit_one;
    rl *= 10;
    rl += count2;
    rl *= 10;
    rl += digit_two;

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
    for (int i = 0; i < nlines; ++i) {
        a[i] = (short*)calloc(ncolumns, sizeof(short));
    }
    return a;
}

void store_key_int(short **matrix, int lines, unsigned long long key){
    int columns = count_digits(key);
    short * key_arr = key_long_2_digits_int(key);
    for (int i = 0; i < lines; ++i) {
        if(matrix[i][0] == 0) {
            for (int j = 0; j < columns; ++j) {
                matrix[i][j] = key_arr[j];
            }
            return;
        }
    }
}

int exists_key_int(short **matrix, int lines, unsigned long long key) {
    int columns = count_digits(key);
    int k=0;
    int line=0;
    short * key_arr = key_long_2_digits_int(key);
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            if(matrix[i][j] == key_arr[j] && matrix[i][j+1] == 0){
                k++;
                line = i;
            }
        }
        if(k == 1) {
            return line;
        }
    }
    return -1;
}

unsigned long long get_private_key_int(short **matrix_kpub, short **matrix_kpriv, int lines, unsigned long long pubkey) {
    short * key_arr = key_long_2_digits_int(pubkey);
    int cnt = count_digits(pubkey);
    unsigned long long final;
    int k=0, lin=0;
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < cnt; ++j) {
            if(matrix_kpub[i][j] == key_arr[j] && matrix_kpub[i][j+1] == 0){
                k++;
                lin = i;
            }
        }
        if(k == 1) {
            return key_digits_2_long_int(matrix_kpriv[lin]);
        }
    }
    return 0;
}

unsigned long long get_runlength_int(short **matrix_kpriv, short **matrix_kcod, int lines, unsigned long long privkey) {
    int cnt = count_digits(privkey);
    int k=0, lin;
    short * key_arr = key_long_2_digits_int(privkey);

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < cnt; ++j) {
            if (matrix_kpriv[i][j] == key_arr[j] && matrix_kpriv[i][j + 1] == 0) {
                k++;
                lin = i;
            }
        }
        if (k == 1) {
            return calc_runlength_int(key_digits_2_long_int(matrix_kpriv[lin]));
        }
    }
    return 0;
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
    for (int i = 0; i < lines; ++i) {
        unsigned long long new_key = new_public_key_int();
        short * new_key_arr = key_long_2_digits_int(new_key);
        for (int j = 0; j < count_digits(new_key); ++j) {
            matrix_kpub[i][j] = new_key_arr[j];
        }
    }
}

void bulk_compute_private_keys_int(short **matrix_kpub, short **matrix_kpriv, int lines) {
    for (int i = 0; i < lines; ++i) {
        unsigned long long new_key = key_digits_2_long_int(matrix_kpub[i]);
        unsigned long long new_priv_key = v1_calc_private_key_int(new_key);
        short * new_key_arr = key_long_2_digits_int(new_priv_key);
        int cnt = count_digits(new_priv_key);

        for (int j = 0; j < cnt; ++j) {
            matrix_kpriv[i][j] = new_key_arr[j];
            printf("new_key_Arr[%d] = %hd",j,new_key_arr[j]);
        }
    }
}

void bulk_compute_runlengths_int(short **matrix_kpriv, short **matrix_kcod, int lines) {
    for (int i = 0; i < lines; ++i) {
        unsigned long long new_key = key_digits_2_long_int(matrix_kpriv[i]);
        unsigned long long new_cod_key = calc_runlength_int(new_key);
        short * new_key_arr = key_long_2_digits_int(new_cod_key);
        for (int j = 0; j < count_digits(new_cod_key); ++j) {
            matrix_kcod[i][j] = new_key_arr[j];
        }
    }
}

int columns_per_line(short ** matrix, int line) {

}

short** search_private_keys_int(short **matrix_kpub, short **matrix_kpriv, int lines, unsigned long long partialpubkey) {
    
}

void sort_matrix_int(short **matrix, int lines, int order){

}