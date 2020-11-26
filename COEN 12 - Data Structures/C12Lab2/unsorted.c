/*
 * File: 
 *
 * Copyright:	2017, Darren C. Atkinson
 *
 * Description: This file contains the public function and type
 *              declarations for a set abstract data type for strings.  A
 */             
# include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int search(SET *sp, char *elt);

typedef struct set{
	int count;
	int length;
	char **string;
} SET;

SET *createSet(int maxElts){//the set is an array and we are using a pointer to point to the array with dynamic sized elements
	//puts("set");
	SET *sp;
	sp=malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count=0;
	sp->length=maxElts;
	sp->string=malloc(sizeof(char*)*maxElts);
	assert(sp->string!=NULL);
	return sp;	
}

void destroySet(SET *sp){//this will free up the space the set had
   // puts("destroy");
	assert(sp!=NULL);
	for(int i=0; i<sp->count; i++)
		free(sp->string[i]);
	free(sp->string);
	free(sp);
}

int numElements(SET *sp){//will give the amount of words in the set
    //puts("num");
	return (sp->count);
}

void addElement(SET *sp, char *elt){//adds a string if its unique
    //puts("\nADD");
    int i;
    i=search(sp, elt);
    if(i!=-1)
        return;
	sp->string[sp->count]=malloc((strlen(elt)+1)*sizeof(char));
	strcpy(sp->string[sp->count], elt);
	sp->count++;//incramented after a word is added
    //printf("count: %d\n", sp->count);
}

void removeElement(SET *sp, char *elt){//this will search for the string and move any string afterwards back one space
    //puts("\nREMOVE");
	int i, j;
    i=search(sp, elt);//since find already confrimed there is a string inside the set, we dont have to make sure
    //printf("i: %d\tsp: %s\n", i, sp->string[i]);
    for(j=i; sp->string[j+1]; j++){//starts at the index
        sp->string[j]=malloc(100*sizeof(char));
        strcpy(sp->string[j], sp->string[j+1]);
    }
    //puts("removetest2");
    sp->count--;
}

char *findElement(SET *sp, char *elt){//will search if a elt is a unique word or not
    //puts("\nFIND");
    int j;
    j=search(sp, elt);
    if(j==-1)//no array index matches the new string, this will go to add
        return NULL;
    else
        return sp->string[j];//will go to remove
}

char **getElements(SET *sp){//puts all the words from the set into a string array
    //puts("gets");
	int i=0;
	int size=sp->count;
	char **new;
	new=malloc(sizeof(char*)*sp->length);	
	while(sp->string[i]){
		new[i]=malloc(10*sizeof(char));
		strcpy(new[i], sp->string[i]);
		i++;
	}
	return new;
}

int search(SET *sp, char *elt){//returns the index of a string
   // puts("\tSEARCH");
    int i=0;
    if(sp->string[i]==NULL)
        return -1;
    while(sp->string[i]){
        if(!strcmp(elt, sp->string[i])){
          //  printf("i: %d\tsp: %s\telt: %s\n", i, sp->string[i], elt);
            return i;
        }
        i++;
    }
    return -1;
}

