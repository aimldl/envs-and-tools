// std-set_simple.cc

//#include "pch.h"  // Uncomment this in Visual Studio
#include <cassert>
#include <iostream>
#include <set>

using namespace std;

void ShowSetElements(set<int> s) {
  assert(!s.empty());

  for (int i : s)
    cout << i << " ";
  cout << endl;
}

int main() {
  //  Elements of set: set keeps ordered unique values
  set<int> set1 {9, 7, 1, 3, 5, 3, 1, 7};
  cout << "set<int> set1 {9, 7, 1, 3, 5, 3, 1, 7};" << endl;
  cout << "set1.size() = " << set1.size() << "\t\t\t" << "set1: ";
  ShowSetElements(set1);  // set1: 1 3 5 7 9

  // insert
  set1.insert(11);
  set1.insert(13);
  set1.insert(15);
  set1.insert(15);
  cout << "insert() 11, 13, 15, & 15" << "\t" << "set1: ";
  ShowSetElements(set1);  // set1: 1 3 5 7 9 11 13 15

  // erase
  set1.erase(1);
  set1.erase(15);
  set1.erase(14);
  cout << "erase() 1, 15 & 14" << "\t\t" << "set1: ";
  ShowSetElements(set1);  // set1: 3 5 7 9 11 13

  // iterator: begin
  set<int>::iterator itr_begin = set1.begin();
  cout << "Iterating from begin() twice\t" << *itr_begin;
  cout << " " << *++itr_begin << endl;  // 3 5

  // iterator: end
  set<int>::iterator itr_end = set1.end();
  // Note *itr_end will cause an error. *--itr_end is the last element!
  cout << "Iterating from end() twice\t" << *--itr_end;
  cout << " " << *--itr_end << endl;  // 13 11

  // advance: backward
  advance(itr_end, -1);
  cout << "advance() -1 from the iterator" << "\t" << *itr_end << endl;
  advance(itr_end, -2);
  cout << "advance() -2 from the iterator" << "\t" << *itr_end << endl;

  // advance: forward
  itr_begin = set1.begin();
  advance(itr_begin, 5);
  cout << "advance() 5 from begin()" << "\t" << *itr_begin << endl;

  // advance & erase
  itr_begin = set1.begin();
  advance(itr_begin, 2);
  cout << "advance() 2 from begin()" << "\t" << *itr_begin << endl;
  cout << "and then erase() to end()" << "\t";
  itr_end = set1.end();
  set1.erase(itr_begin, itr_end);
  cout << "set1: ";
  ShowSetElements(set1); // set1: 3 5

  // insert: from array
  int array[] = {7, 9, 11, 13, 15, 17, 19, 21, 21, 23, 25};
  set1.insert(array, array+9);
  cout << "insert() from array" << "\t\t" << "set1: ";
  ShowSetElements(set1);  // set1: 3 5 7 9 11 13 15 17 19 21

  // find and erase
  //auto value = set1.find(7);
  set<int>::iterator itr_from = set1.find(7);
  set<int>::iterator itr_to   = set1.find(19);
  cout << "find() iterators for " << *itr_from << " and " << *itr_to << endl;
  set1.erase(itr_from, ++itr_to);  // Note ++ for itr_to
  cout << "erase() all values inbetween\t"<< "set1: ";
  ShowSetElements(set1); // set1: 3 5 21

  // swap two sets
  set<int> set2 { 150, 200, 300 };
  cout << endl;
  cout << "set<int> set2 {150, 200, 300};" << "\t" << "set2: ";
  ShowSetElements(set2);

  set2.swap(set1);
  cout << "swap() two sets\t\t\t" << "set1: ";
  ShowSetElements(set1);
  cout << "\t\t\t\tset2: ";
  ShowSetElements(set2);

  return 0;
}
/*
// lower_bound returns an iterator pointing to that element, whereas upper_bound returns an iterator pointing to the next element.

int set_elements[] = { 1, 3, 5, 7, 9 };
int value;
set<int>::iterator itr_lower, itr_upper;

for (int i = 0; i < 5; i++) {
  value = set_elements[i];

  // An iterator to value is returned.
  itr_lower = set1.lower_bound(value);
  itr_upper = set1.lower_bound(value);

  cout << "lower_bound" << "\t" << "upper__bound" << " of " << value << endl;
  cout << *itr_lower << "\t\t" << *itr_upper << endl;

}
//set<int>::iterator itr = set1.begin();

//Notice that lower_bound(30) returns an iterator to 30, whereas upper_bound(60) returns an iterator to 70.
*/
