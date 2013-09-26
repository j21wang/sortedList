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
	SortedListPtr s1 = (SortedListPtr) malloc(sizeof(SortedList));
	Node *head = (Node *) malloc(sizeof(Node));

	head->data = NULL;
	head->next = NULL;

	s1->head = head;
	s1->cf = cf;

	return s1;
}

SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {
	SortedListIteratorPtr slip = (SortedListIteratorPtr) malloc(sizeof(SortedListIterator));
	slip->list = list;
	slip->curr = list->head;
}

int SLInsert(SortedListPtr list, void *newObj) {
	Node *newObjectNode = (Node *) malloc(sizeof(Node));

	Node *curr = list->head;
   Node *temp = curr;
	CompareFuncT cf = list->cf;

   newObjectNode->data = newObj;

   void *item = curr->data;

	while (cf(newObj, item) == -1 && curr != NULL) {
      temp = curr;
      curr = curr->next;
      item = curr->data;
	}

   if (curr == list->head) {
      newObjectNode->next = curr;
      list->head = newObjectNode;
   } else {
      temp->next = newObjectNode;
      newObjectNode->next = curr;
   }
   
   return 1;
	
}

int SLRemove(SortedListPtr list, void *newObj) {
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

   temp->next = curr->next;
   free(curr->data);
   free(curr->next);
   free(curr);
   
   return 1;

}

void *SLNextItem(SortedListIteratorPtr iter) {
	void *item;
	Node *node = iter->curr;
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
      free(temp->next);
      temp = curr;
   }
   free(list->head);
   free(list->cf);
   free(list);
}

void SLDestroyIterator(SortedListIteratorPtr iter) {
   free(iter->list);
   free(iter->curr);
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



	SLDestroy(list);
	SLDestroyIterator(iterator);

}
