#ifndef COZI_H
#define COZI_H

#include "structuri.h"

QUEUE* createQueue();
void enQueue(QUEUE* q, TEAM** firstTeam, TEAM** secondTeam);
void deQueue (QUEUE *q, TEAM** win, TEAM** lose);
void deleteTeam(TEAM** team);
void deleteQueue(QUEUE *q);
QUEUE* reinitQueue(QUEUE* queue);


#endif