#include <stdio.h>
#include <stdlib.h>

typedef struct set{//I want a dynamic sized array. There shouldn't be duplicates in the text files
    int count;
    int length;//we are expecintg like 1.8 mil
    int **data;//we will be using this to sort
    void **name;//this is to just carry the string names
    int (*compare)();
}SET;

SET *createSet(int maxElts, int (*compare)()){
    SET *sp;
    sp=malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->count=0;
    sp->length=maxElts;
    sp->name=malloc(sizeof(char*)*maxElts);
    assert(sp->name!=NULL);
    sp->data=malloc(sizeof(int)*maxElts);
    assert(sp->data!=NULL);
    sp->compare=compare;
}

void AddElts(int value, void *string){//here we add all the stuff in the array. We dont need to find duplicates since the text shouldn't have duplicates
    
}
