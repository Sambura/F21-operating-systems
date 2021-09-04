#include <stdio.h>
#include <stdlib.h>

struct LinkedListNode {
	struct LinkedList* parent;
	struct LinkedListNode* next;
	int value;
};

struct LinkedList {
	struct LinkedListNode* head;
	struct LinkedListNode* tail;
	int size;
};

void print_list(struct LinkedList* list) {
	if (list->size < 1) {
		printf("[ ]\n");
		return;
	}

	struct LinkedListNode* current = list->head;
	printf("[ %d", current->value);
	while (current->next != NULL) {
		current = current->next;
		printf(", %d", current->value);
	}
	printf(" ]\n\n");
}
struct LinkedListNode* create_node(int value, struct LinkedList* parent) {
	struct LinkedListNode* node = (struct LinkedListNode*)malloc(sizeof(struct LinkedListNode));
	*node = (struct LinkedListNode ){ parent, NULL, value };
	return node;
}
struct LinkedListNode* insert_last(struct LinkedList* list, int value) {
	struct LinkedListNode* newNode = create_node(value, list);

	if (list->size == 0) {
		list->head = newNode;
		list->tail = newNode;
		list->size = 1;
	}
	else {
		list->tail->next = newNode;
		list->tail = newNode;
		list->size++;
	}

	return newNode;
}
struct LinkedListNode* insert_after(struct LinkedListNode* insertAfter, int value) {
	struct LinkedList* list = insertAfter->parent;

	if (insertAfter == list->tail)
		return insert_last(list, value);

	struct LinkedListNode* newNode = create_node(value, list);
	newNode->next = insertAfter->next;
	insertAfter->next = newNode;
	list->size++;
	return newNode;
}
void delete_node(struct LinkedListNode* node) {
	struct LinkedList* list = node->parent;
	list->size--;

	if (node == list->head) {
		list->head = node->next;
		free(node);

		if (list->size == 0)
			list->tail = NULL;

		return;
	}

	struct LinkedListNode* current = list->head;

	while (current->next != node)
		current = current->next;

	current->next = node->next;
	if (node == list->tail)
		list->tail = current;
	free(node);
}

int main(void) {
	struct LinkedList list = { NULL, NULL, 0 };

	insert_last(&list, 1);
	struct LinkedListNode* node2 = insert_last(&list, 2);
	insert_last(&list, 3);

	printf("Inintial structure:\n");
	print_list(&list);

	printf("Insert '4' after '2':\n");
	insert_after(node2, 4);
	print_list(&list);

	printf("Delete '2':\n");
	delete_node(node2);
	print_list(&list);

	return 0;
}