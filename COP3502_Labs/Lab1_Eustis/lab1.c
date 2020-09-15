#include <stdio.h>

struct Student {
    int student_ID;
    int g1, g2, g3;
    float average;
};

struct Student getMaxAverageStudent(struct Student *s, int n) {
    
    float max = -1;
    int max_index = 0;
    for (int i = 0; i < n; i++){
        // check if the current student s[i] has average than current max_index
        if (s[i].average > max){
            // if it does, update the current max to s[i]'s average
            max = s[i].average;
            // update the max index to i
            max_index = i;
        }
    }// End for loop
    
    return s[max_index];
} // end function getMaxAverageStudent

int main()
{
    // Variables
    FILE *inputfile;
    FILE *outputfile;
    int n;
    
    // Read from a file
    inputfile = fopen("students.txt", "r");
    // Store the output to a file
    outputfile = fopen("out.txt", "w");
    // Scan the file to read the integer and store it on variable n.
    fscanf(inputfile, "%d", &n);
    
    // Create array of structs of Students
    struct Student students[n];
    // Fill in the array of students, loop through the list of students.
    for(int i = 0; i < n; i++) {
        // Scan the student ID
        fscanf(inputfile, "%d", &students[i].student_ID);
        // Scan the student grades
        fscanf(inputfile, "%d %d %d", &students[i].g1, &students[i].g2, &students[i].g3);
        // Calculate the average of the student's grade
        students[i].average = (students[i].g1 + students[i].g2 + students[i].g3)/3.0;
        // Display the output (student ID, grade 1, 2, 3, and the average.)
        printf("%d %d %d %d %0.2f\n", students[i].student_ID, students[i].g1, students[i].g2, students[i].g3, students[i].average);
        // Save the output to my output file
        fprintf(outputfile, "%d %d %d %d %0.2f\n", students[i].student_ID, students[i].g1, students[i].g2, students[i].g3, students[i].average);
    }// End for loop
    
    // Call function to get the maximum average among all students and which student has it. 
    struct Student maxStudent = getMaxAverageStudent(students, n);
    // Display the max average to output
    printf("\nMaximum Average is %.2f and the student is %d\n", maxStudent.average, maxStudent.student_ID);
    // Save the max average output into my output file 
    fprintf(outputfile, "\nMaximum Average is %.2f and the student is %d\n", maxStudent.average, maxStudent.student_ID);
    // Close the files
    fclose(inputfile);
    fclose(outputfile);
    return 0;
}// End main
