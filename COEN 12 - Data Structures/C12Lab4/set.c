/*
 GENERIC
  LINKED LIST
 
 gcc -o parity set.c list.c parity.c
 gcc -o unique set.c list.c unique.c
 
 Professor Loony also thinks your hashing knowledge is somewhat limited, so he wants you to implement a hashtable withchainingused to resolve collisions. Rather than each slot in the hash table
 holding an element, it holdsa pointer to a list.  The lists themselves hold the elements.  For example, to add an element to our set, we simplyhash the element to its appropriate list and then use
 our list ADT functions to check if the value is already presentin the list, and if not then add the item. The list ADT does all the work for us. Our hash table is only responsible forpicking the
 appropriate list on which to operate.
 
 */

#include "set.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

unsigned hashfun(SET *sp, int value, void *elt);

typedef struct node{//carries list and the pointers to adjacent structs
    void *data;
    struct node *next;
    struct node *prev;
}NODE;

typedef struct set{
    int count;
    int length;
    LIST **list;//array of lists
    int (*compare)();
    unsigned (*hash)();
} SET;

SET *createSet(int maxElts, int(*compare)(), unsigned (*hash)()){//the set is an array and we are using a pointer to point to the array with dynamic sized elements
    SET *sp;
    int i=0;
    sp=malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->count=0;
    sp->length=maxElts;
    sp->list=malloc(50*maxElts);
    assert(sp->list!=NULL);
    sp->hash=hash;
    sp->compare=compare;//initialize the strcmp to this pointer
    return sp;
}

void destroySet(SET *sp){//this function simply frees any memory the set had
    assert(sp!=NULL);
    int i;
    free(sp->list);
    free(sp);
}

int numElements(SET *sp){//this will be called by at the end, it will showcase the number of unique words in the set
    return (sp->count);
}


void addElement(SET *sp, void *elt){ //add element will add a new element under the condition that it is a unique word, need to incrament both
    unsigned i;
    void* check;
    i=(sp->hash(elt))%sp->length;//the hash index
    if(sp->list[i]==NULL)//no linked list, empty index.
        sp->list[i]= createList(sp->compare);//this is the weird step
    check=findItem(sp->list[i], elt);
    if(check!=NULL)//this part of the function is used by uniqe since unique doesn't have a remove
        return;
    addLast(sp->list[i], elt);// doesn't matter if added first or last
    sp->count++;
}

void* findElement(SET *sp, void *elt){//if the initial flag was D and a duplicate exists, it does not go to delete
    unsigned i;
    void* check;
    i=sp->hash(elt)%sp->length;//initial hash index
    if(sp->list[i]==NULL)
        return NULL;//cant find an item in empty list
    check= findItem(sp->list[i], elt);//if it is NULL then no duplicate found, goes to add, otherwise goes to remove
    return check;//will either be a null or string
}

void removeElement(SET *sp, void *elt){//since find has already testified that it is a duplicate, all we need to do is resort the set
    unsigned i;
    i=sp->hash(elt)%sp->length;
    removeItem(sp->list[i], elt);//no other logic needed since find elements found a duplicate
    sp->count--;
}

void *getElements(SET *sp){
    void **elts;
    void **new;//this will be the pointer returned by getItems
    int i, j=0, k;//one for the for loop, one for elts array and one for the new array
    for(i=0; i<sp->length; i++){
        if(sp->list[i]!=NULL){//must have the dummy node or elements
            k=0;//refreshed after every outerloop
            new=getItems(sp->list[i]);
            while(new[k]){//inner loop, as long as there is an element inside new[i]
                elts[j]=new[k];//copy the data
                k++;//increase the index
                j++;//increase the index, this does not refresh since thill will be used in the main functions
            }
        }
    }
    return elts;
}
