/*
** Programming Assignment 3
** Name: Deodatus Marcellino
** UCFID: 4411103
** Spring 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ********** Global Variables ********* //
int globalX; 
int globalY;

// ********** Struct ********* //
typedef struct point
{
  int x;
  int y;
  int distance;
} point;

// ********* Function Prototype ********* //
void merge(point arr[], int l, int m, int r);
void mergeSort(point arr[], int l, int r, int T);
void insertionSort(point arr[], int l, int r) ;
int binarySearch(point arr[], point quiry, int n);
int calculate_distance(point p1, point p2);
void sort(point arr[], int length, int threshold);

int compareTo(point *point1, point *point2);
point* ReadData(FILE* fp, int N, int x, int y);

// *********** Main Function ********** //
int main()
{
  // Variables and File I/O
  int num_points;
  int search_points;
  int threshold;
  point *points;

  FILE *inFile = fopen("Assignment3input.txt","r");
  FILE *outFile = fopen("out.txt", "w");

  if(inFile != NULL)
  {
    fscanf(inFile, "%d", &globalX);
    fscanf(inFile, "%d", &globalY);
    fscanf(inFile, "%d", &num_points);
    fscanf(inFile, "%d", &search_points);
    fscanf(inFile, "%d", &threshold);

    points = ReadData(inFile, num_points, globalX, globalY);

    // sort the points
    sort(points, num_points, threshold);

    // Output to File
    for(int i = 0; i < num_points; i++)
    {
       fprintf(outFile, "%d %d\n", points[i].x, points[i].y);
    }

    printf("output file created.");

    int pointSearch = 0;
    while(pointSearch < search_points)
    {
        int x,y;
        fscanf(inFile, "%d %d", &x, &y);
        point quiry;
        quiry.x = x;
        quiry.y = y;

        //search the points
        int r = binarySearch(points, quiry, num_points - 1);
        if( r >= 0)
         fprintf(outFile, "%d %d found at rank %d\n", x, y, r+1);
        else
          fprintf(outFile, "%d %d not found\n", x, y);

        pointSearch++;
    }

    fclose(inFile);
    fclose(outFile);

    // Free memory
    free(points);

    }
    return 0;
} // end main function

int calculate_distance(point p1, point p2)
{
  int result;
  result = (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);

  return result;
} // end function calculate_distance

int binarySearch(point arr[], point quiry, int n)
{
    // Variables
    point reference_pt;
    reference_pt.x = globalX;
    reference_pt.y = globalY;

    quiry.distance = calculate_distance(quiry, reference_pt) ;

    int low = 0;
    int high = n;
    while(low <= high)
    {
        // middle 
        int mid = (low + high)/2;

        if(compareTo(&arr[mid], &quiry) == 0)
          return mid;

        if(compareTo(&arr[mid], &quiry) <0)
          low = mid + 1;
        else if(compareTo(&arr[mid], &quiry) >0)
          high = mid - 1;
    }
    return -1;

} // end function binarySearch

void merge(point arr[], int l, int m, int r)
{
    // temporary array size
    int size1 = (m-l) + 1;
    int size2 = (r-m);

    point *arr1 = (point*)malloc(size1*sizeof(point));
    point *arr2 = (point*)malloc(size2*sizeof(point));

    //creating arrays 1 and 2
    for(int i = 0; i < size1; i++)
        arr1[i] = arr[i + l];


    for(int i = 0; i < size2; i++)
        arr2[i] = arr[i + m + 1];

    int p1, p2, p3;
    p1 = 0;
    p2 = 0;
    p3 = l;

    //checking for the smallest elements
    // insert them to final array
    while(p1 < size1 && p2 < size2)
    {
        if(compareTo(&arr1[p1], &arr2[p2]) < 0)
        {
          arr[p3] = arr1[p1];
          p1++;

        }
        else
        {
            arr[p3] = arr2[p2];
            p2++;
        }
        p3++;
    }

    while(p1 < size1)
    {
        arr[p3] = arr1[p1];
        p1++;
        p3++;
    }

    while(p2 < size2)
    {
        arr[p3] = arr2[p2];
        p2++;
        p3++;
    }

    free(arr1);
    free(arr2);

} // end function merge

void mergeSort(point arr[], int l, int r, int T)
{
    if( (r - l) <= T)
      insertionSort(arr, l, r);
    else
    if(l<r)
    {
        int mid = (l+r)/2;
        mergeSort(arr,l,mid, T);
        mergeSort(arr,mid+1,r, T);
        merge(arr,l,mid,r);
    }
} // end function mergeSort

void sort(point arr[], int length, int threshold) {
    mergeSort(arr, 0, length-1, threshold);
} // end function sort

point* ReadData(FILE *input, int N, int x, int y){

    // variables
    point reference_pt = {x, y};
    point* arrays = malloc(sizeof(point) * N);
    int i = 0;


    while(i < N){
        fscanf(input, "%d", &arrays[i].x);
        fscanf(input, "%d", &arrays[i].y);
        arrays[i].distance  =calculate_distance(arrays[i], reference_pt);
        i++;
    }

    return arrays;

} // end function ReadData

void insertionSort(point arr[], int l, int r)
{
  // variables
  int i, j;
  int n = r-l+1;
  point item;

  for (i = l+1; i <=r; i++) {
    item = arr[i];
      for(j=i-1; j>=l; j--)
      {
        if(compareTo(&arr[j], &item)>0)
            // Shift array
            arr[j+1] = arr[j]; 
        else
          break;
      }
      arr[j+1] = item;
    }
} // end function insertionSort

int compareTo(point *point1, point *point2)
{
  //compare distance 
  if (point1->distance != point2->distance)
    return point1->distance - point2->distance;

  // comparing x if the distances are same
  if (point1->x != point2->x)
    return point1->x - point2->x;
  // compare y
  if (point1->y != point2->y)
    return point1->y - point2->y;

  return 0;

} //end function compareTo