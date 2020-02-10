
#include "SqList.h"
#include "Int341.h"

#include <iostream>
#include <cstdlib>

using namespace std;

int main(){

  SqList* temp = new SqList();
  cout << "List has " << temp->numItems() << " items." << endl;

  for (int i = 0; i < 15; i++){
    //int rand_int = rand() % 1000;
    cout << "Adding " << i << endl;
    temp->add(Int341(i));
  temp->dump();
  }
  temp->dump();
  cout << "List has " << temp->numItems() << " items." << endl;

  //temp->removeAt(6);
  //temp->removeAt(14);
  temp->dump();

  cout << "Testing Copy Consuctor" << endl;
  SqList copy(*temp);
  copy.dump();
  
  SqList* temp2 = new SqList();;
  for (int i = 0; i < 8; i++){
    int rand_int = rand() % 100;
    cout << "Adding " << rand_int << endl;
    temp2->add(Int341(rand_int));
  }
  temp2->dump();
  cout << "List 2 has " << temp2->numItems() << " items." << endl;

  cout << "Testing Overloaded Assignment Operator" << endl;
  copy = *temp2;
  copy.dump();

  int test_size = temp->numItems();
  temp->dump();
  for (int i = 0; i < test_size; i++){
    temp->removeAt(0);
    temp->dump();
  }

  delete temp;
  temp = NULL;

  delete temp2;
  temp2 = NULL;

  return 0;
}
