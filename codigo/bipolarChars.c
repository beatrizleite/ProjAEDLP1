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


