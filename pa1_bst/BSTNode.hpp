/*
* Author: Megan Chu
* PID: A12814536
* April 14, 2017
* PA1 CSE 100 2017
*
* defines a BSTNode class that takes type Data, and defines public and 
* private functions and members
*
*/

#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>

/** Starter code for PA1, CSE 100 2017
 * Authors: Christine Alvarado, based on code by Paul Kube 
 *          Megan Chu
 */
template<typename Data>
class BSTNode {

public:

  BSTNode<Data>* left;
  BSTNode<Data>* right;
  BSTNode<Data>* parent;
  Data const data;   // the const Data in this node.

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d);


  /** Return the successor of this BSTNode in a BST, or 0 if none.
   ** PRECONDITION: this BSTNode is a node in a BST.
   ** POSTCONDITION:  the BST is unchanged.
   ** RETURNS: the BSTNode that is the successor of this BSTNode,
   ** or 0 if there is none.
   */ 
  BSTNode<Data>* successor(); 
}; 


// Function definitions
// For a templated class it's easiest to just put them in the same file as 
// the class declaration


/* constructor for BSTNode, with data d, and no parent or children*/
template <typename Data>
BSTNode<Data>::BSTNode(const Data & d) : left(0), right(0), parent(0), data(d)
{}


/* Return a pointer to the BSTNode that contains the item that is 
 * sequentially next in the tree */
template <typename Data>
BSTNode<Data>* BSTNode<Data>::successor()
{
  if(right) // if there is right child
  {
    BSTNode<Data>* curr = right;
    while(curr->left) // traverse to leftmost child of right child
    {
      curr = curr->left;
    }
    return curr; // returns leftmost child of right child, or just right 
    // child if it doesn't have left childen
  }

  else if(parent && (parent->data < data)) 
  // this is a right child of its parent
  {    
    BSTNode<Data>* findP = parent;
    while(findP->parent) 
    // traverse parents until parent is greater than current node
    {
      if(findP->data < (findP->parent)->data)
      {
        return findP->parent;
      }
      findP = findP->parent;
    } // if loop exits without finding greater parent, then no successor
    return NULL;    
  }

  else if(parent && (data < parent->data)) // this is left child of its parent
  {
    return parent; // left child with no right child has parent as successor
  }
  else // this has no right child or parent
  {
    return NULL; // there is no successor
  }
}


/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
