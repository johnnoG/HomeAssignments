//
//  main.c
//  Home assignment 3 - Queue + Stack
//
//  Created by Yonatan Glanzman on 23/04/2022.
//
#include <stdio.h>
#include "Stack.h"
#include "Queue.h"
#include <stdlib.h>
#include <string.h>
void printstack(Stack* s);
void ShowQueue(Queue* q);

void main(){
    char option;
    puts("Press 'S' to use Stack or 'Q' to use Queue");
    scanf("%c",&option);
    int S_ch;
    int Q_ch;
    int x,n;
    while (option) {
    char data;
        if (option == 'S' || option == 's') {
            Stack stack;
            do{
                puts("Press 1 to initiate Stack");
                puts("Press 2 to destroy Stack");
                puts("Press 3 to push to stack");
                puts("Press 4 to pop from stack");
                puts("Press 5 to check if stack is empty");
                puts("Press 6 to flip Between Hashes");
                puts("Press 7 to check if stack is Palindrome");
                puts("Press 8 to rotate stack");
                puts("Press 9 to print stack");
                puts("Press 0 to Exit");
                scanf("%d",&S_ch);
                switch (S_ch) {
                    case 1:
                        initStack(&stack);
                        break;
                    case 2:
                        destroyStack(&stack);
                        break;
                    case 3:
                        puts("enter the char you want to push to stack:\n");
                        scanf("%c",&data);
                        push(&stack, data);
                        break;
                    case 4:
                        pop(&stack);
                        break;
                    case 5:
                        if(isEmptyStack(&stack)){
                            puts("stack is empty");
                        }
                        else{
                            puts("stack is not empty");
                        }
                        break;
                    case 6:
                        puts("Please enter a sentence to fleep the hashes");
                        char str[100];
                        gets(str);
                        int senLen = (int)strlen(str);
                        char* sentence = (char*)malloc(sizeof(char)*senLen);
                        strcpy(sentence, str);
                        flipBetweenHashes(sentence);
                        break;
                    case 7:
                        x = isPalindrome(&stack);
                        if (x) {
                            puts("stack is palindrom");
                        }
                        else{
                            puts("stack is not palindrom");
                        }
                        break;
                    case 8:
                        puts("please enter an integer");
                        scanf("%d",&n);
                        rotateStack(&stack, n);
                    case 9:
                        printstack(&stack);
                        break;
                    default:
                        puts("no option has been chosen");
                        break;
                }
            }while(S_ch);
        }
        
        if (option == 'Q' || option == 'q') {
            Queue* queue = NULL;
            do{
                puts("Press 1 to initiate queue");
                puts("Press 2 to destroy queue");
                puts("Press 3 to enqueue");
                puts("Press 4 to dequeue");
                puts("Press 5 to check if queue is empty");
                puts("Press 6 to rotate queue");
                puts("Press 7 to cut and replece poistions in queue");
                puts("Press 8 sort order of queue from small to big");
                puts("Press 9 to print queue");
                puts("Press 0 to Exit");
                scanf("%d",&Q_ch);
            }while(Q_ch);
            
            switch (Q_ch) {
                case 1:
                    initQueue(queue);
                    break;
                case 2:
                    destroyQueue(queue);
                    break;
                case 3:
                    printf("enter an integer you want to add to queue");
                    unsigned int data;
                    scanf("%d",&data);
                    enqueue(queue, data);
                    break;
                case 4:
                    dequeue(queue);
                    break;
                case 5:
                    if (isEmptyQueue(queue)) {
                        puts("queue is empty");
                    }
                    break;
                case 6:
                    rotateQueue(queue);
                    break;
                case 7:
                    cutAndReplace(queue);
                    break;
                case 8:
                    sortKidsFirst(queue);
                    break;
                case 9:
                    ShowQueue(queue);
                    break;
                default:
                    puts("no option has been chosen");
                    break;
            }
        }
    }
}


// a function which prints the stack
void printstack(Stack* s){
    if (!s->head) {
        puts("stack is empty, can't print an empty stack");
        return;
    }
    charNode*tmp = s->head;
    if (!tmp) {
        puts("stack is empty");
    }
    while (tmp) {
        printf("%c\n",tmp->data);
        tmp = tmp->next;
    }
}



void ShowQueue(Queue* q){
    intNode* tmp = q->head;
    while (tmp){
        printf("%d\n", tmp->data);
        tmp = tmp->next;
    }
}
