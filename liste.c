#include "liste.h"

void addTeamBeginning(TEAM **head, char *teamName, int teamMembers, PLAYER* players) {
    TEAM *newTeam = (TEAM *) malloc(sizeof(TEAM));
    int nameLen = strlen(teamName);
    newTeam->name = malloc((nameLen + 1) * sizeof(char));
    memmove(newTeam->name, teamName, nameLen);
    newTeam->name[nameLen] = '\0';
    newTeam->nrMembers = teamMembers;
    newTeam->next = *head;
    *head = newTeam;
    newTeam->members = malloc(sizeof(PLAYERLIST));
    newTeam->members->playerHead = players;
}

void addPlayerBeginning(PLAYER **head, char *playerFirstName, char *playerSecondName, int playerPoints) {
    PLAYER *newPlayer = malloc(sizeof(PLAYER));
    int lenFname = strlen(playerFirstName), lenSname = strlen(playerSecondName);
    newPlayer->firstName = malloc(sizeof(char) * (lenFname + 1));
    newPlayer->secondName = malloc(sizeof(char) * (lenSname + 1));
    memmove(newPlayer->firstName, playerFirstName, lenFname);
    memmove(newPlayer->secondName, playerSecondName, lenSname);
    newPlayer->firstName[lenFname] = '\0';
    newPlayer->secondName[lenSname] = '\0';
    newPlayer->points = playerPoints;
    newPlayer->next = *head;
    *head = newPlayer;
}

void displayTeam(TEAM *head) {
    TEAM* headCopy = head;
    while (headCopy != NULL) {
        printf("\n%s-%d-%d", headCopy->name, headCopy->points, headCopy->nrMembers);
        printf("\n");
        displayPlayers(headCopy->members->playerHead);
        printf("\n--------------------------------------------");
        headCopy = headCopy->next;
    }
}

void displayPlayers(PLAYER *head) {
    PLAYER* headCopy = head;
    while (headCopy != NULL) {
        printf("\n%s %s %d", headCopy->firstName, headCopy->secondName, headCopy->points);
        headCopy = headCopy->next;
    }
}

void deleteTeam(TEAM** team){
    if(team == NULL){
        printf("\n eroare memorie echipa");
        exit(1);
    }
    TEAM* copy = *team;
    while(*team != NULL){
        *team = (*team)->next;
        free(copy->name);
        while(copy->members->playerHead != NULL && copy->members != NULL){
            PLAYER *prev = copy->members->playerHead;
            copy->members->playerHead = copy->members->playerHead->next;
            free(prev->firstName);
            free(prev->secondName);
            free(prev);
        }
        free(copy->members);
        free(copy);
        copy = *team;
    }
}

int alocName(char** name, int newLen, int num, char buffer[100]){
    if (num > 9) {      // difera dimensiunea in functie nr de cifre al lui num
        *name = malloc((newLen - 1) * sizeof(char));
        memmove(*name, buffer, sizeof(char) * (newLen - 2));
        (*name)[newLen - 2] = '\0';
        //newLen = strlen(name);
    } else {
        *name = malloc((newLen) * sizeof(char));
        memmove(*name, buffer, sizeof(char) * (newLen - 1));
        (*name)[newLen - 1] = '\0';
        //newLen = strlen(name);
    }
    return strlen(*name);
}

void separateName(int newLen, char *name, char** fName, char** sName){
    int j = 0;
    for(j = 0; j < newLen; j++)
        if(name[j] == ' ')
            break;
    *fName = malloc(sizeof(char) * (j));
    memcpy(*fName, name, sizeof(char) * j);
    (*fName)[j] = '\0';
    *sName = malloc(sizeof(char) * (newLen - j + 1));        // + 1 pt '\0'
    memcpy(*sName, name + j + 1, newLen - j + 1);
    (*sName)[newLen - j + 1] = '\0';
}

void addTeam(TEAM** team, char* teamName, int nrMembri, PLAYER* players){
    if(*team == NULL){
        addTeamBeginning(team, teamName, nrMembri, players);
        (*team)->next = NULL;
    }
    else
        addTeamBeginning(team, teamName, nrMembri, players);
}

void addPlayer(PLAYER **players, char* fName, char*sName, int num){
    if(*players == NULL){
        addPlayerBeginning(players, fName, sName, num);
        (*players)->next = NULL;
    }
    else
        addPlayerBeginning(players, fName, sName, num);
}

void free3strings(char* name, char* fName, char* sName){
    free(name);
    free(fName);
    free(sName);
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
        if (buffer[0] <= '9' && buffer[0] >= '1') {      //pentru inregistrarea echipei
            num = strtol(buffer, &endPtr, 10);
            len = strlen(endPtr);       //endPtr o sa fie numele echipei(din cauza lui strtol)
            buffer[len - 1] = '\0';
            char* teamName = malloc((len + 1) * sizeof(char));        // len+1 pt '\0'
            memmove(teamName, endPtr + 1, len * sizeof(char));
            teamName[len - 1] = '\0';
            int nrMembrii = num;
            for(int i = 0; i < nrMembrii; i++){     //pentru membrii
                fgets(buffer, sizeof(buffer), in);
                len = strlen(buffer);   //buffer[len-1] = '\n'
                buffer[len - 1] = '\0';
                num = 0;        //scorul
                for (int j = 0; buffer[j] != '\0'; j++) {
                    if (buffer[j] <= '9' && buffer[j] >= '0') {
                        num = num * 10 + buffer[j] - '0';
                    }
                }
                int newLen = len - 3; // pt nume
                newLen = alocName(&name, newLen, num, buffer);
                char *fName = NULL, *sName = NULL;
                separateName(newLen, name, &fName, &sName);
                addPlayer(&players, fName, sName, num);
                free3strings(name, fName, sName);       // pt functia cu 40 de linii de cod
            }
            addTeam(&team, teamName, nrMembrii, players);
            free(teamName);
            players = NULL;
        }
    }
    return team;
}

void getScore(TEAM** team){
    if(team == NULL){
        printf("eroare memorie echipa(calculeazaScor)");
        exit(1);
    }
    TEAM* copy = *team;
    while(copy != NULL){
        int scor = 0, sum = 0;
        PLAYER* playerCopy = copy->members->playerHead;
        while(playerCopy != NULL){
            sum += playerCopy->points;
            playerCopy = playerCopy->next;
        }
        scor = sum/copy->nrMembers;
        copy->points = scor;
        copy = copy->next;
    }
}

void deletePlayers(TEAM** team){
    TEAM* copy = *team;
    while(copy->members->playerHead != NULL && copy->members != NULL){
        PLAYER *prevPlayer = copy->members->playerHead;
        copy->members->playerHead = copy->members->playerHead->next;
        free(prevPlayer->firstName);
        free(prevPlayer->secondName);
        free(prevPlayer);
    }
    free(copy->members);
}

void deleteTeamSurplus(TEAM** team, int nrEchipe, int nrMaxEchipe){
    if(team == NULL){
        printf("\n eroare memorie echipa");
        exit(1);
    }
    TEAM* copy = *team, *prev = copy;
    while(nrEchipe > nrMaxEchipe){
        int min = copy->points;     //calculez scorul minimul
        printf("\n");
        while (copy != NULL) {
            if (min > copy->points) {
                min = copy->points;
            }
            copy = copy->next;
        }
        copy = *team;
        if (copy != NULL && min == copy->points) {        //cazul pt scor minim la capul listei
            *team = (*team)->next;
            free(copy->name);
            deletePlayers(&copy);
            free(copy);
            copy = *team;
            nrEchipe--;
        }
        while (copy != NULL && min != copy->points) {     //cand gasesc echipe cu scor minim le sterg din lista
            prev = copy;
            copy = copy->next;
        }
        if (copy == NULL) {
            printf("\nMinimul nu a fost gasit");
            return;
        }
        prev->next = copy->next;
        free(copy->name);
        deletePlayers(&copy);
        nrEchipe--;
        free(copy);
        copy = *team;
    }
}
