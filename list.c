#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "board.h"

/* Item Functions */

Item *nodeAlloc()
{
  Item *node;

  node = (Item *) malloc( sizeof(Item) );
  assert(node);

  node->parent = NULL;
  node->prev = NULL;
  node->next = NULL;
  node->f = node->g = node->h = (double)0.0;

  return node;
}

void freeItem( Item *node )
{
  if (node && node->board) free(node->board);
	if (node) free(node);
}


void initList( list_t *list_p )
{
	assert(list_p);

	list_p->numElements = 0;
	list_p->first = NULL;
	list_p->last = NULL;
}

int listCount( list_t *list )
{
	return list->numElements;
}

static int max(int a, int b){
  if(a>b) return a;
  return b;
}
// return an item with corresponding board , or null
Item* onList( list_t *list, char *board)
{	
	Item *currentItem = list->first;
	while (currentItem != NULL)
	{
		int maxPos = 0;
		int maxNumber = 0;
		int maxPos2 = 0;
		int maxNumber2 = 0;
		for (int i=0; i<MAX_BOARD; i++) {
			if(max(maxNumber,currentItem->board[i]) > maxNumber) maxPos=i;
			maxNumber = max(maxNumber,currentItem->board[i]);
			if(max(maxNumber2,board[i]) > maxNumber) maxPos2=i;
			maxNumber2 = max(maxNumber,board[i]);
		}
		if(maxPos == maxPos2) return currentItem;
		currentItem = currentItem->next;
	}
	return NULL;
	
}

// return and remove first item
Item *popFirst( list_t *list ) //
{
	Item *itemTmp = list->first;
	delList(list,itemTmp);
	return itemTmp;
}

// return and remove last item
Item *popLast( list_t *list ) //
{
	Item *itemTmp = list->last;
	delList(list,itemTmp);
	return itemTmp;
}

// remove a node from list
void delList( list_t *list, Item *node) {
	if(node->next != NULL) node->next->prev=node->prev;
	else{
		list->last = node->prev;
	}
	if(node->prev != NULL) node->prev->next=node->next;
	else{
		list->first = node->next;
	}
	list->numElements--;
}

// return and remove best item with minimal f value
Item *popBest( list_t *list ) // and remove the best board from the list.
{
	Item *min = list->first;
	Item *currentItem = list->first;
	while (currentItem != NULL)
	{
		if(currentItem->f < min->f){
			min = currentItem;
		}
		currentItem = currentItem->next;
	}
	delList(list,min);
	return min;
}

 // add item in top
void addFirst( list_t *list, Item *node ) // add in head
{
	if(list->last == NULL) list->last = node; 
	node->next = list->first;
	list->first = node;
	if(node->next!=NULL) node->next->prev = node;
	list->numElements++;
}

 // add item in queue
void addLast( list_t *list, Item *node ) // add in tail
{
	if(list->first == NULL) list->first=node;
	node->prev = list->last;
	list->last = node;
	if(node->prev!=NULL) node->prev->next = node;
	list->numElements++;
}

void cleanupList( list_t *list )
{
	Item *currentItem = list->first;
	while (currentItem != NULL)
	{
		Item *tmp = currentItem;
		currentItem = currentItem->next;
		freeItem(tmp);
	}
}

void printList( list_t list ) {
	Item *item = list.first;
  	while (item) {
    	printf("%.2f [%s] - ", item->f, item->board);
    	item = item->next;
  	}
  	printf(" (nb_items: %d)\n", list.numElements);
}


// TEST LIST

// int main()
// {
//   	Item *item;
// 	char str[3];

// 	list_t openList;

// 	initList( &openList );

// 	for (int i=0; i<10; i++) {
// 		item = nodeAlloc();
// 		item->f = i;
// 		sprintf(str, "%2d", i);
//         item->board = strdup(str);
// 		addLast( &openList, item );
// 	}

// 	for (int i=20; i<25; i++) {
// 		item = nodeAlloc();
// 		item->f = i;
// 		sprintf(str, "%2d", i);
// 		item->board = strdup(str);
// 		addFirst( &openList, item );
// 	}	
// 	printList(openList);
// 	printf("\n");
// 	Item *node = popBest( &openList );
// 	printf("best node = %.2f\n", node->f);
// 	printList(openList);
// 	printf("\n");

// 	strcpy(str, "23");
// 	node = onList(&openList, str);
// 	if (node) printf("found %s: %.2f!\n", str, node->f); 
// 	printList(openList);
// 	printf("\n");

// 	node = popFirst(&openList);
	
// 	item = nodeAlloc();
//     item->f = 50;
//     sprintf(str, "50");
//     item->board = strdup(str);
//     addLast( &openList, item );

// 	node = popFirst(&openList);
// 	if (node) printf("first: %.2f\n", node->f); 
// 	printList(openList);
//     printf("\n");

// 	node = popLast(&openList);
// 	if (node) printf("last: %.2f\n", node->f); 
// 	printList(openList);
//     printf("\n");

// 	printf("clean\n");	
// 	cleanupList(&openList);
// 	printList(openList);
// 	printf("\n");
  
// 	return 0;
// }