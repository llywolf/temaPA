#ifndef COZI_H
#define COZI_H

#include "structuri.h"

QUEUE* createQueue();
void enQueue(QUEUE* q, TEAM* firstTeam, TEAM* secondTeam);
void deQueue (QUEUE *q, TEAM** win, TEAM** lose);

#endif