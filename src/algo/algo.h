/*
 * изучение базовых алгоритмов и структур данных
 * автор Андрей Макаров
 */


#ifndef SRC_ALGO_ALGO_H
#define SRC_ALGO_ALGO_H

#include <iostream>
#include <array>



//------------------------------------------------------------------------------
//односвязные списки
//------------------------------------------------------------------------------
struct Node {
  int key;
  Node *next;

  Node() {}
  Node(int key) : key(key), next(nullptr) {}
  ~Node() { key = 0; }

  friend std::ostream &operator<<(std::ostream &os, Node *head) {
    if (head == nullptr)
      os << "(head ==nullptr) list is empty" << std::endl;
    else {
      Node *current_node = head;
      os << "Head -> ";

      while (current_node != nullptr) {
        os << "[" << current_node->key << "]-> "
           << (current_node->next == nullptr ? "nullptr" : "");
        current_node = current_node->next;
      }
    }
    return os;
  }
};

typedef Node *PNode;

void createList(PNode &head, int number);

void reverseList(PNode &head);

void deleteList(PNode &head);

void insert_after(PNode &head, int key, PNode &elem);

void TestLinerList();



//------------------------------------------------------------------------------
//бинарные деревья
//------------------------------------------------------------------------------
template <typename _Ty> struct NodeTree {
  _Ty key;
  NodeTree *left;
  NodeTree *right;
  NodeTree *parent;

  NodeTree() {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
  NodeTree(_Ty key, NodeTree *left, NodeTree *right, NodeTree *parent)
      : key(key), left(left), right(right), parent(parent) {}
  ~NodeTree() {}
};

template <typename _Ty, int n>
NodeTree<_Ty> *createBinaryTree(std::array<_Ty, n> &keys) {
  return nullptr;
}

void TestBinaryTree();

#endif
