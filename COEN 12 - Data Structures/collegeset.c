#include <stdio.h>
#include <stdlib.h>
#include "dataset.h"

#define MAX 3000 //we will only search and make IDs up to 2000

int main (void){
  int randAge, randID=0, records=1, operation, IDsearch;
  LIST *lp;
  NODE *Delete;
  int search=0; 
  puts("This program is automatic. This program will keep running until 3000 student records are present. Presing any key will start the program");
  getchar();
  lp=createDataSet(MAX);//creating the linked list
  while(records<1001){//creating the initial first 1000 IDs
    puts("\n");
    randAge=18+rand()%13;//18+0 to 18+12
    randID=randID+ 1 + rand()%2;//old ID+1 or old ID +2
    insertLast(lp, randAge, randID);//simply insert the values into the linked list
    records++;
    printf("ID: %d Age: %d\n", randID, randAge);
    //maxAgeGap(lp);
  }
  while(records< MAX){//MAX random ID is 2000
    operation= rand()%10;//using this we will simulate the idea of frequent insertions and deletions and less frequent searches
    randAge=18+rand()%13;//18+0 to 18+12
    //printf("\n\noperation: %d\n", operation);
    puts("\n");
    switch(operation){
      case 0: //add new
      case 1:
      case 2:
      case 3:
            randID= randID + 1 + rand()%2;//create a new ID 
            insertLast(lp, randAge, randID);//insert values
            records++;
            break;
      case 4:
      case 5:
      case 6:
      case 7: //search then delete
                IDsearch= rand()%randID;//searching an element in the ID range
                printf("Searching for ID %d to delete\n", IDsearch);
                Delete=searchID(lp, IDsearch);//Delete is a NODE, and this node will be an actual node or a NULL
                if(Delete!=NULL){
                  deletion(lp, Delete);//now we simply delete the NODE without performing another search. So this operation is done in O(1) time
                  records--;
                }
              break;
      case 8: //search ID only
              IDsearch= rand()%randID;//searching an element in the ID range
              printf("Only searching for %d\n", IDsearch);
              Delete=searchID(lp, IDsearch);//note no actual deleting takes place
              break;
      case 9:
            //search age
              randAge=18+rand()%13;//searching an age from 18 to 30
              printf("Searching for student IDs at the age of %d\n", randAge);
              searchAge(lp, randAge);
              break;
      default: 
        puts("INVALID OPERATION");
    }
  }
    maxAgeGap(lp);
    puts("Destroying Data Set");
    destroyDataSet(lp);
}

