// input_args_parser.cc

//#include "pch.h"  // Uncomment this in Visual Studio
#include "input_args_parser.h"

InputArgsParser::InputArgsParser() {
}

InputArgsParser::InputArgsParser(int argc, char **argv)
  : release_date_("Mar.15, 2019"), version_number_("0.1")
{
  // Add private variables here
  parse(argc, argv);
}

InputArgsParser::~InputArgsParser() {
}

void InputArgsParser::parse(int argc, char **argv) {
  //program_name_ = argv[0];
  program_name_ = "program_name";
  GetOpt getopt(argc, argv, "hv");

  int opt;
  while ((opt = getopt()) != EOF) {
    switch (opt) {
      case 'h':  // help
        show_version();
        show_usage();
        exit(1);
        break;
      case 'v':  // version
        show_version();
        exit(1);
        break;
      // Add more arguments below

    default:
      show_default_message();
      exit(1);  // or abort();
    }
  }
}

void InputArgsParser::show_usage() {
  // This is just an example
	std::cout << " Usage\n"
		<< "   " << program_name_ << " [config_file] \n"
		<< "   config_file is located in directory config\n"
		<< " Example\n"
		<< "   " << program_name_ << " default.cfg\n"
		<< " Options\n"
		<< "   -h   help\n"
		<< "   -v   version\n";
}

void InputArgsParser::show_version() {
  std::cout << "[Program Name] " << version_number_ << std::endl;
}

void InputArgsParser::show_default_message() {
  std::cout << "Type " << program_name_ << " -h for help." << std::endl;
}
