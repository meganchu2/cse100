/*
* Author: Megan Chu
* PID: A12814536
* Date: April 14, 2017
* PA1 CSE 100 2017
*
* defines the BSTIterator class, and overloads operators
*/

#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP
#include "BSTNode.hpp"
#include <list>
#include <iterator>


// Notice this class extends the std::iterator class.
template<typename Data>
class BSTIterator : public std::iterator<std::input_iterator_tag,Data> {

private:

  BSTNode<Data>* curr;

public:

  /** Constructor.  Use the argument to initialize the current BSTNode
   *  in this BSTIterator.
   */ 
  BSTIterator(BSTNode<Data>* curr);

  /** Dereference operator. */
  Data operator*() const;
  
  /** Pre-increment operator. */
  BSTIterator<Data>& operator++();

  /** Post-increment operator. */
  BSTIterator<Data> operator++(int);

  /** Equality test operator. */
  bool operator==(BSTIterator<Data> const & other) const;

  /** Inequality test operator. */ 
  bool operator!=(BSTIterator<Data> const & other) const;

};

/** Constructor.  Use the argument to initialize the current BSTNode
 *  in this BSTIterator.
 *  Parameter: BSTNode<Data> pointer to set as curr for iterator
 */ 
template<typename Data>
BSTIterator<Data>::BSTIterator(BSTNode<Data>* curr) 
{
  this->curr = curr;
}


/** Dereference operator. */
template<typename Data>
Data BSTIterator<Data>::operator*() const 
{
  return curr->data;
}
  

/** Pre-increment operator. */
template<typename Data>
BSTIterator<Data>& BSTIterator<Data>::operator++() 
{
  // Call the successor method of the BSTNode pointed to by curr.
  curr = curr->successor();
  return *this;
}


/** Post-increment operator. */
template<typename Data>
BSTIterator<Data> BSTIterator<Data>::operator++(int) 
{
  BSTIterator before = BSTIterator(curr); // stores current iterator to return
  ++(*this); // increment to the successor
  return before;
}


/** Equality test operator. 
 * Notice that other is a reference and not a pointer, thus it cannot be null
 * Return true if other IS EQUAL to the calling object
 * Two iterators are equal if they point to the same BSTNode in the same BST
 * Parameter: reference to BSTIterator<Data>, not pointer so cannot be null
 */
template<typename Data>
bool BSTIterator<Data>::operator==(BSTIterator<Data> const & other) const 
{ 
  if(!other.curr && !curr) // if both iterators point to null nodes
  {
    return true;
  }
  else if(!other.curr || !curr) // if only one iterator points to null node
  {
    return false;
  }  
  else if(curr == other.curr) // if pointer to BSTNodes are equivalent
  {
    return true;
  }
  else // pointer to BSTNodes are not equivalent
  {
    return false;
  }
}


/** Inequality test operator. 
 * Notice that other is a reference and not a pointer, thus it cannot be null
 * Return true if other is NOT equal to the calling object
 * Two iterators are equal if they point to the same BSTNode in the same BST
 */ 
template<typename Data>
bool BSTIterator<Data>::operator!=(BSTIterator<Data> const & other) const 
{
  if(!other.curr && !curr) // if both iterators point to null nodes
  {
    return false;
  }
  else if (!other.curr || !curr) // if only one iterator points to null node
  {
    return true;
  }
  if(curr != other.curr) // if pointer to BSTNodes are not equivalent
  {
    return true;
  }
  else // if pointer to BSTNodes are equivalent
  {
    return false;
  }
}

#endif //BSTITERATOR_HPP
