//
// Created by Bea on 29/11/2022.
//

#include "../headers/bipolarChars.h"
#include <stdio.h>
#include <malloc.h>


int count_chars(unsigned long long key) {
    int count = 0;
    while (key) {
        count++;
        key /= 10;
    }
    return count;
}

char* key_long_2_digits_char(unsigned long long key){
    int cnt = count_chars(key);
    unsigned long long aux = key;
    char * arr = calloc(cnt+1, sizeof(char));
    for (int i = cnt-1; i >= 0; i--) {
        unsigned long long digit = aux % 10;
        arr[i] = digit + '0';
        aux /= 10;
    }
    arr[cnt] = -1;
    return arr;
}

unsigned long long key_digits_2_long_char(char* keydigits){
    unsigned long long num = 0;
    for (int i = 0; keydigits[i] != -1; ++i) {
        num *= 10;
        num += keydigits[i] - '0';
    }
    return num;
}
