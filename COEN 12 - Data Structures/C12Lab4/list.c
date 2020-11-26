#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"
#include "list.h"

//compile like so gcc -o maze maze.c list.c -lcurses
//gcc -o radix radix.c list.c                  ss

typedef struct list{
    int count;
    struct node *head;
    int (*compare)();
}LIST;

typedef struct node{//carries data and the pointers to adjacent structs
    void *data;
    struct node *next;
    struct node *prev;
}NODE;

LIST *createList(int (*compare)()){
    struct list *lp;
    lp=malloc(sizeof(struct list));
    assert(lp!=NULL);
    lp->count=0;
    lp->compare=compare;//initializes strcmp
    lp->head=malloc(sizeof(struct node));
    assert(lp->head!=NULL);
    lp->head->next=lp->head;//these 2 lines make a dummy node
    lp->head->prev=lp->head;
    return lp;
}

void destroyList(LIST *lp){
    assert(lp!=NULL);
    NODE *pDel;
    NODE *pPrev=lp->head->prev;//destroying set from the back end
    do{
        pDel=pPrev;
        pPrev=pDel->prev;
        free(pDel);
    }
    while (pDel!=lp->head);
    free(lp);
}

int numItems(LIST *lp){//return the number of items in the list pointed to bylp
    return lp->count;//returning the items in the list
}

void addFirst(LIST *lp, void *item){//add item as the first item in the list pointed to bylp, the node "after" dummy node
    struct node *new;//new node
    NODE *pPrev;
    NODE *pNext;
    pPrev=lp->head;//prev pointer is now the dummy node x
    pNext=lp->head->next;//next pointer is the node after the dummy node, z
    new=malloc(sizeof(struct node));//allocated memory for a new node
    assert(new!=NULL);
    new->data= item;//added data to new node, now we have to put it in
    new->next=pNext;//from x-> z to y->z,
    pNext->prev=new;// from x <-z to y <-z
    new->prev=pPrev;//from x <-z now x <-y
    pPrev->next=new;//now x->y
    lp->count++;
}

void addLast(LIST *lp, void *item){//add item as the last item in the list pointed to bylp, so the node "before" the dummy node
    //puts("\tADDLAST");
    struct node *new;//new node
    NODE *pPrev;
    NODE *pNext;
    new=malloc(sizeof(struct node));//allocated memory for a new node
    pPrev=lp->head->prev;//prev pointer is now node before the dummy node, x
    pNext=lp->head;//next pointer is now the dummy node, z (x->z & x<-z)
    assert(new!=NULL);
    new->data= item;//added data to new node, now we have to put it in
    new->next=pNext;//from x-> z to y->z, originally prev->next
    pNext->prev=new;// from x <-z to y <-z
    new->prev=pPrev;//from x <-z now x <-y
    pPrev->next=new;//now x->y
    lp->count++;
}

void *removeFirst(LIST *lp){//remove and return the first item in the list pointed to bylp; the list must not be empty
    ////puts("REMOVEFIRST");
    NODE *pDel;
    NODE *pPrev;
    NODE *pNext;
    void *value;
    pPrev=lp->head;
    pDel=pPrev->next;//the node after the dummy node is getting deleted, x->y->z, y is pDel
    pNext=pDel->next;//must be assigned after assgining pDel
    pPrev->next=pNext;// x-> (y->)z
    pNext->prev=pPrev;//x (<-y) <-z
    value=pDel->data;//we are going to return the value later so we must keep it
    assert(value!=NULL);
    free(pDel);
    lp->count--;//decraments the length of the list
    return value;
}

void *removeLast(LIST *lp){//remove and return the last item in the list pointed to bylp; the list must not be empty
    NODE *pDel;
    NODE *pPrev;//see my commeets in remove first, virtually the same
    NODE *pNext;
    void *value;
    pNext=lp->head;
    pDel=pNext->prev;//the node after the dummy node is getting deleted, x->y->z, y is pDel
    pPrev=pDel->prev;//must be declared affter pDel assignment
    pPrev->next=pNext;// x-> (y->)z
    pNext->prev=pPrev;//x (<-y) <-z
    value=pDel->data;
    free(pDel);
    lp->count--;
    return value;
}

void *getFirst(LIST *lp){//return, but do not remove, the first item in the list pointed to bylp; the list must not be empty
    NODE *pGet;
    pGet=lp->head->next;
    return(pGet->data);//returned the data of the first  node
}

void *getLast(LIST *lp){//eturn, but do not remove, the last item in the list pointed to bylp; the list must not be empty
    NODE *pGet;
    pGet=lp->head->prev;
    return(pGet->data);//same as getfirst but the last node
}

void removeItem(LIST *lp, void *item){//if item is present in the list pointed to by lp then remove it; the comparison function must not be NULL
    //puts("\tREMOVE ITEM");
    NODE *pDel;
    NODE *pPrev;
    NODE *pNext;
    pDel=lp->head->next;
    assert(pDel!=NULL);
    while(pDel->data!=NULL){
        if(!(lp->compare(item, pDel->data))){//duplicate found, strcmp returns a 0 if identical
            pPrev=pDel->prev;//sets up pointers
            pNext=pDel->next;
            pPrev->next=pNext;//x->z
            pNext->prev=pPrev;//x<-z
            free(pDel);
            lp->count--;//decrement length of list
            return;//nothing needs to be returned, this function terminates
        }
        pDel=pDel->next;//goes to next node
    }
}

void *findItem(LIST *lp, void *item){//if item is present in the list pointed to by lp then return the matching item, otherwise returnNULL; the com-parison function must not beNULL
    //puts("\tFIND ITEM");
    NODE *pCheck;
    int newcount=1;
    pCheck=lp->head->next;//node after dummy node
    while(newcount<=lp->count){
        if(!(lp->compare(item, pCheck->data))){//duplicate found
            return pCheck->data;//goes to remove
        }
        pCheck=pCheck->next;//goes to next node
        newcount++;
    }
    return NULL;//no duplicate found goes to add
}

void *getItems(LIST *lp){//allocate and return an array of items in the list pointed to bylp
    void **new;
    NODE *pNode;
    pNode=lp->head->next;//the node after the dummy node, this is count==1, if there is no nodes, then the count would be 0 and new is empty
    int i=1;
    while(i<=lp->count){//want to assign all the elements into an array
        new[i]=pNode->data;
        i++;
        pNode=pNode->next;//goes to each filled node 
    }
    return new;
}
