#include "algo.h"





void createList(Node* head, int number)
{
	head = new Node(0);
	Node* current_node = head;

	for (int i = 1; i < number; i++)
	{
		current_node->next = new Node(i);
		current_node = current_node->next;
	}

	
}

void reverseList(Node * head)
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

void test_liner_list()
{
	Node** phead{ nullptr };
	Node* head{ nullptr };

	phead = &head;

	createList(*phead, 5);

	std::cout << std::endl;
	std::cout << *phead;

	reverseList(*phead);

	std::cout << std::endl;
	std::cout << *phead;





}
