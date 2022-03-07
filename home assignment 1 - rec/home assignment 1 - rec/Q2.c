////
////  Q2.c
////  home assignment 1 - rec
////
////  Created by Yonatan Glanzman on 07/03/2022.
////
//
//#include "Q2.h"
//#include <stdio.h>
//#define N 2
//int recurse(int mat[][N],int rows,int cols, int row, int col);
//int path_exists(int mat[][N],int rows,int cols);
//
//void main(){
//    int mat[N][N];
//    printf("enter %d 1's or 0's to the matrix\n",N*N);
//    
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            printf("enter value for row,col (%d,%d): ",i,j);
//            scanf("%d",&mat[i][j]);
//            printf("\n");
//        }
//    }
//    if (path_exists(mat, N, N) == 1){
//        printf("good\n");
//    }
//    else printf("not good\n");
//}
//
//int path_exists(int mat[][N],int rows,int cols){
//    return recurse( mat, rows, cols,  0, 0);
//}
//
//int recurse(int mat[][N],int rows,int cols, int row, int col){
//    if(row >= rows || col >= cols){
//        return 0;
//    }
//
//    if(mat[row][col]!=1){
//        return 0;
//    }
//    
//    if (row == rows - 1 && col == cols -1){
//        return 1;
//    }
//    
//    return
//        recurse(mat, rows, cols,  row, col+1) ||
//        recurse(mat, rows, cols,  row+1, col+1) ||
//        recurse(mat, rows, cols,  row+1, col);
//}
