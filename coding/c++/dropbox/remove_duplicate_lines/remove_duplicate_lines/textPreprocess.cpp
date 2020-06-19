// textPreprocess.cpp

#include "pch.h"
#include "textPreprocess.hpp"

using namespace std;

//==================================================================
//                           Public                               //
//==================================================================

void
textPreprocess::set_filename(string name, string filetype)
{
	     if (filetype == "input")  input_file = name;
	else if (filetype == "output") output_file = name;
	else if (filetype == "output4words") output4words = name;
}

// TODO: This part causes a link error, but I don't know why.
string
textPreprocess::get_filename(string filetype)
{
	if (filetype == "input")
	{
		assert(!input_file.empty());
		return input_file;
	} else if (filetype == "output")
	{
		assert(!output_file.empty());
		return  output_file;
	}
	// TODO: for output4words
//	return filetype;  // If this is returned, it's an error.
}

void
textPreprocess::run()
{
	assert(!input_file.empty());

	sentence_set = file2sentences(input_file);
	word_set = sentences2words(sentence_set);
	cout_stats();
}

void
textPreprocess::save()
{
	save_sentence_set();
	save_word_set();
}

void
textPreprocess::save_sentence_set()
{
	assert(!sentence_set.empty());
	assert(!output_file.empty());
	if (DEBUG_PT3) for (set<string>::iterator itr = sentence_set.begin(); itr != sentence_set.end(); itr++)  cout << *itr << endl;

	ofstream ofs;
	ofs.open(output_file);
	for (set<string>::iterator itr = sentence_set.begin(); itr != sentence_set.end(); itr++)
	{
		ofs << *itr << endl;
	}
}

void
textPreprocess::save_word_set()
{
	assert(!word_set.empty());
	assert(!output4words.empty());
	if (DEBUG_PT4) for (set<string>::iterator itr = word_set.begin(); itr != word_set.end(); itr++)  cout << *itr << endl;

	ofstream ofs;
	ofs.open(output4words);
	for (set<string>::iterator itr = word_set.begin(); itr != word_set.end(); itr++)
	{
		ofs << *itr << endl;
	}
}

void
textPreprocess::import_file2sentence_set(string filename)
{
	string line;  // About a sentence per line
	ifstream ifs(filename);

	while ( getline(ifs, line) )
	{
		sentence_set.insert(line);
	};
	if (DEBUG_PT1) cout_set_string(sentence_set);
}

// Check if a sentence includes the keyword. If yes, remove it.

void
textPreprocess::update(string kw)
{
	if (DEBUG_PT5)  cout << "textPreprocess::update" << endl;
	assert( !sentence_set.empty() );
	assert(!kw.empty());

	ofstream ofs("removed_sentences.txt");
	set<string>    dummy_sentence_set = sentence_set;

	get_index2remove(sentence_set, kw);  // This can be made void, but use input & output arguments to clarify what goes in and out.

	ofs.close();
//	save(sentence_set, "new_uniq_sentences.txt");
}

void
textPreprocess::save(const set<string>& set_string, const string filename)
{
	if (DEBUG_PT5)  cout << "textPreprocess::save(...)" << endl;

	assert(!set_string.empty());
	assert(!filename.empty());

	if (DEBUG_PT3) for (set<string>::iterator itr = set_string.begin(); itr != set_string.end(); itr++)  cout << *itr << endl;

	ofstream ofs;
	ofs.open(filename);
	for (set<string>::iterator itr = set_string.begin(); itr != set_string.end(); itr++)
	{
		ofs << *itr << endl;
	}
}

set<string>
textPreprocess::file2sentences(string filename)
{
	assert(!filename.empty());

	set<string>  sentence_set_;

	ifstream ifs;
	string   line;  // Each line is a sentence.

	ifs.open(filename);
	int line_count = 0;
	if (ifs.is_open())
	{
		while (getline(ifs, line))
		{
			sentence_set_.insert(line);
			line_count++;
		}
		ifs.close();
	}
	set_sentence_count(line_count);  // i.e. sentence_count = line_count;
	set_uniq_sentence_count(sentence_set_.size());

	return sentence_set_;
}


// This is the process to tokenize words.
set<string>
textPreprocess::sentences2words(set<string>  sentence_set)
{
	if (DEBUG_VERBOSE)  cout << "textPreprocess::sentences2words" << endl;
	if (DEBUG_STOP)     getchar();

	set<string> word_set_;
	string word;
	int    word_count;

	// for each sentence in set_string, iterate through all the unique sentences in set_string
	word_count = 0;
	for (set<string>::iterator itr = sentence_set.begin(); itr != sentence_set.end(); itr++)
	{
		if (DEBUG_PT1)  cout << *itr << endl;
		stringstream ss(*itr);

		while (ss >> word)
		{
			if (DEBUG_PT2) cout << word << endl;
			word_set_.insert(word);
			word_count++;
		};
	}

	set_word_count(word_count);
	set_uniq_word_count(word_set_.size());

	return word_set_;
}

//Example: cout_set_string(sentence_set);
void
textPreprocess::cout_set_string(set<string> &set_string)
{
	for ( auto element: set_string )
	{
		cout << element << endl;
	}
}


// TODO: merge these two functions with a template, so this function can be generalized.
void
textPreprocess::cout_vector_string(vector<string> &vector_string)
{
	for ( auto element: vector_string)
	{
		cout << element << endl;
	}
}

void
textPreprocess::cout_stats()
{
	cout << "Input file=" << input_file << endl;
	cout << "Total number of sentences: sentence_count=" << sentence_count << endl;
	cout << "Total number of words: word_count=" << word_count << endl;
	cout << "Number of unique sentences: uniq_sentence_count=" << uniq_sentence_count << endl;
	cout << "Number of unique words: uniq_word_count=" << uniq_word_count << endl;
}

//==================================================================
//                           Private                              //
//==================================================================
void
textPreprocess::set_sentence_count(int count)
{
	sentence_count = count;
}

void
textPreprocess::set_word_count(int count)
{
	word_count = count;
}

void
textPreprocess::set_uniq_sentence_count(int count)
{
	uniq_sentence_count = count;
}

void
textPreprocess::set_uniq_word_count(int count)
{
	uniq_word_count = count;
}

vector<string>
textPreprocess::set2vector(set<string> set_string)
{
	// An external vector needs to be defined!
	// TODO: change this part, so the vector created in this fn can still exist when this function is closed.

	assert(!set_string.empty());

	vector<string> vector_string;
	for (auto element : set_string)
	{
		vector_string.push_back(element);
	}
	return vector_string;
}

// This part is likely to be the bottle neck of this program.
// It's O(n^2) with 100k lines of sentences.
// But it actually runs quite fast. So no worries!

// Save the index of the sentence matching the keyword, 
// so these sentences can be removed in the later part.

// Convert set to vector because it's hard to iterate through and remove elements in a set with index.

vector<int>
get_index2remove(set<string> sentence_set_, string &kw_)
{
	string   word;
	string   sentence;  // For readability
	vector<string> uniq_sentence_list;
	vector<int>    idx2remove;  // Index of uniq_sentence_list to remove.


	for (int i = 0; i < uniq_sentence_list.size(); i++)
	{
		sentence = uniq_sentence_list.at(i);  // Strictly speaking, a line occasionally includes two sentences.
		stringstream ss(sentence);
		while (ss.good())
		{
			ss >> word;
			if (DEBUG_PT5)  cout << kw_ << ": " << word << endl;
			if (DEBUG_STOP) getchar();
			if (kw_ == word)
			{
				if (DEBUG_PT6)  cout << sentence << endl;
				idx2remove.push_back(i);
				break;  // No need to search the rest of the sentence
			}
		}
	}
	return idx2remove;
}



//==================================================================
//                           Obsolete                             //
//==================================================================
/*
void
textPreprocess::file2sentences()
{
	//set<string>  sentence_set; // sentence_set is used the internal variable.

	ifstream ifs;
	string   line;

	ifs.open(input_file);
	line_count = 0;
	if (ifs.is_open())
	{
		while (getline(ifs, line))
		{
			sentence_set.insert(line);
			line_count++;
		}
		ifs.close();
	}

	if (VERBOSE) cout << "line_count or whole sentences=" << line_count << ",'" << "sentence_set.size()=" << sentence_set.size() << endl;
}
*/