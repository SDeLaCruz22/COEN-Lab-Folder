#include <stdio.h>
#include <stdlib.h>
#include "dataset2.h"

#define MAX 3001 //this is the max student limit, note that this is a prime number
/*
maximum number of students is 3000 
Generate 1000 student records with random ages ranging from 18 to 30 

so the size is 1000 during create set we want to make 1000 unique records

Implement a random integer generator, which randomly generates an integer number as either 1 or 2. 

The first student ID can be determined as the return value of the random integer generator (i.e. either 1 or 2). 

For each of the remaining student records, the ID field is determined by the previous student’s ID plus the return value of the random integer generator. For example, assuming that the 3rd student ID is 5, and that 2 is returned as a result of the random integer generator, the 4th student ID can be then determined as 5 + 2 = 7. 

Each time when a new student record is generated, insert it into your data set. 

note the a record includes an id and an age
*/

int main (void){
  int randAge, randID=0, records=1, operation, IDsearch, DEL;
  SET *sp;
  puts("This program is automatic. This program will keep running until there are 3000 student records created. Once you press any key the program will commence");
  getchar();
  sp=createDataSet(MAX);
  while(records<1001){
    puts("\n");
    randAge=18+rand()%13;//18+0 to 18+12
    randID=randID+ 1 + rand()%2;//old ID+1 or old ID +2
    insertion(sp, randAge, randID);
    records++;
    printf("ID: %d Age: %d\n", randID, randAge);
  }
  while(records < MAX){
    operation= rand()%5;//make it 20% likely to search except when need to delete
    puts("\n");
    //printf("\n\noperation: %d\n", operation);
    switch(operation){
      case 0: //add new
            randID= randID + 1 + rand()%2;//create a new ID 
            randAge= 18 + rand()%13;
            insertion(sp, randAge, randID);
            records++;
            break;
      case 1: //search then delete
                IDsearch= rand()%randID +1;//this will make it so that it is never ID 0
                printf("Searching for ID %d to delete\n", IDsearch);
                DEL=searchID(sp, IDsearch);
                if(DEL){
                  deletion(sp, DEL);
                  records--;
                }
              break;
      case 2:
      case 3:
      case 4: //search ID only
              IDsearch= rand()%randID +1;
              printf("Only searching for %d\n", IDsearch);
              DEL=searchID(sp, IDsearch);//note no actual deleting takes place
              break;
      default: 
        puts("INVALID OPERATION");
    }
    
  }
  puts("End of Program Demonstration. Destroying Set");
  destroyDataSet(sp);
}

