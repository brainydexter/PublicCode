#include "utils.h"

#include "dsLinkedList.h"

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

	return 0;
}