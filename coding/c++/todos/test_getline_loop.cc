// test_getline_loop.cc

//#include "pch.h"  // Uncomment this in Visual Studio
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// This file is incomplete

using namespace std;
 
int main()
{
  string input_file = "input/sample_input.txt";
  string output_file = "output/sample_output.txt";
  string line;
          
  ifstream ifs;
  ofstream ofs;
  ifs.open( input_file.c_str() );
  if ( !ifs.is_open() ) {
    cerr << input_file << " is not open." << endl;
  }
  ofs.open( output_file.c_str() );
          
  int loc;
  while ( !ifs.eof() ) {
    getline(ifs,line);
   
    loc = line.find("#");
    cout << loc << "\t" << line << endl;
    getchar();
 
//  cout << line.substr(0,loc-1) << endl;     
//  ofs << line.substr(0,loc-1) << endl;       
  }

  ifs.close();
  ofs.close();
          
  return 0;
}
