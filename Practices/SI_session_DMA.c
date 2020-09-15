#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// allocate an array of structs and fill all of the members of each struct
typedef struct Person {
    int age;
    char *name;
    char ** friends;
} Person;

int main(){
    // create a struct pointer called group and allocate 5 people

    Person *group;
    group = (Person*)malloc(5*sizeof(Person));

    // now lets put the info of each Person

    // how do we access the member of a struct pointer
    // group->age
    // what does the arrow do?
    // what do we do to an address to get tot the value inside

    // how many times do we need to dereference our group pointer to get to the variables inside? 
    // 1

    // create a for loop that will run 5 times and ask the user to input the name of each person.

    // let's change the for loop to be able to take-in a name
    // and then allocate just enough space to store that name
    char buffer[101];
    int length;

    for (int i = 0; i < 5; i++) {
        printf("Put in a name and an age: \n");
        scanf("%s %d", buffer, &group[i].age);
        length = strlen(buffer);
        group[i].name = (char*)malloc(sizeof(char)*(length+1));
        strcpy(group[i].name, buffer);
        printf("\tYour name and age is: %s %d\n", group[i].name, group[i].age);
        // try to allocate a list of 5 friends to each person and fill it with names
        for (int j = 0; j < 5; j++){
            printf("Put in friend's name number %d ", (j+1));
            scanf("%s", buffer);
            length = strlen(buffer);
           group[i].friends = (char**)malloc(sizeof(char*)*(length+1));
           strcpy(group[i].friends[j], buffer); 
           printf("\tFriend number %d is: %s\n", (j+1), group[i].friends[j]);
        }
    }
    return 0;

}