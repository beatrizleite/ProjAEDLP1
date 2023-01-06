//
// Created by Bea on 05/01/2023.
//

#include "../headers/users.h"
#include "../headers/structs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

USER_LIST *user_list;

void users(){
    user_list = (USER_LIST *) malloc(sizeof(USER_LIST));
    user_list = createUserList();
    addUser("Beatriz", "bea@mail.com", user_list);
    addUser("Afonso", "af@mail.com", user_list);
    addUser("Gustavo", "gus@mail.com", user_list);
    searchNameUser("Beatriz", user_list);
    deleteUser("gus@mail.com", user_list);
}

USER_LIST *createUserList(){
    user_list->phead = user_list->ptail = NULL;
    user_list->nusers = 0;
    return user_list;
}

USER * addUser(char name[100], char email[100], USER_LIST *userList){
    USER *user = (USER *) malloc(sizeof(USER));
    strcpy(user->name, name);
    strcpy(user->email, email);
    user->next = NULL;

    //addUserHead(user, userList);
    addUserTail(user, userList);

    orderByName(userList);

    return user;
}

void addUserHead(USER * user, USER_LIST *users_list){
    if(users_list->phead == NULL && users_list->nusers == 0){
        users_list->phead = user;
        users_list->ptail = user;
        users_list->nusers++;
    } else {
        user->next = (struct user *) users_list->phead;
        users_list->phead = user;
        users_list->nusers++;
    }
}

void addUserTail(USER * user, USER_LIST *users_list){
    if(users_list->phead == NULL && users_list->nusers == 0){
        users_list->phead = user;
        users_list->ptail = user;
        users_list->nusers++;
    } else {
        users_list->ptail->next = user;
        users_list->ptail = user;
        users_list->nusers++;
    }
    users_list->ptail->next = NULL;
}

USER_LIST *deleteUser(char email[100], USER_LIST *users_list){
    USER *delete;
    USER *actual = users_list->phead;
    while(actual != NULL) {
        if(strcmp(actual->email, email)){
            users_list->phead = actual->next;
            users_list->nusers--;
            free(actual);
            printf("deleted!\n");
            return users_list;
        } else {
            while(actual->next != NULL) {
                delete = (USER *) actual->next;
                if(strcmp(delete->email, email)) {
                    if (delete->next == NULL) {
                        users_list->ptail = actual;
                        users_list->ptail->next = NULL;
                    } else {
                        actual->next = delete->next;
                    }
                    users_list->nusers--;
                    printf("deleted!\n");
                    free(delete);
                    return users_list;
                } else {
                    actual = actual->next;
                }
            }
        }
    }
    printf("error\n");
    return users_list;
}

void orderByName(USER_LIST * users_list){
    USER *actual = users_list->phead, *index = NULL;
    USER *tmp = (USER *) malloc(sizeof(USER));

    if(users_list->phead == NULL){
        return;
    } else {
        while(actual != NULL) {
            index = actual->next;

            while(index != NULL) {
                if(strcmp(index->name, actual->name)) {
                    strcpy(tmp->name, actual->name);
                    strcpy(tmp->email, actual->email);
                    tmp->porta_chaves = actual->porta_chaves;

                    strcpy(actual->name, index->name);
                    strcpy(actual->email, index->email);
                    actual->porta_chaves = index->porta_chaves;

                    strcpy(index->name, tmp->name);
                    strcpy(index->email, tmp->email);
                    index->porta_chaves = tmp->porta_chaves;
                }
                index = index->next;
            }
            actual = actual->next;
        }
    }
}

USER *searchNameUser(char *name, USER_LIST *users_list){
    USER *user;
    user = users_list->phead;
    while(user != NULL){
        if(strcmp(name, user->name) == 0){
            return user;
        }
        user = user->next;
    }
    return 0;
}