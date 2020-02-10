/*****************************************
 ** File:    INode.cpp
 ** Project: CMSC 341 Project 2 - Square Lists--Round 2, Spring 2018
 ** Author:  Innocent Kironji
 ** Date:    03/15/18
 ** Section: 03
 ** E-mail:  wambugu1@umbc.edu
 **
 **   This file contains implementation of the INode Class
 **   This class is used to index specific portions of the square list
 **     in order to increase speed of traversal
 ***********************************************/

#include "INode.h"
#include <iostream>

// Default Constructor
// Runs in O(1) time
INode::INode(){

  m_dNode = new DNode();
  m_size = 0;
}

// Overloaded constructor
// Runs in O(1) time
INode::INode(DNode* d_node){

  m_dNode = new DNode(d_node->m_data, d_node->m_next);
  m_size = 1;
}

// Second Overloaded constructor
// Used in consolidation (where size needs to be specified
// Runs in O(1) time
INode::INode(DNode* d_node, int size){

  m_dNode = d_node;
  m_size = size;
}

// Copy constructor
// Makes a shallow copy (because it is not used for SqList copy)
// Runs in O(1) time
INode::INode(const INode& other){

  m_size = other.m_size;
  m_dNode = other.m_dNode;
}

// overloaded assignment operator
// Makes a deep copy
// Runs in O(n) time, where n = number of items until the next INode (or NULL)
const INode& INode::operator=(const INode& rhs){

  // Checks for self-assignement
  if (this == &rhs)
    return *this;

  m_size = rhs.m_size;
  m_dNode = new DNode(rhs.m_dNode->m_data);

  DNode* rhs_curr = rhs.m_dNode;
  DNode* curr = m_dNode;

  // Iterates through the INode creating a deep copy of each item
  // The last DNode copied points at NULL
  for (int i = 0; i < rhs.m_size; i++){
      curr->m_next = new DNode(rhs_curr->m_data);
      rhs_curr = rhs_curr->m_next;
      curr = curr->m_next;
  }
  
  return *this;
}
