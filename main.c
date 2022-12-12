//
// Created by Bea on 04/11/2022.
//
#include <stdio.h>
#include "headers/structs.h"
#include "headers/bipolarInts.h"
#include "headers/bipolarChars.h"

int main(int argc, const char *argv[]) {
    printf("Projeto LP1/AED1\n");

    /*
    //printf("!-Metodo menos eficiente-!\nPriv key da public key %d: %llu\n",212,calc_private_key_int(212));
    printf("!-Metodo mais eficiente-!\n%llu\n",v1_calc_private_key_int(212));
    short ** matrix = alloc_matrix_int(5, 7);
    store_key_int(matrix, 5, 212);
    printf("%d\n",exists_key_int(matrix, 5, 212));
    printf("%d\n",exists_key_int(matrix, 5, 21));
    */

    /*
    CHAVE key;
    short ** matrix_pub = alloc_matrix_int(10,10);
    short ** matrix_priv = alloc_matrix_int(10,10);
    short ** matrix_kcod = alloc_matrix_int(10,10);
    key.pubkey = new_public_key_int();
    key.privkey = calc_private_key_int(key.pubkey);
    key.kcodkey = calc_runlength_int(key.privkey);
    key.size = (count_digits(key.pubkey));

    store_key_int(matrix_pub, 10, key.pubkey);
    store_key_int(matrix_priv, 10, key.privkey);
    store_key_int(matrix_kcod, 10, key.kcodkey);

    printf("Key %llu:\nPriv: %llu\t Run-Length: %llu\n\n", key_digits_2_long_int(matrix_pub[0]), key_digits_2_long_int(matrix_priv[0]), key_digits_2_long_int(matrix_kcod[0]));
    */


    short ** rdm_matrix_pub = alloc_matrix_int(10,10);
    short ** rdm_matrix_priv = alloc_matrix_int(10,10);
    short ** rdm_matrix_cod = alloc_matrix_int(10,10);

    bulk_populate_public_keys_int(rdm_matrix_pub, 10); //working
    bulk_compute_private_keys_int(rdm_matrix_pub, rdm_matrix_priv, 10); //working
    bulk_compute_runlengths_int(rdm_matrix_priv, rdm_matrix_cod, 10); //working

    printf("\n==BULK GENERATED==\n");
    for (int i = 0; i < 10; ++i) {
        printf("public key %d: %llu\n", i+1, key_digits_2_long_int(rdm_matrix_pub[i]));
        printf("private key %d: %llu\n", i+1, key_digits_2_long_int(rdm_matrix_priv[i]));
        printf("code key %d: %llu\n\n", i+1, key_digits_2_long_int(rdm_matrix_cod[i]));

    }

    return 0;
}
