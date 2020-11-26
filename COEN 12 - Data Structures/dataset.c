//LINKED LIST ONE
#include "dataset.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct list{
  int count;
  int minAge;
  int maxAge;//this will make it easy for Max age gap
  struct node *head;//the dummy node
} LIST;

typedef struct node{
  int age;
  int id;
  struct node *next;//connecting each node to 2 other nodes
  struct node *prev;
} NODE;

LIST *createDataSet(int size){//will possibly have a structure inside of it for name and id
  struct list *lp;
  lp=malloc(sizeof(struct list));
  assert(lp!=NULL);
  lp->count=0;
  lp->head=malloc(sizeof(struct node));
  assert(lp->head!=NULL);
  lp->head->prev=lp->head;
  lp->head->next=lp->head;//these two lines make it a circular linked list
  lp->minAge=31;
  lp->maxAge=0;//reversing these two will make it easy for logic
  return lp;
}

void destroyDataSet(LIST *lp){
  assert(lp!=NULL);
  NODE *pDel;
  NODE *pPrev=lp->head->prev;//destroying set from the back end
  do{//delete the nodes from the back up to the front
    pDel=pPrev;
    pPrev=pDel->prev;
    free(pDel);
  }
  while (pDel!=lp->head);
  free(lp);
}

void searchAge(LIST *lp, int AGE){//we will also print in this
  NODE *pCheck;//pointer to node in list
  int agefound=0;
  pCheck=lp->head->next;
  printf("Student IDs at the age of %d\n", AGE);
  while(pCheck->id){//checking all the nodes and since we started right after the dummy node, when the id data is NULL that is when we know we are at the dummy node
    if(pCheck->age==AGE){
      printf("ID: %d\n", pCheck->id);
      agefound++;
    }
    pCheck=pCheck->next;
  }
  if(agefound==0)
    puts("No students with that age are found");

  printf("%d students at the age of %d\n", agefound, AGE);
}

NODE *searchID(LIST *lp, int ID){
  NODE *fNext;
  NODE *bPrev;
  int newcount=0;
  fNext=lp->head->next;//first data node
  bPrev=lp->head->prev;//last data node
  while(newcount<=(lp->count)/2+.5){ //the .5 will ensure that it will round to the highest integer if needed. This will make the search at worst O(n/2) which is still O(n)
    if(fNext->id==ID){//if forward search finds it first
      printf("ID found\nStudent ID: %d Age: %d\n", fNext->id, fNext->age);
      return fNext;
    }
    if(bPrev->id==ID){//if backward search finds it first
      printf("ID found\nStudent ID: %d Age: %d\n", bPrev->id, bPrev->age);
      return bPrev;
    }
    bPrev=bPrev->prev;
    fNext=fNext->next;
    newcount++;
  }
  puts("ID not found");
  return NULL;
}

void deletion(LIST *lp, NODE *pDel){//pDel will be given from the search function
  NODE *pPrev;
  NODE *pNext;
  pNext=pDel->next;//node after the pDel
  pPrev=pDel->prev;//node before pDel
  pPrev->next=pNext;
  pNext->prev=pPrev;//readjust the pointers so that pDel can be removed without loss of struture
  free(pDel);
  lp->count--;
  puts("Deletion Success");
}

void insertLast(LIST *lp, int AGE, int ID){//since the random number generator will be in ascending order, we will only add from the back
  struct node *new;//new node, not a pointer
  printf("Inserting new ID %d\n", ID);
  NODE *pPrev;
  NODE *pNext;
  new=malloc(sizeof(struct node));
  pPrev=lp->head->prev;//since we are adding to the back, we need to know what the last data node is
  pNext=lp->head;//the dummy node is the front node
  new->age=AGE;
  if(new->age > lp->maxAge)
    lp->maxAge=new->age;
  if(new->age < lp->minAge)
    lp->minAge=new->age;
  new->id=ID;
  new->next=pNext;//assign the pointers so that new is part of the linked list
  new->prev=pPrev;
  pNext->prev=new;
  pPrev->next=new;
  lp->count++;
  puts("Insertion Success");
}

void maxAgeGap(LIST *lp){//this will just print the max age gap. We recorded what the max and min ages are while inserting
  printf("\n\nMax Age: %d\nMin Age: %d\nAge Gap: %d\n", lp->maxAge, lp->minAge, lp->maxAge - lp->minAge);
}
