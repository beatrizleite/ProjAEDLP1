//
// Created by Bea on 04/11/2022.
//
#include <stdio.h>
#include "headers/structs.h"
#include "headers/bipolarInts.h"
#include "headers/bipolarChars.h"

void printArrayShort(short *a, int N) {
    int i;
    for (i = 0; i < N; i++) {
        printf("%hi ", a[i]);
    }
    printf("\n");
}

int main(int argc, const char *argv[]) {
    printf("Projeto LP1/AED1\n");
    printf("!-Metodo menos eficiente-!\nPriv key da public key %d: %llu\n",212,calc_private_key_int(212));
    printf("!-Metodo mais eficiente-!\n%llu\n",v1_calc_private_key_int(212));
    short ** matrix = alloc_matrix_int(5, 7);
    store_key_int(matrix, 5, 212);
    printf("%d\n",exists_key_int(matrix, 5, 212));
    printf("%d\n",exists_key_int(matrix, 5, 21));


    return 0;
}
