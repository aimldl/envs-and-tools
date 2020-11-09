#ifndef  __REINFORCEMENTLEARNING_HPP_
#define  __REINFORCEMENTLEARNING_HPP_

#include  "Myiostream.hpp"
#include  "RandomVariables.hpp"

#include   <vector>

using namespace std;

//==============================================================================
//                              Type Definitions
//==============================================================================
typedef vector<double> vdouble;

//==============================================================================
//                             Forward Declaration
//==============================================================================
class      Config;

//==============================================================================
//                              Class Declaration
//==============================================================================
class      ReinforcementLearning : public Myiostream
{
public:
	         ReinforcementLearning();
          ~ReinforcementLearning();
  static
  void     configure( Config& configObj );  // IMPORTANT! RUN THESE FUNCTIONS BEFORE THIS CLASS IS CONSTRUCTED!!!

  virtual
  void     initialize();
  virtual
  void     runSimulation( bool showProgressBar );

  void     initializeQ_();

protected:
  int      chooseAction( int state, string actionCriterion );
  int      eGreedy( int state );
  int      argmax( double* vector );
  void     logErrorProfileHeader();

  static
  int      maxNumberOfEpisodes_;
  static
  vdouble  rewardVector_;
  static
  double   alpha_;
  static
  double   gamma_;
  static
  double   epsilon_;
  static
  string   updateMethod_;
  static
  string   actionCriterion_;

  int      numOfStates_;
  int      numOfActions_;
  double** Q_;          // Action-state value function Q
  int*     policy_;

  RandomVariables
           rv_;
};

#endif
//==============================================================================
//                                  Comments
//==============================================================================
