#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ELTS 1000000
 
struct person {
    int num;
    char name[40];
};
 
void insertionSort(struct person *array, int length);

int main(int argc, char * argv[])
{
	int i;
    if (argc != 2) {
        return -1;
    }
    
    FILE *fp = fopen(argv[1], "r");
    
    struct person *arr = malloc(sizeof(struct person) *MAX_ELTS);
    int size = 0;
    while(fscanf(fp, "%d %s\n", &(arr[size].num), arr[size].name) != EOF) //reads all numbers and names from file and determines size of array from the number of names
    {
        size++;
    }
    
    insertionSort(arr, size); //calls insertion sorting function
    printf("Insertion Sort: \n");

    for (i = 0; i < size; i++) //prints each element of sorted array
    {
        printf("%d %s\n", arr[i].num, arr[i].name);
    }
    
    return 0;
}
 
void insertionSort(struct person *array, int length)
{
    int temp;
    char tempName[40];
    int j, i;
    for (i = 1; i < length; i++) //goes through array
    {
        temp = array[i].num; // saves number and name to be compared
        strcpy(tempName, array[i].name);
        for (j = i-1; j >= 0 && temp < array[j].num; j--) //goes backwards in array until a number smaller than temp is found
        {
            array[j+1].num = array[j].num; //switches two elements so smaller one is put before the bigger number
            strcpy(array[j+1].name, array[j].name);
        }
        array[j+1].num = temp; //new element to compare
        strcpy(array[j+1].name, tempName);
    }
}

