#include "bst.h"
#include "cozi.h"

BST* initTree(BST** root, TEAM* data){
    *root = (BST*)malloc(sizeof(BST));
    (*root)->left = NULL;
    (*root)->right = NULL;
    if(data != NULL)
        (*root)->team = data;
    return *root;
}

BST* newNode(TEAM* data){
   BST* node = (BST*)malloc(sizeof(BST));
   node->team = data;
   node->left = node->right = NULL;
   return node;
}

BST* insert(BST* node, TEAM* data){
    if(node == NULL)        //dupa ce coboara de tot creeaza nod
        return newNode(data);
    if(data->points == node->team->points && strcmp(data->name, node->team->name) < 0)
        node->left = insert(node->left, data);
    else if(data->points == node->team->points && strcmp(data->name, node->team->name) > 0)
        node->right = insert(node->right, data);
    else if(data->points < node->team->points)
        node->left = insert(node->left, data);
    else if(data->points > node->team->points)
        node->right = insert(node->right, data);
    return node;
}

void printDescendingOrder(BST* tree, FILE* out){
    if(tree != NULL){
        printDescendingOrder(tree->right, out);
        fprintf(out, "\n%-32s  -  %.2f", tree->team->name, tree->team->points);
        printDescendingOrder(tree->left, out);
    }
}

void deleteTree(BST* node){
    if (node == NULL) return;
    deleteTree(node->left);
    deleteTree(node->right);
    deleteTeam(&node->team);
}
