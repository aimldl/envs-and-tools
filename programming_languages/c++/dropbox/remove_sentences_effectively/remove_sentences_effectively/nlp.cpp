// NLP.hpp

#include "pch.h"
#include "NLP.hpp"

using namespace std;

//==================================================================
//                           Public                               //
//==================================================================
NLP::NLP()
{
	set_chars2forbid("\\/:;?!\<>|,.");
}


NLP::~NLP()
{
}

void
NLP::normalize(string &str)
{
	lowercase(str);
	remove_chars(str);
}

//==================================================================
//                           Private                              //
//==================================================================
void
NLP::set_chars2forbid(string str)
{
	chars2forbid = str;
}

// Convert the string to lower case
void
NLP::lowercase(string& str)
{
	if (DEBUG)  cout << str << "\t";
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	if (DEBUG)  cout << str << "\t";
}

// Remove forbidden characters
// Note this is different from leaving only the alphanumeric characters.
// If alphanumeric characters are left, space between words will be removed.
// To have more control, use the forbidden characters!
void
NLP::remove_chars(string& str)
{
	for (int i = 0; i < str.size(); i++)
		if (chars2forbid.find(str.at(i)) != string::npos) str.at(i) = ' ';

	// Removing : for time is fine. 8:30AM -> 8 30 am is properly pronounced
	if (DEBUG)  cout << str << endl;
	if (DEBUG)  getchar();
}

//==================================================================
//                           Obsolete                             //
//==================================================================