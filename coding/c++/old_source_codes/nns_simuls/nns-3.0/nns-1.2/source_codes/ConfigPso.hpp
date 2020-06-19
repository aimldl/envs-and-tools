#ifndef  __CONFIGPSO_HPP_
#define  __CONFIGPSO_HPP_

#include  <string>
#include  <iostream>
#include  <fstream>  // For ifstream
#include  <cassert>
#include  <limits>

#include  "MyStringUtilFunctions.hpp"
#include  "Myiostream.hpp"

using namespace  std;

//==============================================================================
//                              Class Declaration
//==============================================================================
class     ConfigPso : public Myiostream
{
public:
          ConfigPso();
         ~ConfigPso();
  bool    process( const char* name, ifstream& inputObj, int& validNameFlag,
                   int& validValueFlag, int& alreadyFoundFlag);

  int     get_numberOfParticles_() const;
  bool    get_useParticleHistoryReset_() const;
  double  get_w_() const;
  double  get_c1_() const;
  double  get_c2_() const;
  double  get_VMax_() const;
  double  get_XMin_() const;
  double  get_XMax_() const;
  double  get_V_initialValue_() const;
  double  get_pBest_initialValue_() const;
//  double  get_globalBest_initialValue_() const;
      
private:
  int     numberOfParticles_;
  bool    useParticleHistoryReset_;
  double  w_;
  double  c1_;
  double  c2_;
  double  VMax_;
  double  XMin_;
  double  XMax_;
  double  V_initialValue_;
  double  pBest_initialValue_;

//  double  globalBest_initialValue_;
  bool    numberOfParticles_found_;
  bool    useParticleHistoryReset_found_;
  bool    w_found_;
  bool    c1_found_;
  bool    c2_found_;
  bool    VMax_found_;
  bool    XMin_found_;
  bool    XMax_found_;
  bool    V_initialValue_found_;
  bool    pBest_initialValue_found_;
//  bool    globalBest_initialValue_found_;

  bool    isGotoBookmark_;
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================
