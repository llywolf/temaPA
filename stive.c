#include "stive.h"

void push(STACK** top, TEAM* team){
    STACK* newNode = (STACK*)malloc(sizeof(STACK));
    newNode->team = team;
    newNode->next = *top;
    *top = newNode;
}

TEAM* pop(STACK** top){
    STACK* temp = *top;
    TEAM* aux = (*top)->team;
    *top = (*top)->next;
    free(temp);
    return aux;
}
