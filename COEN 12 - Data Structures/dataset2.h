#ifndef DATASET_H
#define DATASET_H

/*
Application 2:
Assume that the college takes very few transfer students and has most of its students stay for at least one year (Hints: no frequent insertion and deletion operations).

Hash table, BST

Hashtable, we just have to worry about implmenting the first 1000 and then (note the first program ran about 5000 times, and it really is about 10%)

 And the maximum student number is given. But it does require a lot of search operations. Specifically, all of the searches are based on student IDs. The major interfaces provided by your code should include createDataSet, destroyDataSet, searchID, insertion, deletion. 

*/

typedef struct set SET;

SET *createDataSet(int size);//will possibly have a structure inside of it for name and id

void destroyDataSet(SET *sp);

int searchID(SET *sp, int ID);

void insertion(SET *sp, int AGE, int ID);

int probe(SET *sp, int ID);

void deletion(SET *sp, int del);

#endif
