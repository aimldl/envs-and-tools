#pragma once

#include  <iostream>
#include  <cassert>
#include  <string>
#include "GetOpt.hpp"

using namespace  std;

//==================================================================
//                      Class Declaration                         //
//==================================================================

class Args	// (Command Line) Arguments
{
public:
	         Args(int argc, char **argv);
	        ~Args();
	bool    is_word_level();
	bool    is_sentence_level();
	bool    match_filenames();

private:
	void     process(int argc, char **argv);
	void     show_usage();
	void     show_version();
	void     show_default_message();

	string   program_name;
	string   release_date;
	string   version_number;

	bool    process_words;
	bool    process_sentences;
	bool    process_filenames;
};