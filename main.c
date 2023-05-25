#include "structuri.h"
#include "liste.h"
#include "stive.h"
#include "cozi.h"

void openFiles(FILE** checker, FILE** out, FILE** in, char* argv[]){
    *checker = fopen(/*c.in*/argv[1], "rt");
    if (checker == NULL) {
        fprintf(stderr, "\n Eroare checker\n");
        exit(1);
    }
    *in = fopen(/*d.in*/argv[2], "rt");
    if (in == NULL) {
        fprintf(stderr, "\nEroare deschidere fisier date\n");
        exit(1);
    }
    *out = fopen(/*r.out*/argv[3], "wt");
    if (out == NULL) {
        fprintf(stderr, "\nEroare deschidere fisier rezultate\n");
        exit(1);
    }
}

void updateName(char* fName, char* sName){
    if(fName[strlen(fName) - 1] == ' ')
        fName[strlen(fName) - 1] = '\0';
    if(sName[strlen(sName) - 1] == ' ')
        sName[strlen(sName) - 1] = '\0';
}

void firstTask(TEAMLIST** teams, FILE* in, TEAM* aux, FILE* out){
    (*teams)->teamHead = initTeams(in);
    fseek(in, 0, 0);
    aux = (*teams)->teamHead;
    while (aux != NULL) {
        fprintf(out, "%s\n", aux->name);
        aux = aux->next;
    }
}

void secondTask(TEAMLIST** teams, TEAM* aux, FILE* out, int nrEchipe, char* argv[]){
    getScore(&(*teams)->teamHead);
    int nrMaxEchipe = 1;
    for (int i = 2; nrEchipe >= nrMaxEchipe; i++)     //nr maxim de echipe
    {
        nrMaxEchipe *= 2;
    }
    nrMaxEchipe /= 2;
    if(nrMaxEchipe != nrEchipe) {
        deleteTeamSurplus(&(*teams)->teamHead, nrEchipe, nrMaxEchipe);
        fclose(out);
        out = fopen(/*r.out*/argv[3], "wt");
        if (out == NULL) {
            fprintf(stderr, "\nEroare deschidere fisier rezultate\n");
            exit(1);
        }
        aux = (*teams)->teamHead;
        while (aux != NULL) {
            fprintf(out, "%s\n", aux->name);
            aux = aux->next;
        }
    }
}

void thirdTask(TEAM* aux, TEAMLIST** teams, FILE* out){
    aux = (*teams)->teamHead;
    TEAM* finalWinner = NULL;
    int round = 0, onetime = 1, nrNouEchipe = calcNrEchipe(aux);
    QUEUE *queue = NULL;
    while (nrNouEchipe % 2 == 0) {
        round++;
        fprintf(out, "\n--- ROUND NO:%d", round);
        aux = (*teams)->teamHead;
        STACK *winners = NULL, *losers = NULL;
        if(onetime==1) {
            queue = createQueue();
            while (aux != NULL) {
                (aux->name)[strlen(aux->name) - 1] = '\0';
                (aux->next->name)[strlen(aux->next->name) - 1] = '\0';
                enQueue(queue, &aux, &aux->next);
                aux = aux->next->next;
            }
            onetime=0;
        }
        aux = (*teams)->teamHead;
        while (queue->front != NULL) {
            updateName(queue->front->firstTeam->name,queue->front->secondTeam->name);
            fprintf(out, "\n%-32s - %+32s", queue->front->firstTeam->name, queue->front->secondTeam->name);
            TEAM *winnerTeam = NULL, *loserTeam = NULL;
            deQueue(queue, &winnerTeam, &loserTeam);
            push(&winners, winnerTeam);
            push(&losers, loserTeam);
        }
        //creaza stive, sterge losers, schimba scoru
        deleteLosers(losers, &(*teams)->teamHead);
        fprintf(out, "\n\nWINNERS OF ROUND NO:%d", round);
        aux = (*teams)->teamHead;
        queue = reinitQueue(queue);
        updateWinners(winners, finalWinner, teams, queue, out);
        fprintf(out, "\n");
        aux = (*teams)->teamHead;
        nrNouEchipe/=2;
    }
}

void freeMemory(TEAMLIST** teams, char* check){
    TEAM *toDelete = (*teams)->teamHead;
    deleteTeams(&toDelete);
    toDelete = NULL;
    free(*teams);
    free(check);
}

void closeFiles(FILE** checker, FILE** in, FILE** out){
    fclose(*in);
    fclose(*out);
    fclose(*checker);
}

int main(int argc, char *argv[]) {
    //deschidere fisiere
    FILE *checker, *in, *out;
    openFiles(&checker, &out, &in, argv);
    //fac datele din checker un vector
    char *check = malloc(5 * sizeof(char));
    for (int i = 0; i < 5; i++) {
        fscanf(checker, "%c ", &check[i]);

    }
    int nrEchipe;
    fscanf(in, "%d  ", &nrEchipe);       //numarul de echipe se afla pe primul rand
    TEAMLIST *teams = NULL;
    TEAM *aux = NULL;
    //alocari de memorie
    teams = malloc(sizeof(TEAMLIST));
    //------------------------------------TASK 1-------------------------------------
    if (check[0] == '1')
        firstTask(&teams, in, aux, out);
    //------------------------------------TASK 2-------------------------------------
    if (check[1] == '1')
        secondTask(&teams, aux, out, nrEchipe, argv);
    //------------------------------------TASK 3-------------------------------------
    if (check[2] == '1')
        thirdTask(aux, &teams, out);
//eliberare de memorie
    freeMemory(&teams, check);
//inchidere fisiere
    closeFiles(&checker, &in ,&out);
    return 0;
}