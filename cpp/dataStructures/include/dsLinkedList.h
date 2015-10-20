#ifndef _DS_LINKEDLIST_H_
#define _DS_LINKEDLIST_H_

#include "defines.h"

/**
 * @brief Single Linked List
 * @details Class represent linked list node with int data type
 * 
 */
class dsLinkedList
{
public:
	dsLinkedList(int value);
	virtual ~dsLinkedList();

	inline int getData() const { return this->data; }
	inline void setData(int value) { this->data = value; }

	inline dsLinkedList* getNext() const { return this->next; }
	inline void setNext(dsLinkedList* nextNode) { this->next = nextNode; }

protected:
	int data;
	dsLinkedList* next;
};

/**
 * @brief inserts a new node at the beggining of linked list
 * and make new node the head of linked list
 * 
 * @param head existing head of linked list
 * @param value value of the new node to be created
 */
void dsLinkedList_insert(dsLinkedList** head, int value);

/**
 * @brief inserts a new node at the end of linked list
 * If linked list is empty, new node is created 
 * and head with then  point to the new node
 * 
 * @param head existing head of linked list
 * @param value new node created with this value
 */
void dsLinkedList_append(dsLinkedList** head, int value);

/**
 * @brief Append bHead to end of aHead and mark bHead NULL
 * 
 * @param aHead head of first linked list
 * @param bHead head of second linked list
 */
void dsLinkedList_append(dsLinkedList** aHead, dsLinkedList** bHead);

/**
 * @brief insert a new node in linked list at index with the given value
 * @details index should be between 0..length
 * 
 * @param head [head of the linked list]
 * @param index [0 based index(0..length) at which node should be created]
 * @param value [value of the new node]
 */
STATUS dsLinkedList_insertNth( dsLinkedList** head, std::size_t index, int value);

/**
 * @brief Given a sorted list (in increasing order), 
 * insert a new node with value into the correct sorted position
 * 
 * @param head head of the linked list
 * @param value value of the new node
 */
void dsLinkedList_sortedInsert( dsLinkedList** head, int value);

/**
 * @brief Deletes the head Node and fills argument data with the head node's data
 * 
 * @param head head of the linked list
 * @param data head node's data
 * 
 * @return STATUS NO_ERR if head is not null
 */
STATUS dsLinkedList_pop(dsLinkedList** head, int& data);

/**
 * @brief Deallocates all the nodes in linked list and sets the head pointer to NULL
 * 
 * @param head [head of the linked list]
 */
void dsLinkedList_clear(dsLinkedList** head);

dsLinkedList* dsLinkedList_find(dsLinkedList* head, int value);

/**
 * @brief Returns data value stored at index N. N is 0 based index
 * 
 * @param head head of the linked list
 * @param N index (0 based)
 * @param data data stored at Nindex
 * 
 * @return NO_ERR if Nindex is between 0 & (length(linkedList) - 1)
 */
STATUS dsLinkedList_getNValue(const dsLinkedList* head, std::size_t Nindex, int& data);

void dsLinkedList_print(const dsLinkedList* head, std::ostream& os);

/**
 * @brief Length of the linked list given its head
 * 
 * @param head [head of the linked list]
 * @return [number of elements in linked list]
 */
std::size_t dsLinkedList_length(const dsLinkedList* head);
bool dsLinkedList_loopExists(dsLinkedList* head);
bool dsLinkedList_loopDetails(dsLinkedList* head, dsLinkedList** loopNode, std::size_t& loopLength);

dsLinkedList* dsLinkedList_copy(const dsLinkedList* head);

/**
 * @brief Checks if linked list is sorted in increasing order
 * 
 * @param head head of the linked list
 * @return true if linked list is sorted in increasing order; false otherwise
 */
bool dsLinkedList_isSorted(const dsLinkedList* head);

/**
 * @brief Given a list, rearrange nodes so they are sorted in increasing order
 * 
 * @param head Reference to the head of linked list
 */
void dsLinkedList_insertSort(dsLinkedList** head);

/**
 * @brief Given a list, split it into two sublists - front and back half
 * @details in case of odd elements, extra element should go in front list. 
 * For example: {2,3,5,7,11} => {2,3,5} and {7, 11}. 
 * PS: At the very least, solution should work for lengths of 2,3,4
 * 
 * @param source [description]
 * @param frontHead [description]
 * @param backHead [description]
 */
void dsLinkedList_frontBackSplit(dsLinkedList* source, dsLinkedList** frontHead, dsLinkedList** backHead);
void dsLinkedList_alternatingSplit(dsLinkedList* source, dsLinkedList** aHead, dsLinkedList** bHead);
/**
 * @brief Given a sorted list in increasing order, delete duplicate nodes from the list
 * @details [long description]
 * 
 * @param head [description]
 */
void dsLinkedList_sortedRemoveDuplicates(dsLinkedList* head);
void dsLinkedList_moveNode(dsLinkedList** aHead, dsLinkedList** bHead);
dsLinkedList* dsLinkedList_alternateMerge(dsLinkedList* aHead, dsLinkedList* bHead);
dsLinkedList* dsLinkedList_sortedListsMerge(dsLinkedList* aHead, dsLinkedList* bHead);
void dsLinkedList_mergeSort(dsLinkedList* head);
dsLinkedList* dsLinkedList_sortedIntersect(dsLinkedList* aHead, dsLinkedList* bHead);
void dsLinkedList_reverse(dsLinkedList** head);
void dsLinkedList_recursiveReverse(dsLinkedList** head);

#endif // _DS_LINKEDLIST_H_