//
// Created by Bea on 04/11/2022.
//
#define LINES 10
#define COLUMNS 20

#include <stdio.h>
#include <string.h>
#include "headers/structs.h"
#include "headers/bipolarInts.h"
#include "headers/bipolarChars.h"


int main(int argc, const char *argv[]) {
    printf("Projeto LP1/AED1\n");

    /********************************************************
     * ******************************************************
     * *********************** INTS *************************
     * ******************************************************
     * ******************************************************
     */

    /*short ** matrix = alloc_matrix_int(5, 7);
    store_key_int(matrix, 5, 212);
    printf("%d\n",exists_key_int(matrix, 5, 212));
    printf("%d\n",exists_key_int(matrix, 5, 21));

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


    short ** rdm_matrix_pub = alloc_matrix_int(LINES,COLUMNS);
    short ** rdm_matrix_priv = alloc_matrix_int(LINES,COLUMNS);
    short ** rdm_matrix_cod = alloc_matrix_int(LINES,COLUMNS);
    bulk_populate_public_keys_int(rdm_matrix_pub, LINES); //working
    bulk_compute_private_keys_int(rdm_matrix_pub, rdm_matrix_priv, LINES); //working
    bulk_compute_runlengths_int(rdm_matrix_priv, rdm_matrix_cod, LINES); //working


    printf("\n==BULK GENERATED==\n");
    for (int i = 0; i < 10; ++i) {
        printf("public key %d: %llu\n", i+1, key_digits_2_long_int(rdm_matrix_pub[i]));
        printf("private key %d: %llu\n", i+1, key_digits_2_long_int(rdm_matrix_priv[i]));
        printf("code key %d: %llu\n\n", i+1, key_digits_2_long_int(rdm_matrix_cod[i]));
    }

    short ** search = search_private_keys_int(rdm_matrix_pub, rdm_matrix_priv, LINES, 24);
    printf("\n==SEARCH RESULTS==\n");
    if (search != 0) {
        for (int i = 1; i <= search[0][0]; ++i) {
            printf("priv key #%d found: %llu\n", i, key_digits_2_long_int(search[i]));
        }
    } else {
        printf("no keys found.\n");
    }

    short ** matrix_pub = alloc_matrix_int(LINES,COLUMNS);
    short ** matrix_priv = alloc_matrix_int(LINES,COLUMNS);
    short ** matrix_cod = alloc_matrix_int(LINES,COLUMNS);
    short ** bin_matrix_pub = alloc_matrix_int(LINES,COLUMNS);
    short ** bin_matrix_priv = alloc_matrix_int(LINES,COLUMNS);
    short ** bin_matrix_cod = alloc_matrix_int(LINES,COLUMNS);
    save_txt_keys_int(rdm_matrix_pub, rdm_matrix_priv, rdm_matrix_cod, 10, "C:\\Users\\Bea\\Documents\\ProjAEDLP1\\data\\file_ints_txt.txt");
    save_bin_keys_int(rdm_matrix_pub, rdm_matrix_priv, rdm_matrix_cod, 10, "C:\\Users\\Bea\\Documents\\ProjAEDLP1\\data\\file_ints_bin.bin");
    load_txt_keys_int(matrix_pub,matrix_priv,matrix_cod,10, "C:\\Users\\Bea\\Documents\\ProjAEDLP1\\data\\file_ints_txt.txt");
    printf("\n\n==============================================================\n");
    for (int i = 0; i < 10; ++i) {
        printf("public key %d: %llu\n", i+1, key_digits_2_long_int(matrix_pub[i]));
        printf("private key %d: %llu\n", i+1, key_digits_2_long_int(matrix_priv[i]));
        printf("code key %d: %llu\n\n", i+1, key_digits_2_long_int(matrix_cod[i]));
    }
    printf("\n\n==============================================================\n");
    load_bin_keys_int(bin_matrix_pub,bin_matrix_priv,bin_matrix_cod,10,  "C:\\Users\\Bea\\Documents\\ProjAEDLP1\\data\\file_ints_bin.bin");
    for (int i = 0; i < 10; ++i) {
        printf("public key %d: %llu\n", i+1, key_digits_2_long_int(bin_matrix_pub[i]));
        printf("private key %d: %llu\n", i+1, key_digits_2_long_int(bin_matrix_priv[i]));
        printf("code key %d: %llu\n\n", i+1, key_digits_2_long_int(bin_matrix_cod[i]));
    }


    list_keys_int(rdm_matrix_pub, rdm_matrix_priv, rdm_matrix_cod, LINES, 0);
    list_keys_int(rdm_matrix_pub, rdm_matrix_priv, rdm_matrix_cod, LINES, 1);


    /********************************************************
     * ******************************************************
     * *********************** CHARS ************************
     * ******************************************************
     * ******************************************************


    unsigned long long priv_key = calc_private_key_char(123);
    printf("\n\n%llu\n", priv_key);
    printf("%llu\n", calc_runlength_char(priv_key));

    char ** char_rdm_matrix_pub = alloc_matrix_char(LINES,COLUMNS);
    char ** char_rdm_matrix_priv = alloc_matrix_char(LINES,COLUMNS);
    char ** char_rdm_matrix_cod = alloc_matrix_char(LINES,COLUMNS);
    bulk_populate_public_keys_char(char_rdm_matrix_pub, LINES); //working
    bulk_compute_private_keys_char(char_rdm_matrix_pub, char_rdm_matrix_priv, LINES); //working
    bulk_compute_runlengths_char(char_rdm_matrix_priv, char_rdm_matrix_cod, LINES); //working

    list_keys_char(char_rdm_matrix_pub, char_rdm_matrix_priv, char_rdm_matrix_cod, LINES, 1);
    */

    return 0;
}
