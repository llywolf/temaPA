#ifndef TREE_H
#define TREE_H

#include "structuri.h"

BST* initTree(BST** root, TEAM* data);
BST* newNode(TEAM* data);
BST* insert(BST* node, TEAM* data);
void printDescendingOrder(BST* tree, FILE* out);
void deleteTree(BST* node);
int nodeHeight(AVL* root);
int max(int a, int b);
AVL* rRotation(AVL* z);
AVL* lRotation(AVL* z);
AVL* insertForAVL(AVL* node, TEAM* data);
void printCurrentLevel(AVL* root, int level, FILE* out);
void copyToAVL(AVL** rootAvl, BST* rootBst);
void deleteAVL(AVL* node);


#endif
