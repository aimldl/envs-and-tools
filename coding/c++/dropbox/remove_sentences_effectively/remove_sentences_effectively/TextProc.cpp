// TextProc.cpp

#include "pch.h"
#include "TextProc.hpp"

using namespace std;

//==================================================================
//                           Public                               //
//==================================================================

void
TextProc::save_word_set(string input_file, string output_file)
{
	assert(is_configured);
	assert(!input_file.empty());

	sentence_set				  = file2sentences(input_file);
	uniq_sentence_vect			  = set2vector(sentence_set);  // same as sentence_set, but in the form of vector
	normalized_uniq_sentence_vect = normalize(uniq_sentence_vect);
	word_set					  = sentences2words(normalized_uniq_sentence_vect);
	cout_stats();

	save(word_set, output_file);
}

// Convert set to vector because it's hard to iterate through and remove elements in a set with index.
// You may check the output with the following lines:
//   cout_set_string(sentence_set);
//   cout_vector_string(uniq_sentence_vect);
//   cout_vector_string(normalized_uniq_sentence_vect);
void
TextProc::run(string input_file)
{
	assert(is_configured);
	assert(!input_file.empty());

	sentence_set                  = file2sentences(input_file);
	uniq_sentence_vect            = set2vector(sentence_set);
	normalized_uniq_sentence_vect = normalize(uniq_sentence_vect);
	word_set                      = sentences2words(normalized_uniq_sentence_vect);
	cout_stats();

	cout << " " << endl;
	cout << "Sentences matching a keyword will be removed from the (unique) sentence set." << endl;
	string keyword;

	vec_str imported_keyword_vect;
    ifstream ifs;
    ifs.open(cfg_ptr->get_file_keywords2remove());
    while (ifs.good())
    {
	  getline(ifs, keyword);
	  if (DEBUG)  cout << keyword << endl;
	  imported_keyword_vect.push_back(keyword);
    }
	ifs.close();

	 cout << "Importing the existing keywords from " << cfg_ptr->get_file_keywords2remove() << endl;
	 for (auto keyword : imported_keyword_vect)
	 {
		// cout << "keyword=" << keyword << endl;
		 if ( !keyword.empty() )  // remove new line
		 {
			 cout << "keyword=" << keyword << endl;
			 keyword_vect.push_back(keyword);
			 matched_index = get_matched_index(normalized_uniq_sentence_vect, keyword);

			 // More than two indexes may be checked with many keywords. Use set to save only an element.
			 for (auto index : matched_index)  matched_index_set.insert(index);  // Note matched_index_set is sorted!
		 }
	 }
	 cout << endl;

	 // TODO: merge the old keywords from word and then merge down.

	cout << "Saving matched keywords to matched_keywords.txt" << endl;
	save(keyword_vect, "../output/matched_keywords.txt");

	cout << "Saving matched sentences to matched_sentences.txt" << endl;
	matched_sentence_vect = extract(matched_index_set, uniq_sentence_vect);
	save(matched_sentence_vect, "../output/matched_sentences.txt");

	cout << "Saving fIltered-out sentencesto filtered_sentences.txt" << endl;
	// Remember the index for uniq_sentence_vect & normalized_uniq_sentence_vect is identical.
	// I want to save sentences that are NOT normalized because it's easier to read.
	filtered_sentence_vect = remove(matched_index_set, uniq_sentence_vect);
	save(filtered_sentence_vect, "../output/filtered_sentences.txt");

	cout << "Saving unique words to " << "../output/uniq_words.txt" << endl;
	save(word_set, "../output/uniq_words.txt");
}

//==================================================================
//                           Private                              //
//==================================================================

TextProc::TextProc(Config &cfg)
{
	cfg_ptr = &cfg;
	is_configured = true;
}

TextProc::TextProc(Config &cfg, NLP &nlp)
{
	cfg_ptr = &cfg;
	nlp_ptr = &nlp;
	is_configured = true;
}

TextProc::~TextProc()
{
}

// matched_index = filterout(keyword, normalized_uniq_sentence_vect);

// Check if a sentence includes the keyword. If yes, save the index of the sentence matching the keyword, 
// With the index, those matching sentences can be removed in the later part anytime!
//
// This part is likely to be the bottle neck of this program.
// It's O(n^2) with 100k lines of sentences.
// But it actually runs quite fast. So no worries!
// This can be made void, but use input & output arguments to clarify what goes in and out.
vec_int
TextProc::get_matched_index(vec_str sentence_vector, string &keyword)
{
	assert(!sentence_vector.empty());
	assert(!keyword.empty());

	string			word;
	string			sentence;		// For readability
	vec_int     matched_index;	// Index of uniq_sentence_list to remove.

	// Iteratively see if keyword matches any word in sentence.
	// word is tokenized from sentence.
	for (int i = 0; i < sentence_vector.size(); i++)
	{
		sentence = sentence_vector.at(i);	// Each line has a sentence, but strictly speaking, a line occasionally includes two sentences.
		stringstream ss(sentence);			// tokenize each word delimited by space
		while (ss.good())					// While there's a word in ss,
		{
			ss >> word;
			if (DEBUG_PT5)  cout << keyword << ": " << word << endl;
			if (DEBUG_STOP) getchar();
			if (keyword == word)
			{
				if (DEBUG_PT6)  cout << sentence << endl;
				matched_index.push_back(i);
				break;  // No need to search the rest of the sentence
			}
		}
	}
	if (DEBUG) for (auto index : matched_index) cout << index << endl;
	return matched_index;
}

vec_str
TextProc::extract(vec_int matched_index, vec_str sentence_vect)
{
	assert(!matched_index.empty());
	assert(!sentence_vect.empty());

	vec_str matched_sentence_vect;
	int size_vect = sentence_vect.size();

	// Use a flag to save
	// This flag is opposite to that of remove(...)
	bool* flag2save = new bool[size_vect];
	for (int i = 0; i < size_vect; i++)
		flag2save[i] = false;

	int index2skip;
	for (int r = 0; r < matched_index.size(); r++)  // r to remove
	{
		index2skip = matched_index.at(r);
		flag2save[index2skip] = true;
	}

	string sentence;  // for readaiblity
	for (int i = 0; i < size_vect; i++)
	{
		if (flag2save[i])  // if the flag says to save
		{
			sentence = sentence_vect.at(i);
			matched_sentence_vect.push_back(sentence);
		}
	}
	return matched_sentence_vect;
}

vec_str
TextProc::extract(set_int matched_index_set, vec_str sentence_vect)
{
	assert(!matched_index_set.empty());
	assert(!sentence_vect.empty());

	vec_str matched_sentence_vect;
	int size_vect = sentence_vect.size();

	// Use a flag to save
	// This flag is opposite to that of remove(...)
	bool* flag2save = new bool[size_vect];
	for (int i = 0; i < size_vect; i++)
		flag2save[i] = false;

	for ( auto index2save : matched_index_set)
	{
		flag2save[index2save] = true;
	}

	string sentence;  // for readaiblity
	for (int i = 0; i < size_vect; i++)
	{
		if (flag2save[i])  // if the flag says to save
		{
			sentence = sentence_vect.at(i);
			matched_sentence_vect.push_back(sentence);
		}
	}
	return matched_sentence_vect;
}

// Usage example:
//   filtered_sentence_vect = remove(matched_index, uniq_sentence_vect);
// Remove matched_index from sentence_vect and return the sentence_vect without sentences at matched_index
vec_str
TextProc::remove(vec_int matched_index, vec_str sentence_vect)
{
	assert(!matched_index.empty());
	assert(!sentence_vect.empty());

	vec_str filtered_sentence_vect;
	int size_vect = sentence_vect.size();

	// Use a flag to skip
	// This flag is opposite to that of extract(...)
	bool* flag2skip = new bool[size_vect];
	for (int i = 0; i < size_vect; i++)
		flag2skip[i] = false;

	int index2skip;
	for (int r = 0; r < matched_index.size(); r++)  // r to remove
	{
		index2skip = matched_index.at(r);
		flag2skip[index2skip] = true;
	}

	string sentence;  // for readaiblity
	for (int i = 0; i < size_vect; i++)
	{
		if ( !flag2skip[i] )  // if the flag says, don't skip
		{
			sentence = sentence_vect.at(i);
			filtered_sentence_vect.push_back(sentence);
		}
	}
	return filtered_sentence_vect;
}

vec_str
TextProc::remove(set_int matched_index_set, vec_str sentence_vect)
{
	assert(!matched_index_set.empty());
	assert(!sentence_vect.empty());

	vec_str filtered_sentence_vect;
	int size_vect = sentence_vect.size();

	// Use a flag to skip
	// This flag is opposite to that of extract(...)
	bool* flag2skip = new bool[size_vect];
	for (int i = 0; i < size_vect; i++)
		flag2skip[i] = false;

	for (auto index2skip : matched_index_set)
	{
		flag2skip[index2skip] = true;
	}

	string sentence;  // for readaiblity
	for (int i = 0; i < size_vect; i++)
	{
		if (!flag2skip[i])  // if the flag says, don't skip
		{
			sentence = sentence_vect.at(i);
			filtered_sentence_vect.push_back(sentence);
		}
	}
	return filtered_sentence_vect;
}

// Don't use const because the input argument will be modified.
set_str
TextProc::normalize(set_str &sentence_set)
{
	// Exactly speaking, iterate through each line.
	// A line has roughly a sentence.	
	set_str normalized_set;
	for (auto sentence : sentence_set)
	{
		nlp_ptr->normalize(sentence);
		normalized_set.insert(sentence);
	}
	return normalized_set;
}

// Don't use const because the input argument will be modified.
vec_str
TextProc::normalize(vec_str& sentence_vect)
{
	// Exactly speaking, iterate through each line.
    // A line has roughly a sentence.	
	vec_str normalized_vect;
	for (auto sentence : sentence_vect)
	{
		nlp_ptr->normalize(sentence);
		normalized_vect.push_back(sentence);
	}
	return normalized_vect;
}

void
TextProc::import_file2sentence_set(string filename)
{
	string line;  // About a sentence per line
	ifstream ifs(filename);

	while (getline(ifs, line))
	{
		sentence_set.insert(line);
	};
	if (DEBUG_PT1) cout_set_string(sentence_set);
	ifs.close();
}


// sentence.substr(pos+1)
//\KT_STT_HOTEL_ENG_REC - DB_3rd_0051_180402\1M\114_UK_F3KG00\065.pcm	1 scheme and is shown beginning in Fig.
//\KT_STT_HOTEL_ENG_REC - DB_3rd_0065_180402\3M\114_UK_F3KG00\065.pcm	1 scheme and is shown beginning in Fig.
//\KT_STT_HOTEL_ENG_REC - DB_3rd_0051_180402\1M\115_US_M4_PS00\070.pcm	1 to 1 - 1 grams per 100 pounds of body weight.

void
TextProc::match_and_save(string input_file, string target_file, string output_file)
{
	assert(!input_file.empty());
	assert(!target_file.empty());
	assert(!output_file.empty());

	ifstream ifs_input(input_file);

	string line;
	string filename;
	string sentence;
	string ref_sentence;  // reference sentence

	map<string,string>  str_hash;

	// Convert
	size_t pos;
	int    l = 0;  // line count
	int    count = 0;

	// First line
	getline(ifs_input, line);
	pos = line.find_first_of("\t");  // find the location of \t
	sentence = line.substr(pos + 1);
	filename = line.substr(0, pos);
	if (DEBUG)  cout << filename << "\t" << sentence << endl;
	ref_sentence = sentence;
	l++;

	while (ifs_input.good())
	{
		getline(ifs_input, line);
		pos      = line.find_first_of("\t");  // find the location of \t
		sentence = line.substr(pos + 1);
		filename = line.substr(0, pos);
		l++;

		if (DEBUG)  cout << filename << "\t" << sentence << endl;
		if (ref_sentence == sentence)  count++;
		else
		{
			
		}
		getchar();
	}
	ifs_input.close();
}

set_str
TextProc::file2sentences(string filename)
{
	assert(!filename.empty());

	set_str  sentence_set_;

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
	sentence_count      = line_count;
	uniq_sentence_count = sentence_set_.size();

	return sentence_set_;
}

set_str
TextProc::sentences2words(vec_str &sentence_vect)
{
	if (DEBUG_VERBOSE)  cout << "TextProc::sentences2words" << endl;

	set_str word_set_;
	string word;
	int    count;  // word_count

	if (DEBUG_PT1)  cout << "TextProc::sentences2words" << endl;
	// for each sentence in set_string, iterate through all the unique sentences in set_string
	count = 0;
	for (auto sentence : sentence_vect)
	{
		if (DEBUG_PT1)  cout << sentence << endl;
		stringstream ss(sentence);

		while (ss >> word)  // This is the process to tokenize words.
		{
			if (DEBUG_PT2) cout << word << endl;
			word_set_.insert(word);
			count++;
		};
	}
	word_count      = count;
	uniq_word_count = word_set_.size();

	return word_set_;
}

set_str
TextProc::sentences2words(set_str  sentence_set)
{
	if (DEBUG_VERBOSE)  cout << "TextProc::sentences2words" << endl;

	set_str word_set_;
	string word;
	int    count;

	// for each sentence in set_string, iterate through all the unique sentences in set_string
	count = 0;  // word_count
	for (set_str::iterator itr = sentence_set.begin(); itr != sentence_set.end(); itr++)
	{
		if (DEBUG_PT1)  cout << *itr << endl;
		stringstream ss(*itr);

		while (ss >> word)  // This is the process to tokenize words.
		{
			if (DEBUG_PT2) cout << word << endl;
			word_set_.insert(word);
			count++;
		};
	}
	word_count = count;
	uniq_word_count = word_set_.size();

	return word_set_;
}