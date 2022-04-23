//
//  Stack.c
//  Home assignment 3 - Queue + Stack
//
//  Created by Yonatan Glanzman on 23/04/2022.
//

#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>
/***************** Stack ADT Implementation *****************/

charNode* addToHead(charNode *head,charNode *toAdd);
void RemoveItem(charNode **head);
int find_length(Stack* s);
int even_len(Stack* s, int len);
int odd_len(Stack* s, int len);
int flip_str(char* str, int dex);
void change_order(Stack* s, int n, int len);
void ShowStack(Stack* s);

void initStack(Stack* s)
{
    s->head = NULL;
}

void destroyStack(Stack* s)
{
    while (isEmptyStack(s)) { // running the loop as long as the satck is not empty
        pop(s); // earasing the head evey iteration
    }
    puts("the stack has been destroyed");
    
}

void push(Stack* s, char data)
{
    charNode* newnode = (charNode*)calloc(1,sizeof(charNode));
    if (!newnode)
    {
        puts("push: memory allocation problem\n");
        return;
    }
    newnode->data = data;
    s->head = addToHead(s->head,newnode);
}

char pop(Stack* s)
{
    char res;
    Stack* t = NULL;
    if (isEmptyStack(s))
    {
        puts("stack is empty");
        return 0;
    }
    res = s->head->data;
    t->head = s->head;
    s->head = s->head->next;
    RemoveItem(&(t->head));
    return res;
}


int isEmptyStack(const Stack* s)
{
    
    if (s->head) {
        return 0;
    }
    return 1;
}

/*************** Functions using stacks - Implementation/definition **************************/

void flipBetweenHashes(const char* sentence)
{
    int dex = 0;
    int i = 0;
    while (sentence[i]) // running the loop while true(!= '\0')
    {
        if (sentence[i] != '#')
        {
            printf("%c", sentence[i++]);
        }
        else
        {
            dex = flip_str((char*)sentence, ++dex) + 1; // calling a function which flips & prints the string
        }
        
    }
    
}

int isPalindrome(Stack* s)
{
    int len = find_length(s);
    if (isEmptyStack(s))
    {
        return 1;
    }
    
    if (len % 2 == 0)
    {
        return even_len(s,len);
    }
    else return odd_len(s,len);
    
}

void rotateStack(Stack* s, int n)
{
    int len = find_length(s);
    if (n < 0 || n > len)
    {
    return;
    }
    
    if (s == NULL)
    {
        return;
    }
    
    change_order(s,n,len);
    
}






//private functions//


//function which puts the Node as the head of the list

charNode* addToHead(charNode *head,charNode *toAdd) {

toAdd->next = head;
head = toAdd;
return head;
}

// function which deletes first item on the list
void RemoveItem(charNode **head)
{
if(*head == NULL)
return;
charNode* ptr = *head;
*head = (*head)->next;
free(ptr);
}

// function which flips the letter in a sentence

int flip_str(char* str, int dex){

    Stack* sentence = NULL; // creating a stack
    initStack(sentence);
    int i = dex;

    while (str[i] != '#')
    {
        push(sentence,str[i]); // inserting the letters of string into the stack
        i++;
    }

    for (int k = dex; k < i; k++)
    {
        printf("%c", pop(sentence)); // printing the reverse string
    }
    
    return i; // returning the index which the string ends;
}


// function which calculates the stack length

int find_length(Stack* s){

    Stack* s1;
    Stack* s2 = NULL;
    s1= s;
    int counter = 0;

    while (!isEmptyStack(s1))
    {
        push(s2,pop(s1));
        counter++;
    }
    return counter;
}

// two functios which checks if a stack is palindrom based on its lenght(even/odd)

int even_len(Stack* s, int len){
    Stack* s1 = NULL;
    initStack(s1);
        
    for (int i = 0; i < len/2 ; i++)
    {
        push(s1,pop(s));
    }
        
    for (int i = 0; i < len/2; i++)
    {
        if (pop(s1) == pop(s))
        {
            return 1;
        }
    }
        return 0;
}

int odd_len(Stack* s, int len){
    Stack* s1 = NULL;
    initStack(s1);
    Stack* s2 = NULL;
    initStack(s2);
    
    for (int i = 0; i < len/2; i++)
    {
        push(s1,pop(s));
    }

    pop(s); // the "extra" letter in the middel of stack

    for (int i = 0; i < len/2; i++)
    {
        if (pop(s1) == pop(s2))
        {
            return 1;
        }
    }
    return 0;
}
//function the changes the order of the first "n" objects of stack
void change_order(Stack* s, int n, int len){
    Stack* s1 = NULL;
    initStack(s1);
    Stack* s2 = NULL;
    initStack(s2);
    int count = len - n;

    for (int i = 0; i < count; i++)
    {
        push(s1,pop(s));
    }

    for (int i = 0; i < n; i++)
    {
        push(s2,pop(s));
    }

    for (int i = 0; i < n; i++)
    {
        push(s2,pop(s1));
    }

    for (int i = 0; i < len; i++)
    {
        push(s,pop(s2));
    }

}

// a function which prints the stack
void ShowStack(Stack * s)
    {
        charNode* tmp = s->head;
        while (tmp)
        {
            printf("%c\n", tmp->data);
            tmp = tmp->next;
        }
    }
