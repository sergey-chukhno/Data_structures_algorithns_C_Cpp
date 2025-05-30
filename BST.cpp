// binary_search_tree.cpp
// Implements a Binary Search Tree (BST) with insert, search, and inorder traversal using dynamic memory allocation (new/delete). The BST maintains sorted order and allows efficient search, insertion, and traversal operations.
#include <iostream>
using namespace std;

class Node
{
public:
  int data;
  Node *left;
  Node *right;
  Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST
{
private:
  Node *root;
  void insert(Node *&node, int val)
  {
    if (!node)
    {
      node = new Node(val);
      return;
    }
    if (val < node->data)
      insert(node->left, val);
    else if (val > node->data)
      insert(node->right, val);
    // If val == node->data, do nothing (no duplicates)
  }
  bool search(Node *node, int val)
  {
    if (!node)
      return false;
    if (node->data == val)
      return true;
    if (val < node->data)
      return search(node->left, val);
    else
      return search(node->right, val);
  }
  void inorder(Node *node)
  {
    if (!node)
      return;
    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
  }
  void destroy(Node *node)
  {
    if (!node)
      return;
    destroy(node->left);
    destroy(node->right);
    delete node;
  }

public:
  BST() : root(nullptr) {}
  ~BST() { destroy(root); }
  void insert(int val) { insert(root, val); }
  bool search(int val) { return search(root, val); }
  void inorder()
  {
    inorder(root);
    cout << endl;
  }
};

// Example usage
int main()
{
  BST tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(7);
  tree.insert(2);
  tree.insert(4);
  tree.insert(6);
  tree.insert(8);

  cout << "Inorder traversal: ";
  tree.inorder();

  int key = 4;
  cout << "Search " << key << ": " << (tree.search(key) ? "Found" : "Not Found") << endl;
  return 0;
}