#include "dsLinkedList.h"

dsLinkedList::dsLinkedList(int value)
	: data(value), next(NULL) {}

dsLinkedList::~dsLinkedList()
{
	next = NULL;
}

/**
 * @brief Length of the linked list given its head
 * 
 * @param head [head of the linked list]
 * @return [number of elements in linked list]
 */
std::size_t dsLinkedList_length(const dsLinkedList* head)
{
	std::size_t length = 0;

	while(head != NULL)
	{
		++length;
		head = head->getNext();
	}

	return length;
}

/**
 * @brief inserts a new node at the beggining of linked list
 * and make new node the head of linked list
 * 
 * @param head existing head of linked list
 * @param value value of the new node to be created
 */
void dsLinkedList_insert(dsLinkedList** head, int value)
{
	dsLinkedList* node = new dsLinkedList(value);

	node->setNext(*head);
	*head = node;
}

/**
 * @brief inserts a new node at the end of linked list
 * If linked list is empty, new node is created 
 * and head with then  point to the new node
 * 
 * @param head existing head of linked list
 * @param value new node created with this value
 */
void dsLinkedList_append(dsLinkedList** head, int value)
{
	if(*head == NULL)
		return dsLinkedList_insert(head, value);

	// find tail and insert new node there
	dsLinkedList* current = *head;
	while(current->getNext() != NULL)
	{
		current = current->getNext();
	}

	dsLinkedList* node = new dsLinkedList(value);
	current->setNext(node);
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

/**
 * @brief Given a sorted list (in increasing order), 
 * insert a new node with value into the correct sorted position
 * 
 * @param head head of the linked list
 * @param value value of the new node
 */
void dsLinkedList_sortedInsert( dsLinkedList** head, int value)
{
	dsLinkedList* current = *head;

	if(current == NULL)
	{
		dsLinkedList_insert(&current, value);
		return;
	}

	dsLinkedList* prev = current;

	while(current != NULL && current->getData() < value)
	{
		prev = current;
		current = current->getNext();
	}

	// insert new node with prev->next = newNode. newNode->next = current
	dsLinkedList* newNode = new dsLinkedList(value);

	prev->setNext(newNode);
	newNode->setNext(current);
}

/**
 * @brief Deletes the head Node and fills argument data with the head node's data
 * 
 * @param head head of the linked list
 * @param data head node's data
 * 
 * @return STATUS NO_ERR if head is not null
 */
STATUS dsLinkedList_pop(dsLinkedList** head, int& data)
{
	if (*head == NULL)
	{
		return ERR_NULL_PTR;
	}

	data = (*head)->getData();

	dsLinkedList* next = (*head)->getNext();

	delete *head;
	*head = next;

	return NO_ERR;
}


/**
 * @brief Returns data value stored at index N. N is 0 based index
 * 
 * @param head head of the linked list
 * @param N index (0 based)
 * @param data data stored at Nindex
 * 
 * @return NO_ERR if Nindex is between 0 & (length(linkedList) - 1)
 */
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

/**
 * @brief Returns data value stored at index N. N is 0 based index
 * 
 * @param head head of the linked list
 * @param N index (0 based)
 * @param data data stored at Nindex
 * 
 * @return NO_ERR if Nindex is between 0 & (length(linkedList) - 1)
 */
STATUS dsLinkedList_getNValue(const dsLinkedList* head, std::size_t Nindex, int& data)
{
	for (std::size_t i = 0; head != NULL; ++i)
	{
		if(i == Nindex)
		{
			data = head->getData();
			return NO_ERR;
		}

		head = head->getNext();
	}

	return ERR_OUT_OF_BOUNDS;
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