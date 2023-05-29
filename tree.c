#include "tree.h"
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
    if(node == NULL)
        return newNode(data);
    if((data->points == node->team->points && strcmp(data->name, node->team->name) < 0) || (data->points < node->team->points))
        node->left = insert(node->left, data);
    else if((data->points == node->team->points && strcmp(data->name, node->team->name) > 0) || (data->points > node->team->points))
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
    free(node);
}

void deleteAVL(AVL* node){
    if (node == NULL) return;
    deleteAVL(node->right);
    deleteAVL(node->left);

    free(node);
}

int nodeHeight(AVL* root){
    if(root == NULL)
        return -1;
    else
        return root->height;
}

int max(int a, int b){
    return ((a>b)?a:b);
}

AVL* rRotation(AVL* z){
    AVL* y = z->left;
    AVL* T3 = y->right;
    y->right = z;
    z->left = T3;
    z->height = max(nodeHeight(z->left), nodeHeight(z->right)) + 1;
    y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    return y;
}

AVL* lRotation(AVL* z){
    AVL* y = z->right;
    AVL* T2 = y->left;
    y->left = z;
    z->right = T2;
    z->height = max(nodeHeight(z->left), nodeHeight(z->right)) + 1;
    y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    return y;
}

AVL* insertForAVL(AVL* node, TEAM* data){
    if(node == NULL){
        node = (AVL*)malloc(sizeof(AVL));
        node->team = data;
        node->height = 0;
        node->left = node->right = NULL;
        return node;
    }
    if((data->points == node->team->points && strcmp(data->name, node->team->name) < 0) || (data->points < node->team->points))
        node->left = insertForAVL(node->left, data);
    else if((data->points == node->team->points && strcmp(data->name, node->team->name) > 0) || (data->points > node->team->points))
        node->right = insertForAVL(node->right, data);
    else return node;

    node->height = 1 + max(nodeHeight(node->left), nodeHeight(node->right));

    int k = (nodeHeight(node->left) - nodeHeight(node->right));

    if (k > 1 && (data->points < node->left->team->points || (data->points == node->left->team->points && strcmp(data->name, node->left->team->name) < 0)))
        return rRotation(node);
    if (k < -1 && (data->points > node->right->team->points || (data->points == node->right->team->points && strcmp(data->name, node->right->team->name) > 0)))
        return lRotation(node);
    if (k > 1 && (data->points > node->left->team->points || (data->points == node->left->team->points && strcmp(data->name, node->left->team->name) > 0))) {
        node->right = rRotation(node->right);
        return lRotation(node);
    }
    if (k < -1 && (data->points < node->right->team->points || (data->points == node->right->team->points && strcmp(data->name, node->right->team->name) < 0))) {
        node->left = lRotation(node->left);
        return rRotation(node);
    }

    return node;
}

void printCurrentLevel(AVL* root, int level, FILE* out){
    if (root == NULL)
        return;
    if (level == 0)
        fprintf(out, "\n%s", root->team->name);
    else if (level > 0) {
        printCurrentLevel(root->right, level - 1, out);
        printCurrentLevel(root->left, level - 1, out);
    }
}

void copyToAVL(AVL** rootAvl, BST* rootBst){
    if(rootBst != NULL){
        copyToAVL(rootAvl, rootBst->right);
        *rootAvl = insertForAVL(*rootAvl, rootBst->team);
        copyToAVL(rootAvl, rootBst->left);
    }
}
