#ifndef  __CONFIGREINLEARNING_HPP_
#define  __CONFIGREINLEARNING_HPP_

#include  <string>
#include  <iostream>
#include  <fstream>
#include  <vector>

#include  "Myiostream.hpp"
#include  "MyStringUtilFunctions.hpp"

using namespace  std;

//==============================================================================
//                              Type Definitions
//==============================================================================
typedef vector<double> vdouble;

//==============================================================================
//                              Class Declaration
//==============================================================================

class     ConfigReinLearning : public Myiostream
{
public:
	      ConfigReinLearning();
	     ~ConfigReinLearning();

  bool    process( const char* name, ifstream& inputObj, int& validNameFlag,
	               int& validValueFlag, int& alreadyFoundFlag );

  int     get_gridWorldSizeX_() const;
  int     get_gridWorldSizeY_() const;

  int     get_gridWorldStartPositionX_() const;
  int     get_gridWorldStartPositionY_() const;

  int     get_gridWorldEndPositionX_() const;
  int     get_gridWorldEndPositionY_() const;

  int     get_gridWorldCliffPattern_() const;
  int     get_maxNumberOfEpisodes_() const;

  vdouble get_rewardVector_() const;
  double  get_alpha_() const;
  double  get_gamma_() const;
  double  get_epsilon_() const;
  string  get_moveOption_() const;
  string  get_updateMethod_() const;
  string  get_actionCriterion_() const;

private:
  void    extractGridWorldSize_( string tmpString );
  void    extractGridWorldStartPosition_( string tmpString );
  void    extractGridWorldEndPosition_( string tmpString );
  void    extractRewardStructure_( string tmpString );

  void    validate_moveOption_();
  void    validate_updateMethod_();
  void    validate_actionCriterion_();

  int     countNumberOfColumnsIn( string tmpString );

  int     gridWorldSize_[2];
  int     gridWorldStartPosition_[2];
  int     gridWorldEndPosition_[2];
  int     gridWorldCliffPattern_;
  int     maxNumberOfEpisodes_;
  vdouble rewardVector_;
  double  alpha_;
  double  gamma_;
  double  epsilon_;
  string  moveOption_;
  string  updateMethod_;
  string  actionCriterion_;

  bool    gridWorldSize_found_;
  bool    gridWorldStartPosition_found_;
  bool    gridWorldEndPosition_found_;
  bool    gridWorldCliffPattern_found_;
  bool    maxNumberOfEpisodes_found_;
  bool    rewardStructure_found_;
  bool    alpha_found_;
  bool    gamma_found_;
  bool    epsilon_found_;
  bool    moveOption_found_;
  bool    updateMethod_found_;
  bool    actionCriterion_found_;

  bool    isGotoBookmark_;

  MyStringUtilFunctions
          strUtilObj_;
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================
