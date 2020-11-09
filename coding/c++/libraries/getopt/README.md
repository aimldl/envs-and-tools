##### aimldl > cpp > libraries > getopt > README.md
* Revision:
* Draft: Some time ago

getopt is used to process the input arguments.

### How to compile
Run the following command
```
   $ chmod +x run
   $ ./run
```

### How to use this?
* Step 1. Copy all the source codes to your source directory.
* Step 2. Change three lines in your source code for main().
  * Step 2.1. Include the header file for input argument parser.
```cpp
	#include "input_args_parser.h"
```
  * Step 2.2. Change the input argument of main
```cpp
	int main(int argc, char** argv) {
```
  * Step 2.3. Instantiate class InputArgsParser.

```cpp
	InputArgsParser args_parser(argc, argv);
```
or
```cpp
	InputArgsParser args_parser;
        args_parser.parse(argc, argv);
```
Note: For Microsoft Visual Studio on Windows, uncomment "#include "pch.h" on the third line for get_opt.cc and input_args_parser.cc
* Step 3. Adapt input_args_parser.cc to suit your need.
          DO NOT CHANGE get_opt.cc unless you know what you're doing.
  * Step 3.1.
From
```cpp
InputArgsParser::InputArgsParser(int argc, char **argv)
  : release_date_("Mar.15, 2019"), version_number_("0.1")
```
To
```cpp
InputArgsParser::InputArgsParser(int argc, char **argv)
  : release_date_("Mar.19, 2019"), version_number_("0.2")
```
From
```cpp
void InputArgsParser::parse(int argc, char **argv) {
  program_name_ = "program_name";
```
To
```cpp
void InputArgsParser::parse(int argc, char **argv) {
  program_name_ = "create_audio_playlist";
```
From
```cpp
void InputArgsParser::parse(int argc, char **argv) {
  GetOpt getopt(argc, argv, "hv");
```
To
```cpp
void InputArgsParser::parse(int argc, char **argv) {
  GetOpt getopt(argc, argv, "hvc:i:");
```
From
```cpp
  int opt;
  while ((opt = getopt()) != EOF) {
    switch (opt) {
      [...]
      // Add more arguments below

    default:
      show_default_message();
      exit(1);  // or abort();
    }
  }
```
To
```cpp
    switch (opt) {
      [...]
      // Add more arguments below
      case 'c':  // configuration
        config_
        break;
      case 'i':  // input file name
        input_file_name_
        break;
```

In input_args_parser.h
```cpp
 private:
  [...]
  // Add more variables below
  std::string config_;
  std::string input_file_name_;
```
