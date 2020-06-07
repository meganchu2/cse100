/*
* Author: Megan Chu
* PID: A12814536
* Date: April 12, 2017
* PA1 CSE 100 2017
*
* defines the functions in the BSTInt class, insert, find, size, height, 
* empty, and the destructor
*/

#include "BSTInt.h"

/* Function definitions for a int-based BST class */


/** Default destructor.
    Delete every node in this BST.
*/
BSTInt::~BSTInt() {
  deleteAll(root);
}


/** Given a reference to a Data item, insert a copy of it in this BST.
 *  Return  true if the item was added to this BST
 *  as a result of this call to insert,
 *  false if an item equal to this one was already in this BST.
 *  Parameter: int data value of new node to insert
 */
bool BSTInt::insert(int item)
{
  if (!root) // if tree empty make item root
  {
    root = new BSTNodeInt(item);
    ++isize;
    return true;
  }

  BSTNodeInt* curr = root;
  
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
    return false;
  }

  // Ready to insert
  BSTNodeInt* newNode = new BSTNodeInt(item);
  if (item < curr->data) // left child if smaller than parent
  {
    curr->left = newNode;
    newNode->parent = curr;
  }
  else // right child if greater than parent
  {
    curr->right = newNode;
    newNode->parent = curr;
  }

  ++isize;
  return true;

}


/** Find a Data item in the BST.
 *  Return true if the item is in the BST or false otherwise
 *  Parameter: int data value of node to find
 */
bool BSTInt::find(int item) const
{
  BSTNodeInt* curr = root;
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
      return true;
    }
  }
  return false;
}

  
/** Return the number of items currently in the BST.
 */
unsigned int BSTInt::size() const 
{
  return isize;
}

  
/** Return the height of the BST.
    Height of tree with just root node is 0
 */
int BSTInt::height() const
{
  if(isize == 0 || isize == 1)
  // size of empty, and only root are both 0
  {
    return 0;
  }
  return heightHelper(root) - 1; // find longest path recursively
}


/** Return the longest path length in the BST
 * Parameter: BSTNodeInt pointer to starting node
 */
int BSTInt::heightHelper(BSTNodeInt* curr) const
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
bool BSTInt::empty() const 
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


/** do a postorder traversal, deleting nodes
 * This is a helper for the destructor
 * This method is static because it acts on BSTNodeInts
 *   and not on the BSTInt object directly.
 *   Parameter: BSTNodeInt pointer to node to start postorder deletion
 */
void BSTInt::deleteAll(BSTNodeInt* n)
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

