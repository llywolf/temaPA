#include "liste.h"

int main() {
    //deschidere fisiere
    FILE *in, *out;
    in = fopen("/mnt/c/Users/carag/CLionProjects/tema1PA/lan-party-02-checker-main/date/t1/d.in", "rt");
    if (in == NULL) {
        fprintf(stderr, "\nEroare deschidere fisier date");
        exit(1);
    }
    out = fopen("/mnt/c/Users/carag/CLionProjects/tema1PA/r.out", "wt");
    if (out == NULL) {
        fprintf(stderr, "\nEroare deschidere fisier rezultate");
        exit(1);
    }
    //citesc din fisier
    int nrEchipe;
    fscanf(in, "%d ", &nrEchipe);
    TEAMLIST *teams = NULL;
    TEAM* aux = NULL;
    //alocari de memorie
    teams = malloc(sizeof(TEAMLIST));
    printf("ajung aici");
    //------------------------------------TASK 1-------------------------------------
    teams->teamHead = initTeams(in);
    fseek(in, 0,0);
    aux = teams->teamHead;
    while(aux != NULL) {
        fprintf(out, "%s\n", aux->name);
        aux = aux->next;
    }
    displayTeam(teams->teamHead);       //afisare
    //eliberare de memorie
    TEAM* toDelete = teams->teamHead;
    deleteTeam(&toDelete);
    toDelete = NULL;
    free(teams);
    //inchidere fisiere
    fclose(in);
    fclose(out);
    return 0;
}
