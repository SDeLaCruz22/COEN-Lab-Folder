#ifndef DATASET_H
#define DATASET_H

/*
Application 3:
Assume a new college that is expanding frequently and dramatically on its student amount. This leads to two consequences. 
First, accurately estimating the total number of students is extremely difficult.

Second, frequent insertions and deletions are performed. 

is a linked list the best for this? We have to search still even if "searches arent frequent" O(n) across the board

A BST might be really good here. We would need to figure out the root of the entire tree though. Mostly O(logn). Counting is least inefficient. 

A deque has the best insertion and deletion but we still have to search for specific values. (O(n) and O(1))

Hashtable has O(1) features. But I worry about hashing

In addition, the college frequently requires calculating the largest age gap among its students. 

Assume that search operations are not performed frequently. Your implementation has to support searches on either student ID or age. 

The major interfaces provided by your code should include createDataSet, destroyDataSet, searchAge, searchID, insertion, deletion, maxAgeGap.

*/

typedef struct list LIST;
typedef struct node NODE;

LIST *createDataSet(int size);//will possibly have a structure inside of it for name and id

void destroyDataSet(LIST *lp);

void searchAge(LIST *lp, int AGE);

NODE *searchID(LIST *lp, int ID);

void insertLast(LIST *lp, int AGE, int ID);

void deletion(LIST *lp, NODE *pDel);

void maxAgeGap(LIST *lp);

#endif
