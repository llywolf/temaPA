#ifndef STRUCTURI_H
#define STRUCTURI_H

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
    float points;
    int nrMembers;
    PLAYERLIST* members;
    struct Team* next;
}TEAM;

typedef struct TeamList{
    TEAM* teamHead;
}TEAMLIST;

typedef struct Match{
    TEAM* firstTeam;
    TEAM* secondTeam;
    struct Match* next;
}MATCH;

typedef struct Q{
    MATCH *rear, *front;
}QUEUE;

typedef struct Stack{
    TEAM* team;
    struct Stack* next;
}STACK;

typedef struct Bst{
    TEAM* team;
    struct Bst *left, *right;
}BST;

#endif
