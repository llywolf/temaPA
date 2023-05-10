#include "liste.h"

void addTeamBeginning(TEAM **head, char *teamName, int teamMembers, PLAYER* players) {
    TEAM *newTeam = (TEAM *) malloc(sizeof(TEAM));
    int nameLen = strlen(teamName);
    newTeam->name = malloc((nameLen + 1) * sizeof(char));
    memcpy(newTeam->name, teamName, nameLen);
    newTeam->name[nameLen] = '\0';
    newTeam->nrMembers = teamMembers;
    newTeam->next = *head;
    *head = newTeam;
    newTeam->members = malloc(sizeof(PLAYERLIST));
    newTeam->members->playerHead = malloc(sizeof(PLAYER));
    newTeam->members->playerHead = players;
}

void addPlayerBeginning(PLAYER **head, char *playerFirstName, char *playerSecondName, int playerPoints) {
    PLAYER *newPlayer = malloc(sizeof(PLAYER));
    int lenFname = strlen(playerFirstName), lenSname = strlen(playerSecondName);
    newPlayer->firstName = malloc(sizeof(char) * (lenFname + 1));
    newPlayer->secondName = malloc(sizeof(char) * (lenSname + 1));
    memcpy(newPlayer->firstName, playerFirstName, lenFname);
    memcpy(newPlayer->secondName, playerSecondName, lenSname);
    newPlayer->firstName[lenFname] = '\0';
    newPlayer->secondName[lenSname] = '\0';
    newPlayer->points = playerPoints;
    newPlayer->next = *head;
    *head = newPlayer;
}

void displayTeam(TEAM *head) {
    while (head != NULL) {
        printf("\n%s-%d-%d", head->name, head->points, head->nrMembers);
        printf("\n");
        displayPlayers(head->members->playerHead);
        printf("\n--------------------------------------------");
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
    PLAYER* players = NULL;
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
            char* teamName = malloc((len + 1) * sizeof(char));        // len+1 pt '\0'
            memcpy(teamName, endPtr + 1, len * sizeof(char));
            teamName[len - 1] = '\0';
            int nrMembrii = num;
            for(int i = 0; i < nrMembrii; i++){
                // cazul pt inregistrarea membrilor
                fgets(buffer, sizeof(buffer), in);
                len = strlen(buffer);   //scorul, buffer[len-1] = '\n'
                buffer[len - 1] = '\0';
                num = 0;
                for (int j = 0; buffer[j] != '\0'; j++) {
                    if (buffer[j] <= '9' && buffer[j] >= '0') {
                        num = num * 10 + buffer[j] - '0';
                    }
                }
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
                char tok = ' ';
                addPlayerBeginning(&players, strsep(&name, &tok), strsep(&name, &tok), num);
                free(name);
            }
            addTeamBeginning(&team, teamName, nrMembrii, players);
            free(teamName);
            players = NULL;
        }
    }
    return team;
}