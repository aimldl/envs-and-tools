#include "pch.h"
#include "Data.hpp"

using namespace std;

//==================================================================
//                           Public                               //
//==================================================================

Data::Data()
{
}

Data::~Data()
{
}

//==================================================================
//                          Protected                             //
//==================================================================

// An external vector needs to be defined!
// TODO: change this part, so the vector created in this fn can still exist when this function is closed.

vec_str
Data::set2vector(set_str set_string)
{
	assert(!set_string.empty());

	vec_str vector_string;
	for (auto element : set_string)
	{
		vector_string.push_back(element);
	}

	return vector_string;
}

void
Data::save(const set_str& set_string, const string filename)
{
	assert(!set_string.empty());
	assert(!filename.empty());

	if (DEBUG) for (set_str::iterator itr = set_string.begin(); itr != set_string.end(); itr++)  cout << *itr << endl;

	ofstream ofs(filename);
	for (set_str::iterator itr = set_string.begin(); itr != set_string.end(); itr++)
	{
		ofs << *itr << endl;
	}
	ofs.close();
}

// Save sentence_vect to filename
// if (DEBUG) for (auto sentence : sentence_vect)  cout << sentence << endl;
void
Data::save(const vec_str &vect_string, const string filename)
{
	assert(!vect_string.empty());
	assert(!filename.empty());

	ofstream ofs(filename);
	for (auto sentence : vect_string)  ofs << sentence << endl;
	ofs.close();
}

//Example: cout_set_string(sentence_set);
void
Data::cout_set_string(set_str &set_string)
{
	for (auto element : set_string)
	{
		cout << element << endl;
	}
}


// TODO: merge these two functions with a template, so this function can be generalized.
void
Data::cout_vector_string(vec_str &vector_string)
{
	for (auto element : vector_string)
	{
		cout << element << endl;
	}
}

void
Data::cout_stats()
{
	cout << "Total number of sentences: sentence_count=" << sentence_count << endl;
	cout << "Total number of words: word_count=" << word_count << endl;
	cout << "Number of unique sentences: uniq_sentence_count=" << uniq_sentence_count << endl;
	cout << "Number of unique words: uniq_word_count=" << uniq_word_count << endl;
}

/*
// set_string = sentence_set
void
Data::save_sentence_set(set_str  &set_string, string output_file)
{
	assert(!set_string.empty());
	assert(!output_file.empty());
	if (DEBUG) for (set_str::iterator itr = set_string.begin(); itr != set_string.end(); itr++)  cout << *itr << endl;

	ofstream ofs;
	ofs.open(output_file);
	for (set_str::iterator itr = set_string.begin(); itr != set_string.end(); itr++)
	{
		ofs << *itr << endl;
	}
	ofs.close();
}
*/