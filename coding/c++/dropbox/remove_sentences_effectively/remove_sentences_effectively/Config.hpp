#pragma once  // config.hpp

#include <string>
using namespace std;

//==================================================================
//                      Class Declaration                         //
//==================================================================

class Config
{
public:
	        Config();
	       ~Config();

	string  get_file_default_cfg();
	string  get_file_keywords2remove();
	string  get_file_uniq_words();

	string  get_file_similar_sentences();
	string  get_file_filtered_sentences();
	string  get_file_uniq_sentences();
	string  get_file_uniq_sentences_filtered_wt_keywords();
	string  get_file_sorted_transcript_en();

private:
	void    init();

	string  file_default_cfg;
	string  file_keywords2remove;
	string  file_uniq_words;

	string  file_similar_sentences;
	string  file_filtered_sentences;
	string  file_uniq_sentences;
	string  file_uniq_sentences_filtered_wt_keywords;
	string  file_sorted_transcript_en;
};

#define SHOW_INDEX    0	 // 
#define VERBOSE		  0	 // Verbose output

#define DEBUG         0  // Use this flag for the part for debugging now.
#define DEBUG_VERBOSE 0  // Shows all function calls & stuff 
#define DEBUG_STOP    0  // Use getchar to stop the program
#define DEBUG_PT1     0  // Debug point 1: print all the sentences
#define DEBUG_PT2     0  // Debug point 2: print all the words
#define DEBUG_PT3     0  // Debug point 3: print all the sentences in save()
#define DEBUG_PT4     0  // Debug point 4: print all the words in save()
#define DEBUG_PT5     0  // Debug point 5: print kw << ": " << word
#define DEBUG_PT6     0  // Debug point 6: print all the lines with the keyword in it.
#define DEBUG_PT7     0  // Debug point 7: idx2remove in TextProc::filterout()
#define DEBUG_PT8     0  // Debug point 8: Normalize text
#define DEBUG_PT9     0  // matched_index

/*
string filename_normalized_uniq_sentences("../output/normalized_uniq_sentences.txt");
string filename_normalized_uniq_words("../output/normalized_uniq_words.txt");
string filename_removed_sentences("../output/normalized_uniq_seantences.txt");
string filename_proprocessed_sentences("../outputproprocessed_sentences.txt");
*/