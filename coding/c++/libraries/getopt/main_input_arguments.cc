// main_input_arguments.cc

//#include "pch.h"  // Uncomment this in Visual Studio

#include "input_args_parser.h"

int main(int argc, char** argv) {
	InputArgsParser args_parser(argc, argv);
}

// Expected output
//   $ . / input_arguments.exe - h
//   [Program Name] 0.1
//    Usage
//      program_name[config_file]
//      config_file is located in directory config
//    Example
//      program_name default.cfg
//    Options
//      - h   help
//      - v   version
//   $ . / input_arguments.exe - v
//   [Program Name] 0.1
//
//   $
