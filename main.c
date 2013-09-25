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
	SortedListPtr s1;
	Node *head;

	head->data = NULL;
	head->next = NULL;

	s1->head = head;
	s1->cf = cf;

	return s1;
}

SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {
	SortedListIteratorPtr slip;
	slip->list = list;
	slip->curr = list->head;
}

int SLInsert(SortedListPtr list, void *newObj) {
	Node *newobject;

	Node *curr = list->head;
	CompareFuncT cf = list->cf;
	SortedListIteratorPtr iterator = SLCreateIterator(list);

	void *item = SLNextItem(iterator);

	while (cf(newObj, item) == -1 && item != NULL) {
		item = SLNextItem(iterator);
	}
	
}

int SLRemove(SortedListPtr list, void *newObj) {
	//implement
}

void *SLNextItem(SortedListIteratorPtr iter) {
	void *item;
	Node *node = iter->curr;
	item = node->data;
	node = node->next;
	return item;
}

void SLDestroy(SortedListPtr list) {
	//implement
}

void SLDestroyIterator(SortedListIteratorPtr iter) {
	//implement
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
