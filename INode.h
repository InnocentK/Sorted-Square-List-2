/*****************************************
 ** File:    INode.h
 ** Project: CMSC 341 Project 2 - Square Lists--Round 2, Spring 2018
 ** Author:  Innocent Kironji
 ** Date:    03/15/18
 ** Section: 03
 ** E-mail:  wambugu1@umbc.edu
 **
 **   This file contains the INode class and it's members
 **   This class assists with helping to maintain speeds of O(sqrt(n)) in most
 **     of the square list's processes
 ***********************************************/

#ifndef _INODE_H_
#define _INODE_H_

#include "DNode.h"
#include <stddef.h>

class INode {

 public:
  // Constructor
  // Runs in O(1) time
  INode();

  // Overloaded Constructor
  // Runs in O(1) time
  INode(DNode* d_node);

  // Second Overloaded Constructor
  // Used in consolidation
  // Runs in O(1) time
  INode(DNode* d_node, int size);

  // Copy constructor
  // Makes a shallow copy (because of how I manipulate INodes)
  // Not used in SqList copy constructor
  // Runs in O(1) time
  INode(const INode& other);

  // overloaded assignment operator
  // Makes a deep copy
  // Runs in O(n) time, where n = number of items until the next INode (or NULL)
  const INode& operator=(const INode& rhs);

  // Member variables are public
  DNode *m_dNode;
  int m_size;

 private :
};

#endif
