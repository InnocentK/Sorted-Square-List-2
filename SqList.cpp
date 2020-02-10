/*****************************************
 ** File:    SqList.cpp
 ** Project: CMSC 341 Project 2 - Square Lists--Round 2, Spring 2018
 ** Author:  Innocent Kironji
 ** Date:    03/15/18
 ** Section: 03
 ** E-mail:  wambugu1@umbc.edu
 **
 **   This file contains the implementation of the SqList class 
 **   This class is a data structure known as a square list (implemented
 **     using linked lists). It manages addition and removal from the list
 **     as well as managing all dynamic variables and shape of the lsit
 ***********************************************/

#include "SqList.h"
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

// Constructor, default size is 2
// Runs in O(1) time
SqList::SqList(){

  m_total_size = 0;
}

// Copy constructor
// Runs in O(n) time
SqList::SqList(const SqList& other){

  m_total_size = other.m_total_size;

  // Loops through copying indexes (INodes are copied first)
  for (std::list<INode>::const_iterator it = other.m_iList.begin(); 
       it != other.m_iList.end(); ++it){
    
    DNode* tempD = new DNode(it->m_dNode->m_data);
    INode tempI(tempD, it->m_size);
    m_iList.push_back(tempI);
  }
  
  // Keeps track of the length of the square list up to the position
  //   currently being checked
  int curr_index = 0;
  const int LIST_SIZE = m_iList.size();

  std::list<INode>::const_iterator other_it = other.m_iList.begin();

  // Loops through indexes
  for (std::list<INode>::iterator it = m_iList.begin(); 
       it != m_iList.end(); ++it, ++other_it){

    // Helps with traversing both lists
    DNode* curr = it->m_dNode;
    DNode* other_curr = other_it->m_dNode;
    DNode* temp = NULL;

    // First DNode is skipped because it was copied with the INodes
    if(other_curr != NULL){      
      other_curr = other_curr->m_next;

      // Loops until end of inner list
      for(int i = 1; i < it->m_size; i++){
	
	// Copies data
	if (other_curr != NULL){
	  temp = new DNode(other_curr->m_data);
	  curr->m_next = temp;
	  
	  // Moves on to the next position
	  curr = temp;
	   other_curr = other_curr->m_next;
	}
      }
    }

    // Updates last inner node to point at next INode's m_dNode  
    if (curr_index < LIST_SIZE - 1){
      ++it;
      temp = it->m_dNode;
      --it;
    }
    else
      temp = NULL;
    
    // Connects current inner list with it's neighbor
    curr->m_next = temp;
    curr_index++;
  }
}

// Destructor
SqList::~SqList(){

  // All dynamic memory is cleaned up by SqList
  deleteDNodes();
}

// Helps with cleaning up memeory created by dynamic DNodes
// Private Function that runs in O(n)
void SqList::deleteDNodes(){

  if (m_total_size > 0){
    DNode *curr= m_iList.front().m_dNode;
    DNode *next = curr->m_next;

    if (curr == NULL)
      next = NULL;
    
    // Loops through all inner lists deleting data nodes
    while (next != NULL){
      delete curr;
      curr = next;
      
      if (curr != NULL)
	next = curr->m_next;
      else
	next = NULL;
    }

    if (curr == NULL)
      return;    

    // Deletes final node
    delete curr;
    curr = NULL;
  }
}

// overloaded assignment operator
// Runs in O(n) time
const SqList& SqList::operator=(const SqList& rhs){

  // Checks for self-assignement 
  if (this == &rhs)
    return *this;

  // Clears and resets current list
  deleteDNodes();
  m_iList.clear();
  m_total_size = rhs.m_total_size;

  // Loops through copying indexes (INodes are copied first)
  for (std::list<INode>::const_iterator it = rhs.m_iList.begin(); 
       it != rhs.m_iList.end(); ++it){
    
    DNode* tempD = new DNode(it->m_dNode->m_data);
    INode tempI(tempD, it->m_size);
    m_iList.push_back(tempI);
  }
  
  // Keeps track of the length of the square list up to the position
  //   currently being checked
  int curr_index = 0;
  const int LIST_SIZE = m_iList.size();

  std::list<INode>::const_iterator rhs_it = rhs.m_iList.begin();

  // Loops through indexes
  for (std::list<INode>::iterator it = m_iList.begin(); 
       it != m_iList.end(); ++it, ++rhs_it){

    // Helps with traversing both lists
    DNode* curr = it->m_dNode;
    DNode* rhs_curr = rhs_it->m_dNode;
    DNode* temp = NULL;

    // First DNode is skipped because it was copied with the INodes
    if(rhs_curr != NULL){      
      rhs_curr = rhs_curr->m_next;

      // Loops until end of inner list
      for(int i = 1; i < it->m_size; i++){
	
	// Copies data
	if (rhs_curr != NULL){
	  temp = new DNode(rhs_curr->m_data);
	  curr->m_next = temp;
	  
	  // Moves on to the next position
	  curr = temp;
	   rhs_curr = rhs_curr->m_next;
	}
      }
    }

    // Updates last inner node to point at next INode's m_dNode  
    if (curr_index < LIST_SIZE - 1){
      ++it;
      temp = it->m_dNode;
      --it;
    }
    else
      temp = NULL;
    
    // Connects current inner list with it's neighbor
    curr->m_next = temp;
    curr_index++;
  }
  return *this;
}

// Inserts an item into the appropriate sorted position in a SqList
// Runs in O(sqrt(n)) time (not counting consolodate)
void SqList::add(const Int341& data){

  DNode* tempD = new DNode(data);

  // If the Square List is empty
  if (m_total_size <= 0){
    m_iList.push_front(INode(tempD));
    m_total_size = 1;
    consolidate();

    // Cleaning up the unused memeory
    delete tempD;
    tempD = NULL;
    return;
  }

  // Keeps track of the length of the square list up to the position
  //   currently being checked
  int curr_index = 0;
  const int LIST_SIZE = m_iList.size();

  // Loops through indexes
  for (std::list<INode>::iterator it = m_iList.begin(); 
       it != m_iList.end(); ++it){

    int index_size = it->m_size;

    // Data equals the current index's int
    if (it->m_dNode->m_data == data){

      // New node is added after head
      DNode* curr_head = it->m_dNode;
      DNode* curr_next = curr_head->m_next;

      // Checks to make sure new node to be added is properly allocated
      if (tempD != NULL)
	delete tempD;
      tempD = new DNode(data);
      
      curr_head->m_next = tempD;
      tempD->m_next = curr_next;

      // Member variables for both INode and SqList are updated
      m_total_size++;
      it->m_size = ++index_size;
      consolidate();
      return;
    }

    // Data is less than the current index's int
    else if (it->m_dNode->m_data > data){

      // Beginning is a special case where node is automatically added
      if (it == m_iList.begin()){

	// First the new node is added before data is sorted
	DNode* curr_head = it->m_dNode;
	DNode* curr_next = curr_head->m_next;
	curr_head->m_next = tempD;
	tempD->m_next = curr_next;

	// Switching data so that the data being added is at the head
	curr_head->swap(tempD);
      }

      // Goes into previous INode and searches for proper position      
      else{
	--it;
	index_size = it->m_size;
	addToInner(*it, data, tempD);
      }
      
	// Member variables for both INode and SqList are updated
	m_total_size++;
	it->m_size = ++index_size;
	consolidate(); 
	return;
    }

    // Data is larger than current index's int and not at beginning
    else if( (it->m_dNode->m_data < data) ) {	

      // When data is to be added to the end of the list 
      if (curr_index == LIST_SIZE - 1){
	index_size = it->m_size;
	addToInner(*it, data, tempD);
	
	// Member variables for both INode and SqList are updated
	m_total_size++;
	it->m_size = ++index_size;
	consolidate(); 
	return;
      }
    }

    // All other situations loop continues
    curr_index++;
    
    // Cleaning up the unused memeory
    delete tempD;
    tempD = NULL;
  }
}

// Removes a value from a SqList and returns its value
// Runs in O(sqrt(n)) time (not counting consolodate)
Int341 SqList::remove(const Int341& data){

  Int341 removed_data;
  bool not_removed = false;

  // Exception message
  std::stringstream error_stream; 
  error_stream << "Data " << data.m_data << " is not valid; Cannot be removed";
  std::string error_msg = error_stream.str();


  // If the Square List is empty
  if (m_total_size <= 0)
    throw std::out_of_range(error_msg);

  // When last node needs to be deleted
  if (m_total_size == 1){
    DNode* last_node = m_iList.front().m_dNode;
    removed_data = last_node->m_data;

    // Checks if node is to be deleted and updates memebers
    if (data == removed_data){
      delete last_node;
      last_node = NULL;
      m_total_size = 0;
      m_iList.clear();
      return removed_data;
    }
    else
      throw std::out_of_range(error_msg);
  }

  // Keeps track of the length of the square list up to the position
  //   currently being checked
  int curr_index = 0;
  const int LIST_SIZE = m_iList.size();

  // Loops through indexes
  for (std::list<INode>::iterator it = m_iList.begin(); 
       it != m_iList.end(); ++it){

    int index_size = it->m_size;

    // Data equals the current index's int
    if (it->m_dNode->m_data == data){

      // New node is added after head
      DNode* curr_head = it->m_dNode;
      DNode* curr_next = curr_head->m_next;
      DNode* new_next = NULL; 

      if (curr_next != NULL)
	new_next = curr_next->m_next;
      
      // Swaps their data so it is easier to remove
      curr_head->swap(curr_next);

      // List is updated and removed data is retrieved and deleted
      curr_head->m_next = new_next;
      removed_data = curr_next->m_data;
      delete curr_next;
      curr_next = NULL;

      // Member variables for both INode and SqList are updated
      m_total_size--;
      it->m_size = --index_size;
      checkEmpty(it);
      consolidate();
      return removed_data;
    }

    // Data is less than the current index's int
    else if (it->m_dNode->m_data > data){

      // Beginning is a special case where node is automatically added
      if (it == m_iList.begin()){

	// If data searched for is smaller than the front of the square list
	//   then it does not exist
	throw std::out_of_range(error_msg);
      }

      // Goes into previous INode and searches for node to delete      
      else{
	--it;
	index_size = it->m_size;
	removed_data = innerRemoval(*it, data, not_removed);
      }
      
      // Data not found in it's proper location
      if (not_removed)
	throw std::out_of_range(error_msg);
      
      // Member variables for both INode and SqList are updated
      else{
	m_total_size--;
	it->m_size = --index_size;
	checkEmpty(it);
	consolidate(); 
	return removed_data;
      }
    }

    // Data is larger than current index's int and not at beginning
    else if( (it->m_dNode->m_data < data) ) {

      // When data to be removed might be at the end of the list 
      if (curr_index == (LIST_SIZE - 1) ){
	index_size = it->m_size;
	removed_data = innerRemoval(*it, data, not_removed);
	

	// Data not found in it's proper location
	if (not_removed)
	  throw std::out_of_range(error_msg);

	// Member variables for both INode and SqList are updated
	else{
	  m_total_size--;
	  it->m_size = --index_size;
	  checkEmpty(it);
	  consolidate(); 
	  return removed_data;
	}
      }
    }
    
    // All other situations loop continues
    curr_index++;
  }
  // When data was not found
  throw std::out_of_range(error_msg);
}

// Removes an item from a given position and returns its value
// Runs in O(sqrt(n)) time (not counting consolodate)
Int341 SqList::removeAt(int pos){

  Int341 removed_data;
  const int POS = pos;
  bool not_removed = false;

  // Exception message
  std::stringstream error_stream; 
  error_stream << "Position " << pos << " is not valid; Cannot be removed";
  std::string error_msg = error_stream.str();

  // If the Square List is empty
  if (m_total_size <= 0)
    	throw std::out_of_range(error_msg);

  // If the position given exceeds the square list or is not large enough
  if( (POS >= m_total_size) || (POS < 0) )
    	throw std::out_of_range(error_msg);

  // When last node needs to be deleted
  if (m_total_size == 1){
    DNode* last_node = m_iList.front().m_dNode;
    removed_data = last_node->m_data;

    // Checks if node is to be deleted and updates memebers
    if (POS == 0){
      delete last_node;
      last_node = NULL;
      m_total_size = 0;
      m_iList.clear();
      return removed_data;
    }
    else
      throw std::out_of_range(error_msg);
  }

  // Keeps track of the length of the square list up to the position
  //   currently being checked
  int curr_len = 0;
  int curr_index = 0;
  const int LIST_SIZE = m_iList.size();

  // Loops through indexes
  for (std::list<INode>::iterator it = m_iList.begin(); 
       it != m_iList.end(); ++it){

    int index_size = it->m_size;

    // Data equals the current index's int
    if (curr_len == POS){

      // New node is added after head
      DNode* curr_head = it->m_dNode;
      DNode* curr_next = curr_head->m_next;
      DNode* new_next = NULL; 

      // Swaps their data so it is easier to remove      
      if (curr_next != NULL){
	new_next = curr_next->m_next;
	curr_head->swap(curr_next);
	removed_data = curr_next->m_data;
      }

      // List is updated and removed data is retrieved and deleted
      curr_head->m_next = new_next;
      delete curr_next;
      curr_next = NULL;

      // Member variables for both INode and SqList are updated
      m_total_size--;
      it->m_size = --index_size;
      checkEmpty(it);
      consolidate();
      return removed_data;
    }

    // Data is less than the current index's int
    else if (curr_len > POS){

      // Goes into previous INode and searches for node to delete      
      --it;
      index_size = it->m_size;
      curr_len -= index_size;
      removed_data = removeAtInner(*it, POS, curr_len + 1, not_removed);      

      // Data not found in it's proper location
      if (not_removed)
	throw std::out_of_range(error_msg);
      
      // Member variables for both INode and SqList are updated
      else{
	m_total_size--;
	it->m_size = --index_size;
	checkEmpty(it);
	consolidate(); 
	return removed_data;
      }
    }

    // Position is larger than current index and not at beginning
    else if (curr_len < POS){

      // When data to be removed might be at the end of the list 
      if (curr_index == LIST_SIZE - 1){
	index_size = it->m_size;
	removed_data = removeAtInner(*it, POS, curr_len + 1, not_removed);

	// Data not found in it's proper location
	if (not_removed)
	  throw std::out_of_range(error_msg);
	
	// Member variables for both INode and SqList are updated
	else{
	  m_total_size--;
	  it->m_size = --index_size;
	  checkEmpty(it);	
	  consolidate(); 
	  return removed_data;
	}
      }
    }

    // All other situations loop continues
    curr_index++;
    curr_len += it->m_size;
  }
  // Invalid position was given
  throw std::out_of_range(error_msg);
}

// Returns data at a given position by reference (data can be modified)
// If pos is not valid throw an out_of_range exception
// Runs in O(sqrt(n)) time 
Int341& SqList::operator[](int pos){

  DNode* data_node = NULL;
  const int POS = pos;
  bool not_found = false;

  // Exception message
  std::stringstream error_stream; 
  error_stream << "Position " << pos << " is not valid; Cannot be indexed";
  std::string error_msg = error_stream.str();

  // If the Square List is empty
  if (m_total_size <= 0)
    throw std::out_of_range(error_msg);

  // If the position given exceeds the square list or is not large enough
  if( (POS >= m_total_size) || (POS < 0) )
    	throw std::out_of_range(error_msg);

  // Keeps track of the length of the square list up to the position
  //   currently being checked
  int curr_len = 0;
  int curr_index = 0;
  const int LIST_SIZE = m_iList.size();

  // Loops through indexes
  for (std::list<INode>::iterator it = m_iList.begin(); 
       it != m_iList.end(); ++it){

    int index_size = it->m_size;

    // Data equals the current index's int
    if (curr_len == POS){
      data_node = it->m_dNode;
      return data_node->m_data;
    }

    // Data is less than the current index's int
    else if (curr_len > POS){

      // Goes into previous INode and searches for node to delete      
      --it;
      index_size = it->m_size;
      curr_len -= index_size;
      data_node = find(*it, POS, curr_len + 1, not_found);

      // Data not found in it's proper location
      if (not_found)
	throw std::out_of_range(error_msg);
      
      else
	return data_node->m_data;
    }

    // Position is larger than current index and not at beginning
    else if (curr_len < POS){

      // When data looking for is at the end of the list 
      if (curr_index == LIST_SIZE - 1){
	index_size = it->m_size;
	data_node = find(*it, POS, curr_len + 1, not_found);

	// Data not found in it's proper location
	if (not_found)
	  throw std::out_of_range(error_msg);
	
	// Member variables for both INode and SqList are updated
	else
	  return data_node->m_data;
      }
    }

    // All other situations loop continues
    curr_index++;
    curr_len += it->m_size;
  }
  // Invalid position was given
  throw std::out_of_range(error_msg);
}

// Returns the position of the first occurrence of a value
// Returns -1 if data does not appear in list
// Runs in O(sqrt(n)) time
int SqList::indexOf(const Int341& data){

  int pos = -1;

  // If the Square List is empty
  if (m_total_size <= 0)
    return pos;

  // Keeps track of the length of the square list up to the position
  //   currently being checked
  int curr_len = 0;
  int curr_index = 0;
  const int LIST_SIZE = m_iList.size();

  // Loops through indexes
  for (std::list<INode>::iterator it = m_iList.begin(); 
       it != m_iList.end(); ++it){

    int index_size = it->m_size;

    // Data equals the current index's int
    if (it->m_dNode->m_data == data){
      pos = curr_len + 1;
      return pos;
    }

    // Data is less than the current index's int
    else if (it->m_dNode->m_data > data){

      // Beginning is a special case where node is automatically found
      if (it == m_iList.begin()){}

      // Goes into previous INode and searches for proper position      
      else{
	--it;
	curr_len -= index_size;
	index_size = it->m_size;
	pos = indexInInner(*it, data, curr_len);
      }
	return pos;
    }

    // Data is larger than current index's int and not at beginning
    else if( (it->m_dNode->m_data < data) ) {

      // When data is at the end of the list 
      if (curr_index == LIST_SIZE - 1){
	pos = indexInInner(*it, data, curr_len);
	return pos;
      }
    }

    // All other situations loop continues
    curr_index++;
    curr_len += it->m_size;
  }
  return pos;
}

// Returns number of items in SqList. Used for grading
// Runs in O(1) time
int SqList::numItems(){
  return m_total_size;
}

// debugging function. Prints out contents.
// running time does not matter
void SqList::dump(){

  int curr_index = 0;

  if (m_total_size <= 0){
    std::cout << "List is empty" << std::endl;
    return;
  }

  // Loops through indexes
  for (std::list<INode>::iterator it = m_iList.begin(); 
       it != m_iList.end(); ++it){

    DNode *temp = it->m_dNode;
    std::cout << "Index " << curr_index << ": ";

    // Loops through inner list
    for (int i = 0; i < it->m_size; i++){
      if (temp != NULL){
	std::cout << temp->m_data.m_data << " | ";
	temp = temp->m_next;
      }
    }

    // Assits with formatting
    std::cout << std::endl;
    curr_index++;
  }
  return;
}

// Combines and splits lists as necessary to keep squareness
// Runs in O(sqrt(n)) not counting splits
void SqList::consolidate(){

  // Does nothing if list not started
  if (m_total_size <= 1)
    return;

  bool adjacent_short = false;
  int curr_index = 0;
  const int LIST_SIZE = m_iList.size();

  // Loops through indexes                                                     
  for (std::list<INode>::iterator it = m_iList.begin();
       it != m_iList.end();++it){
   
    int index_size = it->m_size;
    
    // Long lists are split
    if(isLong(index_size)){
      
      // Used to identify where to split
      int split_pos = 0;
      DNode* splitter = splitAt(*it, split_pos);
      int new_size = index_size - split_pos;
      
      // Insertion (of INode) occurs before the current index
      m_iList.insert( it, INode(it->m_dNode, new_size) );
      it->m_size = split_pos;
      it->m_dNode = splitter;
    }
    
    // Adjacent short lists are combined
    else if (adjacent_short){
      
      // Updates size of previous INode
      --it;
      it->m_size = it->m_size + index_size;
      
      // Prepares current INode for removal
      ++it;
      it->m_size = 0;
      m_iList.erase(it++);
      adjacent_short = false;
    }
    
    // Helps with checking neighboring adjacent lists
    else if (isShort(index_size))
      adjacent_short = true;

    curr_index++;

    // Checks if end of list has been reached
    if(curr_index >= LIST_SIZE) 
      return;
  }
  return;
}

/*
The following are all private helper functions
(Aside from deleteNodes() which is directly below the destructor)
*/

// Checks if an individual inner list is too short
bool SqList::isShort(int inner_size){

  const double INNER_MIN_SIZE = std::sqrt(m_total_size) / 2;

  if (inner_size <= INNER_MIN_SIZE)
    return true;
  else
    return false;
}

// Checks if an individual inner list is too long
bool SqList::isLong(int inner_size){

  const double INNER_MAX_SIZE = 2 * std::sqrt(m_total_size);

  if (inner_size > INNER_MAX_SIZE)
    return true;
  else
    return false;
}

// Helps with adding to inner lsits
void SqList::addToInner(INode& index, const Int341& data, DNode* tempD){

  // Checks to make sure new node to be added is properly allocated
  if (tempD != NULL)
    delete tempD;

  tempD = new DNode(data);
  DNode* curr = index.m_dNode;
  DNode* next = curr->m_next;

  // Loops until end of inner list
  for(int i = 0; i < index.m_size; i++){

    // When appropriate position to add data is found
    if( (next != NULL) && (next->m_data > data) ){
      curr->m_next = tempD;
      tempD->m_next = next;
      return;
    }

    // Update to check next node
    else if (next != NULL){
      curr = next;
      next = curr->m_next;
    }
  }

  // Adds to the end of current inner list
  curr->m_next = tempD;
  if (next != NULL)
    tempD->m_next = next;
  return;
}

// Helps with removing at node in an inner lsits
Int341 SqList::innerRemoval(INode& index, const Int341& data, bool& not_removed){

  Int341 removed_data;
  DNode* curr = index.m_dNode;
  DNode* next = curr->m_next;
  DNode* new_next = NULL; 
  
  if (next != NULL)
    new_next = next->m_next;
  
  // Loops until end of inner list
  for(int i = 0; i < index.m_size; i++){

    // Data was not found
    if (next == NULL){
      not_removed = true;
      return removed_data;
    } 

    // When data is found it is removed/deleted and nodes are adjusted
    else if (next->m_data == data){
      curr->m_next = new_next;
      removed_data = next->m_data;
      delete next;
      next = NULL;
      return removed_data;
    }

    // Update to check next node
    else if (next != NULL){
      curr = next;
      next = curr->m_next;
      if (new_next != NULL)
	new_next = next->m_next;
    }
  }
}

// Helps with removing when desired position is within an inner list
Int341 SqList::removeAtInner(INode& index, const int POS, int curr_len, bool& not_removed){

  Int341 removed_data;
  DNode* curr = index.m_dNode;
  DNode* next = curr->m_next;
  DNode* new_next = NULL; 
  
  if (next != NULL)
    new_next = next->m_next;
  
  // Loops until end of inner list
  for(int i = 0; i < index.m_size; i++){

    // When data is found it is removed/deleted and nodes are adjusted
    if( (next != NULL) && (curr_len == POS) ){
      curr->m_next = new_next;
      removed_data = next->m_data;
      delete next;
      next = NULL;
      return removed_data;
    }

    // Update to check next node
    else if (next != NULL){
      curr = next;
      next = curr->m_next;
      curr_len++;

      if (new_next != NULL)
	new_next = next->m_next;
    }
  }
  // Data was not found
  not_removed = true;
  return removed_data;
}

// Helps with finding data at a desired position
// Returns the data itself
DNode* SqList::find(INode& index, const int POS, int curr_len, bool& not_found){

  DNode* curr = index.m_dNode;
  DNode* next = curr->m_next;
  DNode* new_next = NULL; 
  
  if (next != NULL)
    new_next = next->m_next;
  
  // Loops until end of inner list
  for(int i = 0; i < index.m_size; i++){

    // When data's position is found
    if( (next != NULL) && (curr_len == POS) )
      return next;

    // Update to check next node
    else if (next != NULL){
      curr = next;
      next = curr->m_next;
      curr_len++;

      if (new_next != NULL)
	new_next = next->m_next;
    }
  }
  // Data was not found
  not_found = true;
  return next;
}

// Helps with indexing items in inner lsits
// Rerturns position of data
int SqList::indexInInner(INode& index, const Int341& data, int curr_len){

  int pos = -1;

  DNode* curr = index.m_dNode;
  DNode* next = curr->m_next;

  // Loops until end of inner list
  for(int i = 0; i < index.m_size; i++){

    // Data was found
    if (curr->m_data == data){
      pos = curr_len + 1;
      return pos;
    }

    // Update to check next node
    else if (next != NULL){
      curr = next;
      next = curr->m_next;
      curr_len++;
    }
  }
  return pos;
}

// Helps with determining where to split a node                               
DNode* SqList::splitAt(INode& index, int& split_pos){

  DNode* curr = index.m_dNode;
  DNode* next = curr->m_next;

  double precision_mid = index.m_size / 2.0;
  int mid = index.m_size / 2;
  
  // Loops until middle of inner list
  for(int i = 0; i < mid; i++){
    
    // Updating in order to check next position
    if (next != NULL){
      curr = next;
      next = curr->m_next;
      split_pos++;
    }
  }

  // Double checks to make sure not to access non-existent nodes
  if (next != NULL){
    curr = next;
    next = curr->m_next;
  }
  
  // In the case of an even number of entries
  if (mid == precision_mid)
    split_pos -= 1;

  // Odd number has no changes
  return curr;
}

// Helps with checking and deleting empty INodes
void SqList::checkEmpty(std::list<INode>::iterator& it){

  // An INode can only be removed if it is empty
  if (it->m_size <= 0)
    m_iList.erase(it);
}
