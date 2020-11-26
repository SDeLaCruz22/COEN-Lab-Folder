/*
 GENERIC
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
    printf("\n\nmax elts%d", maxElts);
    sp=malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->count=0;
    sp->length=maxElts;
    sp->data=malloc(50*maxElts);
    assert(sp->data!=NULL);
    sp->flags=malloc(sizeof(char)*maxElts);
    assert(sp->flags!=NULL);
    sp->hash=hash;
    sp->compare=compare;
    while(i<=maxElts){
        //printf("%d, ", i);
        sp->flags[i]='E';//sets all flag points to empty since none are in use
        i++;
    }
    return sp;
}

void destroySet(SET *sp){//this function simply frees any memory the set had
    assert(sp!=NULL);
    int i;
    for(i=0; i<sp->count; i++)
        free(sp->data[i]);
    free(sp->data);
    free(sp->flags);
    free(sp);
}

int numElements(SET *sp){//this will be called by at the end, it will showcase the number of unique words in the set
    return (sp->count);
}


void addElement(SET *sp, void *elt){ //add element will add a new element under the condition that it is a unique word
    unsigned j, i;
    puts("\n\nADD");
    i=(sp->hash(elt))%sp->length;
    printf("initial hash value: %d flag: %c\n", i, sp->flags[i]);
    if(sp->flags[i]!='E')
        i=hashfun(sp, i, elt);
    printf("final hash value: %d flag: %c\n", i, sp->flags[i]);
    if(sp->flags[i]=='F'){
        puts("duplicate found, terminating add");
        return;//no add
    }
    sp->data[i]=malloc(50*sizeof(elt));
    sp->data[i]=elt;
    sp->flags[i]='F';
    sp->count++;
}

unsigned hashfun(SET *sp, int value, void *elt){//this will take the number value and then use the size of the set to find an index
    unsigned m=sp->length, newhash, i=0; //value + i % m
    puts("\nlinear probing\n");
    while(sp->flags[i]){
        newhash=(value+i)%m;
        if(sp->flags[newhash]=='F' && !sp->compare(elt, sp->data))//filled and the string inside that index is the same
            return newhash;//must check when returned
        if(sp->flags[newhash]=='E')
            return newhash;
        if(sp->flags[newhash]=='D'){//we could take this out, but if we wanted to conserve and make researching easier its best ot take this into account
            printf("Entering secondary search. Newhash: %d\n", newhash);
            unsigned search=newhash;
            while(sp->flags[search]!='E' && search<=m){//empty would mean t hat no linear probing could have been done for the value
                puts("searching");
                if(sp->flags[search]=='F' && !sp->compare(elt, sp->data)){
                    printf("new search index %u\n", search);
                    return search;
                }
                search++;//we want to make sure there isn't a dupliate in the hash table after a deleted node
            }
            puts("search unsucessful,returning newhash");
            return newhash;//no filled spot matches, we take the first deleted spot
        }
        i++;
    }
    return -1;//no space??
}

void* findElement(SET *sp, void *elt){//if the initial flag was D and a duplicate exists, it does not go to delete
    unsigned i;
    int j;
    puts("\n\nFIND");
    i=sp->hash(elt)%sp->length;
    //j=(*sp->compare)(sp->data[i], elt);
    printf("first strhash, check if same i %d, flag %c, compare: \n", i, sp->flags[i]);
    if(sp->flags[i]=='F'){
        j=sp->compare(sp->data[i], elt);
        printf("compare: %d", j);
        if(!j)
            return NULL;
    }
    if(sp->flags[i]!='E'){//deleted or filled, might have to check the concurrent ones
        i=hashfun(sp, i, elt);//happens if either a deleted index OR filled index that is not a duplicate
        printf("after linear probing, check if same j %d, flag %c, string \n", i, sp->flags[i]);
        if(sp->flags[i]=='F'){//if this passes, then the hash incrament returned an index with a duplicate, otherwise it will go to the final if statement
            puts("goes to remove2");
            return sp->data[i];//goes to remove
        }
    }
    if(sp->flags[i]!='F'){//empty or deleted flag, can happen after linear probing
        puts("goes to add");
        return NULL;//goes to add
    }
    return 0;
}

void removeElement(SET *sp, void *elt){//since find has already testified that it is a duplicate, all we need to do is resort the set
    unsigned i;
    puts("\n\nREMOVE");
    i=sp->hash(elt);
    if(sp->flags[i]!='E'){//we know there is a duplicate, so now we have to do linear probing search
        i=hashfun(sp, i, elt);//now we should have the duplicate
    }
    puts("data");
    sp->data[i]=NULL;
    sp->count--;
    sp->flags[i]='D';
    printf("data after remove: \n");
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
