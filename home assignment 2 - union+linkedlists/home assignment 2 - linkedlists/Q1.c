//
//  Q1.c
//  home assignment 2 - union+linkedlists
//
//  Created by Yonatan Glanzman on 11/03/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>





//building struct named worked
typedef struct Worker{
    long  id;
    char* name;
    long    salary;
//YOS = year of start
    char YOS[6];
//    YOB = year of beginning
    unsigned long int  YOB;
}Worker;

//creating the stucture of the linked list named worker list
typedef struct WorkerList {
Worker * data;
struct WorkerList* next;
} WorkerList;

Worker* CreateWorker(Worker* worker,int Z_O);
void PrintWorker(Worker* worker,int Z_O);
WorkerList* addWorker(WorkerList* head, Worker* worker);
int IndexI(WorkerList *head, long unsigned id);
int IndexR(WorkerList *head, long unsigned id);
WorkerList* deleteWorstWorker(WorkerList *head);
void update_worker(WorkerList* head,float percent);
WorkerList *reverse(WorkerList *head);
void freeWorkers(WorkerList* head );
long findworstsal(WorkerList *head);
void printList(WorkerList* head,int num);

int main(){
    Worker* worker = NULL;
    WorkerList* list = (WorkerList*)calloc(1,sizeof(WorkerList));
    WorkerList* head = list;
    if (!list) {
        printf("allocation Error!\n");
        exit(1);
    }
    int x;
    int num;
    do{
        puts("Options:\n press 1 to create a new worker :\n press 2 to print list detials :" );
        puts(" press 3 to find worker place on the list:\n press 4 to delete worst worker:");
        puts(" press 5 to update workers salary:\n press 6 to reverse list order:\n press 7 to erase list:");
        puts(" press 0 to quit:");
    scanf("%d",&x);
    switch (x) {
        case 1:
            printf("if you want to enter  hebrew  Year of employment press 1, else press zero:\n");
            scanf("%d",&num);
            worker = CreateWorker(worker, num);
            head = addWorker(head, worker);
            break;
            
        case 2:
            if (!worker) {
            printf("worker need to be created first\n");
                break;
        }else{
            printf("if you entered  hebrew  Year of employment press 1, else press zero:\n");
            scanf("%d",&num);
            printList(head,num);
            break;
        }
        case 3:
            puts("enter worker id:");
            long unsigned id;
            scanf("%ldu",&id);
            int j = IndexR(head,id);
            if (j > 0) {
           printf("the worker place in the list is : %d\n",j);
            }
            else puts("no match found \n\n");
            break;
        case 4:
            head =  deleteWorstWorker(head);
            break;
        case 5:
            puts("enter amount of percantage to raise:");
            float per;
            scanf("%f",&per);
            update_worker(head, per);
            break;
        case 6:
            head = reverse(head);
            break;
        case 7:
            freeWorkers(head);
            break;
        }
    }while (x);
}



    
    
//creating a function which creates a new worker
    Worker* CreateWorker(Worker* worker,int Z_O){
    Worker* temp =(Worker*)calloc(1,sizeof(Worker));
    if (temp == NULL) {
        printf("allocation Error!\n");
        exit(1);
    }
    puts("Enter id: ");
    scanf("%ld",&temp->id);
    puts("Enter worker name :");
    char name[50];
    fseek(stdin, 0, SEEK_END);
    gets(name);
    int namesize = (int)strlen(name);
   temp->name = (char*)malloc(sizeof(char)*namesize);
    if (!temp->name) {
        printf("allocation Error!\n");
        exit(1);
    }
    strcpy(temp->name, name);
    
    puts("Enter salary: ");
    scanf("%lu",&temp->salary);
    
    puts("enter Year of employment: ");
    if (Z_O) {
        scanf("%s",temp->YOS);
    }
    else
        scanf("%lu",&temp->YOB);
    return temp;
}

//creating a function which prints the worker details
void PrintWorker(Worker* worker,int Z_O){
    if (worker == NULL) {
        puts("no detailes to print");
        return;
    }
    
    if (Z_O) {
        printf("worker details are:\n Id:%ld\n Name: %s\n Salery:%ld\n Year of employment:%s",
           worker->id,worker->name,worker->salary,worker->YOS);
    }
    else{
        printf("worker details are:\n Id:%ld\n Name: %s\n Salery:%ld\n Year of employment:%ld\n",
               worker->id,worker->name,worker->salary,worker->YOB);
    }
}


//creating a function which adding a worker to the list based on his salary size:biggest to smallest

WorkerList* addWorker(WorkerList* head, Worker* worker){
    WorkerList* newworker = (WorkerList*)calloc(1,sizeof(WorkerList));
    
    if (!newworker) {
        puts("allocation failed - the worker has not been added\n");
        exit(1);
    }
    
    newworker->data = worker;
    //    empty list case
    if (head->data == NULL) {
        head = newworker;
        return head;
    }
//    adding an object to the right place in the list
    if (head->data->salary < newworker->data->salary){
            newworker->next = head;
            return newworker;
        }
    
    WorkerList* temp = head->next;
    WorkerList* ptr = head;
    while (temp && temp->data->salary >newworker->data->salary) {
        temp = temp->next;
        ptr = ptr->next;
        }
    ptr->next = newworker;
    newworker->next = ptr;
    return head;
    }


//creating two functions whome find a specific worker id on the list

//iterative function:
int IndexI(WorkerList *head, long unsigned  id){
    int place = 1;
    WorkerList* runner = head;
    
    while (runner) {
        if (head->data->id == id) {
            return place;
        }
        runner = runner->next;
        place++;
    }  return -1;
}
//recursive function:
int IndexR(WorkerList *head, long unsigned  id){
    if (head == NULL)
            return -1;
    if (head->data->id == id) {
        return 1;
    }
    return  1 + IndexR(head->next, id);
}

//creating a function which deletes the worker with the lowest salary

WorkerList* deleteWorstWorker(WorkerList *head){
    long worst_sal = findworstsal(head);
    WorkerList* temp = head;
    WorkerList* prev = NULL;
    //  empty list case
    if (head == NULL) {
        return NULL;
    }
    //  if it is one objact list
    if (head->data->salary == worst_sal) {
        temp = head->next;
        head->data=NULL;
        free(head->data);
        return temp;
    }
    //  deliting the worker with the lowest salary
    while (temp){
        if (temp->data->salary == worst_sal) {
            prev->next = temp->next;
            temp->data=NULL;
            free(temp->data);
        }
        prev = temp;
        temp = temp->next;
    }
    return head;
}

//creating a function which raises the salary of all workers by a certien percentage

void update_worker(WorkerList* head,float percent){
    WorkerList* temp = head;
    while (temp) {
        temp->data->salary += temp->data->salary * percent/100;
        temp = temp->next;
    }
}

//creating a function which reverses the order of the list

WorkerList *reverse(WorkerList *head){
    //    empty list case
    if (!head|!head->next) {
        return head;
    }
    WorkerList* previous = head;
    WorkerList* current = previous->next;
    WorkerList*  next = current->next ;
    
    while (next) {
        // switching pointer direction
        current->next = previous;
        //moving forword the pointer
        previous = current;
        current = next;
        next = next->next;
    }
    //dealing with the last place which becomes the head;
    current->next = previous;
    head->next = NULL;
    head = current;
    return head ;
}

//creating a function which frees the memory allocated in the list
void freeWorkers(WorkerList* head ){
    WorkerList* temp = head;
    while (temp) {
        temp->data = NULL;
        free(temp->data);
        temp = temp->next;
        }
}

long findworstsal(WorkerList *head){
    int place = 0;
    long worst_sal = head->data->salary;
    WorkerList* runner = head;
    
    while (runner) {
        if (runner->data->salary < worst_sal){
            worst_sal = runner->data->salary;
        }
        runner = runner->next;
        place++;
    }  return worst_sal;
}

void printList(WorkerList* head,int num)
{
    WorkerList* temp = head;

    while (temp)
    {
        PrintWorker(temp->data, num);
        temp = temp->next;
        printf("\n");
    }

}
