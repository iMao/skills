#include "algo.h"





void createList(PNode & head, int number)
{
	head = new Node(0);
	Node* current_node = head;

	for (int i = 1; i < number; i++)
	{
		current_node->next = new Node(i);
		current_node = current_node->next;
	}
}

void reverseList(PNode & head)
{
	Node* current{ nullptr };
	Node* tmp{ nullptr };

	while (head != nullptr) 
	{
		tmp = head->next;
		head->next = current;
		current = head;
		head = tmp;
	}
	
	head = current;
}

void deleteList(PNode & head)
{
	Node* current{ nullptr };
	while (head != nullptr)
	{
		current = head;
		head = current->next;
		delete current;
	}
}

void insert_after(PNode & head, int key, PNode & elem)
{
	Node* current{ head };
	while (current != nullptr)
	{
		if (current->key == key)
		{
			elem->next = current->next;
			current->next = elem;
			break;
		}
		current = current->next;
	}
}

void test_liner_list()
{
	Node* head{ nullptr };
	PNode& ph = head;

	createList(ph, 5);
	std::cout << std::endl << head;

	reverseList(ph);
	std::cout << std::endl << head;


	Node* i = new Node(7);
	insert_after(ph, 2, i);

	std::cout << std::endl << head;

	deleteList(ph);
	std::cout << std::endl << head;
}


//--------------------------------------------бинарные деревья-----------------------------------------------------------------
void test_binary_tree()
{







}
