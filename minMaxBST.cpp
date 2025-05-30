// bst_min_max.cpp
// Demonstrates finding the minimum and maximum elements in a Binary Search Tree (BST) using leftmost and rightmost traversal.
#include <iostream>
using namespace std;

class Node
{
public:
  int data;
  Node *left, *right;
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
  int findMin()
  {
    if (!root)
      throw runtime_error("Tree is empty");
    Node *curr = root;
    while (curr->left)
      curr = curr->left;
    return curr->data;
  }
  int findMax()
  {
    if (!root)
      throw runtime_error("Tree is empty");
    Node *curr = root;
    while (curr->right)
      curr = curr->right;
    return curr->data;
  }
};

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

  cout << "Min element: " << tree.findMin() << endl;
  cout << "Max element: " << tree.findMax() << endl;
  return 0;
}
