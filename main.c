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
    /*
    printf("!-Metodo menos eficiente-!\nPriv key da public key %d: %llu\n",212,calc_private_key_int(212));
    printf("!-Metodo mais eficiente-!\n%llu\n",v1_calc_private_key_int(212));
    short ** matrix = alloc_matrix_int(5, 7);
    store_key_int(matrix, 5, 212);
    printf("%d\n",exists_key_int(matrix, 5, 212));
    printf("%d\n",exists_key_int(matrix, 5, 21));
    */

    short ** rdm_matrix_pub = alloc_matrix_int(5,20);

    short ** rdm_matrix_priv = alloc_matrix_int(5,20);
    short ** rdm_matrix_cod = alloc_matrix_int(5,20);

    bulk_populate_public_keys_int(rdm_matrix_pub, 5); //working

    bulk_compute_private_keys_int(rdm_matrix_pub, rdm_matrix_priv, 5);
    //bulk_compute_runlengths_int(rdm_matrix_priv, rdm_matrix_cod, 5);
    for (int i = 0; i < 5; ++i) {
        unsigned long long num_pub = key_digits_2_long_int(rdm_matrix_pub[i]);
        unsigned long long num_priv = key_digits_2_long_int(rdm_matrix_priv[i]);
        //unsigned long long num_cod = key_digits_2_long_int(rdm_matrix_cod[i]);
        printf("[%d] : %llu\t[%d] : %llu\n", i, num_pub, i, num_priv);
    }

    return 0;
}
