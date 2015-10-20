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
	
	if(head == NULL)
		return false;

	const int N = 5;

	for(std::size_t i = 1; i < N; ++i)
	{
		dsLinkedList_append(&head, i);
	}

	if (dsLinkedList_length(head) != N)
		return false;

	dsLinkedList_clear(&head);

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

	dsLinkedList_clear(&head);

	return testPass;
}