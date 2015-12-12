/**
*	Names:
*	David Lambropoulos
*	Demetrios Lambropoulos
**/

#include <stdio.h>
#include "sorted-list.c"
#include "sorted-list.h"
#include <stdlib.h> 
#include <string.h>
 
int intcf(void *a, void *b)
{ 
	int anew = *(int *) a;
	int bnew = *(int *) b;

	if (anew > bnew)
	{ 
		return -1;
	}
	else if (anew < bnew)
	{
		return 1;
	} 
	else
	{ 
		return 0;
	}
}

int strcf(void *a, void *b)
{
	char *str1 = a;
	char *str2 = b;

	return strcmp(str1,str2);
}
void destroy(void * item) 
{
	free(item); 
}  
int main(int argc, char ** argv)
{
	SortedListPtr list = calloc(1, sizeof(SortedListPtr));
	list = SLCreate(intcf, destroy);
	int *p = calloc(1,sizeof(int));
	*p = 32;
	int *q = calloc(1,sizeof(int));
	*q = 5;
	int *e = calloc(1,sizeof(int));
	*e = 4;
	int *f = calloc(1,sizeof(int));
	*f = 4;
	int *m = calloc(1,sizeof(int));
	*m = 12; 
	int *n = calloc(1,sizeof(int));
	*n = 6;
	int *o = calloc(1,sizeof(int));
	*o = 2;
	int *s = calloc(1,sizeof(int));
	*s = 3;
	//printf("%d\n", intcf(q, p));
	SLInsert(list, p);
	SLInsert(list, q);
	SLInsert(list, e);
	SLInsert(list, f);
	SLInsert(list, m);
	SLInsert(list, n);
	SLInsert(list, o);
	SLInsert(list, s);
	PrintList(list);
	SLRemove(list, q);
	PrintList(list); 
	SortedListIteratorPtr iterator = SLCreateIterator(list);
	printf("%d \n", *(int *)SLGetItem(iterator));
	SLNextItem(iterator);
	SLNextItem(iterator);
	printf("%d \n", *(int *)SLGetItem(iterator));
	SLDestroy(list);  
 	SLDestroyIterator(iterator);

	SortedListPtr list2 = calloc(1, sizeof(SortedListPtr));
	list2 = SLCreate(strcf, destroy);
	char *a = calloc(1,sizeof(char *));
	a = "chalk";
	char *b = calloc(1,sizeof(char *));
	b = "type";
	char *c = calloc(1,sizeof(char *));
	c = "chalk";
	char *d = calloc(1,sizeof(char *));
	d = "milk";
	char *w = calloc(1,sizeof(char *));
	w = "dogs";
	char *x = calloc(1,sizeof(char *));
	x = "money";
	char *y = calloc(1,sizeof(char *));
	y = "dogs";
	char *z = calloc(1,sizeof(char *));
	z = "cheese";
	//printf("%d\n", intcf(q, p));
	SLInsert(list2, a);
	SLInsert(list2, b);
	SLInsert(list2, c);
	SLInsert(list2, d);
	SLInsert(list2, w);
	SLInsert(list2, x);
	SLInsert(list2, y);
	SLInsert(list2, z);
	PrintStringList(list2);
	SLRemove(list2, b);
	PrintStringList(list2);
	SLDestroy(list2);
	return 0;
}
