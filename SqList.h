/*****************************************
 ** File:    SqList.h
 ** Project: CMSC 341 Project 2 - Square Lists--Round 2, Spring 2018
 ** Author:  Innocent Kironji
 ** Date:    03/15/18
 ** Section: 03
 ** E-mail:  wambugu1@umbc.edu
 **
 **   This file contains the SqList class and it's members
 **   This class manages the entire square list
 ***********************************************/

#ifndef _SQLIST_H_
#define _SQLIST_H_

#include <list>
#include "INode.h"

class SqList {

 public:
  // Constructor
  // Runs in O(1) time
  SqList();

  // Copy constructor
  // Makes a deep copy
  // Runs in O(n) time
  SqList(const SqList& other);

  // Destructor
  ~SqList();

  // overloaded assignment operator
  // Runs in O(n) time
  const SqList& operator=(const SqList& rhs);

  // Inserts an item into the appropriate sorted position in a SqList
  // Duplicates are allowed
  // Should call consolidate() after insertion
  // Runs in O(sqrt(n)) time (not counting consolodate)
  void add(const Int341& data);

  // Removes a value from a SqList and returns its value
  // If data is not valid throw an out_of_range exception
  // Should call consolidate() after removal
  // Runs in O(sqrt(n)) time (not counting consolodate)
  Int341 remove(const Int341& data);

  // Removes an item from a given position and returns its value
  // Positions start at index 0
  // If pos is not valid throw an out_of_range exception
  // Should call consolidate() after removal
  // Runs in O(sqrt(n)) time (not counting consolodate)
  Int341 removeAt(int pos);

  // Returns data at a given position by reference (data can be modified)
  // Positions start at index 0
  // If pos is not valid throw an out_of_range exception
  // Does not need to check if a modified items preserves list order
  // Runs in O(sqrt(n)) time 
  Int341& operator[](int pos);

  // Returns the position of the first occurrence of a value
  // Positions start at index 0
  // Returns -1 if data does not appear in list
  // Runs in O(sqrt(n)) time
  int indexOf(const Int341& data);

  // Returns number of items in SqList. Used for grading
  // Runs in O(1) time
  int numItems();

  // debugging function. Prints out contents.
  // running time does not matter
  void dump();

  // grading function used to examine private data members.
  // Do not implement!
  void inspector();

 private :
  
  std::list<INode> m_iList;
  int m_total_size;

  // Helps with cleaning up memeory created by dynamic DNodes
  void deleteDNodes();

  // Checks if an individual inner list is too short
  bool isShort(int inner_size);

  // Checks if an individual inner list is too long
  bool isLong(int inner_size);

  // Helps with adding to inner lsits
  void addToInner(INode& index, const Int341& data, DNode* tempD);

  // Helps with removing at node in an inner lsits
  Int341 innerRemoval(INode& index, const Int341& data, bool& not_removed);

  // Helps with removing when desired position is within an inner list
  Int341 removeAtInner(INode& index, const int POS, int curr_len, bool& not_removed);

  // Helps with finding a node at a specific position
  DNode* find(INode& index, const int POS, int curr_len, bool& not_found);

  // Helps with indexing items in inner lsits
  int indexInInner(INode& index, const Int341& data, int curr_len);

  // Helps with determining where to split a node
  DNode* splitAt(INode& index, int& split_pos);

  // Helps with checking and deleting empty INodes
  void checkEmpty(std::list<INode>::iterator& it);

  // Combines and splits lists as necessary to keep squareness
  // Must not call contructor, copy constructor or assignment operator 
  //   of Int341 class
  // Runs in O(sqrt(n)) not counting splits
  void consolidate();
};

#endif
