#include <stdio.h>
//#include "set.h"
#include "list.h"

//compile like so gc -o maze maze.c list.c -
//gcc -o radix radix.c list.c

struct LIST{
    int count;
    struct node *head;
    int (*compare)();
};

struct NODE{//carries data and the pointers to adjacent structs
    void *data;
    struct node *next;
    struct node *prev;
};

LIST *createList(int (*compare)){
    struct list *lp;
    lp=malloc(sizeof(struct list));
    assert(lp!=NULL);
    lp->count=0;
    lp->compare=compare;
    lp->head=maloc(sizeof(struct NODE));
    assert(lp->head!=NULL);
    lp->head->next=lp->head;//these 2 lines make a dummy node
    lp->head->prev=lp->head;
    return lp;
}

void destroyList(LIST *lp){
    assert(lp!=NULL);
    NODE *pDel;
    NODE *pPrev=lp->head->prev;
    do{
        pDel=pPrev;
        pPrev=pDel->prev;
        free(pDel);
    }
    while (pDel!=lp->head)
    free(lp);
}

int numItems(LIST *lp){//return the number of items in the list pointed to bylp
    return lp->count;
}

void addFirst(LIST *lp, void *item){//add item as the first item in the list pointed to bylp, the node "after" dummy node
    struct node *new;//new node
    NODE *pPrev;
    NODE *pNext;
    pPrev=lp->head;//prev pointer is now the dummy node x
    pNext=lp->head->next;//next pointer is the node after the dummy node, z
    new=malloc(sizeof(struct NODE));//allocated memory for a new node
    assert(new!=NULL);
    new->data= item;//added data to new node, now we have to put it in
    //what is prev and next?
    new->next=pPrev->next;//from x-> z to y->z, these might be wrong
    new->prev=pNext->prev;//from x <-z now x <-y
    pPrev->next=new;//now x->y
    pNext->prev=new;// from x <-z to y <-z
    lp->count++;
}

void addLast(LIST *lp, void *item){//add item as the last item in the list pointed to bylp, so the node "before" the dummy node
    struct node *new;//new node
    NODE *pPrev;
    NODE *pNext;
    pPrev=lp->head->prev;//prev pointer is now node before the dummy node, x
    pNext=lp->head;//next pointer is now the dummy node, z (x->z & x<-z)
    new=malloc(sizeof(struct NODE));//allocated memory for a new node
    assert(new!=NULL);
    new->data= item;//added data to new node, now we have to put it in
    //what is prev and next?
    new->next=pPrev->next;//from x-> z to y->z
    new->prev=pNext->prev;//from x <-z now x <-y
    pPrev->next=new;//now x->y
    pNext->prev=new;// from x <-z to y <-z
    lp->count++;
}

void *removeFirst(LIST *lp){//remove and return the first item in the list pointed to bylp; the list must not be empty
    NODE *pDEl;
    NODE *pPrev;
    NODE *pNext;
    pPrev=lp->head;
    pDel=pPrev->next;//the node after the dummy node is getting yeeted, x->y->z, y is pDel
    pNext=pDel->next;
    pPrev->next=pDel->next;// x-> (y->)z
    pNext->prev=pDel->prev;//x (<-y) <-z
    free(pDel);
}

void *removeLast(LIST *lp){//remove and return the last item in the list pointed to bylp; the list must not be empty
    NODE *pDEl;
    NODE *pPrev;
    NODE *pNext;
    pNext=lp->head;
    pDel=pNext->prev;//the node after the dummy node is getting yeeted, x->y->z, y is pDel
    pPrev=pDel->prev;
    pPrev->next=pDel->next;// x-> (y->)z
    pNext->prev=pDel->prev;//x (<-y) <-z
    free(pDel);
    
}

void *getFirst(LIST *lp){//return, but do not remove, the first item in the list pointed to bylp; the list must not be empty
    NODE *pGet;
    pGet=lp->head->next;
    return(pGet->data);
}

void *getLast(LIST *lp){//eturn, but do not remove, the last item in the list pointed to bylp; the list must not be empty
    NODE *pGet;
    pGet=lp->head->prev;
    return(pGet->data);
}

void removeItem(LIST *lp, void *item){//if item is present in the list pointed to by lp then remove it; the comparison function must not be NULL
    NODE *Del;
    NODE *pPrev;
    NODE *pNext;
    pDel=lp->head->next;
    while(pDel->prev!=lp->head){
        if(!lp->compare(item, pDel->data)){//duplicate found
            pPrev=pDel->prev;//sets up pointers
            pNext=pDel->next;
            pPrev->next=pDel->next;//x->z
            pNext->prev=pDel->prev;//x<-z
            free(pDel);
        }
        pDel=pDel->next;//goes to next node
    }
}

void *findItem(LIST *lp, void *item){//if item is present in the list pointed to by lp then return the matching item, otherwise returnNULL; the com-parison function must not beNULL
    NODE *pCheck;
    pCheck=lp->head->next;
    while(!pCheck->prev!=lp->head){
        if(lp->compare(item, pCheck->data))//duplicate found
            return pCheck->data;//goes to remove
        pCheck=pCheck->next;//goes to next node
    }
    return NULL;//no duplicate found goes to add
}

void *getItems(LIST *lp){//allocate and return an array of items in the list pointed to bylp
    void *new;
    puts("yeah idk");
}
