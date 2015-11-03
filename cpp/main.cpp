#include "utils.h"

#include "dsLinkedList.h"

#include "testDsLinkedList.h"

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
	outputStream << "Test test_dsLinkedList_append status : " << convertBoolToString(test_dsLinkedList_append()) << std::endl;
	outputStream << "Test test_dsLinkedList_getNValue status : " << convertBoolToString(test_dsLinkedList_getNValue()) << std::endl;
	outputStream << "Test test_dsLinkedList_pop status : " << convertBoolToString(test_dsLinkedList_pop()) << std::endl;
	outputStream << "Test test_dsLinkedList_isSorted status : " << convertBoolToString(test_dsLinkedList_isSorted()) << std::endl;
	outputStream << "Test test_dsLinkedList_sortedInsert status : " << convertBoolToString(test_dsLinkedList_sortedInsert()) << std::endl;
	outputStream << "Test test_dsLinkedList_insertSort status : " << convertBoolToString(test_dsLinkedList_insertSort()) << std::endl;
	

	return 0;
}
