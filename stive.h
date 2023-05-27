#ifndef STIVE_H
#define STIVE_H

#include "structuri.h"

void push( STACK** top , TEAM* team);
TEAM* pop(STACK** top);
void deleteLosers(STACK *losers, TEAM** teams);
void updateWinners(STACK* winners, TEAM* finalWinner, TEAMLIST** teams, QUEUE* queue, FILE *out);
void deleteStack(STACK** top);


#endif