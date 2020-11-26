/*
 S T R I N G S
  IT WORKS YEEEEAAH
 */

#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

unsigned hashfun(SET *sp, int value, char *elt);
unsigned strhash(char *s);

typedef struct set{
    int count;
    int length;
    void **string;
    char *flags;
} SET;

SET *createSet(int maxElts){//the set is an array and we are using a pointer to point to the array with dynamic sized elements
    SET *sp;
	int i=0;
	printf("\n\nmax elts%d", maxElts);
    sp=malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->count=0;
    sp->length=maxElts;
    sp->string=malloc(sizeof(char*)*maxElts);
    assert(sp->string!=NULL);
	sp->flags=malloc(sizeof(char)*maxElts);
	assert(sp->flags!=NULL);
	while(i<=maxElts){
		printf("%d, ", i);
		sp->flags[i]='E';//sets all flag points to empty since none are in use
		i++;
	}
    return sp;
}

void destroySet(SET *sp){//this function simply frees any memory the set had
    assert(sp!=NULL);
	int i;
    for(i=0; i<sp->count; i++)
        free(sp->string[i]);
    free(sp->string);
	free(sp->flags);
    free(sp);
}

int numElements(SET *sp){//this will be called by at the end, it will showcase the number of unique words in the set
    return (sp->count);
}


void addElement(SET *sp, void *elt){ //add element will add a new element under the condition that it is a unique word
    unsigned j, i;
	puts("\n\nADD");
	i=strhash(elt)%sp->length;
    printf("initial hash value: %d flag: %c string: %s elt: %s\n", i, sp->flags[i], sp->string[i], elt);
	if(sp->flags[i]!='E')
		i=hashfun(sp, i, elt);//since find element already investigated this element, we don't have to check if there are duplicates, why does this give me a correct value
    printf("final hash value: %d flag: %c string: %s elt: %s\n", i, sp->flags[i], sp->string[i], elt);
    if(sp->flags[i]=='F'){
        puts("duplicate found, terminating add");
        return;//no add
    }
	sp->string[i]=malloc(sizeof(char*)*sizeof(elt));
    strcpy(sp->string[i], elt);
	sp->flags[i]='F';
	sp->count++;
}

char* findElement(SET *sp, void *elt){//if the initial flag was D and a duplicate exists, it does not go to delete
    unsigned j, i;
	puts("\n\nFIND");
    i=strhash(elt)%sp->length;
    printf("i %d, flag %c, string %s elt: %s\n", i, sp->flags[i], sp->string[i], elt);//E & D flags should show a null
	
    if(sp->flags[i]!='E'){//deleted or filled, might have to check the concurrent ones
		//printf("first strhash, check if same j %d, flag %c, string %s\n", i, sp->flags[i], sp->string[i]);
		i=hashfun(sp, i, elt);//happens if either a deleted index OR filled index that is not a duplicate
        //printf("after linear probing, check if same j %d, flag %c, string %s\n", i, sp->flags[i], sp->string[i]);
		if(sp->flags[i]=='F'){//if this passes, then the hash incrament returned an index with a duplicate, otherwise it will go to the final if statement
			puts("goes to remove2");
			return sp->string[i];//goes to remove
		}
    }
    /*if(sp->flags[i]!='F'){//empty or deleted flag, can happen after linear probing, this was og =='F'. it has no affect aparently
        puts("goes to add");
        return NULL;//goes to add
    }*/
    return 0;
}

unsigned strhash(char *s){//this will convert a string into a number
    unsigned hash=0;
	puts("strhash");
    while(*s!='\0')
        hash=31*hash + *s++;
    printf("hash indedx: %u\n", hash%18000);
    return hash;
}

unsigned hashfun(SET *sp, int value, char *elt){//this will take the number value and then use the size of the set to find an index
    unsigned m=sp->length, newhash, i=0; //value + i % m
	puts("\nlinear probing\n");
    while(sp->flags[i]){
        newhash=(value+i)%m;
        if(sp->flags[newhash]=='F' && !strcmp(sp->string[newhash], elt))//filled and the string inside that index is the same
            return newhash;//must check when returned
        if(sp->flags[newhash]=='E')
            return newhash;
        if(sp->flags[newhash]=='D'){//we could take this out, but if we wanted to conserve and make researching easier its best ot take this into account
            printf("Entering secondary search. Newhash: %d\n", newhash);
            unsigned search=newhash;
            while(sp->flags[search]!='E' && search<=m){//empty would mean t hat no linear probing could have been done for the value
                puts("searching");
                if(sp->flags[search]=='F' && !strcmp(sp->string[search], elt)){
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

void removeElement(SET *sp, void *elt){//since find has already testified that it is a duplicate, all we need to do is resort the set
    unsigned i;
	puts("\n\nREMOVE");
	i=strhash(elt)%sp->length;
	if(sp->flags[i]=='F' && strcmp(sp->string[i], elt)){//we know there is a duplicate, so now we have to do linear probing search
		i=hashfun(sp, i, elt);//now we should have the duplicate
	}
	else if(sp->flags[i]=='D'){
		i=hashfun(sp, i, elt);//must do this seperately because if it was a deleted node, it would receive a seg fault
	}
    printf("string %s at %d\n", sp->string[i], i);
    sp->string[i]=NULL;
	sp->count--;
	sp->flags[i]='D';
    printf("String after remove: %s\n", sp->string[i]);
}

char **getElements(SET *sp){
    char **elts;
    int i, j;
    assert(sp!=NULL);
    elts=malloc(sizeof(char*)*sp->count);
    assert(elts!=NULL);
    for(i=0, j=0; i<sp->length; i++){
        if(sp->flags[i]=='F')
            elts[j++]=sp->string[i];
    }
    return elts;
}
