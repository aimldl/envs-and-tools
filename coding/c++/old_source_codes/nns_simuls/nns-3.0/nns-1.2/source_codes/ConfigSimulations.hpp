#ifndef  __CONFIGSIMULATIONS_HPP_
#define  __CONFIGSIMULATIONS_HPP_

#include  <string>
#include  <iostream>
#include  <fstream>
#include  <cstdlib>  // for exit

#include  "Myiostream.hpp"

using namespace  std;

//==============================================================================
//                              Class Declaration
//==============================================================================
class      ConfigSimulations : public Myiostream
{
public:
           ConfigSimulations();
          ~ConfigSimulations();
  bool     process( const char* name, ifstream& inputObj, int& validNameFlag,
                    int& validValueFlag, int& alreadyFoundFlag);
  string   get_taskType_() const;
  int      get_boardSize_() const;
  bool     get_postprocess_() const;
  bool     get_showProgressBar_() const;
  string   get_player_() const;
  bool     get_trace4dbg_() const;
  bool     get_trace4dbg_found_() const;

private:
  void     validate_taskType_();
  void     validate_player_();

  string   taskType_;
  int      boardSize_;
  bool     postprocess_;
  bool     showProgressBar_;
  string   player_;
  bool     trace4dbg_;

  bool     taskType_found_;
  bool     boardSize_found_;
  bool     postprocess_found_;
  bool     showProgressBar_found_;
  bool     player_found_;
  bool     trace4dbg_found_;

  bool     isGotoBookmark_;
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================

// This class is to configure simulations.
