//
//  Queue.c
//  Home assignment 3 - Queue + Stack
//
//  Created by Yonatan Glanzman on 23/04/2022.
//

#include "Queue.h"
#include "stdio.h"
#include <stdlib.h>

/***************** Queue ADT Implementation *****************/
int FindLen(Queue* q);
int findAverage(Queue* q, int len);
void flipQueue(Queue* q);
int findMin(Queue* q);
void ShowQueue(Queue* q);
void fillQueue(Queue* q, Queue* q1);

void initQueue(Queue* q)
{
    q->head = q->tail = NULL;
}

void destroyQueue(Queue* q)
{
    Queue* tmp = NULL;
    initQueue(tmp);
     tmp->head = q->head;     // creating a pointer to help navigate the realese
    while (tmp->head)
    {
        dequeue(tmp);
        tmp->head = tmp->head->next;
    }
    puts("the queue have been destroyed succesfully");
}

void enqueue(Queue* q, unsigned int data)
{
    intNode* newNode = (intNode*)calloc(1,sizeof(intNode));
    if(!newNode){
        puts("alloctain faild, can not add to queue");
        exit(1);
    }
    newNode->data = data;
    
    
    if(!q->head){      // empty queue case
        q->head = q->tail = newNode;
    }
    else{
        q->tail->next = newNode;     // adding a new object to the end of the queue
        q->tail = newNode;
    }

}

unsigned int dequeue(Queue* q)
{
    unsigned int data;
    
    if (isEmptyQueue(q))     // empty queue case
    {
        puts("queue is empty");
        return 1;
    }

    if (q->head == q->tail)     // one object queue case
    {
        data = q->head->data;
        free(q->head);
        initQueue(q);
    }
    else{
        intNode* tmp = q->head;        // creating a pointer to help navigate the realese
        q->head = q->head->next;
        data = tmp->data;
        free(tmp);
    }
return data;     // returning the data of earased object
    
    
}

int isEmptyQueue(const Queue* q)
{
    if (q->head) {
        return 0;
    }
    return 1;
}

/***************** Functions using Queues - Implementation/definition **************************/

void rotateQueue(Queue* q)
{
    if (isEmptyQueue(q))    // empty queue case
    {
        puts("the queue is empty");
        return;
    }
    
    Queue* tmp = NULL;
    initQueue(tmp);

    while (q->head != q->tail)
    {
        enqueue(tmp, dequeue(q));
    }

    while (!isEmptyQueue(tmp))
    {
        enqueue(q, dequeue(tmp));
    }
    
}

void cutAndReplace(Queue* q)
{
    if (isEmptyQueue(q))    // empty queue case
    {
        puts("can not complete task, queue is empty");
        return;
    }

    Queue* tmp = NULL;
    initQueue(tmp);
    int len = FindLen(q);
    int half = (len + 1)/2;

    if (len % 2)     //odd queue lenght case
    {
        int avarage = findAverage(q,len);
        enqueue(q,avarage);
    }
    

    for (int i = 0; i < half; i++)
    {
        enqueue(tmp,dequeue(q));
    }
    
    flipQueue(q);
    for (int i = 0; i < half; i++)
    {
        enqueue(q,dequeue(tmp));
    }
}

void sortKidsFirst(Queue* q)
{
    int min;
    int len  = FindLen(q);
    Queue* tmp = NULL;
    Queue* org = NULL;
    initQueue(tmp);
    initQueue(org);

    for (int i = 0; i < len; i++)
    {
         min = findMin(q);

        while (!isEmptyQueue(q))
        {
            if(q->head->data == min)
            {
                enqueue(org,dequeue(q));
            }
            else{
                enqueue(tmp,dequeue(q));
            }
        }
        fillQueue(q,tmp);
    }
    fillQueue(q,org);
}





//private functions//

int FindLen(Queue* q){
    int counter = 0;
    Queue* tmp = NULL;
    initQueue(tmp);

    while (!isEmptyQueue(q))
    {
        enqueue(tmp,dequeue(q));
        counter++;
    }
    fillQueue(q,tmp);
    return counter;
}

int findAverage(Queue* q, int len){
intNode* tmp;
    tmp = q->head;
int sum=0;
int avarage;
while (tmp)
{
    sum += tmp->data;
    tmp = tmp->next;
}
avarage = sum/len;
return avarage;
}

void flipQueue(Queue* q){
    Queue* tmp1 = NULL;
    Queue* tmp2 = NULL;
    initQueue(tmp1);
    initQueue(tmp2);

    while (!isEmptyQueue(q))
    {
        while (!isEmptyQueue(tmp1))
        {
            enqueue(tmp2,dequeue(tmp1));
        }

        enqueue(tmp1,dequeue(q));

        while (!isEmptyQueue(tmp2))
        {
            enqueue(tmp1,dequeue(tmp2));
        }
        
    }
    
    fillQueue(q,tmp1);
}

int findMin(Queue* q){
    int min = q->head->data;
    Queue* tmp = NULL;
    initQueue(tmp);
    while (!isEmptyQueue(q))
    {
        if (q->head->data < min)
        {
            min = q->head->data;
        }
        enqueue(tmp, dequeue(q));
    }

    fillQueue(q,tmp);
    return min;
}
 // function which fills a queue whith the content of another
void fillQueue(Queue* q, Queue* q1){
    while (!isEmptyQueue(q1))
    {
        enqueue(q, dequeue(q1));
    }
    
}



