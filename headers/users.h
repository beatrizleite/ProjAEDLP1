//
// Created by Bea on 05/01/2023.
//

#include "structs.h"
#include <string.h>
#include <stdio.h>

#ifndef NUMEROSBIPOLARES_USERS_H
#define NUMEROSBIPOLARES_USERS_H

#endif //NUMEROSBIPOLARES_USERS_H

USER_LIST *createUserList();
KEY_HOLDERS_LIST *createKeyHolderList();
KEY_HOLDERS *createKeyHolder(KEY_HOLDER *key_holder);
void addUserHead(USER * user, USER_LIST *users_list);
void addUserTail(USER * user, USER_LIST *users_list);
USER_LIST *deleteUser(char email[100], USER_LIST *users_list);
void orderByName(USER_LIST * users_list);
USER *searchNameUser(char *name, USER_LIST *users_list);
