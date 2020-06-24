#ifndef  __APIPOSTPROCESS_HPP_
#define  __APIPOSTPROCESS_HPP_

#include  <iostream>
#include  <cassert>
#include  <cstdlib>
#include  <string>

#include  "Myiostream.hpp"

using namespace  std;

//==============================================================================
//                              Class Declaration
//==============================================================================
class      ApiPostprocess : public Myiostream
{
public:
           ApiPostprocess();
          ~ApiPostprocess();
  void     run();
          
private:
  string   postprocessCommand_;
  string   systemCommandRunPostprocess_;
  ofstream
           traceFileStream_;
};

#endif
