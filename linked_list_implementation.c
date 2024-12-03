#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct ListNode
{
	void* data;
	struct ListNode* previous;
	struct ListNode* next;
};

struct ListNode* createListNode(void* data, struct ListNode* prev, struct ListNode* next);
int linkedListAppend(struct ListNode* head, void* data);
struct ListNode* linkedListGetNode(struct ListNode* head, int index);
void* linkedListGet(struct ListNode* head, int index);
void linkedListListContents(struct ListNode* head);
void linkedListDeleteNode(struct ListNode* node);
int linkedListDestroy(struct ListNode* head);
void* linkedListPop(struct ListNode* head,int index);

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
	
	printf("Element at index 1: %d\n", *(int*) linkedListGet(numberList,1));
	puts("Contents of list before deleting second element:\n");
	linkedListListContents(numberList);
	linkedListDeleteNode(numberList->next);
	puts("Contents of list after deleting second element:");
	linkedListListContents(numberList);
	
	puts("Contents of new list after adding five elements");
	int* numbers[5]; 
	for (int i = 0; i < 5; i++)
	{
		numbers[i] = (int*) malloc(sizeof(int));
		*numbers[i] = 3*i+3;
		linkedListAppend(numberList, (void *) numbers[i]);
	}
	linkedListListContents(numberList);
	printf("Element at index 2: %d\n", *(int*) linkedListGetNode(numberList,2)->data);
	printf("Popping element at index 3. Value: %d\n", *(int*) linkedListPop(numberList,3));
	puts("Content of list after deleting element at index 3: ");
	linkedListListContents(numberList);
	linkedListDestroy(numberList);
	//linkedListListContents(numberList); // This line of code should segfault.


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

struct ListNode* linkedListGetNode(struct ListNode* head, int index)
{
	if (head->previous != NULL)
	{
		return NULL; // Not head of list.
	}
	struct ListNode* current_node = head;
	for (int i = 0; i < index; i++)
	{
		if (current_node->next == NULL)
		{
			return NULL; // Index too large
		}
		current_node = current_node->next;
	}
	return current_node;
}
void* linkedListGet(struct ListNode* head, int index)
{
	if (head->previous != NULL)
	{
		return NULL; // Not head of list.
	}
	struct ListNode* current_node = head;
	for (int i = 0; i < index; i++)
	{
		if (current_node->next == NULL)
		{
			return NULL; // Index too large
		}
		current_node = current_node->next;
	}
	return current_node->data;
}
void linkedListListContents(struct ListNode* head) 
// Currently assumes int
{
	struct ListNode* current_node = head;
	int index = 0;
	while (current_node != NULL)
	{
		printf("Data %d: %d\n",index, *(int *) current_node->data);
		current_node = current_node->next;
		index++;
	}
}
void linkedListDeleteNode(struct ListNode* node)
{
	struct ListNode* nextNode = node->next;
	struct ListNode* prevNode = node->previous;

	if (nextNode != NULL)
	{
		nextNode->previous = prevNode;
	}
	if (prevNode != NULL)
	{
		prevNode->next = nextNode;
	}

	free(node->data); // This will break stuff if the node's data is passed by reference
	free(node);

	return;
}
int linkedListDestroy(struct ListNode* head)
{
	if (head->previous != NULL)
	{
		return -1;
	}

	struct ListNode* current_node = head;
	struct ListNode* next_node = head->next;

	while (current_node->next != NULL)
	{
		current_node = current_node->next;
		linkedListDeleteNode(current_node->previous);
	}
	linkedListDeleteNode(current_node);
	return 0;
}
void* linkedListPop(struct ListNode* head,int index)
{
	struct ListNode* target_node = linkedListGetNode(head,index);
	struct ListNode* nextNode = target_node->next;
	struct ListNode* prevNode = target_node->previous;

	if (nextNode != NULL)
	{
		nextNode->previous = prevNode;
	}
	if (prevNode != NULL)
	{
		prevNode->next = nextNode;
	}
	
	void* data = target_node->data;
	free(target_node);
	return data;
}
