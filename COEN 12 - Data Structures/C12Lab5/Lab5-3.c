#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ELTS 1000000
 
struct person {
    int num;
    char name[40];
};
 
void mergeSort(struct person *array, int start, int end);
void merge(struct person *array, int start, int middle, int end); 
 
int main(int argc, char * argv[])
{
    if (argc != 2) {
        return -1;
    }
    
    FILE *fp = fopen(argv[1], "r");
    
    struct person *arr = malloc(sizeof(struct person) *MAX_ELTS);
    int size = 0, i;
    while(fscanf(fp, "%d %s\n", &(arr[size].num), arr[size].name) != EOF) {
        size++;
    }
        
    mergeSort(arr, 0, size - 1);
    printf("Merge Sort: \n");
    
    for (i = 0; i < size; i++)
    {
        printf("%d %s\n", arr[i].num, arr[i].name);
    }
    
    return 0;
}
 
void merge(struct person *array, int start, int middle, int end)
{
    int i, j, k;
    int n1 = middle - start + 1;
    int n2 =  end - middle;
    
    struct person L[n1];
    struct person R[n2];
    
    for (i = 0; i < n1; i++) //put elements into temp subarrays
    {
        L[i].num = array[start + i].num;
        strcpy(L[i].name, array[start + i].name);
    }
    for (j = 0; j < n2; j++)
    {
        R[j].num = array[middle + j + 1].num;
        strcpy(R[j].name, array[middle + j + 1].name);
    }
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = start; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i].num < R[j].num) //compares the first element of both subarrays and adds lowest to array
        {
            array[k].num = L[i].num;
            strcpy(array[k].name, L[i].name);
            i++;
        }
        else if (L[i].num > R[j].num)
        {
            array[k].num = R[j].num;
            strcpy(array[k].name, R[j].name);
            j++;
        }
        else //if both elements are the same number, compare the names instead
        {
            if ((strcmp(L[i].name, R[j].name)) < 0) //compare names to determine which one gets added to array first
            {
                array[k].num = L[i].num;
                strcpy(array[k].name, L[i].name);
                i++;
            }
            else
            {
                array[k].num = R[j].num;
                strcpy(array[k].name, R[j].name);
                j++;
            }

        }
            
        k++;
    }
    
    while (i < n1) //copy rest of uncopied elements in unempty subarray into array, depending on which on was emptied first
    {
        array[k].num = L[i].num;
        strcpy(array[k].name, L[i].name);
        i++;
        k++;
    }
    
    while (j < n2)
    {
        array[k].num = R[j].num;
        strcpy(array[k].name, R[j].name);
        j++;
        k++;
    }
}
void mergeSort(struct person *array, int start, int end)
{
    if (start < end)
    {
        int middle = start + (end - start) / 2;
        //int middle = (end + start) / 2; //recursively splits array into subarrays then calls merge function
        mergeSort(array, start, middle);
        mergeSort(array, middle + 1, end);
        merge(array, start, middle, end);
    }
}
