/*
Iterator Coding Exercise
Given the following definition of a Node<T>, 
please implement preorder traversal that returns a sequence of Ts. 
I have greatly simplified the problem by adding an accumulator argument into 
the preorder_traversal()  function.

*/

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct Node
{
    T value;
    Node *left{nullptr}, *right{nullptr}, *parent{nullptr};

    Node(T value) : value(value) {}

    Node(T value, Node<T> *left, Node<T> *right) : value(value), left(left), right(right) {
      left->parent = right->parent = this;
    }

    ~Node()
    {
      if(left)
        delete left;
      if(right)
        delete right;
      if(parent)
        delete parent;
    }

    // traverse the node and its children preorder
    // and put all the results into `result`
    void preorder_traversal(vector<Node<T>*>& result)
    {
      // Adding current node first
       result.push_back(this);

       // traverse left subtree
       if(left)
         left->preorder_traversal(result);

       // traverse right subtree
       if(right)
         right->preorder_traversal(result);
    }
};


int main()
{
    // Creating a simple binary tree
    //         1
    //        / \
    //       2   3
    //      / \
    //     4   5
    
    Node<int>* n4 = new Node<int>(4);
    Node<int>* n5 = new Node<int>(5);
    Node<int>* n2 = new Node<int>(2, n4, n5);
    Node<int>* n3 = new Node<int>(3);
    Node<int>* n1 = new Node<int>(1, n2, n3);

    
    vector<Node<int>*> result;
    n1->preorder_traversal(result);
    
    cout << "Preorder Traversal: ";
    for(auto node : result)
    {
        cout << node->value << " ";
    }
    cout << endl;
  return 0;
}