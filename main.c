#include "liste.h"

int main() {
    //deschidere fisiere
    FILE *in, *out;
    in = fopen("/mnt/c/Users/carag/CLionProjects/tema1PA/lan-party-02-checker-main/date/t1/d.in", "rt");
    //folosesc wsl, nu am linux
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
    teams->teamHead = malloc(sizeof(TEAM));
    printf("ajung aici");
    teams->teamHead = initTeams(in);
    fseek(in, 0,0);
    aux = teams->teamHead;
    while(aux != NULL) {
        fprintf(out, "%s\n", aux->name);
        aux = aux->next;
    }
    displayTeam(teams->teamHead);       //afisare
    //eliberari de memorie
    free(teams->teamHead->members->playerHead);
    free(teams->teamHead->members);
    free(teams->teamHead);
    free(teams);
    //inchidere fisiere
    fclose(in);
    fclose(out);
    return 0;
}
