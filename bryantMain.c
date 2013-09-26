#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	"sorted-list.h"
/*
#include	"sorted-list.c"



In sorted-list.c

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
*/
int main(int argc, char **argv)
{	
	/*Numbers*/
	double * num1, *num2, *remove, current;
	
	/*Strings*/
	char * word1, *word2, *word3, *word4, *word5, *cur;

	/*Other variable*/
	void * obj;
	SortedListPtr list;
	SortedListIteratorPtr iter;
	int (*CF)(void *, void *);
	
	iter = NULL;
	
	/*make Sorted-List*/
	CF = &compareDoubles;
	list = SLCreate(CF);
	
	/*1 - Nothing in List Test Cases*/

		/*1a - Remove*/
		remove = (double *)malloc(sizeof(double));
		*remove = 230.9;
		if(!SLRemove(list,remove)){
			printf("Passed Test 1a\n");
			printf("\n");
		}
		else{
			printf("Failed test 1a\n");
			printf("\n");
		}

		/*1b - Iterator*/
		iter = SLCreateIterator(list);
		if(iter == NULL){
			printf("Passed Test 1b\n");
			printf("\n");
		}
		else{
			printf("Failed Test 1b\n");
			printf("\n");
		}

	/*2 - No Iterator Test Cases*/

		/*2a - Next Item*/
		obj = SLNextItem(iter);

		if(obj == NULL){
			printf("Passed Test 2a\n");
			printf("\n");
		}
		else{
			printf("Failed Test 2a\n");
			printf("\n");
		}

		/*2b - Destory*/
		printf("Testing SLDestoryIterator with NULL iter. Test 2b\n");
		SLDestroyIterator(iter);
		printf("Program did not break- Passed Test 2b\n");
		printf("\n");

	/*3 - One Value Test Cases*/

			num1 = (double *)malloc(sizeof(double));
			*num1 = 1.9;


		/*3a - Remove Value that is Present*/
			SLInsert(list,num1);
			if(SLRemove(list,remove)){
				printf("Passed Test 3a\n");
				printf("\n");
			}
			else{
				printf("Failed test 3a\n");
				printf("\n");
			}

		/*3b - Remove value that is not Present*/
			SLInsert(list,num1);
			*remove = 2.7;
			if(!SLRemove(list,remove)){
				printf("Passed Test 3b\n");
				printf("\n");
			}
			else{
				printf("Failed test 3b\n");
				printf("\n");
			}

		/*3c - Iterator and iterate w/o Adding or Removing*/
			/*Create Iterator*/
				iter = SLCreateIterator(list);
				if(iter != NULL){
					printf("Iterator Created\n");
					printf("\n");
				}
				else{
					printf("Nothing in list\n");
					printf("\n");
				}


				/*Iterate*/
				while(1){
					obj = SLNextItem(iter);

					if(obj != NULL){
						current = *((double*)obj);
						printf("Next Double: %f", current);
						printf("\n");
					}
					else{
						printf("Iterator returned NULL\n");
						printf("\n");
						SLDestroyIterator(iter);
						break;
					}
				}

				printf("If printed out 1 vale (1.9) and stopped then Passed Test 3c\n");
				printf("\n");


				/*3d - Iterator and delete what iterator is on and iterate*/
					/*Create Iterator*/
					iter = SLCreateIterator(list);
					if(iter != NULL){
						printf("Iterator Created\n");
						printf("\n");
					}
					else{
						printf("Nothing in list\n");
						printf("\n");
					}

					/*Delete*/
					*remove = 1.9;
					if(SLRemove(list,remove)){
						printf("1.9 deleted\n");
						printf("\n");
					}
					else{
						printf("1.9 not deleted - Something is wrong\n");
						printf("\n");
					}

					/*Iterate*/
					while(1){
						obj = SLNextItem(iter);

						if(obj != NULL){
							current = *((double*)obj);
							printf("Next Double: %f", current);
							printf("\n");
						}
						else{
							printf("Iterator returned NULL\n");
							printf("\n");
							SLDestroyIterator(iter);
							break;
						}
					}

					printf("Iterator should not return anything - if so Passed Test 3d\n");
					printf("\n");

				/*3e - Add Before*/
				SLInsert(list,num1);
				num2 = (double *)malloc(sizeof(double));
				*num2 = 54.2;
				SLInsert(list,num2);

					/*Create Iterator*/
				iter = SLCreateIterator(list);
				if(iter != NULL){
					printf("Iterator Created\n");
					printf("\n");
				}
				else{
					printf("Nothing in list\n");
					printf("\n");
				}


					/*Iterate*/
					while(1){
						obj = SLNextItem(iter);

						if(obj != NULL){
							current = *((double*)obj);
							printf("Next Double: %f", current);
							printf("\n");
						}
						else{
							printf("Iterator returned NULL\n");
							printf("\n");
							SLDestroyIterator(iter);
							break;
						}
					}

				printf("If printed out 2 val (54.2,1.9) and stopped then Passed Test 3e\n");
				printf("\n");

				/*3f - Add After*/
				SLRemove(list,num2);
				*num2 = 9.8;

				SLInsert(list,num2);

					/*Create Iterator*/
					iter = SLCreateIterator(list);
					if(iter != NULL){
						printf("Iterator Created\n");
						printf("\n");
					}
					else{
						printf("Nothing in list\n");
						printf("\n");
					}


					/*Iterate*/
					while(1){
						obj = SLNextItem(iter);

						if(obj != NULL){
							current = *((double*)obj);
							printf("Next Double: %f", current);
							printf("\n");
						}
						else{
							printf("Iterator returned NULL\n");
							printf("\n");
							SLDestroyIterator(iter);
							break;
						}
					}

				printf("If printed out 2 val (1.9,9.8) and stopped then Passed Test 3f");

				/*3g - Add Same*/
				SLRemove(list,num2);
				*num2 = 0.9;

				SLInsert(list,num2);

					/*Create Iterator*/
					iter = SLCreateIterator(list);
					if(iter != NULL){
						printf("Iterator Created\n");
						printf("\n");
					}
					else{
						printf("Nothing in list\n");
						printf("\n");
					}


					/*Iterate*/
					while(1){
						obj = SLNextItem(iter);

						if(obj != NULL){
							current = *((double*)obj);
							printf("Next Double: %f", current);
							printf("\n");
						}
						else{
							printf("Iterator returned NULL\n");
							printf("\n");
							SLDestroyIterator(iter);
							break;
						}
					}

				printf("If printed out 1 val (0.9) and stopped then Passed Test 3g\n");

	//Clean-Up One
	SLDestroy(list);
	free(num1);
	free(num2);
	free(remove);

	//Switch to Strings
	/*make Sorted-List*/
	CF = &compareStrings;
	list = SLCreate(CF);


	/*4 - Two or more Items in List*/
		word1 = (char *)malloc(sizeof(char)*4);
		word1[0] = 'c';
		word1[1] = 'a';
		word1[2] = 't';
		word1[3] = '\0';
		word2 = (char *)malloc(sizeof(char)*5);
		word2[0] = 'b';
		word2[1] = 'a';
		word2[2] = 'l';
		word2[3] = 'l';
		word2[4] = '\0';

		SLInsert(list,word1);
		SLInsert(list,word2);

		/*4a - Remove Foot*/
			if(SLRemove(list, word2)){
				printf("Passed Test 4a\n");
				printf("\n");
			}
			else{
				printf("Failed test 4a\n");
				printf("\n");
			}

			SLInsert(list,word2);

		/*4b - Remove Head*/
			if(SLRemove(list, word1)){
				printf("Passed Test 4b\n");
				printf("\n");
			}
			else{
				printf("Failed test 4b\n");
				printf("\n");
			}

			SLInsert(list,word1);
		/*4c - Iterate*/

			/*Create Iterator*/
			iter = SLCreateIterator(list);
			if(iter != NULL){
				printf("Iterator Created\n");
				printf("\n");
			}
			else{
				printf("Nothing in list\n");
				printf("\n");
			}


			while(1){
				obj = SLNextItem(iter);

				if(obj != NULL){
					cur = (char*)obj;
					printf("Next word: %s", cur);
					printf("\n");
				}
				else{
					printf("Iterator returned NULL\n");
					printf("\n");
					SLDestroyIterator(iter);
					break;
				}
			}

			printf("If printed out 2 val (ball,cat) and stopped then Passed Test 3c\n");

		/*4d - Iterate delete head while on head*/

			/*Create Iterator*/
			iter = SLCreateIterator(list);
			if(iter != NULL){
				printf("Iterator Created\n");
				printf("\n");
			}
			else{
				printf("Nothing in list\n");
				printf("\n");
			}

			SLRemove(list, word1);

			while(1){
				obj = SLNextItem(iter);

				if(obj != NULL){
					cur = (char*)obj;
					printf("Next word: %s", cur);
					printf("\n");
				}
				else{
					printf("Iterator returned NULL\n");
					printf("\n");
					SLDestroyIterator(iter);
					break;
				}
			}

			printf("If printed out 1 val (ball) and stopped then Passed Test 4d\n");

			SLInsert(list,word1);

		/*4e - Iterate delete foot while on head*/
			/*Create Iterator*/
				iter = SLCreateIterator(list);
				if(iter != NULL){
					printf("Iterator Created\n");
					printf("\n");
				}
				else{
					printf("Nothing in list\n");
					printf("\n");
				}

				SLRemove(list, word2);

				while(1){
					obj = SLNextItem(iter);

					if(obj != NULL){
						cur = (char*)obj;
						printf("Next word: %s", cur);
						printf("\n");
					}
					else{
						printf("Iterator returned NULL\n");
						printf("\n");
						SLDestroyIterator(iter);
						break;
					}
				}

				printf("If printed out 1 val (cat) and stopped then Passed Test 4e\n");

				SLInsert(list,word2);

		/*4f - Iterate delete foot while on foot*/
				/*Create Iterator*/
					iter = SLCreateIterator(list);
					if(iter != NULL){
						printf("Iterator Created\n");
						printf("\n");
					}
					else{
						printf("Nothing in list\n");
						printf("\n");
					}


					obj = SLNextItem(iter);

					if(obj != NULL){
						cur = (char*)obj;
						printf("Next word: %s", cur);
						printf("\n");
					}
					else{
						printf("Iterator returned NULL\n");
						printf("\n");
						SLDestroyIterator(iter);
					}

					SLRemove(list, word1);

					while(1){
						obj = SLNextItem(iter);

						if(obj != NULL){
							cur = (char*)obj;
							printf("Next word: %s", cur);
							printf("\n");
						}
						else{
							printf("Iterator returned NULL\n");
							printf("\n");
							SLDestroyIterator(iter);
							break;
						}
					}

					printf("If printed out 1 val (ball) and stopped then Passed Test 4f\n");

					SLInsert(list,word1);

		/*4g - Iterate delete head and foot while on head*/
			iter = SLCreateIterator(list);
			if(iter != NULL){
				printf("Iterator Created\n");
				printf("\n");
			}
			else{
				printf("Nothing in list\n");
				printf("\n");
			}


			SLRemove(list, word1);
			SLRemove(list, word2);

			while(1){
				obj = SLNextItem(iter);

				if(obj != NULL){
					cur = (char*)obj;
					printf("Next word: %s", cur);
					printf("\n");
				}
				else{
					printf("Iterator returned NULL\n");
					printf("\n");
					SLDestroyIterator(iter);
					break;
				}
			}

			printf("If printed out no vals and stopped then Passed Test 4g\n");

			SLInsert(list,word1);
			SLInsert(list, word2);

		/*4h - Insert between head and foot*/
			word3 = (char *)malloc(sizeof(char)*3);
			word3[0] = 'a';
			word3[1] = 'j';
			word3[2] = '\0';

			SLInsert(list, word3);

			/*Create Iterator*/
			iter = SLCreateIterator(list);
			if(iter != NULL){
				printf("Iterator Created\n");
				printf("\n");
			}
			else{
				printf("Nothing in list\n");
				printf("\n");
			}


			while(1){
				obj = SLNextItem(iter);

				if(obj != NULL){
					cur = (char*)obj;
					printf("Next word: %s", cur);
					printf("\n");
				}
				else{
					printf("Iterator returned NULL\n");
					printf("\n");
					SLDestroyIterator(iter);
					break;
				}
			}
			printf("If printed out 3 val (ball, aj, cat) and stopped then Passed Test 4h\n");

		/*4i - Insert after foot*/
			word4 = (char *)malloc(sizeof(char)*6);
			word4[0] = 'a';
			word4[1] = 'l';
			word4[2] = 'l';
			word4[3] = 'e';
			word4[4] = 'n';
			word4[5] = '\0';

			SLInsert(list, word4);

			/*Create Iterator*/
			iter = SLCreateIterator(list);
			if(iter != NULL){
				printf("Iterator Created\n");
				printf("\n");
			}
			else{
				printf("Nothing in list\n");
				printf("\n");
			}


			while(1){
				obj = SLNextItem(iter);

				if(obj != NULL){
					cur = (char*)obj;
					printf("Next word: %s", cur);
					printf("\n");
				}
				else{
					printf("Iterator returned NULL\n");
					printf("\n");
					SLDestroyIterator(iter);
					break;
				}
			}
			printf("If printed out 4 val (ball, aj, cat, allen) and stopped then Passed Test 4i\n");


		/*4j - Iterate before head*/
			word5 = (char *)malloc(sizeof(char)*4);
			word5[0] = 'm';
			word5[1] = 'm';
			word5[2] = 'm';
			word5[3] = '\0';

			SLInsert(list, word5);

			/*Create Iterator*/
			iter = SLCreateIterator(list);
			if(iter != NULL){
				printf("Iterator Created\n");
				printf("\n");
			}
			else{
				printf("Nothing in list\n");
				printf("\n");
			}


			while(1){
				obj = SLNextItem(iter);

				if(obj != NULL){
					cur = (char*)obj;
					printf("Next word: %s", cur);
					printf("\n");
				}
				else{
					printf("Iterator returned NULL\n");
					printf("\n");
					SLDestroyIterator(iter);
					break;
				}
			}
			printf("If printed out 5 val (mmm, ball, aj, cat, allen) and stopped then Passed Test 4j\n");

	/*5 - Multiple Items in List*/
		/*5a - Iterate delete on */

			iter = SLCreateIterator(list);
			if(iter != NULL){
				printf("Iterator Created\n");
				printf("\n");
			}
			else{
				printf("Nothing in list\n");
				printf("\n");
			}

			obj = SLNextItem(iter);

			if(obj != NULL){
				cur = (char*)obj;
				printf("Next word: %s", cur);
				printf("\n");
			}
			else{
				printf("Iterator returned NULL\n");
				printf("\n");
				SLDestroyIterator(iter);
			}

			SLRemove(list, word2);

			while(1){
				obj = SLNextItem(iter);

				if(obj != NULL){
					cur = (char*)obj;
					printf("Next Double: %s", cur);
					printf("\n");
				}
				else{
					printf("Iterator returned NULL\n");
					printf("\n");
					SLDestroyIterator(iter);
					break;
				}
			}

			printf("If printed out 4 val (mmm, aj, cat, allen) and stopped then Passed Test 5a\n");

			SLInsert(list,word2);

		/*5b - Iterate delete on and after*/
			iter = SLCreateIterator(list);
			if(iter != NULL){
				printf("Iterator Created\n");
				printf("\n");
			}
			else{
				printf("Nothing in list\n");
				printf("\n");
			}

			obj = SLNextItem(iter);

			if(obj != NULL){
				cur = (char*)obj;
				printf("Next word: %s", cur);
				printf("\n");
			}
			else{
				printf("Iterator returned NULL\n");
				printf("\n");
				SLDestroyIterator(iter);
			}

			SLRemove(list, word2);
			SLRemove(list, word3);

			while(1){
				obj = SLNextItem(iter);

				if(obj != NULL){
					cur = (char*)obj;
					printf("Next word: %s", cur);
					printf("\n");
				}
				else{
					printf("Iterator returned NULL\n");
					printf("\n");
					SLDestroyIterator(iter);
					break;
				}
			}

			printf("If printed out 3 val (mmm, cat, allen) and stopped then Passed Test 5b\n");

			SLInsert(list,word2);
			SLInsert(list,word3);

		/*5c - Iterate delete on till end*/

			iter = SLCreateIterator(list);
			if(iter != NULL){
				printf("Iterator Created\n");
				printf("\n");
			}
			else{
				printf("Nothing in list\n");
				printf("\n");
			}

			obj = SLNextItem(iter);

			if(obj != NULL){
				cur = (char*)obj;
				printf("Next word: %s", cur);
				printf("\n");
			}
			else{
				printf("Iterator returned NULL\n");
				printf("\n");
				SLDestroyIterator(iter);
			}

			obj = SLNextItem(iter);

			if(obj != NULL){
				cur = (char*)obj;
				printf("Next word: %s", cur);
				printf("\n");
			}
			else{
				printf("Iterator returned NULL\n");
				printf("\n");
				SLDestroyIterator(iter);
			}

			SLRemove(list, word3);
			SLRemove(list, word1);
			SLRemove(list, word4);

			while(1){
				obj = SLNextItem(iter);

				if(obj != NULL){
					cur = (char*)obj;
					printf("Next word: %s", cur);
					printf("\n");
				}
				else{
					printf("Iterator returned NULL\n");
					printf("\n");
					SLDestroyIterator(iter);
					break;
				}
			}

			printf("If printed out 2 val (mmm, ball) and stopped then Passed Test 5c\n");

			SLInsert(list, word3);
			SLInsert(list, word1);
			SLInsert(list, word4);

		/*5d - Iterate delete before*/

			iter = SLCreateIterator(list);
			if(iter != NULL){
				printf("Iterator Created\n");
				printf("\n");
			}
			else{
				printf("Nothing in list\n");
				printf("\n");
			}

			obj = SLNextItem(iter);

			if(obj != NULL){
				cur = (char*)obj;
				printf("Next word: %s", cur);
				printf("\n");
			}
			else{
				printf("Iterator returned NULL\n");
				printf("\n");
				SLDestroyIterator(iter);
			}

			SLRemove(list,word5);

			while(1){
				obj = SLNextItem(iter);

				if(obj != NULL){
					cur = (char*)obj;
					printf("Next word: %s", cur);
					printf("\n");
				}
				else{
					printf("Iterator returned NULL\n");
					printf("\n");
					SLDestroyIterator(iter);
					break;
				}
			}


			/*Create Iterator*/
			iter = SLCreateIterator(list);
			if(iter != NULL){
				printf("Iterator Created\n");
				printf("\n");
			}
			else{
				printf("Nothing in list\n");
				printf("\n");
			}


			while(1){
				obj = SLNextItem(iter);

				if(obj != NULL){
					cur = (char*)obj;
					printf("Next word: %s", cur);
					printf("\n");
				}
				else{
					printf("Iterator returned NULL\n");
					printf("\n");
					SLDestroyIterator(iter);
					break;
				}
			}

			printf("if print all values (mmm, ball, aj, cat, alean) and then prints only (ball, aj, cat, allen)passed test 5d\n");

			SLInsert(list, word5);
		/*5e - Iter delete before and on*/

			iter = SLCreateIterator(list);
			if(iter != NULL){
				printf("Iterator Created\n");
				printf("\n");
			}
			else{
				printf("Nothing in list\n");
				printf("\n");
			}

			obj = SLNextItem(iter);

			if(obj != NULL){
				cur = (char*)obj;
				printf("Next word: %s", cur);
				printf("\n");
			}
			else{
				printf("Iterator returned NULL\n");
				printf("\n");
				SLDestroyIterator(iter);
			}

			SLRemove(list,word5);
			SLRemove(list,word2);

			while(1){
				obj = SLNextItem(iter);

				if(obj != NULL){
					cur = (char*)obj;
					printf("Next word: %s", cur);
					printf("\n");
				}
				else{
					printf("Iterator returned NULL\n");
					printf("\n");
					SLDestroyIterator(iter);
					break;
				}
			}


			/*Create Iterator*/
			iter = SLCreateIterator(list);
			if(iter != NULL){
				printf("Iterator Created\n");
				printf("\n");
			}
			else{
				printf("Nothing in list\n");
				printf("\n");
			}


			while(1){
				obj = SLNextItem(iter);

				if(obj != NULL){
					cur = (char*)obj;
					printf("Next word: %s", cur);
					printf("\n");
				}
				else{
					printf("Iterator returned NULL\n");
					printf("\n");
					SLDestroyIterator(iter);
					break;
				}
			}

			printf("if print 4 values (mmm, aj, cat, allen) and then prints only (aj, cat, allen) passed test 5e\n");

			SLInsert(list,word5);
			SLInsert(list,word2);
		/*5f - Iter delete before and on and after*/
			iter = SLCreateIterator(list);
			if(iter != NULL){
				printf("Iterator Created\n");
				printf("\n");
			}
			else{
				printf("Nothing in list\n");
				printf("\n");
			}

			obj = SLNextItem(iter);

			if(obj != NULL){
				cur = (char*)obj;
				printf("Next word: %s", cur);
				printf("\n");
			}
			else{
				printf("Iterator returned NULL\n");
				printf("\n");
				SLDestroyIterator(iter);
			}

			SLRemove(list,word5);
			SLRemove(list,word2);
			SLRemove(list, word3);

			while(1){
				obj = SLNextItem(iter);

				if(obj != NULL){
					cur = (char*)obj;
					printf("Next word: %s", cur);
					printf("\n");
				}
				else{
					printf("Iterator returned NULL\n");
					printf("\n");
					SLDestroyIterator(iter);
					break;
				}
			}


			/*Create Iterator*/
			iter = SLCreateIterator(list);
			if(iter != NULL){
				printf("Iterator Created\n");
				printf("\n");
			}
			else{
				printf("Nothing in list\n");
				printf("\n");
			}


			while(1){
				obj = SLNextItem(iter);

				if(obj != NULL){
					cur = (char*)obj;
					printf("Next word: %s", cur);
					printf("\n");
				}
				else{
					printf("Iterator returned NULL\n");
					printf("\n");
					SLDestroyIterator(iter);
					break;
				}
			}

			printf("if print 4 values (mmm, cat, allen) and then prints only (cat, allen) passed test 5f\n");

			SLInsert(list,word5);
			SLInsert(list,word2);

		/*5g Delete on then Insert*/
			iter = SLCreateIterator(list);
			if(iter != NULL){
				printf("Iterator Created\n");
				printf("\n");
			}
			else{
				printf("Nothing in list\n");
				printf("\n");
			}

			obj = SLNextItem(iter);

			if(obj != NULL){
				cur = (char*)obj;
				printf("Next: %s", cur);
				printf("\n");
			}
			else{
				printf("Iterator returned NULL\n");
				printf("\n");
				SLDestroyIterator(iter);
			}

			SLRemove(list,word2);
			SLInsert(list, word3);

			while(1){
				obj = SLNextItem(iter);

				if(obj != NULL){
					cur = (char*)obj;
					printf("Next: %s", cur);
					printf("\n");
				}
				else{
					printf("Iterator returned NULL\n");
					printf("\n");
					SLDestroyIterator(iter);
					break;
				}
			}


			/*Create Iterator*/
			iter = SLCreateIterator(list);
			if(iter != NULL){
				printf("Iterator Created\n");
				printf("\n");
			}
			else{
				printf("Nothing in list\n");
				printf("\n");
			}


			while(1){
				obj = SLNextItem(iter);

				if(obj != NULL){
					cur = (char*)obj;
					printf("Next: %s", cur);
					printf("\n");
				}
				else{
					printf("Iterator returned NULL\n");
					printf("\n");
					SLDestroyIterator(iter);
					break;
				}
			}

			printf("if print 4 values (mmm, cat, allen) and then prints (mmm, aj, cat, allen) passed test 5g\n");

	//Clean-Up two
	SLDestroy(list);
	free(word1);
	free(word2);
	free(word3);
	free(word4);
	free(word5);

	return 0;
	
}

