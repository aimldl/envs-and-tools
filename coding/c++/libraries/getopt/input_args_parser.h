// input_args_parser.h

#ifndef INPUT_ARGS_PARSER_H_
#define INPUT_ARGS_PARSER_H_

#include  <cassert>
#include  <iostream>
#include  <string>
#include "get_opt.h"

class InputArgsParser {
 public:
  InputArgsParser();
  InputArgsParser(int argc, char **argv);
  ~InputArgsParser();

  void     parse(int argc, char **argv);
  void     show_usage();
  void     show_version();
  void     show_default_message();
 
 private:
  std::string   program_name_;
  std::string   release_date_;
  std::string   version_number_;
};

#endif // INPUT_ARGS_PARSER_H_
