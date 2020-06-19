#pragma once
// textPreprocess.hpp

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <cassert>
#include <vector>

using namespace std;

#define VERBOSE 0		 // Verbose output

#define DEBUG_VERBOSE 0  // Shows all function calls & stuff 
#define DEBUG_STOP    1  // Use getchar to stop the program
#define DEBUG_PT1     0  // Debug point 1: print all the sentences
#define DEBUG_PT2     0  // Debug point 2: print all the words
#define DEBUG_PT3     0  // Debug point 3: print all the sentences in save()
#define DEBUG_PT4     0  // Debug point 4: print all the words in save()
#define DEBUG_PT5     1  // Debug point 5: print kw << ": " << word
#define DEBUG_PT6     1  // Debug point 6: print all the lines with the keyword in it.

class textPreprocess
{
public:
	void   set_filename(string name, string filetype);
	string get_filename(string filetype);  // This part causes a link error.

	void   run();
	set<string>   file2sentences(string filename);
	set<string>   sentences2words(set<string>  sentence_set);

	void   save();
	void   save_sentence_set();
	void   save_word_set();
	void   save( const set<string>& set_string, const string filename);

	void   import_file2sentence_set(string filename);
	void   update(string kw);

	void   cout_stats();
	void   cout_set_string(set<string> &set_string);
	void   cout_vector_string(vector<string> &vector_string);

private:
	void   set_sentence_count(int count);
	void   set_word_count(int count);
	void   set_uniq_sentence_count(int count);
	void   set_uniq_word_count(int count);

	vector<string>  set2vector(set<string>);
	vector<int>     get_index2remove(set<string> sentence_set_, string &kw_);

	string input_file;
	string output_file;
	string output4words;
	set<string>  sentence_set;
	set<string>  word_set;
	int    sentence_count;
	int    uniq_sentence_count;
	int    word_count;
	int    uniq_word_count;
};