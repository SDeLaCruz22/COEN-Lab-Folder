/*ss
 * File:        set.h
 *
 * Copyright:	2017, Darren C. Atkinson
 *
 * Description: This file contains the public function and type
 *              declarations for a set abstract data type for strings.  A
 *              set is an unordered collection of distinct elements.
 */

# ifndef SET_H
# define SET_H

typedef struct set{
	int count;
	int length;
	char **string;
} SET;

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

void destroySet(SET *sp){
	free(sp);
}

int numElements(SET *sp){
	while(sp->string){
		if(sp->string[i]!=NULL)
			sp->count++;
	}
	return (sp->count);
}

void addElement(SET *sp, char *elt){//does not add a new element to already preexisting
	strcpy(sp->string[count-1], elt);
}

void removeElement(SET *sp, char *elt){
	int i=0, j;
	while(sp->string){
		if(!strcmp(sp->string[i], elt)){
			for(j=i;j<sp->count; j++){
				strcpy(sp->string[j+1], sp->string[j]);
				//if(j==count-1) want to see if this is necessary
			}
		}
		i++;
	}
}

char *findElement(SET *sp, char *elt){
	int i=0;
	while(sp->string){
		if(!strcmp(sp->string[i], elt)){
			return sp->string[i];	
		}
		i++;
	}
	return NULL;//this should only happen if no return happens in the loop
}

char **getElements(SET *sp){
	int i=0;
	//size=count;
	char *new[count];	
	whie(sp->string){
		strcpy(new[i], sp->string[i]);
		i++;
	}
	return new;
}

# endif /* SET_H */


