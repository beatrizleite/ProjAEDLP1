//
// Created by Bea on 29/11/2022.
//

#include "../headers/bipolarInts.h"


int count_digits(unsigned long long key) {
    short aux = (short) key;
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

unsigned long long key_digits_2_long_int(short* keydigits){
    int digit_num = sizeof(keydigits)/sizeof(keydigits[0]);
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
    int i = 53;
    while(k){
        //int i = 1 + rand() % 100000;
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
        if(digit_one == digit_two) {
            digit_one = digit;
            count1++;
        } else {
            digit_two = digit;
            count2++;
        }
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
    short * key_arr = key_long_2_digits_int(key);
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            if(matrix[i][j] == key_arr[j] && matrix[i][j+1] == 0){
                k++;
            }
        }
        if(k == 1) {
            return 1;
        }
    }
    return 0;
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
