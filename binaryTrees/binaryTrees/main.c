//
//  main.c
//  binaryTrees
//
//  Created by Yonatan Glanzman on 05/06/2022.
//
#include "BST.h"
#include "TreePrintLibrary.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    BST* bst = (BST*)calloc(1, sizeof(BST));
    int choise;
    int val;
    int num;
    do {
        puts("Press 1 to init BST ");
        puts("Press 2 to insert a value to BST ");
        puts("Press 3 to Print BST ");
        puts("Press 4 to destroy BST ");
        puts("Press 5 to find the N'th Index From Last ");
        puts("Press 6 to check if all leaves are the same height");
        puts("Press 0 to Exit");
        scanf("%d",&choise);
        
    switch (choise) {
        case 1:
            initBST(bst);
            break;
            
        case 2:
            puts("Enter an integer value");
            scanf("%d",&val);
            insertBST(bst, val);
            break;
            
        case 3:
           // print_ascii_tree(bst->root);
            printTreeInorder(bst);
            break;
            
        case 4:
            destroyBST(bst);
            break;
            
        case 5:
            puts("Enter the N'th Index from last you wish to get\n");
            scanf("%d",&num);
            printf("the N'th Index from last is: %d \n",findIndexNFromLast(bst, num));
            break;
            
        case 6:
            if(sameHeightLeaves(bst)){
                puts("All leaves are the same height\n");
            }
            else{
                puts("Not all leaves are the same height\n");
            }
            break;
        default:
            puts("Input is not valid, please try again\n");
            break;
        }
    }while(choise);
}
