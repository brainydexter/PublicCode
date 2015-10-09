#include "dsLinkedList.h"

dsLinkedList::dsLinkedList(int value)
	: data(value), next(NULL) {}

dsLinkedList::~dsLinkedList()
{
	next = NULL;
}

void dsLinkedList_insert(dsLinkedList** head, int value)
{
	dsLinkedList* node = new dsLinkedList(value);

	node->setNext(*head);
	*head = node;
}

/**
 * @brief Append bHead to end of aHead and mark bHead NULL
 * 
 * @param aHead head of first linked list
 * @param bHead head of second linked list
 */
void dsLinkedList_append(dsLinkedList** aHead, dsLinkedList** bHead)
{
	if(*bHead == NULL) return;

	if(*aHead == NULL)
	{
		*aHead = *bHead;
		*bHead = NULL;
		return;
	}

	// traverse to the end of linked list
	dsLinkedList* current = *aHead;
	while(current->getNext() != NULL)
	{
		current = current->getNext();
	}

	current->setNext(*bHead);
	*bHead = NULL;
	return;
}

/**
 * @brief insert a new node in linked list at index with the given value
 * @details index should be between 0..length
 * 
 * @param head [head of the linked list]
 * @param index [0 based index(0..length) at which node should be created]
 * @param value [value of the new node]
 */
STATUS dsLinkedList_insertNth( dsLinkedList** head, std::size_t index, int value)
{
	// if we are trying to insert at the beginning, its the same as regular insert
	if(index == 0) 
	{
		dsLinkedList_insert(head, value);
	}

	dsLinkedList* current = *head;

	for(std::size_t i = 0; i < index - 1; ++i)
	{
		if(current == NULL)
		{
			return ERR_OUT_OF_BOUNDS;
		}

		current = current->getNext();
	}

	if(current == NULL)
		return ERR_OUT_OF_BOUNDS;

	//insert new node at current->next
	dsLinkedList* newNode = new dsLinkedList(value);
	newNode->setNext(current->getNext());
	current->setNext(newNode);

	return NO_ERR;	
}

void dsLinkedList_clear(dsLinkedList** head)
{
	dsLinkedList *next = NULL, *current = *head;

	while(current)
	{
		next = current->getNext();

		delete current;

		current = next;
		*head = current;
	}
}

dsLinkedList* dsLinkedList_find(dsLinkedList* head, int value)
{
	while (head)
	{
		if (head->getData() == value)
		{
			return head;
		}

		head = head->getNext();
	}
	return NULL;
}

void dsLinkedList_print(const dsLinkedList* head, std::ostream& os)
{
	if(!head)
	{
		os << "Empty Linked list \n";
	}

	while (head)
	{
		os << head->getData() << " (" << head << ")";
		os << ((head->getNext() != NULL) ? " -> " : " -> .\n");

		head = head->getNext();
	}
}

bool dsLinkedList_loopExists(dsLinkedList* head)
{
	if (head == NULL)
	{
		return false;
	}

	dsLinkedList *slow = head, *fast = head;
	do
	{
		if (fast->getNext() && fast->getNext()->getNext())
		{
			fast = fast->getNext()->getNext();
		}
		else
		{
			return false;
		}

		slow = slow->getNext();

		if(slow == fast)
			return true;
	}
	while(fast != NULL);
	
	return false;
}

bool dsLinkedList_loopDetails(dsLinkedList* head, dsLinkedList** loopNode, std::size_t& loopLength)
{
	if (head == NULL)
	{
		return false;
	}

	*loopNode = NULL;
	loopLength = 0;
	bool found = false;
	
	dsLinkedList *slow = head, *fast = head;
	do
	{
		if (fast->getNext() && fast->getNext()->getNext())
		{
			fast = fast->getNext()->getNext();
		}
		else
		{
			return false;
		}

		slow = slow->getNext();

		if(slow == fast)
		{
			found = true;
			break;
		}
	}
	while(fast != NULL);
	
	if(found)
	{
		slow = head;
		while(slow != fast)
		{
			slow = slow->getNext();
			fast = fast->getNext();
		}

		*loopNode = slow;
		while(slow->getNext() != *loopNode)
		{
			++loopLength;
			slow = slow->getNext();
		}
		++loopLength; //including the loopNode
	}

	return found;
}