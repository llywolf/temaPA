#include "structuri.h"
#include "liste.h"
#include "stive.h"
#include "cozi.h"

int main(int argc, char *argv[]) {
    //deschidere fisiere
    FILE *checker, *in, *out;
    checker = fopen(/*c.in*/argv[1], "rt");
    if (checker == NULL) {
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
    for (int i = 0; i < 5; i++) {
        fscanf(checker, "%c ", &check[i]);

    }
    int nrEchipe;
    fscanf(in, "%d ", &nrEchipe);       //numarul de echipe se afla pe primul rand
    TEAMLIST *teams = NULL;
    TEAM *aux = NULL;
    //alocari de memorie
    teams = malloc(sizeof(TEAMLIST));
    //------------------------------------TASK 1-------------------------------------
    if (check[0] == '1') {
        teams->teamHead = initTeams(in);
        fseek(in, 0, 0);
        aux = teams->teamHead;
        while (aux != NULL) {
            fprintf(out, "%s\n", aux->name);
            aux = aux->next;
        }
        //displayTeam(teams->teamHead);
    }
    //------------------------------------TASK 2-------------------------------------
    if (check[1] == '1') {
        getScore(&teams->teamHead);
        int nrMaxEchipe = 1;
        for (int i = 2; nrEchipe > nrMaxEchipe; i++)     //nr maxim de echipe
        {
            nrMaxEchipe *= 2;
        }
        nrMaxEchipe /= 2;
        if(nrMaxEchipe != nrEchipe) {
            deleteTeamSurplus(&teams->teamHead, nrEchipe, nrMaxEchipe);
            fclose(out);
            out = fopen(/*r.out*/argv[3], "wt");
            if (out == NULL) {
                fprintf(stderr, "\nEroare deschidere fisier rezultate\n");
                exit(1);
            }
            aux = teams->teamHead;
            while (aux != NULL) {
                fprintf(out, "%s\n", aux->name);
                aux = aux->next;
            }
        }
    }
    //------------------------------------TASK 3-------------------------------------
    if (check[2] == '1') {
        aux = teams->teamHead;
        int nrNouEchipe = calcNrEchipe(aux);
        TEAM* finalWinner = NULL;
        int round = 0;
        int onetime = 1;
        QUEUE *queue = NULL;
        while (nrNouEchipe % 2 == 0) {
            round++;
            fprintf(out, "\n--- ROUND NO:%d", round);
            aux = teams->teamHead;

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
            aux = teams->teamHead;
            while (queue->front != NULL) {
                fprintf(out, "\n%-32s - %+32s", queue->front->firstTeam->name, queue->front->secondTeam->name);
                TEAM *winnerTeam = NULL, *loserTeam = NULL;
                deQueue(queue, &winnerTeam, &loserTeam);
                push(&winners, winnerTeam);
                push(&losers, loserTeam);
            }
            //creaza stive, modifica echipe
            //sterge losers, schimba scoru
            while (losers != NULL) {
                TEAM *auxStack = pop(&losers);
                aux = teams->teamHead;
                if (auxStack == aux) {
                    teams->teamHead = teams->teamHead->next;
                    aux = teams->teamHead;
                    deleteTeam(&auxStack);
                }
                else if (auxStack != NULL) {
                    aux = teams->teamHead;
                    if (aux != NULL) {
                        while (aux->next != auxStack) {
                            aux = aux->next;
                        }
                    }
                    aux->next = auxStack->next;
                    deleteTeam(&auxStack);
                }
            }

            fprintf(out, "\n\nWINNERS OF ROUND NO:%d", round);
            aux = teams->teamHead;
            if (queue != NULL) {
                deleteQueue(queue);
            }
            queue = createQueue();
            //enQueue le baga inversat ca e stiva
            while (winners != NULL) {
                TEAM *winner = pop(&winners);
                if(winners == NULL) {
                    finalWinner = winner;
                    scoreUpdate(&finalWinner);
                    getScore(&finalWinner);
                    teams->teamHead = finalWinner;
                    //deleteQueue(queue);
                    fprintf(out, "\n%-32s  -  %.2f",finalWinner->name, finalWinner->points);
                    break;
                }
                TEAM *nextWinner = pop(&winners);
                scoreUpdate(&winner);
                scoreUpdate(&nextWinner);
                getScore(&winner);
                getScore(&nextWinner);
                fprintf(out, "\n%-32s  -  %.2f\n%-32s  -  %.2f", winner->name, winner->points, nextWinner->name, nextWinner->points);
                enQueue(queue, &winner, &nextWinner);

            }
            fprintf(out, "\n");
            aux = teams->teamHead;
            nrNouEchipe/=2;
        }
    }


//eliberare de memorie
    TEAM *toDelete = teams->teamHead;
    //deleteTeams(&toDelete);
    toDelete = NULL;
    //free(teams);
    free(check);
//inchidere fisiere
    fclose(in);
    fclose(out);
    fclose(checker);
    return 0;
}