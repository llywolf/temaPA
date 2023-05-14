#include "liste.h"

int main(/*int argc, char *argv[]*/) {
    //argc = 4;
    //deschidere fisiere
    FILE *checker, *in, *out;
    checker =fopen("/mnt/c/Users/carag/CLionProjects/tema1PA/date/t1/c.in"/*argv[0]*/, "rt");
    if(checker == NULL){
        fprintf(stderr, "\n Eroare checker\n");
        exit(1);
    }
    in = fopen("/mnt/c/Users/carag/CLionProjects/tema1PA/date/t1/d.in"/*argv[1]*/, "rt");
    if (in == NULL) {
        fprintf(stderr, "\nEroare deschidere fisier date\n");
        exit(1);
    }
    out = fopen("/mnt/c/Users/carag/CLionProjects/tema1PA/r.out"/*argv[2]*/, "wt");
    if (out == NULL) {
        fprintf(stderr, "\nEroare deschidere fisier rezultate\n");
        exit(1);
    }
    //fac datele din checker un vector
    char *check = malloc(5 * sizeof(char));
    for(int i = 0; i < 5; i++) {
        fscanf(checker, "%c ", &check[i]);
        //printf("\n%c ", check[i]);
    }
    //citesc din fisier
    int nrEchipe;
    fscanf(in, "%d ", &nrEchipe);
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
    /*if(check[1] == '1'){

    }*/
    //displayTeam(teams->teamHead);       //afisare
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
