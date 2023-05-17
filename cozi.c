#include "cozi.h"

QUEUE* createQueue() {
    QUEUE *q;
    q = (QUEUE*) malloc(sizeof(QUEUE));
    if (q == NULL) return NULL;
    q->front = q->rear = NULL;
    return q;
}

void enQueue(QUEUE* q, TEAM* firstTeam, TEAM* secondTeam){
    MATCH *newNode = (MATCH *)malloc(sizeof(MATCH));
    newNode->firstTeam = firstTeam;
    newNode->secondTeam = secondTeam;
    newNode->next = NULL;
    if (q->rear == NULL )
        q->rear = newNode ;
    else {
        (q->rear)->next = newNode;
        (q->rear)= newNode;
    }
    if (q->front == NULL ) q->front =q->rear;
}

void deQueue (QUEUE *q, TEAM** win, TEAM** lose){
    if(q->front == NULL){
        q->rear = NULL;
        return;
    }
    MATCH *aux;
    aux = q->front;
    q->front = q->front->next;
    if(aux->secondTeam->points > aux->firstTeam->points) {
        *win = aux->secondTeam;
        *lose = aux->firstTeam;
    }
    else{//daca sunt egale intra tot pe a 2a ramura
        *win = aux->firstTeam;
        *lose = aux->secondTeam;
    }
    free(aux);
}
