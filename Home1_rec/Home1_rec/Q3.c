////
////  Q3.c
////  Home1_rec
////
////  Created by Yonatan Glanzman on 05/03/2022.
////
//
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//int strcomp(char* str1, char* str2);
//
//void main(){
//    char str1[30];
//    char str2[30];
//    printf("please  enter TWO strings:\n");
//    gets(str1);
//    gets(str2);
//
//    int x = strcomp(str1, str2);
//
//    if (x > 0) {
//        printf("first string's bigger\n");
//    }
//    if (x < 0) {
//        printf("second string's bigger\n");
//    }
//    if (x == 0) {
//        printf("strings are equal\n");
//    }
//}
//
//int strcomp(char* str1, char* str2){
//
//
//    if (!*str1 || !*str2) {
//        return 0;
//       }
//    if (*str1 > *str2) {
//       return 1;
//    }
//    if (*str1 < *str2) {
//        return -1;
//    }
//    else return strcomp(str1 + 1, str2 + 1);
//}
//
