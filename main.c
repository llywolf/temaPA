#include "structuri.h"
#include "liste.h"
#include "stive.h"
#include "cozi.h"
#include "tree.h"

void openFiles(FILE** checker, FILE** out, FILE** in, char* argv[]){
    *checker = fopen(/*c.in*/argv[1], "rt");        //configuration file
    if (checker == NULL) {
        fprintf(stderr, "\n Checker error\n");
        exit(1);
    }
    *in = fopen(/*d.in*/argv[2], "rt");     //input file
    if (in == NULL) {
        fprintf(stderr, "\nInput error\n");
        exit(1);
    }
    *out = fopen(/*r.out*/argv[3], "wt");       //output file
    if (out == NULL) {
        fprintf(stderr, "\nOutput error\n");
        exit(1);
    }
}

void firstTask(TEAMLIST** teams, FILE* in, TEAM* aux, FILE* out){
    (*teams)->teamHead = initTeams(in);     //where the teams will be stored
    fseek(in, 0, 0);
    aux = (*teams)->teamHead;
    while (aux != NULL) {
        fprintf(out, "%s\n", aux->name);
        aux = aux->next;
    }
    getScore(&(*teams)->teamHead);      //calculate the score for each team
}

void secondTask(TEAMLIST** teams, TEAM* aux, FILE** out, int nrEchipe, char* argv[]){
    int nrMaxEchipe = 1;
    for (int i = 2; nrEchipe >= nrMaxEchipe; i++){     //the final team number should be a power of 2(for the tournament)
        nrMaxEchipe *= 2;
    }
    nrMaxEchipe /= 2;
    if(nrMaxEchipe != nrEchipe) {
        deleteTeamSurplus(&(*teams)->teamHead, nrEchipe, nrMaxEchipe);
        fclose(*out);       //actualising the teams participating in the tournament
        *out = fopen(/*r.out*/argv[3], "wt");
        if (*out == NULL) {
            fprintf(stderr, "\nTask 2 output error\n");
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
        STACK *winners = NULL, *losers = NULL;      //stacks for winners and losers
        if(onetime==1) {
            queue = createQueue();      //match queue
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
            //push the winners and losers in their stacks
        }
        deleteLosers(losers, &(*teams)->teamHead);      //delete the losers from the team list
        fprintf(out, "\n\nWINNERS OF ROUND NO:%d", round);
        aux = (*teams)->teamHead;
        queue = reinitQueue(queue);
        updateWinners(winners, finalWinner, teams, queue, out);     //print round winners
        fprintf(out, "\n");
        aux = (*teams)->teamHead;
        nrNouEchipe/=2;
        if(nrNouEchipe == 8)        //build the leaderboard
            buildLeaderBoard(firstEight, teams);
    }
}

BST* fourthTask(TEAMLIST* firstEight, FILE* out){
    TEAM* aux = firstEight->teamHead;
    BST *root = initTree(&root, aux), *rootCopy = root;
    aux = aux->next;
    while(aux != NULL) {
        root = insert(root, aux);
        aux = aux->next;
    }
    fprintf(out, "\nTOP 8 TEAMS:");
    printDescendingOrder(rootCopy, out);        //print the leaderboard
    return root;
}

void fifthTask(BST* root, FILE* out, AVL** rootAvl){
    BST* bstCopy = root;
    copyToAVL(rootAvl, bstCopy);        //copy elements from the BST to the AVL
    fprintf(out, "\n\nTHE LEVEL 2 TEAMS ARE: ");
    printCurrentLevel(*rootAvl, 2, out);
}

void freeMemory(TEAMLIST** teams, char* check, TEAMLIST** firstEight, BST* root, AVL* rootAvl){
    deleteTeams(&(*teams)->teamHead);
    if(check[3] == '0' && check[4] == '0')      //free only the leaderboard if tasks 4 & 5 are disabled
        deleteTeams(&(*firstEight)->teamHead);
    free(*teams);
    if(check[3] == '1' && check[4] == '0') {
        deleteTree(root);
        deleteTeams(&(*firstEight)->teamHead);
    }
    if(check[4] == '1') {
        deleteTree(root);
        deleteAVL(rootAvl);
        deleteTeams(&(*firstEight)->teamHead);
    }
    free(check);
    free(*firstEight);
}

void closeFiles(FILE** checker, FILE** in, FILE** out){
    fclose(*in);
    fclose(*out);
    fclose(*checker);
}


int main(int argc, char *argv[]) {
    //open files
    FILE *checker, *in, *out;
    openFiles(&checker, &out, &in, argv);
    //checker data to char array
    char *check = malloc(5 * sizeof(char));
    for (int i = 0; i < 5; i++)
        fscanf(checker, "%c ", &check[i]);
    int nrEchipe;
    fscanf(in, "%d  ", &nrEchipe);       //first line is teams number
    TEAMLIST *teams = NULL, *firstEight = NULL;
    TEAM *aux = NULL;
    //memory allocation for the teams and leaderboard lists
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
    //------------------------------------TASK 4-------------------------------------
    BST* rootBst = NULL;
    if(check[3] == '1') {
        rootBst = fourthTask(firstEight, out);
    }
    //------------------------------------TASK 5-------------------------------------
    AVL* rootAvl = NULL;
    if(check[4] == '1')
        fifthTask(rootBst, out, &rootAvl);
    freeMemory(&teams, check, &firstEight, rootBst, rootAvl);      //freeing memory
    closeFiles(&checker, &in ,&out);        //closing files
    return 0;
}