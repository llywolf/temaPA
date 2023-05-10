#include "liste.h"

void addTeamBeginning(TEAM **head, char *teamName, int teamPoints, int teamMembers) {
    TEAM *newTeam = (TEAM *) malloc(sizeof(TEAM));
    strcpy(newTeam->name, teamName);
    newTeam->nrMembers = teamMembers;
    newTeam->points = teamPoints;
    newTeam->next = *head;
    *head = newTeam;
}

void addPlayerBeginning(PLAYER **head, char *playerFirstName, char *playerSecondName, int playerPoints) {
    PLAYER *newPlayer = malloc(sizeof(PLAYER));
    strcpy(newPlayer->firstName, playerFirstName);
    strcpy(newPlayer->secondName, playerSecondName);
    newPlayer->points = playerPoints;
    newPlayer->next = *head;
    *head = newPlayer;
}

void displayTeam(TEAM *head) {
    while (head != NULL) {
        printf("\n%s-%d-%d", head->name, head->points, head->nrMembers);
        displayPlayers(head->members);
        head = head->next;
    }
}

void displayPlayers(PLAYER *head) {
    while (head != NULL) {
        printf("\n%s %s %d", head->firstName, head->secondName, head->points);
        head = head->next;
    }
}

TEAM *initTeams(FILE *in) {
    TEAM* team = NULL;
    char buffer[100], *endPtr = NULL, *name = NULL;
    int len, num;       //initial num e nr membrii echipa
    while (!feof(in)) {
        fgets(buffer, sizeof(buffer), in);
        if (strcmp(buffer, "\r\n") == 0)
            continue;
        if (buffer[0] <= '9' && buffer[0] >= '1') {      //cazul pentru inregistrarea echipei
            num = strtol(buffer, &endPtr, 10);
            len = strlen(endPtr);       //endPtr o sa fie numele echipei(din cauza lui strtol)
            buffer[len - 1] = '\0';
            name = malloc((len + 1) * sizeof(char));        // len+1 pt '\0'
            memcpy(name, endPtr + 1, len * sizeof(char));
            name[len - 1] = '\0';

            printf("\n%s", name);
            free(name);
        } else {        // cazul pt inregistrarea membrilor
            len = strlen(buffer);   //scorul, buffer[len-1] = '\n'
            buffer[len - 1] = '\0';
            num = 0;
            for (int i = 0; buffer[i] != '\0'; i++)
                if (buffer[i] <= '9' && buffer[i] >= '0')
                    num = num * 10 + buffer[i] - '0';
            int newLen = len - 3; // pt nume
            if (num > 9) {      // difera dimensiunea in functie nr de cifre al lui num
                name = malloc((len - 1) * sizeof(char));
                memcpy(name, buffer, sizeof(char) * (newLen + 1));
                name[newLen - 2] = '\0';
            } else {
                name = malloc(len * sizeof(char));
                memcpy(name, buffer, sizeof(char) * (newLen + 2));
                name[newLen - 1] = '\0';
            }
            printf("\n\t|%d|%s|", num, name);
            free(name);
        }
    }
    return team;
}