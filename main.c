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
   printf("Test 2a: Call SLNextItem with NULL iterator\n");
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

   //INTEGERS
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

   //Test 3f: Insert and delete multiple items in a list and delete list
   printf("Test 3f: Inserting and deleting multiple items in a list and delete list\n");
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


   //STRINGS
   //Test 4a: Inserting two items in list
	cf = &compareStrings;
	list = SLCreate(cf);
   printf("Test 4a: Inserting and deleting multiple items in a list and delete list\n");
   char *w1, *w2, *w3, *w4;
	char *ch;

   w1 = (char *)malloc(sizeof(char)*4);
   w1[0] = 'r';
   w1[1] = 'a';
   w1[2] = 't';
   w1[3] = '\0';
   w2 = (char *)malloc(sizeof(char)*5);
   w2[0] = 'm';
   w2[1] = 'u';
   w2[2] = 'c';
   w2[3] = 'h';
   w2[4] = '\0';

   SLInsert(list,w1);
   SLInsert(list,w2);
   
   iterator = SLCreateIterator(list);
   ch = SLNextItem(iterator);
   printf("The sorted list is:\n");

	while (ch != NULL) {
		printf("%s\n", ch);
		ch = SLNextItem(iterator);
	}   

   SLDestroyIterator(iterator);

   //Test 4b: Delete first word
   printf("Test 4b: Deleting head word \n");
   iterator = SLCreateIterator(list);

   SLRemove(list,w1);

   ch = SLNextItem(iterator);
   printf("The sorted list is:\n");

	while (ch != NULL) {
		printf("%s\n", ch);
		ch = SLNextItem(iterator);
	}

   SLDestroyIterator(iterator);

   //Test 4c: Delete last and only word
   printf("Test 4c: Deleting last word \n");
   iterator = SLCreateIterator(list);

   SLRemove(list,w2);

   ch = SLNextItem(iterator);
   printf("The sorted list is:\n");

	while (ch != NULL) {
		printf("%s\n", ch);
		ch = SLNextItem(iterator);
	}

   SLDestroyIterator(iterator);
   SLDestroy(list);

   //Test 4d: Add more than two words (iterator created after words inserted)
   printf("Test 4d: Add more than two words and create iterator before inserting words\n");
   cf = &compareStrings;
	list = SLCreate(cf);

   iterator = SLCreateIterator(list);

   w3 = (char *)malloc(sizeof(char)*6);
   w3[0] = 'h';
   w3[1] = 'e';
   w3[2] = 'l';
   w3[3] = 'l';
   w3[4] = 'o';
   w3[5] = '\0';
   w4 = (char *)malloc(sizeof(char)*6);
   w4[0] = 'w';
   w4[1] = 'o';
   w4[2] = 'r';
   w4[3] = 'l';
   w4[4] = 'd';
   w4[5] = '\0';

   SLInsert(list,w1);
   SLInsert(list,w2);
   SLInsert(list,w3);
   SLInsert(list,w4);

   ch = SLNextItem(iterator);
   printf("The sorted list is:\n");

	while (ch != NULL) {
		printf("%s\n", ch);
		ch = SLNextItem(iterator);
	}

   SLDestroyIterator(iterator);

   //Test 4e: Add more than two words (iterator created before words inserted)
   printf("Test 4e: Add more than two words and create iterator after inserting words\n");
   iterator = SLCreateIterator(list);
   ch = SLNextItem(iterator);
   printf("The sorted list is:\n");

	while (ch != NULL) {
		printf("%s\n", ch);
		ch = SLNextItem(iterator);
	}

   SLDestroyIterator(iterator);

   //Test 4f: Delete item that iterator is currently on
   printf("Test 4f: Delete item that iterator is currently on\n");
   iterator = SLCreateIterator(list);
   ch = SLNextItem(iterator);
   ch = SLNextItem(iterator); //should be on "rat"
   SLRemove(list,w1); //delete rat

   SortedListIteratorPtr iterator2;
   iterator2 = SLCreateIterator(list);
   ch = SLNextItem(iterator2);
   printf("The sorted list is:\n");

	while (ch != NULL) {
		printf("%s\n", ch);
		ch = SLNextItem(iterator2);
	}

   SLDestroyIterator(iterator);
   SLDestroyIterator(iterator2);

   //Test 4g: Delete item before the item that iterator is currently on
   printf("Test 4g: Delete item before the item iterator is currently on\n");
   iterator = SLCreateIterator(list);
   SLInsert(list,w1);
   ch = SLNextItem(iterator);
   ch = SLNextItem(iterator); //should be on "rat"
   SLRemove(list,w4); //delete world

   iterator2 = SLCreateIterator(list);
   ch = SLNextItem(iterator2);
   printf("The sorted list is:\n");

	while (ch != NULL) {
		printf("%s\n", ch);
		ch = SLNextItem(iterator2);
	}

   SLDestroyIterator(iterator);
   SLDestroyIterator(iterator2);

   //Test 4h: Delete item after the item that iterator is currently on
   printf("Test 4h: Delete item after the item iterator is currently on\n");
   iterator = SLCreateIterator(list);
   SLInsert(list,w4);
   ch = SLNextItem(iterator);
   ch = SLNextItem(iterator); //should be on "rat"
   SLRemove(list,w2); //delete much

   iterator2 = SLCreateIterator(list);
   ch = SLNextItem(iterator2);
   printf("The sorted list is:\n");

	while (ch != NULL) {
		printf("%s\n", ch);
		ch = SLNextItem(iterator2);
	}

   SLDestroyIterator(iterator);
   SLDestroyIterator(iterator2);
   SLDestroy(list);

   //Test 4i: Duplicate strings
   printf("Test 4i: Duplicate strings\n");
   char *dup1, *dup2, *dup3, *dup4;
   list = SLCreate(cf);

   dup1 = (char *)malloc(sizeof(char)*6);
   dup1[0] = 'h';
   dup1[1] = 'o';
   dup1[2] = 'u';
   dup1[3] = 's';
   dup1[4] = 'e';
   dup1[5] = '\0';
   dup2 = (char *)malloc(sizeof(char)*6);
   dup2[0] = 'h';
   dup2[1] = 'o';
   dup2[2] = 'u';
   dup2[3] = 's';
   dup2[4] = 'e';
   dup2[5] = '\0';
   dup3 = (char *)malloc(sizeof(char)*6);
   dup3[0] = 'h';
   dup3[1] = 'o';
   dup3[2] = 'u';
   dup3[3] = 's';
   dup3[4] = 'e';
   dup3[5] = '\0';
   dup4 = (char *)malloc(sizeof(char)*6);
   dup4[0] = 'h';
   dup4[1] = 'o';
   dup4[2] = 'u';
   dup4[3] = 's';
   dup4[4] = 'e';
   dup4[5] = '\0';

   SLInsert(list,dup1);
   SLInsert(list,dup2);
   SLInsert(list,dup3);
   SLInsert(list,dup4);

   iterator = SLCreateIterator(list);
   
   ch = SLNextItem(iterator);
   printf("The sorted list after insertion is:\n");

	while (ch != NULL) {
		printf("%s\n", ch);
		ch = SLNextItem(iterator);
	}

   SLRemove(list,dup3);
   SLRemove(list,dup4);
   SLRemove(list,dup2);

   iterator2 = SLCreateIterator(list);
   ch = SLNextItem(iterator2);
   printf("The sorted list after deletion is:\n");

	while (ch != NULL) {
		printf("%s\n", ch);
		ch = SLNextItem(iterator2);
	}

   SLDestroyIterator(iterator);
   SLDestroyIterator(iterator2);


   //Test 5: Destroy iterator after SLDestroy left things to clean up
   printf("Test 5: Destroy iterator after SLDestroy left things to clean up\n");
   list = SLCreate(cf);

   SLInsert(list,w1);
   SLInsert(list,w2);
   SLInsert(list,w3);
   SLInsert(list,w4);

   iterator = SLCreateIterator(list);
   ch = SLNextItem(iterator);
   ch = SLNextItem(iterator);
   printf("iterator is after:%s\n", ch);

   SLDestroy(list);
   SLDestroyIterator(iterator);
   
   //Test 6: Doubles testing   
   printf("Test 6: Doubles testing (adding, iterating, removing)\n");
   cf = &compareDoubles;
   list = SLCreate(cf);
	double *j, *k, *l, *m;
	double *db;
	j = (double *) malloc(sizeof(double));
	k = (double *) malloc(sizeof(double));
	l = (double *) malloc(sizeof(double));
	m = (double *) malloc(sizeof(double));

	*j = 1.69;
	*k = 10.8;
	*l = 33.33333;
	*m = 0.1;

   SLInsert(list,j);
   SLInsert(list,k);
   SLInsert(list,l);
   SLInsert(list,m);
	
   iterator = SLCreateIterator(list);
   db = SLNextItem(iterator);
   printf("The sorted list is:\n");

	while (db != NULL) {
		printf("%f\n", *db);
		db = SLNextItem(iterator);
	} //iterator pointing to null

   SLRemove(list,k); //remove 10.8
   iterator2 = SLCreateIterator(list);
   db = SLNextItem(iterator2);
   printf("The sorted list after deletion is:\n");

	while (db != NULL) {
		printf("%f\n", *db);
		db = SLNextItem(iterator2);
	}

     

   SLDestroy(list);
   SLDestroyIterator(iterator);
   SLDestroyIterator(iterator2);


	return 1;
}
