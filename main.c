/*
 * sorted-list.c
 */

#include	<string.h>
#include <stdio.h>
#include	"sorted-list.h"

int compareInts(void *p1, void *p2)
{
	int i1 = *(int*)p1;
	int i2 = *(int*)p2;

	return i1 - i2;
}

int compareDoubles(void *p1, void *p2)
{
	double d1 = *(double*)p1;
	double d2 = *(double*)p2;

	return (d1 < d2) ? -1 : ((d1 > d2) ? 1 : 0);
}

int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}

SortedListPtr SLCreate(CompareFuncT cf) {
	SortedListPtr s1 = (SortedListPtr) malloc(sizeof(struct SortedList));
	Node *head = (Node *) malloc(sizeof(struct Node));

	head->data = NULL;
	head->next = NULL;
   (*head).ptrCount = 1;

	s1->head = head;
	s1->cf = cf;
	(*s1).size = 0;

	return s1;
}

SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {
	SortedListIteratorPtr slip = (SortedListIteratorPtr) malloc(sizeof(struct SortedListIterator));
	slip->list = list;
	slip->curr = list->head;
   (*(list->head)).ptrCount++;
	return slip;
}

int SLInsert(SortedListPtr list, void *newObj) {

	if ((*list).size == 0) {
		(list->head)->data = newObj;
		(*list).size++;
      //printf("Z data is %d, size is %d\n", *((int *) newObj), (*list).size);
		return 1;
	}

	Node *newObjectNode = (Node *) malloc(sizeof(struct Node));
   newObjectNode->data = newObj;
   (*newObjectNode).ptrCount = 0;

	Node *curr = list->head;
   Node *temp = curr;
	CompareFuncT cf = list->cf;

	while (curr != NULL && cf(newObj, curr->data) < 0 ) {
      temp = curr;
      curr = curr->next;
      //printf("enters\n");
	}

   if (curr == list->head) {
      newObjectNode->next = curr;
      list->head = newObjectNode;
      (*newObjectNode).ptrCount++;
      //printf("A data is %d, size before insertion is %d\n", *((int *) newObj), (*list).size);
   } else if (curr != NULL) {
      temp->next = newObjectNode;
      newObjectNode->next = curr;
      (*newObjectNode).ptrCount++;
      //printf("B data is %d, size before insertion is %d\n", *((int *) newObj), (*list).size);
   } else {
	  temp->next = newObjectNode;
	  newObjectNode->next = NULL;
     (*newObjectNode).ptrCount++;
     //printf("C data is %d, size before insertion is %d\n", *((int *) newObj), (*list).size);
	}
   
   (*list).size++;
   return 1;
	
}

int SLRemove(SortedListPtr list, void *newObj) {

	if ((*list).size == 0) {
		return 0;
	}

   Node *curr = list->head;
   Node *temp = curr;
   CompareFuncT cf = list->cf;

   void *item = curr->data;

   while(curr != NULL && cf(newObj, item) != 0){
      temp = curr;
      curr = curr->next;
      item = curr->data;
      if (cf(item, newObj) < 0) {
         return 0;
      }
   }

   if (curr == list->head) {
		temp = curr->next;
		list->head = temp;
      (*curr).ptrCount--;
      if ((*curr).ptrCount == 0) {
		   free(curr->data);
		   free(curr);
      }
		return 1;
	}

   temp->next = curr->next;
   (*curr).ptrCount--;
   (*(temp->next)).ptrCount++;
   if ((*curr).ptrCount == 0) {
      free(curr->data);
      free(curr);
   }
   
   (*list).size--;
   return 1;

}

void *SLNextItem(SortedListIteratorPtr iter) {
   if (iter == NULL) {
      return NULL;
   }
	void *item;
   Node *temp;
	Node *node = iter->curr;
	if (node == NULL) {
		return NULL;
	}
   while ((*node).ptrCount == 1) {
      temp = node;
      node = node->next;
      free(temp->data);
      free(temp);
      iter->curr = node;
   }
	item = node->data;
	iter->curr = node->next;
   (*node).ptrCount--;
   if (iter->curr != NULL) {
      (*(iter->curr)).ptrCount++;
   }
	return item;
}

void SLDestroy(SortedListPtr list) {
   if (list == NULL) {
      return;
   }
   Node *curr = list->head;
   Node *temp = curr;
   while (curr != NULL) {
      curr = curr->next;
      free(temp->data);
	   free(temp);
      temp = curr;
   }
   free(list);
}

void SLDestroyIterator(SortedListIteratorPtr iter) {
   if (iter != NULL) {
      free(iter);
   }
}

int main()
{

	SortedListPtr list;
	SortedListIteratorPtr iterator;
	CompareFuncT cf;

	cf = &compareInts;
	
	list = SLCreate(cf);

	//Begin Testing

	int *a, *b, *c, *d, *e, *f, *g;
	int *n;
	a = (int *) malloc(sizeof(int));
	b = (int *) malloc(sizeof(int));
	c = (int *) malloc(sizeof(int));
	d = (int *) malloc(sizeof(int));
	e = (int *) malloc(sizeof(int));
	f = (int *) malloc(sizeof(int));
	g = (int *) malloc(sizeof(int));


   //Test 1a: Empty list
   printf("Test 1a: Empty list\n");
   iterator = SLCreateIterator(list);
   n = SLNextItem(iterator);
	while (n != NULL) {
		printf("%d\n", *n);
		n = SLNextItem(iterator);
	}

   //Test 1b: Removing from empty list
   printf("Test 1b: Remove from empty list\n");
   iterator = SLCreateIterator(list);
   *a = 1;
   SLRemove(list, a);
   n = SLNextItem(iterator);
	while (n != NULL) {
		printf("%d\n", *n);
		n = SLNextItem(iterator);
	}

   //Test 2a: Calling SLNextItem with NULL iterator
   printf("Test 2b: Call SLNextItem with NULL iterator\n");
   iterator = NULL;
   n = SLNextItem(iterator);
	while (n != NULL) {
		printf("%d\n", *n);
		n = SLNextItem(iterator);
	}
   
   //Test 2b: Destroy NULL iterator
   printf("Test2b: Destroy NULL iterator\n");
   iterator = NULL;
   SLDestroyIterator(iterator);

   //Test 2c: Destroy NULL list
   printf("Test 2c: Destroy NULL list\n");
   SortedListPtr alist = NULL;
   SLDestroy(alist);

   //Test 3a: Insert and Delete
   
   printf("Test 2: Inserting\n");

	*a = 1;
	*b = 2;
	*c = 3;
	*d = 4;
	*e = 5;
	*f = 6;
	*g = 7;

   printf("Items to be inserted: %d, %d, %d, %d, %d, %d, %d\n", *a, *b, *c, *d, *e, *f, *g);

	SLInsert(list, b);
	SLInsert(list, e);
	SLInsert(list, g);
	SLInsert(list, c);
	SLInsert(list, d);
	SLInsert(list, f);
	SLInsert(list, a);

   SLRemove(list, d);
   SLRemove(list, c);
   SLRemove(list, g);
   d = (int *) malloc(sizeof(int));
   *d = 4;
   SLInsert(list, d);

	iterator = SLCreateIterator(list);

	n = SLNextItem(iterator);
   printf("The sorted list is:\n");

	while (n != NULL) {
		printf("%d\n", *n);
		n = SLNextItem(iterator);
	}

	SLDestroy(list);
	SLDestroyIterator(iterator);

	return 1;

}
