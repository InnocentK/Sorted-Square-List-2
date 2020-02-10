/*****************************************
 ** File:    DNode.h
 ** Project: CMSC 341 Project 2 - Square Lists--Round 2, Spring 2018
 ** Author:  Innocent Kironji
 ** Date:    03/15/18
 ** Section: 03
 ** E-mail:  wambugu1@umbc.edu
 **
 **   This file contains the DNode class as well as it's members
 **   This class is the node class of the square linked list and holds the
 **     list's data
 ***********************************************/

#ifndef _DNODE_H_
#define _DNODE_H_

#include "Int341.h"
#include <stddef.h>

class DNode {

 public:

  // Constructor
  // Runs in O(1) time
  DNode();

  // Overloaded Constructor, default next is null
  // Runs in O(1) time
  DNode(const Int341& data, const DNode* next = NULL);

  //Destructor
  ~DNode();

  // Copy constructor
  // Makes a deep copy
  // Runs in O(1) time
  DNode(const DNode& other);

  // overloaded assignment operator
  // Runs in O(1) time
  const DNode& operator=(const DNode& rhs);

  // Helper to swap the data between two nodes
  // Runs in O(1) time
  void swap(DNode* other);
  
  // Member variables are public
  Int341 m_data;
  DNode *m_next;

 private:
};

#endif
