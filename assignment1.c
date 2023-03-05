/* COP 3502 - Assignment 1
** Name: Deodatus Marcellino
** ID:   4411106
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student{
   int id;
   char *lname;
   float *scores;
   float std_avg;
   }student;


typedef struct course{
   char *course_name;
   int num_sections;
   student **sections;
   int *num_students;
   int *num_scores;
} course;

//////// Function Prototype /////////
course *read_courses(FILE *fp, int *num_courses);
student **read_sections(FILE *fp, int num_students[], int num_scores[],int num_sections);
void process_courses(course* courses, int num_courses);
void print_to_output(student **sections, int num_students[], int num_scores[], int num_sections);
void release_courses(course *courses, int num_courses);
void release_sections(student **sections, int num_sections, int *num_students, int *num_scores);

//////// Main Start Here ////////////
int main(void) {
  
  // Declare Variables Here
  FILE *fp;
  course *courses;
  int test_cases, num_courses;
  int i;

  fp = fopen("assignment1input.txt", "r");
  fscanf(fp, "%d", &test_cases);

  for (i = 0; i < test_cases; i++)
  {
    printf("test case %d\n",i+1);
    courses = read_courses(fp, &num_courses);
    process_courses(courses, num_courses);
    release_courses(courses, num_courses);
    printf("\n\n");
    
  }// end for loop

  fclose(fp);
  printf("File closed...\n");

  return 0;
} // end main function

////////// Functions ///////////////
course *read_courses(FILE *fp, int *num_courses)
{
  char className[50];
  int name_size;
  int num_students[50], num_scores[20];
  int j;

  // read number of courses
  fscanf(fp, "%d", num_courses);

  course *courses = malloc(*num_courses * sizeof(course));
  
  for (int i = 0; i < *num_courses; i++)
  {
    // read course name
    fscanf(fp, "%s", className);
    name_size = strlen(className);

    courses[i].course_name = malloc(name_size+1);
    strcpy(courses[i].course_name, className);

    // read number of sections for the course
    fscanf(fp, "%d", &courses[i].num_sections);

    // allocate for number of students and scores 
    courses[i].num_students = (int*)malloc(courses[i].num_sections * sizeof(int));
    courses[i].num_scores = (int*)malloc(courses[i].num_sections * sizeof(int));
    
    // call read section function
    courses[i].sections = read_sections(fp, courses[i].num_students, courses[i].num_scores, courses[i].num_sections);

  }

  return courses;

} //end function read_courses

student **read_sections(FILE *fp, int num_students[], int num_scores[], int num_sections)
{
  int i, j, k;
  float total_score;
  char last_name[50];
  student **students = (student**)malloc(num_sections * sizeof(student*));

  // read students for each section
  for (i = 0; i < num_sections; i++)
  {
    // read number of student and assignments 
    fscanf(fp, "%d %d", &num_students[i], &num_scores[i]);

    // allocate memory for students
    students[i] = (student*)malloc(sizeof(student)*num_students[i]);

    for (j = 0; j < num_students[i]; j++)
    {
      // read student ID and student last name
      fscanf(fp, "%d %s", &students[i][j].id, last_name);

      // copy last name 
      students[i][j].lname = malloc(strlen(last_name) + 1);
      strcpy(students[i][j].lname, last_name);

      // allocate memory for student score
      students[i][j].scores = (float*)malloc(num_scores[i] * sizeof(float));
      total_score = 0;

      // adding scores for the student
      for (k = 0; k < num_scores[i]; k++)
      {
        fscanf(fp, "%f", &students[i][j].scores[k]);
        total_score =  total_score + students[i][j].scores[k];
      }

      // calculate average scores
      students[i][j].std_avg = total_score / num_scores[i];


    }

  }

  return students;
} // end function read_sections

void process_courses(course* courses, int num_courses)
{
  
  for (int i = 0; i < num_courses; i++)
  {
    //printing the course name
    printf("%s ", courses[i].course_name);

    //printing the data of the course
    print_to_output(courses[i].sections, courses[i].num_students, courses[i].num_scores, courses[i].num_sections);

  }

} // end function process_courses

void print_to_output(student **sections, int num_students[], int num_scores[], int num_sections)
{

  float *average = (float *) malloc(num_sections * sizeof(float));
  int highest_score_student, highest_section, flag = 0;
  float total_section;
  float highest_average = -1;
  
  // go through each section
  for(int i = 0; i < num_sections; i++)
  {
    total_section = 0;
    //calculate sum of average
    for(int j = 0; j<num_students[i]; j++)
    {
      
      if (sections[i][j].std_avg >=70 )
      {
        flag++;
      }
      total_section += sections[i][j].std_avg; // the total of the averages 

      // keep track of students with the highest average
      if(sections[i][j].std_avg>highest_average)
      {
        highest_average = sections[i][j].std_avg;
        highest_score_student = j;
        highest_section = i;
      }
    }

    // calculating the average
    average[i] = total_section/num_students[i];
  }

  printf("%d ", flag);

  for(int i = 0; i < num_sections; i++)
    printf("%.2f ", average[i]);

  printf("%d %s %.2f\n",sections[highest_section][highest_score_student].id, 
    sections[highest_section][highest_score_student].lname, sections[highest_section][highest_score_student].std_avg);

  // freeing the memory
  free(average);

} // end function print_to_output

void release_courses(course *courses, int num_courses)
{

  for (int i = 0; i<num_courses; i++)
  {
    // freeing class name
    free(courses[i].course_name);

    // freeing sections
    release_sections(courses[i].sections, courses[i].num_sections, courses[i].num_students, 
      courses[i].num_scores);

    //free the num_students and num_scores array.
    free(courses[i].num_students);
    free(courses[i].num_scores);
  }

  //finally free the courses
  free(courses);
} // end function release_courses

void release_sections(student **sections, int num_sections, int *num_students, int *num_scores)
{
  for(int i = 0; i < num_sections; i++)
  {
    // go through each students
    for(int j = 0; j <num_students[i]; j++)
    {
      //freeing last name and assignment scores
      free(sections[i][j].lname);
      free(sections[i][j].scores);
    }

    free(sections[i]);
  }
  free(sections);
}