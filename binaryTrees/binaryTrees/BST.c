//
#include <stdio.h>
#include <stdlib.h>
#include "BST.h"


#define allocation(ptr) do{\
if(!ptr){\
puts("allocation failed");\
exit(1);\
}\
}while(0)


void initBST(BST* bst){
    bst->root = NULL;
}


void insertBST(BST* bst, int value){
    bst->root = AddNode(bst->root, value);
}


void printTreeInorder(BST* bst){
    if (bst->root == NULL) {
        puts("Sorry Tree is empty\n");
    }
    else{
    printInorder(bst->root);
    }
}

void destroyBST(BST* bst){
    if (bst->root == NULL) {
        puts("Sorry Tree is empty\n");
    }
    else{
        bst->root = PostOrderDelete(bst->root);
    }
}
int findIndexNFromLast(BST* bst, int N){
    return Nth_largest(bst->root, N);
}

int sameHeightLeaves(BST* bst){
    return sameHeight(bst->root);
}




// Private functions!!! //
TreeNode* createLeaf(){
    TreeNode* newNode = (TreeNode*)calloc(1, sizeof(TreeNode));
    allocation(newNode);
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


TreeNode* AddNode(TreeNode* root,int value){
    TreeNode* newNode = createLeaf();
    newNode->element = value;
    if (root == NULL) {
        newNode->element = value;
        return newNode;
    }
    if (newNode->element <= root->element) {
        if (!root->left) {
            root->left = newNode;
        }else AddNode(root->left, value);
    }
    if (newNode->element > root->element) {
        if (!root->right) {
            root->right = newNode;
        }else AddNode(root->right, value);
    }
    return root;
}




void printInorder(TreeNode* root){
    if (!root) {
        return;
    }
    if (root) {
        printInorder(root->left);
        printf("%d\n",root->element);
        printInorder(root->right);
    }
}

TreeNode* PostOrderDelete(TreeNode* root){
    if (!root) {
        return NULL;
    }
//    delets the children first and root last
    PostOrderDelete(root->left);
    PostOrderDelete(root->right);
    root = NULL;
    free(root);
    return root;
}


int height(TreeNode* root){
    if (!root){
        return 0;
    }
    else{
//        calculating height of each subtree
        int lheight = height(root->left);
        int rheight = height(root->right);
 
//        choosing the bigger subtree
        if (lheight > rheight)
            return(lheight+1);
        else return(rheight+1);
    }
}


//        calculating height of the right subtree
int R_height(TreeNode* root){
    if (!root){
        return 0;
    }
    else{
        int rhieght = R_height(root->right);
        return (rhieght + 1);
    }
}


//        calculating height of the left subtree
int L_height(TreeNode* root){
    if (!root){
        return 0;
    }
    else{
        int lhieght = L_height(root->left);
        return (lhieght + 1);
    }
}


// finding the node with the largest element
TreeNode* findMax(TreeNode* root){
    TreeNode* tmp = root;
    while (tmp && tmp->right !=NULL) {
        tmp = tmp->right;
    }
    return tmp;
}


// finding the Nth lergest reverse inorder traversals counting numbers of nodes passed untill the largest
void Nth_largestUtil(TreeNode* root, int Num,int count){
      
    if (!root || count > Num) {
        return;
    }
    
    Nth_largestUtil(root->right, Num, count);
    count++;
    
    if (count == Num) {
        printf("the N'th Index from last is: %d \n",root->element);
    }
}
//returning the Nth lergst element
int Nth_largest(TreeNode* root, int Num){
    if (root == NULL) {
        puts("Sorry Tree is empty\n");
        exit(1);
    }
    if (Num > height(root)) {
        Nth_largest(root->left->right,  Num - height(root));
    }
    int high = (height(root) - Num);
    
    if (!high) {
        return root->element;
    }
    else{
        Nth_largest(root->right, Num);
        Nth_largest(root->left, Num);
    }
    return 0;
}

//cheking if the height of all leaves is equal
int sameHeight(TreeNode* root){
    if (!root) {
        return 0;
    }
    
    //        calculating height of each subtree
    int Rheight  = R_height(root->right);
    int Lheight  = L_height(root->left);
    
    // checkking if height of subtrees is equal
    
    if (Rheight == Lheight) {
        return 1;
    }
    else return 0;
}

