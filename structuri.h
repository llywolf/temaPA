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

typedef struct Match{       //teams in the match are pointers to the teamlist, not duplicated data
    TEAM* firstTeam;
    TEAM* secondTeam;
    struct Match* next;
}MATCH;

typedef struct Q{
    MATCH *rear, *front;
}QUEUE;

typedef struct Stack{       //teams in the stacks are also pointers and not duplicated
    TEAM* team;
    struct Stack* next;
}STACK;

typedef struct Bst{     //the BST teams are pointers to the leaderboard teams list
    TEAM* team;
    struct Bst *left, *right;
}BST;

typedef struct Avl{     //the AVL duplicates the teams from the BST
    int height;
    TEAM* team;
    struct Avl *left, *right;
}AVL;

#endif
