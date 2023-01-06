//
// Created by Bea on 05/01/2023.
//

#include "structs.h"
#include <string.h>
#include <stdio.h>

#ifndef NUMEROSBIPOLARES_USERS_H
#define NUMEROSBIPOLARES_USERS_H

#endif //NUMEROSBIPOLARES_USERS_H

void users();
USER_LIST *createUserList();
USER * addUser(char name[100], char email[100], USER_LIST *userList);
void addUserHead(USER * user, USER_LIST *users_list);
void addUserTail(USER * user, USER_LIST *users_list);
USER_LIST *deleteUser(char email[100], USER_LIST *users_list);
void orderByName(USER_LIST * users_list);
USER *searchNameUser(char *name, USER_LIST *users_list);
