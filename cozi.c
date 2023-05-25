#include "cozi.h"

QUEUE* createQueue() {
    QUEUE *q;
    q = (QUEUE*) malloc(sizeof(QUEUE));
    if (q == NULL) return NULL;
    q->front = q->rear = NULL;
    return q;
}

void enQueue(QUEUE* q, TEAM** firstTeam, TEAM** secondTeam){
    MATCH *newNode = (MATCH *)malloc(sizeof(MATCH));
    newNode->firstTeam = *firstTeam;
    newNode->secondTeam = *secondTeam;
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
    if(aux->secondTeam->points >= aux->firstTeam->points) {
        *win = aux->secondTeam;
        *lose = aux->firstTeam;
    }
    else{
        *win = aux->firstTeam;
        *lose = aux->secondTeam;
    }
}

void deleteTeam(TEAM** team){
    if(team == NULL){
        printf("\n eroare memorie echipa");
        exit(1);
    }
    TEAM* copy = *team;
    free(copy->name);
    while (copy->members->playerHead != NULL && copy->members != NULL) {
        PLAYER *prev = copy->members->playerHead;
        copy->members->playerHead = copy->members->playerHead->next;
        free(prev->firstName);
        free(prev->secondName);
        free(prev);
    }
    free(copy->members);
    free(copy);
}

void deleteQueue(QUEUE *q){
    MATCH *aux;
    while(q->front != NULL){
        aux = q->front;
        q->front = q->front->next;
        free(aux);
    }
    free(q);
}

QUEUE* reinitQueue(QUEUE* queue){
    if (queue != NULL) {
        deleteQueue(queue);
    }
    queue = createQueue();
    return queue;
}
