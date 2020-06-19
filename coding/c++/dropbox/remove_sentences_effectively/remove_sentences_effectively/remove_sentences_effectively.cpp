// remove_sentences_effectively.cpp
// 
// Last updated:  2019-01-29 (Tue)
// First written: 2019-01-22 (Tue)

#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include "TextProc.hpp"
#include "Args.hpp"
#include "NLP.hpp"

using namespace std;

int
main(int argc, char **argv)
{
	Args	 cmd_line_obj(argc, argv);
	Config	 cfg_obj;
	NLP		 nlp_obj;
	TextProc proc_obj(cfg_obj, nlp_obj);
	
	string   input_file;
	string   target_file;
	string   output_file;

	if (cmd_line_obj.is_word_level())		// Option -w
	{
		input_file  = cfg_obj.get_file_filtered_sentences();
		output_file = cfg_obj.get_file_uniq_words();
		cout << "Word-level processing of " << input_file << endl;
		proc_obj.save_word_set(input_file, output_file);
	}

	if (cmd_line_obj.is_sentence_level())   // Option -s
	{
		input_file = cfg_obj.get_file_similar_sentences();

		cout << "Sentence-level processing of " << input_file << endl;
		proc_obj.run(cfg_obj.get_file_similar_sentences());
	}

	if (cmd_line_obj.match_filenames())		// Option -f
	{
		//proc_obj.run(cfg_obj.get_file_filtered_sentences());

		input_file  = cfg_obj.get_file_sorted_transcript_en();
		target_file = cfg_obj.get_file_uniq_sentences_filtered_wt_keywords();
		output_file = "output.txt";
		cout << "Step 1. See if a sentence in " << input_file << endl;
		cout << "        matches sentences in " << target_file << endl;
		cout << "Step 2. For the matched sentences, save the corresponding file names to " << output_file << endl;
		
		proc_obj.match_and_save(input_file, target_file, output_file);
	}

	return 0;
 }

// input file is a sorted list of English sentences.
// The output file is a uniq sentence.

// Usage
// Step 1. Open config/keywords2remove.txt and add keywords to remove each line.
// Step 2. Run this program.
// Step 3. Check output/filtered_sentences.txt and find more keywords.
// Step 4. Iterate Step 1 through 3.

// Note: If you add keywords to config/keywords2remove.txt, output/matched_keywords.txt is the same.
//       But these two files differ when keywords are added in the command line.
//       In this case, added keywords in output/matched_keywords needs to be moved to config/keywords2remove.txt.