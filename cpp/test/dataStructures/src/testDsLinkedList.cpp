#include "testDsLinkedList.h"

#include "dsLinkedList.h"

#include "defines.h"

dsLinkedList* build_dsLinkedList()
{
	const int N = 4;
	dsLinkedList* head = NULL;

	for (int i = N; i >= 0; --i )
	{
		dsLinkedList_insert(&head, i);
	}

	return head;
}

bool test_dsLinkedList_appendTail()
{
	dsLinkedList* head = NULL;

	dsLinkedList_append(&head, 0);
	
	if(head == NULL || head->getData() != 0)
		return false;

	if(test_dsLinkedList_getNValue())
	{
		const int N = 5;

		for(std::size_t i = 1; i < N; ++i)
		{
			dsLinkedList_append(&head, i);

			int data = -1;
			if( (dsLinkedList_getNValue(head, i, data) != NO_ERR) || data != i)
				return false;
		}

		if (dsLinkedList_length(head) != N)
			return false;

		dsLinkedList_clear(&head);
	}

	return true;
}

bool test_dsLinkedList_length()
{
	dsLinkedList* head = NULL;

	const int N = 5;

	for (int i = N; i >= 0; --i )
	{
		dsLinkedList_insert(&head, i);
	}

	if(dsLinkedList_length(head) != N+1)
		return false;

	dsLinkedList_clear(&head);

	return true;
}

bool test_dsLinkedList_getNValue()
{
	int data = 0;
	bool testPass = true;
	dsLinkedList* head = NULL;

	if(dsLinkedList_getNValue(head, 3, data) != ERR_OUT_OF_BOUNDS)
		return false;

	head = build_dsLinkedList();

	// check golden case
	if( (dsLinkedList_getNValue(head, 2, data) != NO_ERR) || (data != 2) )
		testPass = false;

	if( dsLinkedList_getNValue(head, 5, data) != ERR_OUT_OF_BOUNDS)
		testPass = false;

	dsLinkedList_clear(&head);

	return testPass;
}

bool test_dsLinkedList_pop()
{
	int data = 0;
	bool testPass = true;
	dsLinkedList* head = NULL;

	if(dsLinkedList_pop(&head, data) != ERR_NULL_PTR)
		return false;

	head = build_dsLinkedList();

	if( (dsLinkedList_pop(&head, data) != NO_ERR) || (data != 0) )
		testPass = false;

	// ensure data was popped
	if( (dsLinkedList_pop(&head, data) != NO_ERR) || (data != 1) ) 
		testPass = false;

	dsLinkedList_clear(&head);

	return testPass;
}

bool test_dsLinkedList_isSorted()
{
	dsLinkedList* head = NULL;

	if(dsLinkedList_isSorted(head) == false)
		return false;

	head = build_dsLinkedList();

	if(dsLinkedList_isSorted(head) == false)
		return false;

	dsLinkedList_clear(&head);

	if(test_dsLinkedList_appendTail() == true)
	{
		// building list : 5 , 2 , 3
		dsLinkedList_append(&head, 5);
		dsLinkedList_append(&head, 2);
		dsLinkedList_append(&head, 3);

		if(dsLinkedList_isSorted(head) == true)
			return false;
	}
	else
	{
		return false;
	}

	return true;
}

bool test_dsLinkedList_sortedInsert()
{
	// check if isSorted is working OK
	if(test_dsLinkedList_isSorted())
	{
		// check if empty
		dsLinkedList* head = NULL;
		
		// check if single element gets inserted correctly
		dsLinkedList_sortedInsert(&head, 4);
		if(head->getData() != 4 || (!dsLinkedList_isSorted(head)))	return false;

		dsLinkedList_sortedInsert(&head, 8);
		dsLinkedList_sortedInsert(&head, 7);
		if(!dsLinkedList_isSorted(head))	return false;

		// inserting at the starting of list
		dsLinkedList_sortedInsert(&head, 2);
		if(!dsLinkedList_isSorted(head))	return false;

		// inserting in the middle of list
		dsLinkedList_sortedInsert(&head, 5);
		if(!dsLinkedList_isSorted(head))	return false;

		// inserting in the end of list
		dsLinkedList_sortedInsert(&head, 10);
		if(!dsLinkedList_isSorted(head))	return false;

		// inserting duplicate
		dsLinkedList_sortedInsert(&head, 10);
		if(!dsLinkedList_isSorted(head))	return false;

	} else return false;

	return true;
}

bool test_dsLinkedList_insertSort()
{
	if (test_dsLinkedList_isSorted() && test_dsLinkedList_appendTail())
	{
		dsLinkedList* head = NULL;
		dsLinkedList_insertSort(&head); 
		if(!dsLinkedList_isSorted(head))	return false;

		// check if single element is sorted correctly
		dsLinkedList_append(&head, 5); dsLinkedList_insertSort(&head);
		if(!dsLinkedList_isSorted(head))	return false;

		// check if golden case works
		dsLinkedList_append(&head, 8);
		dsLinkedList_append(&head, 7);
		dsLinkedList_insertSort(&head);
		if(!dsLinkedList_isSorted(head))	return false;

		// ll should be 5->7->8. check if duplicate at end is handled
		dsLinkedList_append(&head, 8); dsLinkedList_insertSort(&head);
		if(!dsLinkedList_isSorted(head))	return false;

	} else return false;

	return true;
}