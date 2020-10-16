/*COP 3502 Assignment 1
This program is written by: Deodatus Marcellino */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 50

typedef struct monster
{
    char *name;
    char *element;
    int population;
} monster;

typedef struct region
{
    char *name;
    int nmonsters;
    int total_population;
    monster **monsters;
} region;

typedef struct itinerary
{
    int nregions;
    region **regions;
    int captures;
} itinerary;

typedef struct trainer
{
    char *name;
    itinerary *visits;
} trainer;

monster *createMonster(char *name, char *element, int population)
{
    monster *temp = malloc(sizeof(monster));
    strcpy(temp->name, name);
    strcpy(temp->element, element);
    temp->population = population;
    return temp;
} // end createMonster

monster **readMonsters(FILE *in, int *mCount)
{
    char tempString[11];
    char tempName[SIZE];
    char tempElement[SIZE];
    int tempPopulation[1000000];
    int lengthName;
    int lengthElement;

    in = fopen("in.txt", "r");
    fscanf(in, "%d", mCount);
    fscanf(in, "%s", tempString);

    // allocate memory to create mCount number of monsters array
    monster **myMonsters = malloc(*mCount * sizeof(monster *));
    // Scan for the monsters information
    for (int i = 0; i < *mCount; i++)
    {
        fscanf(in, "%s %s %d", tempName, tempElement, &tempPopulation);
        myMonsters[i] = createMonster(*tempName, *tempElement, tempPopulation);
        /*  lengthName = strlen(tempName);
        lengthElement = strlen(tempElement);
        myMonsters[i].name = (char*)malloc(sizeof(char)*(lengthName+1));
        myMonsters[i].element = (char*)malloc(sizeof(char)*(lengthElement+1));
        strcpy(myMonsters[i].name, tempName);
        strcpy(myMonsters[i].element, tempElement);
        myMonsters[i].population = tempPopulation; */
        printf("The values are %s %s %d", myMonsters[i]->name, myMonsters[i]->element, myMonsters[i]->population);
    }

    // free the memory
    for (int i = 0; i < *mCount; i++)
    {
        free(myMonsters[i]);
    }
    return myMonsters;
} // end readMonsters

int main()
{
    // atexit(report_mem_leak);
    FILE *in = fopen("in.txt", "r"); // read from FILE
    int mCount, rCount, tCount, trCount;

    monster **monsters = readMonsters(in, &mCount);
    free(monsters);
    fclose(in);

} // end main