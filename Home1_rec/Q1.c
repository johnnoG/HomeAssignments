//
//  main.c
//  Home1_rec
//
//  Created by Yonatan Glanzman on 03/03/2022.
//

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
    static int counter = 0;
    if (!num) {
        return 0;
    }
  int x = num%10;
    if (x % dig == 0) {
        counter++;
    }
    divider(num/10, dig);
    return counter;
}
