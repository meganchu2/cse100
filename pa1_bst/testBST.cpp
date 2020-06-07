/*
* Author: Megan Chu and Christine Alvarado
* PID: A12814536
* Date: April 14, 2017
* PA1 CSE 100 2017
*
* code that will test methods defined in BSTInt.cpp, BST.hpp, and 
* BSTIterator.hpp for correctness (also indirectly tests node classes)
* 
*/

#include "BSTInt.h"
#include "BST.hpp"
#include "BSTIterator.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;

/**
 * A test driver for the BST int class and class template.
 * PA1 CSE 100 2017
 * Author: Christine Alvarado and Megan Chu
 */
int main() {

    /* Create an STL vector of some ints */
    /*test*/
    vector<int> v;
    v.push_back(3);

    /* Create an instance of BST holding int */
    BSTInt b;

    /* Test empty. */
    cout << "Checking BSTInt empty" << endl;
    if(!b.empty())
    {
        cout << "  Incorrect return value for empty BST" << endl;
        return -1;
    }

    // Could use: for(auto item : v) instead of the line below
    cout << "Initializing tester BSTInt" << endl;
    cout << "Checking initial BSTInt insert" << endl;
    b.insert(3); // insert item
    bool found = b.find(3);
    if(!found) // new item should have been found in bst
    {
      cout << "  Insert not found!!" << endl;
      return -1;
    }

    /* Test insert for duplicates */
    cout << "Checking duplicate BSTInt insert" << endl;
    bool duplicate1 = b.insert(3);
    if(duplicate1) // duplicate should not have been inserted
    {
      cout << "  Incorrect return value for duplicate insert" << endl;
      return -1;
    }
    cout << "  Duplicate was not inserted" << endl;
    
    /* checking return value of good inserts */
    cout << "Checking rest of BSTInt initialization inserts" << endl;
    v.push_back(4);
    v.push_back(1);
    v.push_back(100);
    v.push_back(-33);

    for(int item : v) 
    {
        if(item != 3)
        {
          bool pr = b.insert(item);
          if(! pr ) {
              cout << "  Incorrect bool return value when inserting " << item 
                   << endl;
              return -1;
          }
        }
    }
    cout << "  All items inserted successfully" << endl;


    /* Test size. */
    cout << "Checking initialized size" << endl;
    cout << "  Size is: " << b.size() << endl;
    if(b.size() != v.size()) {
        cout << "  ... which is incorrect." << endl;
        return -1;
    }


    /* Test height, should be 2 */
    cout << "Checking initial height" << endl;
    cout << "  Height is: " << b.height() << endl;
    if(b.height() != 2)
    {
      cout << "  Incorrect return value for height" << endl;
      return -1;
    }


    /* For buggy insert method, it may possibly overwrite a node that is 
     * the only child of another node. */
    cout << "Checking 2nd insert" << endl;
    v.push_back(0);
    b.insert(0); // will overwrite -33 in buggy implementation

    // Test height after adding int that increments height to 3.
    cout << "  Height is: " << b.height() << endl;
    if(b.height() != 3) // height should have incremented
    {
        cout << "  Incorrect return value for height" << endl;
        return -1;
    }
    cout << "  Size is: " << b.size() << endl;
    if(b.size() != v.size()) // size should have incremented
    {
        cout << "  ... which is incorrect." << endl;
        return -1;
    }


    /* Test find return value. */
    // Test the items that are already in the tree
    cout << "Checking find" << endl;
    for(int item : v) {
        if(!b.find(item)) {
            cout << "  Incorrect return value when finding " << item << endl;
            return -1;
        }
    }
    cout << "  All items found" << endl;    

    
    /* Test insert for new item. */
    cout << "Checking 3rd insert" << endl;
    v.push_back(2);
    bool insertTwo = b.insert(2);
    if(!insertTwo) // should have inserted good insert
    {
        cout << "  Incorrect bool return value when inserting" << 2 << endl;
        return -1;
    }
    cout << "  Size is: " << b.size() << endl;
    if(b.size() != v.size())  // size after insert
    {
        cout << "  Incorrect size after insert" << v.size() << endl;
        return -1;
    }
    if(!b.find(2)) // find newly inserted item
    {
        cout << "  Inserted item not found" << 2 << endl;
        return -1;
    }
    cout << "  New insert found in BST!" << endl;
    

    /* Test empty. */
    cout << "Checking empty" << endl;
    if(b.empty()) // should not be empty
    {
        cout << "  Incorrect return value for unempty BST" << endl;
        return -1;
    }   



    /* UNCOMMENT THE LINES BELOW TO TEST THE TEMPLATE-BASED ITERATOR */

    // Test the template version of the BST  with ints 
    cout << "Initializing template-based BST..." << endl;
    BST<int> btemp;
    for (int item : v) {
        // The auto type here is the pair of BSTIterator<int>, bool
        cout << "Inserting " << item << " into the int template-based BST...";
        auto p = btemp.insert(item);
        if (*(p.first) != item) {
            cout << "Wrong iterator returned.  "
                 << "Expected " << item << " but got " << *(p.first) << endl;
            return -1;
        }
        if (!p.second) {
            cout << "Wrong boolean returned.  Expected true but got " 
                 << p.second << endl;
            return -1;
        }
        cout << "success!" << endl;
              
    }

    // Now test finding the elements we just put in
    for (int item: v) {
        cout << "Finding " << item << "...." << endl;
        BSTIterator<int> foundIt = btemp.find(item);
        if (*(foundIt) != item) {
            cout << "incorrect value returned.  Expected iterator pointing "
                 << "to " << item << " but found iterator pointing to " 
                 << *(foundIt) << endl;
            return -1;
        }
        cout << "success!" << endl;
    }


    // Test the iterator: The iterator should give an in-order traversal
  
    // Sort the vector, to compare with inorder iteration on the BST
    sort(v.begin(),v.end());

    cout << "traversal using iterator..." << endl;
    auto vit = v.begin();
    auto ven = v.end();

    // This is equivalent to BSTIterator<int> en = btemp.end();
    auto en = btemp.end();

    //This is equivalent to BST<int>::iterator it = btemp.begin();
    auto it = btemp.begin();
    for(; vit != ven; ++vit) 
    {
        if(! (it != en)) 
        {
            cout << *it << "," << *vit 
                 << ": Early termination of BST iteration." << endl;
            return -1;

        }
        cout << *it << endl;
        if(*it != *vit) {
            cout << *it << "," << *vit 
                 << ": Incorrect inorder iteration of BST." << endl;
            return -1;
        }
        ++it;
    }

    cout << "success!" << endl;

    /* Check template-based bst size and height */
    cout << "Checking template BST Size and Height" << endl;
    cout << "  Size is: " << btemp.size() << endl;
    cout << "  Height is: " << btemp.height() << endl;
    if(btemp.size() != v.size())
    {
      cout << "  Incorrect return value for size" << endl;
      return -1;
    }
    if(btemp.height() != 3)
    {
      cout << "  Incorrect return value for height" << endl;
      return -1;
    }

    /* Check that template-based bst is not empty */
    cout << "Checking template BST Emptiness" << endl;
    bool full = btemp.empty();
    if(full)
    {
      cout << "  Incorrect return value for empty" << endl;
      return -1;
    }

    
    /* tests for a different template-based bst */
    BST<int> btemp1;
    v.clear();
    v.push_back(0);
    v.push_back(2);
    v.push_back(1);
    // Test the template version of the BST  with ints 
    cout << "Initializing 2nd template-based BST..." << endl;
    for (int item : v) {
        // The auto type here is the pair of BSTIterator<int>, bool
        cout << "Inserting " << item << " into the int template-based BST...";
        auto p = btemp1.insert(item);
        if (*(p.first) != item) {
            cout << "Wrong iterator returned.  "
                 << "Expected " << item << " but got " << *(p.first) << endl;
            return -1;
        }
        if (!p.second) {
            cout << "Wrong boolean returned.  Expected true but got " 
                 << p.second << endl;
            return -1;
        }
        cout << "success!" << endl;
              
    }

    // Now test finding the elements we just put in
    for (int item: v) {
        cout << "Finding " << item << "...." << endl;
        BSTIterator<int> foundIt = btemp1.find(item);
        if (*(foundIt) != item) {
            cout << "incorrect value returned.  Expected iterator pointing "
                 << "to " << item << " but found iterator pointing to " 
                 << *(foundIt) << endl;
            return -1;
        }
        cout << "success!" << endl;
    }

    /* Check template-based bst size and height */
    cout << "Checking template BST Size and Height" << endl;
    cout << "  Size is: " << btemp1.size() << endl;
    cout << "  Height is: " << btemp1.height() << endl;
    if(btemp1.size() != v.size())
    {
      cout << "  Incorrect return value for size" << endl;
      return -1;
    }
    if(btemp1.height() != 2)
    {
      cout << "  Incorrect return value for height" << endl;
      return -1;
    }

    /* Check template-based bst size and height */
    cout << "Checking template BST Size and Height after new insert" << endl;
    v.push_back(-1);
    btemp1.insert(-1);
    cout << "  Size is: " << btemp1.size() << endl;
    cout << "  Height is: " << btemp1.height() << endl;
    if(btemp1.size() != v.size())
    {
      cout << "  Incorrect return value for size" << endl;
      return -1;
    }
    if(btemp1.height() != 2)
    {
      cout << "  Incorrect return value for height" << endl;
      return -1;
    }   
    

    // Test the iterator: The iterator should give an in-order traversal
  
    // Sort the vector, to compare with inorder iteration on the BST
    sort(v.begin(),v.end());

    cout << "traversal using iterator..." << endl;
    vit = v.begin();
    ven = v.end();

    // This is equivalent to BSTIterator<int> en = btemp.end();
    en = btemp1.end();

    //This is equivalent to BST<int>::iterator it = btemp.begin();
    it = btemp1.begin();
    for(; vit != ven; ++vit) 
    {
        if(! (it != en)) 
        {
            cout << *it << "," << *vit 
                 << ": Early termination of BST iteration." << endl;
            return -1;

        }
        cout << *it << endl;
        if(*it != *vit) {
            cout << *it << "," << *vit 
                 << ": Incorrect inorder iteration of BST." << endl;
            return -1;
        }
        ++it;
    }

    cout << "success!" << endl;


    cout << "All tests passed!" << endl;
    return 0;
}
