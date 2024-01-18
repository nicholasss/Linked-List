// creating and using singly linked lists

// Nicholas Zingleman @ 15-Jan-2024

#include <stdio.h>
#include <stdlib.h>

// Create Node Structure
typedef struct {
	void * next;
	int data;
} Node;

// First node that points into our list
Node *head = NULL;

// Add node to the list
Node *addNode(int data) {
	Node *new = NULL;

	// First insertion
	if (NULL == head) {
		new = malloc(sizeof(Node));
		if (NULL == new) {
			printf("Issue with malloc operation.\n");
			return NULL;
		}

		new->data = data; // Setting data
		head = new;		  // Setting the head pointer to point to the new head
		new->next = NULL; // Setting the nodes link, to null, as its the first
	} else {
	// Creating additional nodes *at the front*
		new = malloc(sizeof(Node));
		if (NULL == new) {
			printf("Issue with malloc operation.\n");
			return NULL;
		}

		new->data = data; // Setting data
		new->next = head; // Setting the nodes link, to the previous first or head
		head = new; 	  // Setting the head pointer to the new pointer
	}

	return new;
}

// remove a node from the list
int removeNode(int data) {
	printf("\n================================\n");
	printf("Finding '%d' to remove from list.\n", data);

	Node *current = head;
	Node *previous = NULL;
	int nodeCounter = 1;
	
	while (current != NULL) {

		if (current->data == data) {
			// if current node is list head
			if (current == head) {
				head = current->next;
				free(current);
				current = NULL;
			
			} else {
			// if current node is in the list
				previous->next = current->next;
				free(current);
				current = NULL;
			}

			printf("================================\n");
			printf("Data '%d' was found\n", data);
			printf("Node %d was removed\n", nodeCounter);
			printf("================================\n\n");
			return 1;
		}
		previous = current;
		current = current->next;
		nodeCounter += 1;
	}

	printf("================================\n");
	printf("Data '%d' was not found in list.\n", data);
	printf("================================\n\n");
	return 0;
}

// insert a node into a position in the list
// create new node
// walk to before the new position
// set the current->next to the following
// set the previous->next to the current
Node *insertNode(int data, int position) {
	Node *current = head;
	Node *previous = NULL;
	int nodeCounter = 1;

	Node *new = NULL;

	if (head == NULL) {
		printf("Requesting insert on empty list.\nPlease use Add instead.\n");
		return NULL;
	}

	if (position == 1) {
		printf("*** WARNING - Inserting at position 1 has a memory leak bug.\n");
	}
	
	while (current != NULL) {

		if (position == nodeCounter) {
			new = malloc(sizeof(Node));
			if (NULL == new) {
				printf("Issue with malloc operation.\n");
				return NULL;
			}
			new->data = data;

			new->next = current;
			if (previous!= NULL) {
				previous->next = new;
			}
			return new;
		}

		previous = current;
		current = current->next;
		nodeCounter += 1;
	}

	if (position > nodeCounter) {
		printf("Requested position too far into list.\n");
		return NULL;
	}
}


// print the list
void printList() {
	Node *current = head;
	int nodeCounter = 1;

	printf("\nCurrent Linked List:\n");
	printf("================================\n");
	printf("Head of List\n");
	printf("Address: %p - First Node: %p\n", &head, head);
	printf("================================\n");
	while (current != NULL) {
		
		printf("Node: %d    - Data: %d\n", nodeCounter, current->data);
		printf("Address: %p - Next Address: %p\n", current, current->next);
		printf("================================\n");

		current = current->next; // using the nodes links
		nodeCounter += 1;
	}
	printf(" \n");
}

// print menu
void printMenu() {
	printf("You have the following options: \n");
	printf("1. Add a node to the list.\n");
	printf("2. Remove a node to the list\n");
	printf("3. Insert a node to the list\n");
	printf("4. Print current list\n");
	printf("5. Quit.\n");
	return;
}

int main(int argc, char const *argv[])
{
	int option = -1;
	while (option != 5) {
		printMenu();
		int numReceived = scanf("%d", &option);

		if (numReceived == 1 && option > 0 && option <= 5) {
			switch (option) {
			case 1:
				printf("Enter number to add to node: ");
				scanf("%d", &option);
				Node *newAdded = addNode(option);
				
				// Reset option to beginning value
				option = -1;
				break;
			case 2:
				printf("Enter number to remove from list: ");
				scanf("%d", &option);
				removeNode(option);

				option = -1;
				break;
			case 3:
				int insertData, insertPosition;
				
				printf("Please enter a number to insert to the list:\n");
				scanf("%d", &insertData);
				printf("Please enter an insert position:\n");
				scanf("%d", &insertPosition);

				Node *newInserted = insertNode(insertData, insertPosition);

				option = -1;
				break;
			case 4:
				printList();
				break;
			case 5:
				exit(0);
				break;
			default:
				printf("Unknown option picked: %d\n", option);
				break;
			}
		
			
		}
	}
	

	return 0;
}
