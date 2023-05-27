#ifndef BST_H
#define BST_H

#include "structuri.h"

BST* initTree(BST** root, TEAM* data);
BST* newNode(TEAM* data);
BST* insert(BST* node, TEAM* data);
void printDescendingOrder(BST* tree, FILE* out);
void deleteTree(BST* node);

#endif
