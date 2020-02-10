/*****************************************
 ** File:    DNode.cpp
 ** Project: CMSC 341 Project 2 - Square Lists--Round 2, Spring 2018
 ** Author:  Innocent Kironji
 ** Date:    03/15/18
 ** Section: 03
 ** E-mail:  wambugu1@umbc.edu
 **
 **   This file contains implementation of the DNode class
 **   This class helps maintain the data of the square list
 ***********************************************/

#include "DNode.h"
#include <cstddef>

// Constructor
DNode::DNode(){
  m_data.m_data = 0;
  m_next = NULL;
}

// Overloaded Constructor, default next is null
// Runs in O(1) time
DNode::DNode(const Int341& data, const DNode* next){
  m_data = data;
  m_next = const_cast<DNode*>(next);
}

// Destructor
// Simply resets the data to help with debugging
DNode::~DNode(){
  m_data.m_data = 0;
}

// Copy constructor
// Makes a deep copy
// Runs in O(1) time
DNode::DNode(const DNode& other){

  m_data = other.m_data;

  // Cannot copy next or other's data will be affected
  m_next = NULL;
}

// overloaded assignment operator
// Runs in O(1) time
const DNode& DNode::operator=(const DNode& rhs){

  // Checks for self-assignment
  if (this == &rhs)
    return *this;

  m_data = rhs.m_data;

  // Cannot copy next or rhs's data will be affected
  m_next = NULL;

  return *this;
}

// Helper to swap the data between two nodes
// Runs in O(1) time
void DNode::swap(DNode* other){

  // Checks if position holds something
  if (other == NULL)
    return;

  int temp_data = m_data.m_data;
  m_data = other->m_data;
  other->m_data.m_data = temp_data;
}
