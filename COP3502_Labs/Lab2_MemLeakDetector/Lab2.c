#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"

#define SIZE 50

typedef struct student 
{
    char *lname;
    int assignment;
    int finalExam;
    int total;
    int *quizzes;
} student;

void printHighestTotal(FILE *out, student** courses, int C, int N, int M) {
    int highest = 0;
    student* highestScoreStudent = NULL;
    int courseNumber = -1;
    // iterate through the C courses
    for(int i = 0; i < C; i++) {
        // iterate through the N student
        for (int j = 0; j < N; j++) {
            if(courses[i][j].total > highest) {
                // store the highest score
                highest = courses[i][j].total;
                highestScoreStudent = &courses[i][j];
                courseNumber = i+1;
            }
        }
    }
    // Write to output FILE
    fprintf(out, "Name: %s", highestScoreStudent->lname);
    fprintf(out, "\nAssignment: %d", highestScoreStudent->assignment);
    fprintf(out, "\nQuizzes: ");
    for(int q = 0; q < M; q++) {
        fprintf(out, "%d ", highestScoreStudent->quizzes[q]);
    }
    fprintf(out, "\nFinal Exam: %d", highestScoreStudent->finalExam);
    fprintf(out, "\nTotal: %d", highestScoreStudent->total);
    fprintf(out, "\nCourse Number: %d", courseNumber);
} // end printHighestTotal

student ** readCourses(FILE *in, int *C, int *N, int *M) {
    // file pointer to open and read "in.txt" file
    in = fopen("in.txt", "r");
    // scan the "in.txt" file for data and store it in the variable
    fscanf(in, "%d %d %d", C, N, M);

    // Allocate memory to create C number of courses with the size of student pointer 
    student** courses = calloc(*C, sizeof(student*)); 
    // fill up each array of courses with students information
    for (int i = 0; i < *C; i++){
        courses[i] = calloc(*N, sizeof(student));

        // create temporary value for lname with size (SIZE = 50)
        char lastName[SIZE];
        for (int j = 0; j < *N; j++) {
            // READ LASTNAME from "in.txt" file to the temporary value lname.
            fscanf(in, "%s", lastName);
            // determine the size of the name + 1 for the end character '\0'. 
            int nameSize = sizeof(lastName) + 1;
            // allocate memory for lname because lname is a pointer.
            courses[i][j].lname = malloc(nameSize * sizeof(char));
            // copy the value in the temporary lastName to the allocated space.
            strncpy(courses[i][j].lname, lastName, nameSize);
            // strncpy (destination, source, how many char I want to copy)

            // READ ASSIGNMENT score
            fscanf(in, "%d", &courses[i][j].assignment);

            // READ QUIZZES
            // allocate memory for N number of quizzes with size int
            courses[i][j].quizzes = calloc(*M, sizeof(int));
            // create temporary variable to store total quiz scores
            int total = 0;
            // read the quizzes from "in.txt" file
            for (int k = 0; k < *M; k++) {
                fscanf(in, "%d", &courses[i][j].quizzes[k]);
                // sum of quiz scores
                total += courses[i][j].quizzes[k];
            }
            // READ FINAL EXAM
            fscanf(in, "%d", &courses[i][j].finalExam);

            // total score = (sum of quizzes) + (assignment score) + (final exam)
            courses[i][j].total = total + courses[i][j].assignment + courses[i][j].finalExam;
        }
  
    }
    return courses;
} // end readCourses

void release_memory(student ** st, int C, int N, int M) {
    for(int i = 0; i < C; i++) {
        for (int j = 0; j < N; j++) {
            free(st[i][j].lname);
            free(st[i][j].quizzes);
        }
        free(st[i]);
    }
    free(st);
} // end release memory

int main() {
    // memory leak detector
    atexit(report_mem_leak);
    FILE *in = fopen("in.txt", "r"); // read from FILE
    int C, N, M;
    student** courses = readCourses(in, &C, &N, &M);
    FILE *out = fopen("out.txt", "w"); // write to FILE

    printHighestTotal(out, courses, C, N, M);

    release_memory(courses, C, N, M);

    fclose(in);
    fclose(out);
    return 0;

} // end main