#ifndef _BST_ADT_H
#define _BST_ADT_H

typedef struct TreeNode TreeNode;

struct TreeNode
{
    TreeNode* left;
    TreeNode* right;
    int element;
};

typedef struct BST
{
    TreeNode* root;
}BST;

#endif // !_BST_ADT_H

void initBST(BST* bst);
TreeNode* createLeaf(void);
void insertBST(BST* bst, int value);
TreeNode* AddNode(TreeNode* root,int value);
void printTreeInorder(BST* bst);
void printInorder(TreeNode* root);
void destroyBST(BST* bst);
TreeNode* PostOrderDelete(TreeNode* root);
int findIndexNFromLast(BST* bst, int N);
int height(TreeNode* root);
TreeNode* findMax(TreeNode* root);
int R_height(TreeNode* root);
void Nth_largestUtil(TreeNode* root, int Num,int count);
int Nth_largest(TreeNode* root, int Num);
int sameHeightLeaves(BST* bst);
int sameHeight(TreeNode* root);
int L_height(TreeNode* root);
