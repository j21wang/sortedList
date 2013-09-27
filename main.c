/*
 * sorted-list.c
 */

#include	<string.h>
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

	s1->head = head;
	s1->cf = cf;
	(*s1).size = 0;

	return s1;
}

SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {
	SortedListIteratorPtr slip = (SortedListIteratorPtr) malloc(sizeof(struct SortedListIterator));
	slip->list = list;
	slip->curr = list->head;
	return slip;
}

int SLInsert(SortedListPtr list, void *newObj) {

	if ((*list).size == 0) {
		(list->head)->data = newObj;
		(*list).size++;
		return 1;
	}

	Node *newObjectNode = (Node *) malloc(sizeof(struct Node));
    newObjectNode->data = newObj;

	Node *curr = list->head;
    Node *temp = curr;
	CompareFuncT cf = list->cf;


   void *item = curr->data;

	while (cf(newObj, item) == -1 && curr != NULL) {
      temp = curr;
      curr = curr->next;
      item = curr->data;
	}

   if (curr == list->head) {
      newObjectNode->next = curr;
      list->head = newObjectNode;
   } else if (curr != NULL) {
      temp->next = newObjectNode;
      newObjectNode->next = curr;
   } else {
	  temp->next = newObjectNode;
	  newObjectNode->next = NULL;
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

   while(cf(newObj, item) != 0 && curr != NULL){
      temp = curr;
      curr = curr->next;
      item = curr->data;
      if (cf(item, newObj) == -1) {
         return 0;
      }
   }

   if (curr == list->head) {
		temp = curr->next;
		list->head = temp;
		free(curr->data);
		free(curr);
		return 1;
	}

   temp->next = curr->next;
   free(curr->data);
   free(curr);
   
   (*list).size--;
   return 1;

}

void *SLNextItem(SortedListIteratorPtr iter) {
	void *item;
	Node *node = iter->curr;
	if (node == NULL) {
		return NULL;
	}
	item = node->data;
	iter->curr = node->next;
	return item;
}

void SLDestroy(SortedListPtr list) {
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
   free(iter);
}

int main()
{

	SortedListPtr list;
	SortedListIteratorPtr iterator;
	CompareFuncT cf;

	cf = &compareInts;
	
	list = SLCreate(cf);
	iterator = SLCreateIterator(list);

	//Begin Testing

	int *a, *b, *c, *d, *e, *f, *g;
	a = (int *) malloc(sizeof(int));
	b = (int *) malloc(sizeof(int));
	c = (int *) malloc(sizeof(int));
	d = (int *) malloc(sizeof(int));
	e = (int *) malloc(sizeof(int));
	f = (int *) malloc(sizeof(int));
	g = (int *) malloc(sizeof(int));

	*a = 1;
	*b = 2;
	*c = 3;
	*d = 4;
	*e = 5;
	*f = 6;
	*g = 7;

	SLInsert(list, e);
	SLInsert(list, f);
	SLInsert(list, g);
	SLInsert(list, c);
	SLInsert(list, d);
	SLInsert(list, b);
	SLInsert(list, a);

	int *n = malloc(sizeof(int));
	n = SLNextItem(iterator);

	while (n != NULL) {
		printf("%d\n", *n);
		n = SLNextItem(iterator);
	}

	//End Testing

	SLDestroy(list);
	SLDestroyIterator(iterator);

	return 1;

}
