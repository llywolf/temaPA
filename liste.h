#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int Data;

typedef struct Player
{
    char* firstName;
    char* secondName;
    int points;
    struct Player *next;
}PLAYER;

typedef struct Team{
    char* name;
    int points;
    int nrMembers;
    PLAYER* members;
    struct Team* next;
}TEAM;

typedef struct TeamList{
    TEAM* teamHead;
}TEAMLIST;

void addTeamBeginning(TEAM **head, char* teamName, int teamPoints, int teamMembers);
void addPlayerBeginning(PLAYER **head, char* playerFirstName, char* playerSecondName, int playerPoints);
void displayTeam(TEAM *head);
void displayPlayers(PLAYER *head);
TEAM* initTeams(FILE* in);