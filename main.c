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
   (*head).deleted = 0;

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

   if (newObj == NULL) {
      return 0;
   }

	if ((*list).size == 0) {
		(list->head)->data = newObj;
      (*(list->head)).deleted = 0;
		(*list).size++;
      //printf("Z data is %d, size is %d\n", *((int *) newObj), (*list).size);
		return 1;
	}

	Node *newObjectNode = (Node *) malloc(sizeof(struct Node));
   newObjectNode->data = newObj;
   (*newObjectNode).ptrCount = 0;
   (*newObjectNode).deleted = 0;

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

  // void *item = curr->data;

   while(curr != NULL && cf(newObj, curr->data) != 0){
      temp = curr;
      curr = curr->next;
   }

   if (curr == NULL) {
      return 0;
   }

   if ((*list).size == 1) {   //Deleting from single-node list
      curr->data = NULL;
      (*curr).deleted = 1;
      (*list).size--;
      return 1;
   } 

   if (curr->next == NULL) {  //Deleting last element
      temp->next = NULL;
      (*curr).ptrCount--;
      if ((*curr).ptrCount == 0) {  //No iterator pointing to curr
         free(curr);
      } else {
         (*curr).deleted = 1;
      }
      (*list).size--;
      return 1;
   } 

   if (curr == list->head) {  //Deleting head
		temp = curr->next;
		list->head = temp;
      (*curr).ptrCount--;
      if ((*curr).ptrCount == 0) {
		   free(curr);
      } else {
         (*curr).deleted = 1;
      }
      (*list).size--;
		return 1;
	}

   temp->next = curr->next;
   (*curr).ptrCount--;
   (*(temp->next)).ptrCount++;
   if ((*curr).ptrCount == 0) {
      free(curr);
   } else {
      (*curr).deleted = 1;
   }
   
   (*list).size--;
   return 1;

}

void *SLNextItem(SortedListIteratorPtr iter) {
   if (iter == NULL) {
      return NULL;
   }
   if ((*(iter->list)).size == 0) { //Empty list
      return NULL;
   } 
	void *item;
   Node *temp;
	Node *node = iter->curr;
	if (node == NULL || node->data == NULL) {
		return NULL;
	}
   //printf("node->data is %f\n", *((double *) node->data));
   while (node != NULL && (*node).deleted == 1) {
      temp = node;
      //if (node->next == NULL) {
      //   printf("node->next is %f\n",*((double *)node->next->data));
      //}
      node = node->next;
      //   printf("node is %f\n",*((double *)node->data));
      (*temp).ptrCount--;
      if ((*temp).ptrCount == 0) {
         free(temp);
      }
      iter->curr = node;
   }
   if (node == NULL || node->data == NULL) {
      return NULL;
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
      (*temp).ptrCount--;
      if ((*temp).ptrCount == 0) {
	      free(temp);
      }
      temp = curr;
   }
   free(list);
}

void SLDestroyIterator(SortedListIteratorPtr iter) {
   if (iter == NULL) {
      return;
   }

   Node *node = iter->curr;
   if (node == NULL) {
      free(iter);
      return;
   }

   if ((*node).deleted == 1) {

      while (1) {

         (*node).ptrCount--;

         if ((*node).ptrCount == 0) {
            iter->curr = node->next;
            free(node);
            node = iter->curr;
            if (node == NULL) {
               break;
            }
         } else {
            break;
         }

      }
      
   }

   free(iter);
         
}

int main()
{

	SortedListPtr list;
	SortedListIteratorPtr iterator;
	CompareFuncT cf;

	cf = &compareInts;
	

	//Begin Testing

	list = SLCreate(cf);
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
   SLDestroyIterator(iterator);

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

   //Test 3: One item in list
   *a = 1;

   //Test 3a: Remove value that exists
   printf("Test 3a: Adding, iterating, and removing existing item from one item list\n");

   SLDestroy(list);
   list = SLCreate(cf);
   SLInsert(list, a);
   iterator = SLCreateIterator(list);

	n = SLNextItem(iterator);
   printf("The sorted list is:\n");

	while (n != NULL) {
		printf("%d\n", *n);
		n = SLNextItem(iterator);
	}

   if(SLRemove(list, a)){
      printf("PASS\n");
   } else {
      printf("FAIL\n");
   }

	SLDestroyIterator(iterator);

   //Test 3b: Remove value that doesn't exist
   printf("Test 3b: Adding and iterating. Removing non-existent item from one item list\n");
   *b = 2;
   *a = 1;

   SLInsert(list, a);
   iterator = SLCreateIterator(list);

   n = SLNextItem(iterator);
   printf("The sorted list is:\n");

	while (n != NULL) {
		printf("%d\n", *n);
		n = SLNextItem(iterator);
	}

   if(!SLRemove(list, b)){
      printf("PASS\n");
   } else {
      printf("FAIL\n");
   }

   //Test 3c: Adding value before that one item in list
   printf("Test 3c: Adding value before the one item in list\n");
   SLInsert(list, b);
   iterator = SLCreateIterator(list);
   n = SLNextItem(iterator);
   while (n != NULL) {
		printf("%d\n", *n);
		n = SLNextItem(iterator);
	}
   SLRemove(list,b);
	SLDestroyIterator(iterator);

   //Test 3d: Adding value after that one item in list
   printf("Test 3d: Adding value after the one item in list\n");
   *b = 0;
   SLInsert(list, b);
   iterator = SLCreateIterator(list);
   n = SLNextItem(iterator);
   printf("The current list is:\n");
   while (n != NULL) {
		printf("%d\n", *n);
		n = SLNextItem(iterator);
	}
   SLRemove(list,b);
	SLDestroyIterator(iterator);
   SLDestroy(list);

   //Test 3e: Adding value same as that one item in list
   printf("Test 3e: Adding value same as the one item in list\n");
   list = SLCreate(cf);
   int *z;
   z = (int *) malloc(sizeof(int));
   *b = 3;
   *z = 3;
   SLInsert(list, z);
   SLInsert(list, b);
   iterator = SLCreateIterator(list);
   n = SLNextItem(iterator);
   printf("The current list is:\n");
   while (n != NULL) {
		printf("%d\n", *n);
		n = SLNextItem(iterator);
	}
   SLRemove(list,z);
   SLRemove(list,b);
	SLDestroyIterator(iterator);

   //Test 4: Insert and delete multiple items in a list and delete list
   printf("Test 4: Inserting and deleting multiple items in a list and delete list\n");
   a = (int *) malloc(sizeof(int));
   b = (int *) malloc(sizeof(int));

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

   free(a);
   free(b);
   free(c);
   free(d);
   free(e);
   free(f);
   free(g);

	return 1;

}
