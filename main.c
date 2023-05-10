#include "liste.h"

int main() {
    //deschid fisierul
    FILE *in;
    in = fopen("/mnt/c/Users/carag/CLionProjects/tema1PA/lan-party-02-checker-main/date/t1/d.in", "rt");
    //folosesc wsl, nu am linux
    if (in == NULL) {
        fprintf(stderr, "\nEroare deschidere fisier");
        exit(1);
    }
    //citesc din fisier
    int nrEchipe;
    fscanf(in, "%d ", &nrEchipe);
    TEAMLIST *teams = NULL;
    teams = malloc(sizeof(TEAMLIST));
    teams->teamHead = malloc(sizeof(TEAM));
    teams->teamHead = initTeams(in);
    displayTeam(teams->teamHead);
    free(teams->teamHead->members->playerHead);
    free(teams->teamHead->members);
    free(teams->teamHead);
    free(teams);
    return 0;
}
