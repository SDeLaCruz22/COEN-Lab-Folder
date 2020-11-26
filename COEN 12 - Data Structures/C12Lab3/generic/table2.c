/*
 GENERIC


sss

 */

#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

unsigned hashfun(SET *sp, int value, void *elt);

typedef struct set{
    int count;
    int length;
    void **data;
    char *flags;
    int (*compare)();
    unsigned (*hash)();
} SET;

SET *createSet(int maxElts, int(*compare)(), unsigned (*hash)()){//the set is an array and we are using a pointer to point to the array with dynamic sized elements
    SET *sp;
    int i=0;
    //printf("\n\nmax elts%d", maxElts);
    sp=malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->count=0;
    sp->length=maxElts;
    sp->data=malloc(50*maxElts);
    assert(sp->data!=NULL);
    sp->flags=malloc(sizeof(char)*maxElts);
    assert(sp->flags!=NULL);
    sp->hash=hash;
    sp->compare=compare;//initialize the strcmp to this pointer
    while(i<=maxElts){
        ////printf("%d, ", i);
        sp->flags[i]='E';//sets all flag points to empty since none are in use
        i++;
    }
    return sp;
}

void destroySet(SET *sp){//this function simply frees any memory the set had
    assert(sp!=NULL);
    int i;
    ////puts("\n\n\nDESTROY\n\n");
    /*for(i=0; i<sp->count; i++){
        if(sp->flags[i]=='F'){
            
        }
    }*/
    ////puts("destroy");
    free(sp->data);
    free(sp->flags);
    free(sp);
}

int numElements(SET *sp){//this will be called by at the end, it will showcase the number of unique words in the set
    return (sp->count);
}


void addElement(SET *sp, void *elt){ //add element will add a new element under the condition that it is a unique word
    unsigned j, i;
    ////puts("\n\nADD");
    i=(sp->hash(elt))%sp->length;//hash value of string divided by the modular
    ////printf("initial hash value: %d flag: %c\n", i, sp->flags[i]);
    if(sp->flags[i]!='E')//needs to check for duplicate
        i=hashfun(sp, i, elt);//this will give us the final hash index. No more conditions need to be applied since find element has already checked for them
    ////printf("final hash value: %d flag: %c\n", i, sp->flags[i]);
    if(sp->flags[i]=='F'){//this is the duplicate. Necessary statement for unique
        ////puts("duplicate found, terminating add");
        return;//does not add
    }
    sp->data[i]=malloc(50*sizeof(elt));//it passes the test and is added to the set
    sp->data[i]=elt;
    sp->flags[i]='F';
    sp->count++;
}

unsigned hashfun(SET *sp, int value, void *elt){//this will take the number value and then use the size of the set to find an index
    unsigned m=sp->length, newhash, i=0; //value + i % m
    ////puts("\nlinear probing\n");
    while(sp->flags[i]){//as long as the flag array exists
        newhash=(value+i)%m;//this will be the first thing it will do, it will linear probe every time
        if(sp->flags[newhash]=='F' && !sp->compare(sp->data[newhash], elt))//filled and the string inside that index is the same
            return newhash;//must be  check when returned
        if(sp->flags[newhash]=='E')//found a spot and no duplicate found between its original value and this empty slot
            return newhash;
        if(sp->flags[newhash]=='D'){//we could take this out, but if we wanted to conserve and make researching easier its best ot take this into account
            ////printf("Entering secondary search. Newhash: %d\n", newhash);
            unsigned search=newhash;//do a secondary search. Keep deleted spot if we can still use it
            while(sp->flags[search]!='E' && search<=m){//empty would mean t hat no linear probing could have been done for the value
                ////puts("searching");
                if(sp->flags[search]=='F' && !sp->compare(sp->data[search], elt)){
                    //printf("new search index %u\n", search);
                    return search;
                }
                search++;//we want to make sure there isn't a dupliate in the hash table after a deleted node
            }
            ////puts("search unsucessful,returning newhash");
            return newhash;//no filled spot matches, we take the first deleted spot
        }
        i++;
    }
    return -1;//should never happen
}

void* findElement(SET *sp, void *elt){//if the initial flag was D and a duplicate exists, it does not go to delete
    unsigned i;
    int j;
    ////puts("\n\nFIND");
    i=sp->hash(elt)%sp->length;//initial hash index
    //j=(*sp->compare)(sp->data[i], elt);
    ////printf("first strhash, check if same i %d, flag %c, compare: \n", i, sp->flags[i]);
    if(sp->flags[i]=='F'){//must check if there is a duplicate
        j=sp->compare(sp->data[i], elt);
        //printf("compare: %d", j);
        if(!j)
            return sp->data[i];
    }
    if(sp->flags[i]!='E'){//deleted or filled, might have to check the concurrent ones
        i=hashfun(sp, i, elt);//happens if either a deleted index OR filled index that is not a duplicate
        //printf("after linear probing, check if same j %d, flag %c, string \n", i, sp->flags[i]);
        if(sp->flags[i]=='F'){//if this passes, then the hash incrament returned an index with a duplicate, otherwise it will go to the final if statement
            //puts("goes to remove2");
            return sp->data[i];//goes to remove
        }
    }
    if(sp->flags[i]!='F'){//empty or deleted flag, can happen after linear probing
        //puts("goes to add");
        return sp->data[i];//goes to remove
    }
    return NULL;
}

void removeElement(SET *sp, void *elt){//since find has already testified that it is a duplicate, all we need to do is resort the set
    unsigned i;
    //puts("\n\nREMOVE");
    i=sp->hash(elt)%sp->length;
    //printf("initial hash value: %d\n", i);
    if(sp->flags[i]!='E'){//we know there is a duplicate, so now we have to do linear probing search
        i=hashfun(sp, i, elt);//now we should have the duplicate
    }
    //printf("hash flag: %c\n", sp->flags[i]);
    sp->data[i]=NULL;//deleting the information
    sp->count--;
    sp->flags[i]='D';
    //printf("data after remove: \n");
}

void *getElements(SET *sp){
    void **elts;
    int i, j;
    assert(sp!=NULL);
    elts=malloc(sizeof(void*)*sp->count);
    assert(elts!=NULL);
    for(i=0, j=0; i<sp->length; i++){
        if(sp->flags[i]=='F')
            elts[j++]=sp->data[i];
    }
    return elts;
}
