#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dataset2.h"

typedef struct set{//hashtable    
  int count;    
  int length;    
  int *id;
  int *age;
  char *flag;//set null as empty
} SET;

typedef struct set SET;

SET *createDataSet(int size){//will possibly have a structure inside of it for name and id
  SET *sp;
  sp=malloc(sizeof(SET));
  assert(sp!=NULL);
  sp->count=0;
  sp->length=size;
  sp->id=malloc(sizeof(int*)*size);//assign memory to all elements of the set
  assert(sp->id!=NULL);
  sp->age=malloc(sizeof(int*)*size);
  sp->flag=malloc(sizeof(char)*size);
  assert(sp->age!=NULL);
  return sp;
}

void destroyDataSet(SET *sp){
  assert(sp!=NULL);
  free(sp->id);
  free(sp->age);
  free(sp);
}

int searchID(SET *sp, int ID){
  int i;
  i=probe(sp, ID);
  if(sp->id[i]==ID){
    printf("ID Found: ID %d\tAge:%d\n", sp->id[i], sp->age[i]);
    return i;//goes to delete
  }
  puts("ID not found");
  return 0;//this will indicate the main function that there is no index that has the ID
}

void insertion(SET *sp, int AGE, int ID){//no need to check if there is a duplicate. An ID will always be unique
  printf("Inserting new ID %d into system\n", ID);
  int i;
  i=probe(sp, ID);
  sp->id[i]=ID;
  sp->age[i]=AGE;
  sp->flag[i]='F';
  assert(sp->id[i]!=0);
  puts("Insertion Complete");
}

int probe(SET *sp, int ID){
  int i, j;
  for(i=0; i<sp->length-1; i++){
    j= (ID+i)%sp->length;//hashing function
    if(!sp->flag[j] || sp->id[j]==ID){//either it is a free space or identical. This will make sure that even if it was a previously deleted node, it will return the best fit
     // printf("number of loops %d, index %d flag %c\n", i, j, sp->flag[j]);
      return j;
    }
  }
  //printf("number of loops %d j %d flag %c\n", i+1, j, sp->flag[j]);
  assert(sp->id[j]!=ID);//countermeasure for logical error
  return 0;
}

void deletion(SET *sp, int del){
  puts("Beginning Deletion");
  sp->id[del]=0;//NULLS wont work, but luckily there is no 0 ID or a 0 age
  sp->age[del]=0;
  sp->flag[del]='D';//
  sp->count--;
  puts("Deletion Complete");
}
