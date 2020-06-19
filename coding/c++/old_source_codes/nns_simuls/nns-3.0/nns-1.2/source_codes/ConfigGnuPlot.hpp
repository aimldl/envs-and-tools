#ifndef  __CONFIGGNUPLOT_HPP_
#define  __CONFIGGNUPLOT_HPP_

#include  <string>
#include  <iostream>
#include  <fstream>  // For ifstream

#include  "Myiostream.hpp"

using namespace  std;

//==============================================================================
//                              Class Declaration
//==============================================================================
class     ConfigGnuPlot : public Myiostream
{
public:
          ConfigGnuPlot();
         ~ConfigGnuPlot();
  bool    process( const char* name, ifstream& inputObj, int& validNameFlag,
                   int& validValueFlag, int& alreadyFoundFlag);
  string  get_graphTitle_() const;
  int     get_run_() const;

private:
  int     run_;
  string  graphTitle_;
  double  rangeXFrom_;
  double  rangeXTo_;
  double  rangeXIncrement_;

  bool    run_found_;
  bool    graphTitle_found_;
  bool    rangeXFrom_found_;  
  bool    rangeXTo_found_;  
  bool    rangeXIncrement_found_;  
  
  bool    isGotoBookmark_;
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================
