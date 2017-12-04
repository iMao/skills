#ifndef _ALGO_H_
#define _ALGO_H_


#include <iostream>



//----------------------------------алгоритмы-------------------------------------------------------------------------------

//----------------------------------односвязные списки----------------------------------------------------------------------

struct Node {
	int key;
	Node* next;

	Node() {}
	Node(int key) :key(key), next(nullptr) {}
	~Node() { key = 0; }

	friend std::ostream& operator<<(std::ostream&  os, Node* head) 
	{
		if (head == nullptr)
			os << "(head ==nullptr) list is empty" << std::endl;
		else
		{
			Node* current_node = head;
			os << "Head -> ";

			while (current_node != nullptr)
			{
				os << "[" << current_node->key << "]-> "<<(current_node->next == nullptr ? "nullptr" : "");
				current_node = current_node->next;
			}
		}
		return os;
	}
};


void createList(Node* head, int number);

void reverseList(Node* head);






void test_liner_list();































#endif

