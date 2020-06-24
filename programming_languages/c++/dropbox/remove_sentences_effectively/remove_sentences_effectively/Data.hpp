#pragma once

#include  <iostream>
#include  <fstream>
#include  <cassert>
#include  <string>
#include  <vector>
#include  <set>

using namespace  std;

#define DEBUG 0

//==================================================================
//                      Type Declaration                          //
//==================================================================
typedef vector<string> vec_str;
typedef vector<int>    vec_int;
typedef set<string>    set_str;
typedef set<int>       set_int;

//==================================================================
//                      Class Declaration                         //
//==================================================================

class Data
{
public:
	Data();
	~Data();

protected:
	vec_str  set2vector(set_str);

	void     save(const set_str &set_string, const string filename);
	void     save(const vec_str &sentence_vect, const string filename);

	void     cout_stats();
	void     cout_set_string(set_str &set_string);
	void     cout_vector_string(vec_str &vector_string);

	set_str  sentence_set;
	set_str  normalized_sentence_set;
	vec_str  uniq_sentence_vect;
	vec_str  normalized_uniq_sentence_vect;
	vec_str  keyword_vect;
	vec_str  filtered_sentence_vect;
	vec_str  matched_sentence_vect;
	vec_int  matched_index;
	set_str  word_set;
	set_int  matched_index_set;

	int      sentence_count;
	int      uniq_sentence_count;
	int      word_count;
	int      uniq_word_count;
};

//void     save_sentence_set(set_str  &sentence_set, string output_file);