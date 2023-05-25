#include "stive.h"
#include "cozi.h"
#include "liste.h"

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

void deleteLosers(STACK *losers, TEAM** teams){
    TEAM* aux = NULL, * copy = NULL;
    copy = *teams;
    while (losers != NULL) {
        TEAM *auxStack = pop(&losers);
        aux = copy;
        if (auxStack == aux) {
            copy = copy->next;
            aux = copy;
            deleteTeam(&auxStack);
            auxStack = NULL;
        }
        else if (auxStack != NULL) {
            aux = copy;
            if (aux != NULL) {
                while (aux->next != auxStack) {
                    aux = aux->next;
                }
            }
            aux->next = auxStack->next;
            deleteTeam(&auxStack);
            auxStack = NULL;
        }
    }
}

void updateWinners(STACK* winners, TEAM* finalWinner, TEAMLIST** teams, QUEUE* queue, FILE *out){
    while(winners != NULL){
        TEAM *winner = pop(&winners);
        if (winners == NULL) {
            finalWinner = winner;
            scoreUpdate(&finalWinner);
            getScore(&finalWinner);
            (*teams)->teamHead = finalWinner;
            deleteQueue(queue);
            fprintf(out, "\n%-32s  -  %.2f", finalWinner->name, finalWinner->points);
            break;
        }
        TEAM *nextWinner = pop(&winners);
        scoreUpdate(&winner);
        scoreUpdate(&nextWinner);
        getScore(&winner);
        getScore(&nextWinner);
        fprintf(out, "\n%-32s  -  %.2f\n%-32s  -  %.2f", winner->name, winner->points, nextWinner->name,
                nextWinner->points);
        enQueue(queue, &winner, &nextWinner);
    }
}
