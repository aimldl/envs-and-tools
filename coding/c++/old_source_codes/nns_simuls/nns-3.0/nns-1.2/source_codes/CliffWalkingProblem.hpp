#ifndef  __CLIFFWALKINGPROBLEM_HPP__
#define  __CLIFFWALKINGPROBLEM_HPP__

#include  "ReinforcementLearning.hpp"
#include  "GridWorld.hpp"

using namespace std;

//==============================================================================
//                              Type Definitions
//==============================================================================
typedef vector<double> vdouble;

//==============================================================================
//                             Forward Declaration
//==============================================================================

//==============================================================================
//                              Class Declaration
//==============================================================================

class      CliffWalkingProblem : public ReinforcementLearning
{
public:
           CliffWalkingProblem();
          ~CliffWalkingProblem();
  static
  void     configure( Config& configObj );  // IMPORTANT! RUN THESE FUNCTIONS BEFORE THIS CLASS IS CONSTRUCTED!!!

  void     initialize();
  void     logResults();
  void     runSimulation( bool showProgressBar );

private:
  void     runSARSA( bool showProgressBar, int resolution );
  void     runQLearning( bool showProgressBar, int resolution );

  bool     isTerminal( Location currentLocation );
  int      getStateIndex( Location state );
  int      getStateIndex( int x, int y );
//  int      chooseAction( Location currentLocation, string actionCriterion );
  int      greedy( Location currentLocation );
  int      eGreedy( Location currentLocation );
  double   observeReward( Location loc );
  Location getNewLocation( int action, Location currentLocation );
  Location standardMove( int action );
  Location kingsMove( int action );
  Location kingsMoveWithPause( int action );

  void     show_policy_();
  void     show_policy_dout();
  void     showQ_();
  void     showQ_dout();
  void     showStateIndexMapping();
  void     showGridWorldOutput();
  void     logGridWorldOutput();
  string   a2u( int x, int y );
  string   useFullBlock();
  string   useAnArrow( int action );
  string   useDoubleArrow( int action );
  string   useBlackArrow( int action );


  static
  string   moveOption_;

  GridWorld
           grid_;
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================
// CliffWalkingProblem.hpp
// Created on: Apr 8, 2011
//     Author: tk424
