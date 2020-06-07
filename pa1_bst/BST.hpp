/*
* Author: Megan Chu
* PID: A12814536
* Date: April 14, 2017
* PA1 CSE 100 2017
*
* defines the functions in the BST class, insert, find, size, height, 
* empty, and the destructor
*/

#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>

template<typename Data>
class BST {

public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
      This is inlined because it is trivial.
   */
  BST() : root(nullptr), isize(0) {}


  /** Default destructor.
      Delete every node in this BST.
  */
  ~BST();

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return a pair where the first element is an iterator 
   *  pointing to either the newly inserted element or the element 
   *  that was already in the BST, and the second element is true if the 
   *  element was newly inserted or false if it was already in the BST.
   * 
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=)  
   */
  std::pair<iterator, bool> insert(const Data& item);


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=).  For the reasoning
   *  behind this, see the assignment writeup.
   */
  iterator find(const Data& item) const;

  
  /** Return the number of items currently in the BST.
   */ 
  unsigned int size() const;
  
  /** Return the height of the BST.
      height of a tree starts with root at height 0
	  height of an empty tree is -1 (0 not -1)
   */ 
  int height() const;

  /** Return true if the BST is empty, else false.
   */
  bool empty() const;

  /** Return an iterator pointing to the first (smallest) item in the BST.
   */ 
  iterator begin() const;

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const;


private:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;
  
  /** Number of Data items stored in this BST. */
  unsigned int isize;

  /** Find the first element of the BST
   * Helper function for the begin method above.
   */ 
  static BSTNode<Data>* first(BSTNode<Data>* root);

  /** do a postorder traversal, deleting nodes
   */
  static void deleteAll(BSTNode<Data>* n);

  /** method to recursively calls itself to find longest path in bst
   * This is a helper for the height() method
   */
  int heightHelper(BSTNode<Data>* curr) const;
 };


// ********** Function definitions ****************


/** Default destructor.
    Delete every node in this BST.
*/
template <typename Data>
BST<Data>::~BST() {
  deleteAll(root);
}


/** Given a reference to a Data item, insert a copy of it in this BST.
 *  Return a pair where the first element is an iterator pointing to either 
 *  the newly inserted element or the element that was already in the BST, 
 *  and the second element is true if the element was newly inserted or 
 *  false if it was already in the BST.
 *  Parameter: int data reference of new node to insert
 */
template <typename Data>
std::pair<BSTIterator<Data>, bool> BST<Data>::insert(const Data& item) 
{
  if (!root) // if tree empty make item root
  {
    root = new BSTNode<Data>(item);
    ++isize;
    return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(root), true);
  }

  BSTNode<Data>* curr = root;
  
  while (curr->left || curr->right) // if there is at least one child
  {
    if(curr->left && item < curr->data) 
    // if item less than current node and there is still a left child
    {
      curr = curr->left;
    }
    else if(item < curr->data)
    // if no left child, curr is parent node
    {
      break;
    }
    else if(curr->right && curr->data < item) 
    // if current node less than item and there is still a right child
    {
      curr = curr->right;
    }
    else if(curr->data < item)
    // if no right child, curr is parent node
    {
      break;
    }
  }

  if(curr->data == item)
  // cannot insert duplicate item
  {
    return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(curr), false);
  }

  // Ready to insert
  BSTNode<Data>* newNode = new BSTNode<Data>(item);
  if (item < curr->data) // left child if smaller than parent
  {
    curr->left = newNode;
    newNode->parent = curr;
    ++isize;
    return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(curr->left), 
                                              true);
  }
  else // right child if greater than parent
  {
    curr->right = newNode;
    newNode->parent = curr;
    ++isize;
    return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(curr->right), 
                                              true);
  }
}


/** Find a Data item in the BST.
 *  Return an iterator pointing to the item, or pointing past
 *  the last node in the BST if not found.
 *  Parameter: Data reference of node to find
 */
template <typename Data>
BSTIterator<Data> BST<Data>::find(const Data& item) const
{
  BSTNode<Data>* curr = root;
  while (curr) // while we are still at a node in BST
  {
    if (curr->data < item) // if item greater than curr, traverse right
    {
      curr = curr->right;
    }
    else if (item < curr->data) // if item less than curr, traverse left
    {
      curr = curr->left;
    }
    else // item = data at curr node
    {
      return BSTIterator<Data>(curr);
    }
  }
  return BSTIterator<Data>(nullptr);
}

  
/** Return the number of items currently in the BST.
 */ 
template <typename Data>
unsigned int BST<Data>::size() const
{
  return isize;
}

/** Return the height of the BST.
 */
template <typename Data> 
int BST<Data>::height() const
{
  if(isize == 0 || isize == 1)
  // size of empty, and only root are both 0
  {
    return 0;
  }
  return heightHelper(root) -1; // find longest path recursively
}


/** Return the longest path length in the BST
 * Parameter: BSTNode<Data> pointer to starting node
 */
template <typename Data>
int BST<Data>::heightHelper(BSTNode<Data>* curr) const
{
  if(!(curr->right || curr->left)) // no children
  {
    return 1; // count curr leaf node
  }
     
  int rightLen;
  int leftLen;
  rightLen = 0;
  leftLen = 0;
     
  if(curr->right) // if there is right child get length or right path
  {
    rightLen = heightHelper(curr->right);
  }
  if(curr->left) // if there is left child get lenth of left path
  {
    leftLen = heightHelper(curr->left);
  }
     
  if(leftLen < rightLen) // return longest length + 1 for curr node
  // rightLen longer
  {
    return rightLen + 1;
  }
  else // leftLen is longer
  {
    return leftLen + 1;
  }
}


/** Return true if the BST is empty, else false.
 */ 
template <typename Data>
bool BST<Data>::empty() const
{
  if(isize == 0) // no nodes in tree
  {
    return true;
  }
  else
  {
    return false;
  }
}

/** Return an iterator pointing to the first (smallest) item in the BST.
 */ 
template <typename Data>
BSTIterator<Data> BST<Data>::begin() const
{
  return BSTIterator<Data>(first(root));
}

/** Return an iterator pointing past the last item in the BST.
 */
template <typename Data>
BSTIterator<Data> BST<Data>::end() const
{
  return BSTIterator<Data>(nullptr);
}

/** Find the first element of the BST
 * Helper function for the begin method above.
 * Parameter: BSTNode<Data> pointer to sarting root node
 */ 
template <typename Data>
BSTNode<Data>* BST<Data>::first(BSTNode<Data>* root)
{
  BSTNode<Data>* curr = root;
  while(curr->left) // the left-most child of root is the first node
  {
    curr = curr->left;
  }
  return curr;
}

/** do a postorder traversal, deleting nodes
 * Parameter: BSTNode<Data> pointer to root node starts post-order traversal
 */
template <typename Data>
void BST<Data>::deleteAll(BSTNode<Data>* n)
{
   if(!n) // current node is null
  {
    return;
  }

  deleteAll(n->left); // traverse left subtree and delete
  deleteAll(n->right); // traverse right subtree and delete
    
  // remove/delete current node
  n->left = NULL;
  n->right = NULL;
  n->parent = NULL;
  delete n;
  n = NULL;
}


#endif //BST_HPP
