// config.cpp

#include "pch.h"
#include "Config.hpp"

using namespace std;

//==================================================================
//                           Public                               //
//==================================================================

Config::Config()
{
	init();
}

Config::~Config()
{
}

string
Config::get_file_default_cfg()
{
	return file_default_cfg;
}

string
Config::get_file_keywords2remove()
{
	return file_keywords2remove;
}

string
Config::get_file_similar_sentences()
{
	return file_similar_sentences;
}
string
Config::get_file_filtered_sentences()
{
	return file_filtered_sentences;
}
string
Config::get_file_uniq_sentences()
{
	return file_uniq_sentences;
}
string
Config::get_file_uniq_sentences_filtered_wt_keywords()
{
	return file_uniq_sentences_filtered_wt_keywords;
}
string
Config::get_file_sorted_transcript_en()
{
	return file_sorted_transcript_en;
}
string
Config::get_file_uniq_words()
{
	return file_uniq_words;
}
//==================================================================
//                           Private                              //
//==================================================================

void
Config::init()
{
	file_default_cfg		= "../config/default.cfg";
	file_keywords2remove    = "../config/keywords2remove.txt";
	file_similar_sentences  = "../input/similar_sentences.txt";
	file_filtered_sentences = "../input/uniq_sentences_filtered_wt_keywords.txt";
	file_uniq_sentences		= "../output/uniq_sentences.txt";
	file_uniq_words			= "../output/uniq_words.txt";

	file_uniq_sentences_filtered_wt_keywords = "../input/uniq_sentences_filtered_wt_keywords.txt";
	//file_uniq_sentences_filtered_wt_keywords = "../output/uniq_sentences_filtered_wt_keywords.txt";
	file_sorted_transcript_en = "../input/sorted_transcript_en.txt";	
}

//==================================================================
//                           Obsolete                             //
//==================================================================