#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Player
{
    char* firstName;
    char* secondName;
    int points;
    struct Player *next;
}PLAYER;

typedef struct PlayerList{
    PLAYER* playerHead;
}PLAYERLIST;

typedef struct Team{
    char* name;
    int points;
    int nrMembers;
    PLAYERLIST* members;
    struct Team* next;
}TEAM;

typedef struct TeamList{
    TEAM* teamHead;
}TEAMLIST;

void addTeamBeginning(TEAM **head, char* teamName, int teamMembers, PLAYER *players);
void addPlayerBeginning(PLAYER **head, char* playerFirstName, char* playerSecondName, int playerPoints);
void displayTeam(TEAM *head);
void displayPlayers(PLAYER *head);
void deleteTeam(TEAM **team);
TEAM* initTeams(FILE* in);