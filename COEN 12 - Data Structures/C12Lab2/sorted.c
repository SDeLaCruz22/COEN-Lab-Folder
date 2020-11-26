# include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

typedef struct set{
    int count;
    int length;
    char **string;
} SET;

int Bsearch(SET *sp, char* x);

SET *createSet(int maxElts){//the set is an array and we are using a pointer to point to the array with dynamic sized elements
    SET *sp;
    sp=malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->count=0;
    sp->length=maxElts;
    sp->string=malloc(sizeof(char*)*maxElts);
    assert(sp->string!=NULL);
    return sp;
}

void destroySet(SET *sp){//this function simply frees any memory the set had
    assert(sp!=NULL);
    for(int i=0; i<sp->count; i++)
        free(sp->string[i]);
    free(sp->string);
    free(sp);
}

int numElements(SET *sp){//this will be called by at the end, it will showcase the number of unique words in the set
    return (sp->count);
}


void addElement(SET *sp, char *elt){ //add element will add a new element under the condition that it is a unique word
    int j, i;
    j=Bsearch(sp, elt);
    if(sp->string[j]==NULL){//we will occasionally run into nulls, nulls will result in a segmentation fault when using strcmp. In this case, a null index is good since the word will go into that empty space
        sp->string[j]=malloc(sizeof(char*)*50);
        strcpy(sp->string[j], elt);
        sp->count++;//count is incramented AFTER the new word is added. This is to reduce logical errors
        return;
    }
    else if(!strcmp(elt, sp->string[j]))//identical string found, add is not commenced
        return;
    
    else{//this will be the case for when the unique word is in the middle of the set, as such we must sort the elements after adding
        for(i=sp->count; i>=j; i--){//we are starting from the end of the set since only the strings after elt are going to be affected, this also makes it easier to code
            sp->string[i]=malloc(sizeof(char*)*50);
            if(i==j){//the index where the string should be, since everything after this has been moved, all this is is a simple replacement,
                strcpy(sp->string[i], elt);
                break;
            }
            strcpy(sp->string[i], sp->string[i-1]);//the normal process for every other string
        }
    sp->count++;//count is incramented after a word has been added
    }
}

char* findElement(SET *sp, char *elt){
    int j;
    j=Bsearch(sp, elt);
    if(sp->string[j]==NULL)//in case the string is not found
        return NULL;//will go to add
    if(strcmp(elt, sp->string[j])){//it will go to add if the strings are different, which means they are unique to each other
        return NULL;//goes to add
    }
    else//string is identical
        return sp->string[j];//goes to remove
}

int Bsearch(SET *sp, char* x){//it will either return the index of where the string should be in relation to the set or where its duplicate. As such we must make sure in the other functions that the elt and the index are not the same string before proceeding
    int lo=0, mid, hi;
    hi= sp->count;
    int i=0;
    if(hi==0)//start of code, only one space, and it will be null. strcmp gets really butthurt about it
        return 0;
    while(lo<=hi){
        mid=(lo+hi)/2;
        if(sp->string[mid]==NULL){//due to the nature of the algorithm, there will be times when the final space is the mid, as such we must spot this before we get a segmentation fault due to strcmp imcpompatiblity with NULL
            return mid;
        }
        else if(strcmp(x, sp->string[mid])>0){
            lo=mid+1;//+1
        }
        else if(strcmp(x, sp->string[mid])<0){
            hi=mid-1;
        }
        else
            return mid;
    }
    return lo;//this should not happen
}

void removeElement(SET *sp, char *elt){//since find has already testified that it is a duplicate, all we need to do is resort the set
    int j;
    j=Bsearch(sp, elt);
    for(int i=j; i<sp->count-1; i++){
            sp->string[i]=malloc(sizeof(char*)*50);
            strcpy(sp->string[i], sp->string[i+1]);
    }
        sp->count--;//and conversely we removed a word from the set, thus count is decramented
    return;
}

char **getElements(SET *sp){
    char**elts;
    assert(sp!=NULL);
    elts=malloc(sizeof(char*)*sp->count);
    assert(elts!=NULL);
    return memcpy(elts, sp->string, sizeof(char*)*sp->count);
}
