#include "structuri.h"
#include "liste.h"
#include "stive.h"
#include "cozi.h"

int main(int argc, char *argv[]) {
    //deschidere fisiere
    FILE *checker, *in, *out;
    checker =fopen(/*c.in*/argv[1], "rt");
    if(checker == NULL){
        fprintf(stderr, "\n Eroare checker\n");
        exit(1);
    }
    in = fopen(/*d.in*/argv[2], "rt");
    if (in == NULL) {
        fprintf(stderr, "\nEroare deschidere fisier date\n");
        exit(1);
    }
    out = fopen(/*r.out*/argv[3], "wt");
    if (out == NULL) {
        fprintf(stderr, "\nEroare deschidere fisier rezultate\n");
        exit(1);
    }
    //fac datele din checker un vector
    char *check = malloc(5 * sizeof(char));
    for(int i = 0; i < 5; i++) {
        fscanf(checker, "%c ", &check[i]);

    }
    int nrEchipe;
    fscanf(in, "%d ", &nrEchipe);       //numarul de echipe se afla pe primul rand
    TEAMLIST *teams = NULL;
    TEAM* aux = NULL;
    //alocari de memorie
    teams = malloc(sizeof(TEAMLIST));
    //------------------------------------TASK 1-------------------------------------
    if(check[0] == '1'){
        teams->teamHead = initTeams(in);
        fseek(in, 0, 0);
        aux = teams->teamHead;
        while (aux != NULL) {
            fprintf(out, "%s\n", aux->name);
            aux = aux->next;
        }
    }
    //------------------------------------TASK 2-------------------------------------
    if(check[1] == '1'){
        getScore(&teams->teamHead);
        fclose(out);
        out = fopen(/*r.out*/argv[3], "wt");
        if (out == NULL) {
            fprintf(stderr, "\nEroare deschidere fisier rezultate\n");
            exit(1);
        }
        int nrMaxEchipe = 1;
        for(int i = 1; nrEchipe > nrMaxEchipe; i++)     //nr maxim de echipe
        {
            nrMaxEchipe *= 2;
        }
        nrMaxEchipe /=2;
        deleteTeamSurplus(&teams->teamHead, nrEchipe, nrMaxEchipe);
        aux = teams->teamHead;
        while (aux != NULL) {
            fprintf(out, "%s\n", aux->name);
            aux = aux->next;
        }
    }
    //------------------------------------TASK 3-------------------------------------
    if(check[2] == '1'){
        aux = teams->teamHead;
        QUEUE *queue = createQueue();
        STACK *winners = NULL, *losers = NULL;
        while (aux != NULL) {
            enQueue(queue, aux, aux->next);
            aux = aux->next->next;
            //printf("%s-%s | %s-%s\n", queue->rear->firstTeam->name, queue->rear->secondTeam->name, queue->front->firstTeam->name, queue->front->secondTeam->name);
        }
        //creaza stive, modifica echipe
        while(queue->front != NULL){
            TEAM *winnerTeam = NULL, *loserTeam = NULL;
            deQueue(queue, &winnerTeam, &loserTeam);
            push(&winners, winnerTeam);
            push(&losers, loserTeam);
        }
        while(winners != NULL){
            //sterge losers, schimba scoru
            TEAM *auxStack = pop(&winners);
            printf("|%s|\n", auxStack->name);
        }
    }


    //eliberare de memorie
    TEAM* toDelete = teams->teamHead;
    deleteTeam(&toDelete);
    toDelete = NULL;
    free(teams);
    free(check);
    //inchidere fisiere
    fclose(in);
    fclose(out);
    fclose(checker);
    return 0;
}
