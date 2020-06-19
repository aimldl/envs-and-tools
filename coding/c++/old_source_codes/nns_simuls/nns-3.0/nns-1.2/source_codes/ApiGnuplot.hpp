#ifndef  __APIGNUPLOT_HPP_
#define  __APIGNUPLOT_HPP_

#include  "Myiostream.hpp"

using namespace  std;

//==============================================================================
//                              Class Declaration
//==============================================================================
class      ApiGnuplot : public Myiostream
{
public:
           ApiGnuplot();
          ~ApiGnuplot();
  void     run();
          
private:
  string   gnuplotCommand_;
  string   systemCommandRunGnuplot_;
  string   systemCommandRunGnugv_;
};

#endif
