#ifndef  __CONFIGDATA_HPP_
#define  __CONFIGDATA_HPP_

#include  <string>
#include  <iostream>
#include  <fstream>

#include  "Myiostream.hpp"

using namespace  std;

//==============================================================================
//                              Class Declaration
//==============================================================================
class     ConfigData : public Myiostream
{
public:
          ConfigData();
         ~ConfigData();
  bool    process( const char* name, ifstream& inputObj, int& validNameFlag,
                     int& validValueFlag, int& alreadyFoundFlag);
  string  get_inputConfig_() const;
  string  get_targetConfig_() const;
  string  get_dataRepresentation_() const;
  double  get_dataRepresentationOffset_() const;
  string  get_dataType_() const;

private:
  void    validate_dataRepresentation_();
  void    validate_dataRepresentationOffset_();
  void    validate_dataType_();

  string  inputConfig_;
  string  targetConfig_;
  string  dataRepresentation_;
  double  dataRepresentationOffset_;
  string  dataType_;

  bool    inputConfig_found_;
  bool    targetConfig_found_;
  bool    dataRepresentation_found_;
  bool    dataRepresentationOffset_found_;
  bool    dataType_found_;

  bool    isGotoBookmark_;
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================

// This class is to configure simulations.
