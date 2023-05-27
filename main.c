#include "structuri.h"
#include "liste.h"
#include "stive.h"
#include "cozi.h"
#include "bst.h"

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

void firstTask(TEAMLIST** teams, FILE* in, TEAM* aux, FILE* out){
    (*teams)->teamHead = initTeams(in);
    fseek(in, 0, 0);
    aux = (*teams)->teamHead;
    while (aux != NULL) {
        fprintf(out, "%s\n", aux->name);
        aux = aux->next;
    }
}

void secondTask(TEAMLIST** teams, TEAM* aux, FILE** out, int nrEchipe, char* argv[]){
    getScore(&(*teams)->teamHead);
    int nrMaxEchipe = 1;
    for (int i = 2; nrEchipe >= nrMaxEchipe; i++){     //nr maxim de echipe
        nrMaxEchipe *= 2;
    }
    nrMaxEchipe /= 2;
    if(nrMaxEchipe != nrEchipe) {
        deleteTeamSurplus(&(*teams)->teamHead, nrEchipe, nrMaxEchipe);
        fclose(*out);
        *out = fopen(/*r.out*/argv[3], "wt");
        if (*out == NULL) {
            fprintf(stderr, "\nEroare deschidere fisier rezultate\n");
            exit(1);
        }
        aux = (*teams)->teamHead;
        while (aux != NULL) {
            fprintf(*out, "%s\n", aux->name);
            aux = aux->next;
        }
    }
}

void thirdTask(TEAM* aux, TEAMLIST** teams, FILE* out, TEAMLIST** firstEight){
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
                enQueue(queue, &aux, &aux->next);
                aux = aux->next->next;
            }
            onetime=0;
        }
        aux = (*teams)->teamHead;
        while (queue->front != NULL) {
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
        if(nrNouEchipe == 8)
            buildLeaderBoard(firstEight, teams);
    }
}

void fourthTask(TEAMLIST* firstEight, FILE* out){
    TEAM* aux = firstEight->teamHead;
    BST *root = initTree(&root, aux), *rootCopy = root;
    aux = aux->next;
    while(aux != NULL) {
        root = insert(root, aux);
        aux = aux->next;
    }
    fprintf(out, "\nTOP 8 TEAMS:");
    printDescendingOrder(rootCopy, out);
    deleteTree(root);
    root = NULL;
}

void freeMemory(TEAMLIST** teams, char* check, TEAMLIST** firstEight){
    deleteTeams(&(*teams)->teamHead);
    if(check[3] == 0 && check[4] == 0)      //altfel se elibereaza aceeasi memorie de 2 ori
        deleteTeams(&(*firstEight)->teamHead);
    free(*teams);
    free(*firstEight);
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
    for (int i = 0; i < 5; i++)
        fscanf(checker, "%c ", &check[i]);
    int nrEchipe;
    fscanf(in, "%d  ", &nrEchipe);       //numarul de echipe se afla pe primul rand
    TEAMLIST *teams = NULL, *firstEight = NULL;
    TEAM *aux = NULL;
    //alocari de memorie
    teams = malloc(sizeof(TEAMLIST));
    firstEight = malloc(sizeof(TEAMLIST));
    //------------------------------------TASK 1-------------------------------------
    if (check[0] == '1')
        firstTask(&teams, in, aux, out);
    //------------------------------------TASK 2-------------------------------------
    if (check[1] == '1')
        secondTask(&teams, aux, &out, nrEchipe, argv);
    //------------------------------------TASK 3-------------------------------------
    if (check[2] == '1')
        thirdTask(aux, &teams, out, &firstEight);
    if(check[3] == '1')
        fourthTask(firstEight, out);
//    displayTeam(teams->teamHead);
    freeMemory(&teams, check, &firstEight);      //eliberare de memorie
    closeFiles(&checker, &in ,&out);        //inchidere fisiere
    return 0;
}