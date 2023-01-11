//
// Created by Bea on 05/01/2023.
//

#include "../headers/structs.h"

#ifndef NUMEROSBIPOLARES_KEY_HOLDER_H
#define NUMEROSBIPOLARES_KEY_HOLDER_H

void key_holder();
KEY_HOLDERS_LIST *createKeyHolderList();
KEY_HOLDER *createKeyHolder(int lines, int columns, int order);
KEY_HOLDERS *createKeyHolders(KEY_HOLDER *keyHolder);
KEY_HOLDERS_LIST *insertKeyHolder(KEY_HOLDERS_LIST *keyHoldersList, KEY_HOLDERS *keyHolders);
KEY_HOLDERS_LIST *deleteKeyHolder(KEY_HOLDERS_LIST *keyHoldersList, KEY_HOLDERS *keyHolders);
void searchKeyHolder(KEY_HOLDER *keyHolder, unsigned long long key);

#endif //NUMEROSBIPOLARES_KEY_HOLDER_H
