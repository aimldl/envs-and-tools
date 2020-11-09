#pragma once	// TextProc.hpp

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <cassert>
#include <vector>
#include <algorithm> 

#include "Config.hpp"
#include "NLP.hpp"
#include "Data.hpp"

using namespace std;

//==================================================================
//                      Class Declaration                         //
//==================================================================

class TextProc : public Data	// Text Pre-Processing
{
public:
	         TextProc(Config &cfg);
		     TextProc(Config &cfg, NLP &nlp);
	        ~TextProc();

	void     save_word_set(string input_file, string output_file);
	void     run(string input_file);
	void     match_and_save(string input_file, string target_file, string output_file);

private:
	void     import_file2sentence_set(string filename);
	set_str  file2sentences(string filename);
	set_str  sentences2words(vec_str &sentence_vect);
	set_str  sentences2words(set_str  sentence_set);

	vec_str  extract(vec_int matched_index, vec_str sentence_vect);
	vec_str  extract(set_int matched_index_set, vec_str sentence_vect);
	vec_str  remove(vec_int matched_index, vec_str sentence_vect);
	vec_str  remove(set_int matched_index_set, vec_str sentence_vect);
	vec_str  normalize(vec_str  &sentence_vect);
	set_str  normalize(set_str &sentence_set);

	vec_int  get_matched_index(vec_str sentence_list, string &kw_);

	bool     is_configured;

	// Pointer to class
	Config  *cfg_ptr;
	NLP     *nlp_ptr;
};