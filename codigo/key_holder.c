//
// Created by Bea on 05/01/2023.
//

#include "../headers/key_holder.h"
#include "../headers/structs.h"
#include "../headers/bipolarInts.h"
#include "../headers/bipolarChars.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

KEY_HOLDERS_LIST *key_holders_list;

void key_holder(){
    key_holders_list = (KEY_HOLDERS_LIST *) malloc(sizeof(KEY_HOLDERS_LIST));
    key_holders_list = createKeyHolderList();

    KEY_HOLDER *keyHolder = createKeyHolder(LINES, COLUMNS, 1);
    KEY_HOLDER *keyHolder2 = createKeyHolder(LINES, COLUMNS, 1);
    KEY_HOLDERS *keyHolders = createKeyHolders(keyHolder);
    keyHolders = createKeyHolders(keyHolder2);
    searchKeyHolder(keyHolder, 42);
    searchKeyHolder(keyHolder, 20038);
    insertKeyHolder(key_holders_list, keyHolders);
    deleteKeyHolder(key_holders_list, keyHolders);
}

KEY_HOLDERS_LIST *createKeyHolderList(){
    key_holders_list->phead = key_holders_list->ptail = NULL;
    key_holders_list->nkey_holder = 0;
    return key_holders_list;
}



KEY_HOLDER *createKeyHolder(int lines, int columns, int order){
    KEY_HOLDER *keyHolder = (KEY_HOLDER *) malloc(sizeof(KEY_HOLDER) * lines);
    keyHolder->lines = lines;
    keyHolder->CHAR_matrix_kpub = alloc_matrix_char(lines, columns);
    keyHolder->CHAR_matrix_kpriv = alloc_matrix_char(lines, columns);
    keyHolder->CHAR_matrix_kcod = alloc_matrix_char(lines, columns);
    keyHolder->INT_matrix_kpub = alloc_matrix_int(lines, columns);
    keyHolder->INT_matrix_kpriv = alloc_matrix_int(lines, columns);
    keyHolder->INT_matrix_kcod = alloc_matrix_int(lines, columns);

    bulk_populate_public_keys_char(keyHolder->CHAR_matrix_kpub, keyHolder->lines);
    bulk_compute_private_keys_char(keyHolder->CHAR_matrix_kpriv, keyHolder->CHAR_matrix_kpriv, keyHolder->lines);
    bulk_compute_runlengths_char(keyHolder->CHAR_matrix_kcod, keyHolder->CHAR_matrix_kpriv, keyHolder->lines);
    bulk_populate_public_keys_int(keyHolder->INT_matrix_kpub, keyHolder->lines);
    bulk_compute_private_keys_int(keyHolder->INT_matrix_kpriv, keyHolder->INT_matrix_kpub, keyHolder->lines);
    bulk_compute_runlengths_int(keyHolder->INT_matrix_kcod, keyHolder->INT_matrix_kpriv, keyHolder->lines);

    sort_matrix_int(keyHolder->INT_matrix_kpub, LINES, 1);
    return keyHolder;
}

KEY_HOLDERS *createKeyHolders(KEY_HOLDER *keyHolder){
    KEY_HOLDERS *keyHolders = (KEY_HOLDERS *) malloc(sizeof(KEY_HOLDERS));
    time_t time_now = time(0);
    char buff[100];
    struct tm now = *localtime(&time_now);
    strftime(buff, 100, "%d-%m-%Y %H:%M:%S", &now);
    keyHolders->created.hour = now.tm_hour;
    keyHolders->created.minute = now.tm_min;
    keyHolders->created.second = now.tm_sec;
    keyHolders->created.day = now.tm_mday;
    keyHolders->created.month = now.tm_mon + 1;
    keyHolders->created.year = now.tm_year + 1900;
    keyHolders->updated = keyHolders->created;
    keyHolders->next = NULL;
    keyHolders->porta_chave = keyHolder;
    return keyHolders;
}

KEY_HOLDERS_LIST *insertKeyHolder(KEY_HOLDERS_LIST *keyHoldersList, KEY_HOLDERS *keyHolders){
    time_t time_now = time(0);
    char buff[100];
    struct tm now = *localtime(&time_now);
    strftime(buff, 100, "%d-%m-%Y %H:%M:%S", &now);
    keyHolders->updated.hour = now.tm_hour;
    keyHolders->updated.minute = now.tm_min;
    keyHolders->updated.second = now.tm_sec;
    keyHolders->updated.day = now.tm_mday;
    keyHolders->updated.month = now.tm_mon+1;
    keyHolders->updated.year = now.tm_year+1900;
    keyHolders->next = keyHoldersList->phead;
    keyHoldersList->phead = keyHolders;
    keyHoldersList->nkey_holder++;
    return keyHoldersList;
}

KEY_HOLDERS_LIST *deleteKeyHolder(KEY_HOLDERS_LIST *keyHoldersList, KEY_HOLDERS *keyHolders){
    KEY_HOLDERS *delete;
    KEY_HOLDERS *actual = keyHoldersList->phead;
    while(actual != NULL) {
        if(actual == keyHolders){
            keyHoldersList->phead = actual->next;
            keyHoldersList->nkey_holder--;
            free(actual);
            return keyHoldersList;
        } else {
            while(actual->next != NULL){
                delete = actual->next;
                if(delete == keyHolders){
                    if(delete->next == NULL){
                        keyHoldersList->ptail = actual;
                        keyHoldersList->ptail->next = NULL;
                    } else {
                        actual->next = delete->next;
                    }
                    keyHoldersList->nkey_holder--;
                    free(delete);
                    return keyHoldersList;
                } else {
                    actual = actual->next;
                }
            }
        }
    }
    return keyHoldersList;
}

void searchKeyHolder(KEY_HOLDER *keyHolder, unsigned long long key){
    //aplying binary search
    int k=0;
    int low = 0;
    int high = keyHolder->lines-1;
    int mid;
    while(low <= high) {
        mid = (low + high) / 2;
        unsigned long long comp = key_digits_2_long_int(keyHolder->INT_matrix_kpub[mid]);
        if(comp < key){
            high = mid - 1;
        } else if(comp > key){
                low = mid + 1;
        } else if(comp == key){
            k++;
            break;
        } else {
            printf("key not found\n");
        }
    }
    if(k==1){
        printf("found key %llu in position %d!\n", key, mid);
    } else {
        printf("key not found\n");
    }
}


