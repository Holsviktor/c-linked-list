#include <stdio.h>
#include <stdlib.h>
struct ListNode
{
	void* data;
	struct ListNode* previous;
	struct ListNode* next;
};
struct ListNode* createListNode(void* data, struct ListNode* prev, struct ListNode* next);
int linkedListAppend(struct ListNode* head, void* data);

int main()
{
	int* first_number = (int *) malloc(sizeof(int));
	*first_number = 5;
	int* second_number = (int *) malloc(sizeof(int));
	*second_number = 10;
	int* third_number = (int *) malloc(sizeof(int));
	*third_number = 17;

	struct ListNode* numberList = createListNode((void *) first_number, NULL, NULL);
	if (linkedListAppend(numberList, (void *) second_number) == -1)
	{
		puts("First append failed, this is bad.\n");
	}
	if (numberList->next == NULL)
	{
		printf("New element: %d", *(int *) numberList->next->data);
	}
	if (linkedListAppend(numberList, (void *) third_number) == -1)
	{
		puts("Second append failed, this is also bad.\n");
	}
	struct ListNode* current_node = numberList;
	while (current_node != NULL)
	{
		printf("Data: %d\n", *(int *) current_node->data);
		current_node = current_node->next;
	}
	
	return 0;
}
struct ListNode* createListNode(void* data, struct ListNode* prev, struct ListNode* next)
{
	struct ListNode* newNode = (struct ListNode *) malloc(sizeof(struct ListNode));
	newNode->previous = prev;
	newNode->next = next;
	newNode->data = data;

	return newNode;
	
}
int linkedListAppend(struct ListNode* head, void* data)
{
	if (head->previous != NULL)
	{
		return -1; // Not head of list.
	}
	struct ListNode* current_node = head;

	// Find end of list
	while (current_node->next != NULL)
	{
		current_node = current_node->next;
	}

	// Append new node to list.
	struct ListNode* newNode = createListNode(data, current_node, NULL); 
	current_node->next = newNode;

	return 0;
}
