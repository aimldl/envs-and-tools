// std-multimap-int_int_simple.cc
// References
//   개발이 하고 싶어요, https://hyeonstorage.tistory.com/330

#include "pch.h"
#include <iostream>
#include <map>

using namespace std;

int main() {
  multimap<int, int> mm;
  mm.insert(pair<int, int>(5, 100));
  mm.insert(pair<int, int>(3, 100));
  mm.insert(pair<int, int>(3, 50));
  mm.insert(pair<int, int>(3, 60));
  mm.insert(pair<int, int>(3, 40));
  mm.insert(pair<int, int>(8, 30));
  mm.insert(pair<int, int>(1, 70));
  mm.insert(pair<int, int>(7, 100));
  mm.insert(pair<int, int>(7, 20));
  mm.insert(pair<int, int>(7, 12));
  mm.insert(pair<int, int>(8, 50));

  multimap<int, int>::iterator iter;
  for (iter = mm.begin(); iter != mm.end(); ++iter)
    cout << "(" << iter->first << "," << iter->second << ") ";
  cout << endl;

  //int key = 3;
  int key = 7;

  cout << "Number of elements in key " << key << ": " << mm.count(key) << endl;

  iter = mm.find(key);
  if (iter != mm.end())
    cout << "The first value mapped to key " << key << ": " << iter->second << endl;
  
  map<int, int>::iterator itr_lower;
  map<int, int>::iterator itr_uppter;
  itr_lower  = mm.lower_bound(key);
  itr_uppter = mm.upper_bound(key);

  cout << "itr_lower: " << "(" << itr_lower->first << "," << itr_lower->second << ") " << endl;
  cout << "itr_uppter: " << "(" << itr_uppter->first << "," << itr_uppter->second << ") " << endl;

  pair<map<int, int>::iterator, map<int, int>::iterator> itr_equal;
  itr_equal = mm.equal_range(key);

  for (iter = itr_equal.first; iter != itr_equal.second; ++iter)
    cout << "(" << iter->first << ',' << iter->second << ") ";
  cout << endl;

  return 0;
}

// Expected Output
//(1, 70) (3, 100) (3, 50) (3, 60) (3, 40) (5, 100) (7, 100) (7, 20) (7, 12) (8, 30) (8, 50)
//Number of elements in key 7: 3
//The first value mapped to key 7 : 100
//itr_lower : (7, 100)
//itr_uppter : (8, 30)
//(7, 100) (7, 20) (7, 12)
