// remove_duplicate_lines.cpp
// 2019-01-22 (Tue)

#include "pch.h"
#include <iostream>
#include "textPreprocess.hpp"

using namespace std;

// input file is a sorted list of English sentences.
// The output file is a uniq sentence.

#include <fstream>
bool
file_exist( const string& filename)
{
	ifstream ifs(filename.c_str());
	return ifs.good();
}

int
main(int argc, char * argv[])
{
	//string filename_uniq_sentences("uniq_sentences.txt");
	string filename_uniq_sentences("uniq_sentences_manual.txt");

	textPreprocess ps;
	ps.set_filename("similar_sentences.txt", "input");
	ps.set_filename(filename_uniq_sentences, "output");
	ps.set_filename("uniq_words.txt", "output4words");

	// If uniq_sentences.txt exists, skip run() & save() and .
	// If not, run() & save() to create the file.
	if ( !file_exist(filename_uniq_sentences) )
	{
		if (DEBUG_PT5)  cout << "File doesn't exist; so run & save" << endl;
		ps.run();
		ps.save();
	} else
	{
		ps.import_file2sentence_set(filename_uniq_sentences);
	}

	cout << "Sentences matching a keyword will be removed from the (unique) sentence set." << endl;
	string keyword;
	while ( true )  // Intentionally use an infinite loop
	{
		cout << "Enter a keyword: ";
		cin >> keyword;
		if (DEBUG_PT5)  cout << "keyword=" << keyword << endl;
		ps.update(keyword);
		getchar();
	};

	return 0;
}