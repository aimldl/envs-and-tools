#include "pch.h"
#include "Args.hpp"

//==============================================================================
//                            Public functions
//==============================================================================

Args::Args(int argc, char **argv)
	: release_date("Jan.29, 2019"), version_number("0.2")
{
	process_words     = false;
	process_sentences = false;
	process_filenames = false;

	process(argc, argv);
}

Args::~Args()
{
}

bool
Args::is_word_level()
{
	return process_words;
}

bool
Args::is_sentence_level()
{
	return process_sentences;
}

bool
Args::match_filenames()
{
	return process_filenames;
}

//==============================================================================
//                            Private functions
//==============================================================================

void
Args::process(int argc, char **argv)
{
	//program_name = argv[0];           // C:\Users\phil4\source\repos\remove_sentences_effectively\Debug\remove_sentences_effectively.exe
	program_name = "remove_sentences_effectively.exe";
	GetOpt getopt(argc, argv, "hvswf");

	int opt;
	while ((opt = getopt()) != EOF)
	{
		switch (opt)
		{
			case 'h':  // help
				show_version();
				show_usage();
				exit(1);
				break;
			case 'v':  // version
				show_version();
				exit(1);
				break;
			case 's':  // Sentence-level processing
				process_sentences = true;
				break;
			case 'w':  // word-level processing
				process_words = true;
				break;
			case 'f':  // get the matched file names
				process_filenames = true;
				break;

			default:
				show_default_message();
				exit(1);  // or abort();
		}
	}
}

void
Args::show_usage()
{
	cout << " Usage\n"
		 << "   " << program_name << " [config_file] \n"
		 << "   config_file is located in directory config\n"
		 << " Example\n"
		 << "   " << program_name << " default.cfg\n"
		 << " Options\n"
		 << "   -s   sentence-level processing \n"
		 << "   -w   word-level processing \n"
		 << endl;
}

void
Args::show_version()
{
	cout << " LID Transcript Preprocessor " << version_number << endl;
}

void
Args::show_default_message()
{
	cout << "Type " << program_name << " -h for help." << endl;
}