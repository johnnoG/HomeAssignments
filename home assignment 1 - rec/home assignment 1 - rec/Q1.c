//
//  Q1.c
//  home assignment 1 - rec
//
//  Created by Yonatan Glanzman on 07/03/2022.
//

#include "Q1.h"
#include <stdio.h>
int divider(int num, int dig);
void main(){
    int num;
    int dig;
    printf("Please enter a number and a digit:\n");
    scanf("%d %d",&num,&dig);
    printf("number of digits divided by %d is: %d\n",dig,divider(num, dig));
}

int divider(int num, int dig){
    if (!num) {
        return 0;
    }
    int x = num%10;
    int y = divider(num/10, dig);

    if (x % dig == 0) {
        return 1 + y;
    }

    return y;
}
