// std-multimap-string_string_simple.cc
// References
//   개발이 하고 싶어요, https://hyeonstorage.tistory.com/330

#include "pch.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
  multimap<string, string> mm;
  mm.insert(pair<string, string>("PORTSMOUTH", "00210"));
  mm.insert(pair<string, string>("PORTSMOUTH", "00211"));
  mm.insert(pair<string, string>("PORTSMOUTH", "00212"));
  mm.insert(pair<string, string>("PORTSMOUTH", "00213"));
  mm.insert(pair<string, string>("PORTSMOUTH", "00214"));
  mm.insert(pair<string, string>("PORTSMOUTH", "00215"));
  mm.insert(pair<string, string>("HOLTSVILLE", "00501"));
  mm.insert(pair<string, string>("HOLTSVILLE", "00544"));
  mm.insert(pair<string, string>("ADJUNTAS", "00601"));
  mm.insert(pair<string, string>("AGUADA", "00602"));
  mm.insert(pair<string, string>("AGUADILLA", "00603"));

  multimap<string, string>::iterator itr;
  for (auto itr = mm.begin(); itr != mm.end(); ++itr)
    cout << "(" << itr->first << "," << itr->second << ") ";
  cout << endl;

  string key = "HOLTSVILLE";
  cout << "Number of elements in key " << key << ": " << mm.count(key) << endl;

  itr = mm.find(key);
  if (itr != mm.end())
    cout << "The first value mapped to key " << key << ": " << itr->second << endl;

  map<string, string>::iterator itr_lower;
  map<string, string>::iterator itr_uppter;
  itr_lower = mm.lower_bound(key);
  itr_uppter = mm.upper_bound(key);

  cout << "itr_lower: " << "(" << itr_lower->first << "," << itr_lower->second << ") " << endl;
  cout << "itr_uppter: " << "(" << itr_uppter->first << "," << itr_uppter->second << ") " << endl;

  // Note time complexity of equal_range(key) is O(1)
  pair<map<string, string>::iterator, map<string, string>::iterator> itr_equal;
  itr_equal = mm.equal_range(key);

  for (itr = itr_equal.first; itr != itr_equal.second; ++itr)
    cout << "(" << itr->first << ',' << itr->second << ") ";
  cout << endl;

  for (itr = itr_equal.first; itr != itr_equal.second; ++itr)
    cout << itr->second << " ";
  cout << endl;

  return 0;
}

// Expected Output
//(ADJUNTAS, 00601) (AGUADA, 00602) (AGUADILLA, 00603) (HOLTSVILLE, 00501) (HOLTSVILLE, 00544) (PORTSMOUTH, 00210) (PORTSMOUTH, 00211) (PORTSMOUTH, 00212) (PORTSMOUTH, 00213) (PORTSMOUTH, 00214) (PORTSMOUTH, 00215)
//Number of elements in key HOLTSVILLE : 2
//The first value mapped to key HOLTSVILLE : 00501
//itr_lower : (HOLTSVILLE, 00501)
//itr_uppter : (PORTSMOUTH, 00210)
//(HOLTSVILLE, 00501) (HOLTSVILLE, 00544)
//00501 00544
