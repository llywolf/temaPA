#ifndef LISTE_H
#define LISTE_H

#include "structuri.h"

void addTeamBeginning(TEAM **head, char* teamName, int teamMembers, PLAYER *players);
void addPlayerBeginning(PLAYER **head, char* playerFirstName, char* playerSecondName, int playerPoints);
void displayTeam(TEAM *head);
void displayPlayers(PLAYER *head);
void deleteTeams(TEAM **team);
TEAM* initTeams(FILE* in);
int alocName(char** name, int newLen, int num, char buffer[100]);
void separateName(int newLen, char *name, char** fName, char** sName);
void addTeam(TEAM** team, char* teamName, int nrMembri, PLAYER* players);
void free3strings(char* name, char* fName, char* sName);
void getScore(TEAM** team);
void deletePlayers(TEAM** team);
void deleteTeamSurplus(TEAM** team, int nrEchipe, int nrMaxEchipe);
int calcNrEchipe(TEAM* head);
void scoreUpdate(TEAM** head);
PLAYER* copyPlayers(PLAYER* head);
TEAM* recordFirstEight(TEAMLIST** head);
void updateFirstEight(TEAMLIST** leaderBoardHead, TEAMLIST** head);
char *strdup(const char *c);
void buildLeaderBoard(int nrNouEchipe, TEAMLIST** firstEight, TEAMLIST** teams);


#endif