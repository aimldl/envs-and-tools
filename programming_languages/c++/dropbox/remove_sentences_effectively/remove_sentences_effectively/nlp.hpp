#pragma once  // NLP.hpp

#include <iostream>
#include <string>
#include <algorithm>  // transform

using namespace  std;

#define DEBUG 0

//==================================================================
//                      Class Declaration                         //
//==================================================================


class NLP	// Natural Language Processing
{
public:
	     NLP();
	    ~NLP();
	void normalize(string &str);
private:
	void set_chars2forbid(string str);
	void lowercase(string& str);
	void remove_chars(string& str);

	string chars2forbid;
};
