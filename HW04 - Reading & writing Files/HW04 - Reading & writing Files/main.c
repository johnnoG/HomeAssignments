//
//  main.c
//  HW04 - Reading & writing Files
//
//  Created by Yonatan Glanzman on 07/07/2022.
//


#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h> //https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#define SIZE 256

typedef struct StudentCourseGrade{
    
    char courseName[35];
    int grade;
}StudentCourseGrade;

typedef struct Student{
    
    char name[35];
    StudentCourseGrade* grades; //dynamic array of courses
    int numberOfCourses;
}Student;


//Part A
void countStudentsAndCourses(const char* fileName, int** coursesPerStudent, int* numberOfStudents);
int countPipes(const char* lineBuffer, int maxCount);
char*** makeStudentArrayFromFile(const char* fileName, int** coursesPerStudent, int* numberOfStudents);
void printStudentArray(const char* const* const* students, const int* coursesPerStudent, int numberOfStudents);
void factorGivenCourse(char** const* students, const int* coursesPerStudent, int numberOfStudents, const char* courseName, int factor);
void studentsToFile(char*** students, int* coursesPerStudent, int numberOfStudents);
int lines_num(FILE* fptr);
//Part B
Student* transformStudentArray(char*** students, const int* coursesPerStudent, int numberOfStudents);
void writeToBinFile(const char* fileName, Student* students, int numberOfStudents);
Student* readFromBinFile(const char* fileName);

int main()
{
    //Part A
    int* coursesPerStudent = NULL;
    int numberOfStudents = 0;
    char*** students = makeStudentArrayFromFile("studentList.txt", &coursesPerStudent, &numberOfStudents);
    factorGivenCourse(students, coursesPerStudent, numberOfStudents, "Advanced Topics in C", +5);
    printStudentArray(students, coursesPerStudent, numberOfStudents);
    //studentsToFile(students, coursesPerStudent, numberOfStudents); //this frees all memory. Part B fails if this line runs. uncomment for testing (and comment out Part B)
    
    //Part B
    Student* transformedStudents = transformStudentArray(students, coursesPerStudent, numberOfStudents);
    writeToBinFile("students.bin", transformedStudents, numberOfStudents);
    Student* testReadStudents = readFromBinFile("students.bin");

    for (int i = 0; i < numberOfStudents; i++)
        {
            for  (int j = 0; j < *coursesPerStudent;j++)
            {
                free(transformedStudents[i].grades[j].courseName);
                free(testReadStudents[i].grades[j].courseName);
            }
        }


    /*_CrtDumpMemoryLeaks();*/ //uncomment this block to check for heap memory allocation leaks.
    // Read https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019

    return 0;
}


//PART A:
void countStudentsAndCourses(const char* fileName, int** coursesPerStudent, int* numberOfStudents)
{
    FILE* Fptr = fopen(fileName, "r");
    //    cheking if the filed was opend succesfully
    if (!Fptr) {
        puts("There was a error opening the file");
        exit(1);
    }
    *numberOfStudents = lines_num(Fptr);
    
    *coursesPerStudent = (int*)malloc((*numberOfStudents) * sizeof(int));
    char Rows[SIZE];
    
    int i = 0, j = 0;
        char buffer = 'a';
    
    while (!feof(Fptr)){

            while (buffer != '\n' && buffer != EOF)
            {
                buffer = fgetc(Fptr);
                Rows[i] =  buffer;
                i++;
            }
        
            (*coursesPerStudent)[j] = countPipes(Rows, SIZE);
        
            for (int r = 0; r < SIZE; r++)
            {
                Rows[r] = '\0';
            }
            buffer = fgetc(Fptr);
            j++;
        }
    fclose(Fptr);
}

int countPipes(const char* lineBuffer, int maxCount)
{
    
    if (lineBuffer == NULL){
        return -1;
    }
    if (maxCount <= 0) {
        return 0;
    }
    int counter = 0;
    
    for (int i = 0; i < maxCount; i++) {
        if (lineBuffer[i] == '\0') {
            return counter;
        }
        else if (lineBuffer[i] == '|'){
            counter++;
        }
    }
    return counter;
}

char*** makeStudentArrayFromFile(const char* fileName, int** coursesPerStudent, int* numberOfStudents)
{
    char Rows[SIZE];
    char buffer = 'a';
    
    FILE* Fptr = fopen(fileName, "r");
//    cheking if the filed was opend succesfully
    if (!Fptr) {
        puts("There was a error opening the file");
        exit(1);
    }
    
    countStudentsAndCourses(fileName, coursesPerStudent, numberOfStudents);
    char*** students = (char***)malloc(sizeof(char*));
    
    if (!students) {
        puts("allocation faild");
        exit(1);
    }
//    allocating memory for students array indexes
    for (int i = 0; i < *numberOfStudents; i++) {
        students[i] = (char**)malloc(sizeof(char*) * (*numberOfStudents));
        
        if (!students[i]) {
            puts("allocation faild");
            exit(1);
        }
    }
    int w = 0;
    int k = 0;
    int j = 0;
//    going threw the file untill the end of it
    while (!feof(Fptr)) {
        
        while (buffer!=EOF && buffer !='\n') {
            
        
            while ((buffer != '|') && (buffer != ',') && (buffer != '\n') && (buffer != EOF)){
                buffer = fgetc(Fptr);
                
                if (buffer== EOF){
                    break;
                    }
                
                if (buffer != '|' && buffer != ','){
                    Rows[j] = buffer;
                    }
                
                    j++;
                
            }
            
            Rows[j] = '\0';
            
            students[w][k] = *(char**)malloc(j * sizeof(char*));
                        strcpy(students[w][k], Rows);
            
            for (int s = 0; s < j; s++){
                Rows[s] = '\0';
            }
                        j = 0;
                        k++;
        }
                w++;
                k = 0;
                buffer = 'a';

    }
    fclose(Fptr);
    return students;
}

void factorGivenCourse(char** const* students, const int* coursesPerStudent, int numberOfStudents, const char* courseName, int factor)
{
    //cheking if the given factor range is legal
    
    if (factor > 20 || factor < -20) {
        puts("The given factor is ilegal");
        exit(1);
    }
    char buffer [10];
    int fixedgrade = 0;
    
    for (int i = 0;  i < numberOfStudents; i++) {
        
        for (int j = 0; j < ((coursesPerStudent[i]) * 2) + 1; j++){
                    
            if (strcmp(courseName, students[i][j]) == 0){
                
                fixedgrade = atoi(students[i][j + 1]) + factor;
                
//                makong sure the grade is not bigger then 100 or smaller then 0
                if (fixedgrade > 100){
                    fixedgrade = 100;
                }
                
                if (fixedgrade < 0){
                    fixedgrade = 0;
                }
                strcpy(students[i][j + 1], itoa(fixedgrade, buffer, 10));
            }
        }
    }
}

void printStudentArray(const char* const* const* students, const int* coursesPerStudent, int numberOfStudents)
{
    for (int i = 0; i < numberOfStudents; i++)
    {
        printf("name: %s\n*********\n", students[i][0]);
        for (int j = 1; j <= 2 * coursesPerStudent[i]; j += 2)
        {
            printf("course: %s\n", students[i][j]);
            printf("grade: %s\n", students[i][j + 1]);
        }
        printf("\n");
    }
}

void studentsToFile(char*** students, int* coursesPerStudent, int numberOfStudents)
{
    FILE* Fptr = fopen("studentList.txt", "w");
    //    cheking if the filed was opend succesfully
    if (!Fptr) {
        puts("There was a error opening the file");
        exit(1);
    }
    int i = 0;
    while (i < numberOfStudents) {
        for (int j = 0; j < (*coursesPerStudent * 2) + 1 ; j++) {
            fprintf(Fptr, "%s",students[i][j]);
            free(students[i][j]);
        }
        fprintf(Fptr, "\n");
        i++;
    }
    free(students);
}

//PART B:

void writeToBinFile(const char* fileName, Student* students, int numberOfStudents)
{
    FILE* Fptr = fopen(fileName, "wb");
    //    cheking if the filed was opend succesfully
    if (!Fptr) {
        puts("There was a error opening the file");
        exit(1);
    }
    char buffer[39];
    
    for (int i = 0; i < numberOfStudents; i++){
            fwrite((void*)'    ', 1, 1, Fptr);
            strcpy(buffer, students[i].name);
            fwrite(buffer, sizeof(buffer), 1, Fptr);
            fwrite(&students[i].numberOfCourses, sizeof(students[i].numberOfCourses), 4, fileName);
            
            for (int j = 0; j < students[i].numberOfCourses; j++){
                strcpy(buffer, &students[i].grades->courseName[j]);
                fwrite((void*)'    ', 1, 1, Fptr);
                fwrite(buffer, sizeof(buffer), 1, Fptr);
            }
        }
        fclose(Fptr);

}


Student* readFromBinFile(const char* fileName)
{
    FILE* Fptr = fopen(fileName, "wb");
    //    cheking if the filed was opend succesfully
    if (!Fptr) {
        puts("There was a error opening the file");
        exit(1);
    }
    
    int numberOfStudents=0;
    int numOfCurses=0;
    
    fread(&numberOfStudents,sizeof(int),sizeof(int), Fptr);
    
    //allocating memory for studnt array
    Student* studarr = (Student*)malloc(numberOfStudents * sizeof(Student));
    
    if (!studarr) {
        puts("allocation failed");
        exit(1);
    }

    for (int i = 0; i < numberOfStudents; i++){
        
            fread(studarr[i].name, sizeof(studarr[i].name), 1, Fptr);
            fread(&numOfCurses, sizeof(numOfCurses), 4, Fptr);
            studarr[i].grades = (StudentCourseGrade*)malloc(numOfCurses * sizeof(StudentCourseGrade));
            assert(studarr[i].grades);
        
            for (int j = 0; j < numOfCurses; j++){
                fread(studarr[i].grades[j].courseName, sizeof(studarr[i].grades->courseName), 1, Fptr);
            }
        
        }
    
        fclose(Fptr);
        return studarr;
    }


Student* transformStudentArray(char*** students, const int* coursesPerStudent, int numberOfStudents){
    
    //allocating memory for studnt array
    Student* studarr = (Student*)malloc(numberOfStudents * sizeof(Student));
    
    if (!studarr) {
        puts("allocation failed");
        exit(1);
    }
    for (int i = 0; i < numberOfStudents; i++){
//        inserting the data from 'old' arrays to the struct array
            strcpy(studarr[i].name, students[i][0]);
            studarr[i].numberOfCourses = coursesPerStudent[i];
        
        for ( int j = 1; j < (coursesPerStudent[i] * 2) - 1; j += 2) {
//           allocating memory for sub array 'grades'
            
            studarr[i].grades = (StudentCourseGrade*)malloc(coursesPerStudent[i] * sizeof(StudentCourseGrade));
            
            if (!studarr[i].grades) {
                puts("allocation failed");
                exit(1);
            }
                        strcpy(studarr[i].grades[j].courseName, students[i][j]);
                        studarr[i].grades->grade = atoi(students[i][j + 1]);
        }
    }
    return studarr;
}



//privte functions!!

int lines_num(FILE* fptr){
   int counter = 0;
    if (!fptr) {
        puts("There was a error opening the file");
        exit(1);
    }
    char buffer;
    
    int Rowdex = 0;
    while (Rowdex!=EOF) {
    
    Rowdex = fscanf(fptr, "%c", &buffer);
        if (Rowdex == '\n') {
            counter++;
        }
    }
    if (counter) {
        counter++;
    }
    rewind(fptr);
    return counter;
}
