/**
*	Names:
*	David Lambropoulos
*	Demetrios Lambropoulos
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorted-list.h"
 
SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df)
{ // Begin SLCreate

	// If an the CompareFuncT or DestructFuncT functions that are
	// passed to the SLCreate function is NULL, returns NULL.
	if (cf == NULL || df == NULL)
	{
		return NULL;
	}

	// Allocated the memory required for the SortedList pointer
	// size of the SortedList structure.
	SortedListPtr sl = calloc(1, sizeof(SortedListPtr));

	// Set the Comparator function to the inputed CompareFuncT
	sl->cf = cf;

	// Set the Destructor function of the SortedList struct
	// to the inputed DestructFuncT function.
	sl->df = df;

	// Set the item count in the list to 0.
	sl->manyItems = 0;

	// Return the SortedListPtr to user.
	return sl;
} // End SLCreate

/**
*	SLRemove looks for a given object in a list and removes it
*	from the list.
*	Inputs: 
*	list - A pointer to a list.
*	newObj - void pointer to be found.
**/
int SLRemove(SortedListPtr list, void *newObj)
{
	if (list == NULL || newObj == NULL)
	{
		return 0;
	}
	Node curr = list->head;
	Node prev = NULL;
	
	if ((list->cf)(curr->data, newObj) == 0)
	{
		list->head = curr->next;
		free(curr);
		return 1;	
	}
	for( ; curr != 0; curr = curr->next)
	{
		if ((list->cf)(curr->data, newObj) == 0)
		{
			prev->next = curr->next;
			free(curr);
			return 1;
		}
		prev = curr;
	}
	return 0;
}

/**
*	SLDestroy destorys a SortedListPtr list given to it.
*	Inputs:
*	list - sortedListPtr to be destroyed.
**/
void SLDestroy(SortedListPtr list)
{ // Begin SLDestroy

	// Check that a proper list was passed.
	if (list == NULL)
	{
		return;
	}

	// Check that head is not null.
	if (list->head == 0)
	{ // Begin if-statement

		// Free the memory dynamically allocated for the SortedListPtr
		free(list);

		// End the SLDestroy method.
		return;
	} // End if-statement

	// If the head is not null, iterate through the list
	// freeing all dynamic allocations. Once finished free
	// the memory allocated for head.
	while (list->head != 0)
	{ // Begin while-loop
		Node temp = list->head;
		list->head = temp->next;
		//if (temp->data != NULL)
		//{
		//	list->df(temp->data);
		//}
		list->df(temp);
	} // End while-loop

	// Free the memory dynamically allocated for the head pointer.
	free(list->head);

} // End SLDestroy

/**
*	SLInsert inserts an item into a list in an appropriate
*	location such that it is sorted.
*	Inputs:
*	list - a SortedListPtr that is to be appended to.
*	newObj - a void pointer to an item to be added.
**/
int SLInsert(SortedListPtr list, void *newObj)
{ // Begin SLInsert

	// Check if the list or the newObj entered into the SLInsert method
	// was NULL
	if (list == NULL || newObj == NULL)
	{
		return 0;
	}
	
	Node newNode = calloc(1, sizeof(Node));
	
	newNode->next = 0;
	newNode->data = newObj;
	newNode->numRef = 1;
	
	//printf("%d\n", list->manyItems);
	//printf("%d\n", *(int *)newObj);
	
	/*
	 * Check that the head node in the SortedList is empty. If so, this will insert
	 * the given data newObj to the head of the list.
	 */
	if (list->manyItems == 0)
	{
		list->head = newNode;
		list->manyItems++;
		return 1;
	}
	
	if((list->cf)((list->head)->data, newObj) == 0)
	{
		printf("WARNING: Duplicate Insertion\n");
		return 0;
	}
	else if((list->cf)((list->head)->data, newObj) < 0)
	{
		newNode->next = list->head;
		list->head = newNode;
		list->manyItems++;
		return 1;
	}

	if (list == NULL || list->head == NULL || list->cf == NULL || newNode == NULL)
	{	
		printf("WARNING: Invalid Input\n");
		return 0;
	}

	Node newHead = list->head;
	Node nextNode = newHead->next;

	/**
	 * This infinite while loop is used to traverse the list while still
	 * being ignorant of the size.
	 */
	while(1)
	{
		if (nextNode == NULL)
		{
			list->manyItems++;
			newHead->next = newNode;
			return 1;
		}

		/**
		 * Check if the data in the next node is smaller than the data
		 * in the node n that is passed to the function. If so replace the
		 * node.
		 */
		if ((list->cf)(nextNode->data,newNode->data) < 0)
		{
			newHead->next = newNode;
			newNode->next = nextNode;
			return 1;
		}
		else if ((list->cf)(nextNode->data,newNode->data) == 0)
		{
			printf("WARNING: Duplicate Insertion\n");
			return 0;
		}
		newHead = nextNode;
		nextNode = nextNode->next;
	}

}

/**
*	SLCreateIterator creates an iterator that points to an item in a list.
*	Inputs:
*	list - a SortedListPtr that creates an iterator.
**/
SortedListIteratorPtr SLCreateIterator(SortedListPtr list)
{
	// Check if the list insert is NULL
	if (list == NULL)
	{
		return NULL;
	}

	SortedListIteratorPtr iterator = calloc(1, sizeof(SortedListIteratorPtr));
	iterator->iterator = list->head;
	(list->head)->numRef++;
	return iterator;
}

/**
*	SLDestroyIterator destroys an iterator that points to an item in a list.
*	Inputs:
*	list - a SortedListPtr that destroys an iterator.
**/
void SLDestroyIterator(SortedListIteratorPtr iter)
{
	if (iter == NULL)
	{
		return;
	}
	//free(iter->iterator);
	free(iter);
}

/**
*	SLGetItem returns a void pointer to an item in the list.
**/
void * SLGetItem( SortedListIteratorPtr iter )
{
	if((iter->iterator) == NULL)
	{
		printf("WARNING: Invalid Input\n");
		return 0;
	}
	else
	{
		return (iter->iterator)->data;
	}
};

/**
*	SLNextItem returns a void pointer to an item that a given item
*	in the list points to.
**/
void * SLNextItem(SortedListIteratorPtr iter)
{  
	void* tempData;
	if(iter == NULL)
	{
		printf("The Iterator provided has not been defined correctly!");
		return NULL;
	}
	else if(iter->iterator == NULL)
	{
		printf("This Iterator refers to an empty list.");
		return NULL;
	}
	if((iter->iterator)->numRef == 1)
	{
		if((iter->iterator)->next != NULL)
		{
			(iter->iterator)->numRef--; //Decrease current nodes count
			tempData = iter->iterator; //Save data in node
			iter->iterator = (iter->iterator)->next;//Move iterator to next node
			(iter->iterator)->numRef++;//Increase current nodes count
			return tempData;
		}
		else
		{
			printf("Cannot proceed forward. End of list has been reached!");
			return NULL;
		}
	}
	return NULL;

}  

void PrintList(SortedListPtr list)
{ // Begin PrintList
//	if (list == NULL)
//	{
//		return;
//	}
//	Node n = list->head;
//	while(n != NULL)
//	{
//		printf("apple\n");
//		printf("%d\n", *((int *)n->data));
//		n = n->next;
//	}
//	return;

	Node n = list->head;
	for(;n!=0;n=n->next) 
	{
		printf("%d ",*((int*)n->data));
	}
	printf("\n");
} // End PrintList

void PrintStringList(SortedListPtr list)
{
	Node n = list->head;
	for(;n!=0;n=n->next) 
	{
		printf("%s ", (char *)n->data);
	}
	printf("\n");
}

