#include "utils.h"

#include "dsLinkedList.h"

bool test_dsLinkedList_appendTail();
bool test_dsLinkedList_length();
bool test_dsLinkedList_getNValue();
bool test_dsLinkedList_pop();

/**
 * @brief returns a dsLinkedList* 0->1->2->3->4
 * @return head of the linked list
 */
dsLinkedList* build_dsLinkedList();


int main()
{
	std::ostream& outputStream = std::cout;	
	int start = 0, N = 5;
	dsLinkedList* head = NULL;

	for (int i = N; i >= 0; --i )
	{
		dsLinkedList_insert(&head, i);
	}

	dsLinkedList* tail = dsLinkedList_find(head, N);

	int x = 4;
	dsLinkedList* nodeX = dsLinkedList_find(head, x);

	dsLinkedList_print(head, outputStream);

	bool loopExists = dsLinkedList_loopExists(head);
	outputStream << "Loop exists in linked list ? " << convertBoolToString(loopExists);
	outputStream << std::endl;

	outputStream << "Connecting tail to node: " << nodeX->getData() << std::endl;
	tail->setNext(nodeX);

	loopExists = dsLinkedList_loopExists(head);
	outputStream << "Loop exists in linked list ? " << convertBoolToString(loopExists);
	outputStream << std::endl;

	if (loopExists)
	{
		dsLinkedList* loopNode = NULL;
		std::size_t loopLength = 0;
		dsLinkedList_loopDetails(head, &loopNode, loopLength);
		std:: cout << "Loop exists at node: " << loopNode->getData() << " with a length of: " << loopLength;
		outputStream << std::endl;
	}

	outputStream << "Disconnecting tail and pointing it to NULL\n";
	tail->setNext(NULL);

	outputStream << "Deleting all nodes of the linked list\n";
	dsLinkedList_clear(&head);
	dsLinkedList_print(head, outputStream);

	dsLinkedList_insertNth(&head, 0, 50);
	dsLinkedList_insertNth(&head, 1, 70);
	dsLinkedList_insertNth(&head, 1, 60);
	dsLinkedList_insertNth(&head, 3, 80);
	dsLinkedList_print(head, outputStream);
	STATUS status = dsLinkedList_insertNth(&head, 5, 100);
	outputStream << "Trying to insert 100 at index 5 in above linked list: " << ::convertStatusToString(status) << std::endl;
	dsLinkedList_clear(&head);
	dsLinkedList_print(head, outputStream);

	outputStream << "Test test_dsLinkedList_length status : " << convertBoolToString(test_dsLinkedList_length()) << std::endl;
	outputStream << "Test test_dsLinkedList_appendTail status : " << convertBoolToString(test_dsLinkedList_appendTail()) << std::endl;
	outputStream << "Test test_dsLinkedList_getNValue status : " << convertBoolToString(test_dsLinkedList_getNValue()) << std::endl;
	outputStream << "Test test_dsLinkedList_pop status : " << convertBoolToString(test_dsLinkedList_pop()) << std::endl;

	return 0;
}

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