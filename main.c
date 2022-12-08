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
    time_t t;
    srand((unsigned)time(&t));

    /*
    //printf("!-Metodo menos eficiente-!\nPriv key da public key %d: %llu\n",212,calc_private_key_int(212));
    printf("!-Metodo mais eficiente-!\n%llu\n",v1_calc_private_key_int(212));
    short ** matrix = alloc_matrix_int(5, 7);
    store_key_int(matrix, 5, 212);
    printf("%d\n",exists_key_int(matrix, 5, 212));
    printf("%d\n",exists_key_int(matrix, 5, 21));
    */

    short ** rdm_matrix_pub = alloc_matrix_int(10,20);
    short ** rdm_matrix_priv = alloc_matrix_int(10,20);
    short ** rdm_matrix_cod = alloc_matrix_int(10,20);

    bulk_populate_public_keys_int(rdm_matrix_pub, 10); //working
    bulk_compute_private_keys_int(rdm_matrix_pub, rdm_matrix_priv, 10); //not fully working
    bulk_compute_runlengths_int(rdm_matrix_priv, rdm_matrix_cod, 10);


    //so imprime 4 numeros
    printf("%llu\n", key_digits_2_long_int(rdm_matrix_pub[0]));
    printf("%llu\n", key_digits_2_long_int(rdm_matrix_priv[0]));
    printf("%llu\n", key_digits_2_long_int(rdm_matrix_cod[0]));
    return 0;
}
