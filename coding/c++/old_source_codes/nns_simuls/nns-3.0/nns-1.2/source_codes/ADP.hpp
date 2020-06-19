#ifndef  __ADP_HPP_
#define  __ADP_HPP_

#include  <iostream>
#include  <fstream>
#include  <algorithm>
#include  <functional>
#include  <vector>

#include  "Config.hpp"
#include  "Myiostream.hpp"

//#include "WindyGridworld.h"
//#include "CliffWalking.h"

using namespace std;

//==============================================================================
//                              Type Definitions
//==============================================================================
//==============================================================================
//                              Class Declaration
//==============================================================================
class     ADP : public Myiostream
{
public:
          ADP();
         ~ADP();

  int*    policy;

protected:
  static  int      time_o_;  // epoch for outer lopp
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================

/*
class ADP {
public:
	
	ADP();
//	ADP(enum moveType type_);
//	ADP(enum moveType type_, double alpha_, double gamma_, double epsilon_);
	int r;

	int maxNumActions;
	double **Q;							// state-action value function
	double alpha;
	double gamma;
	double epsilon;

	location state;
	location movement_;

	int chooseNextAction(int currentState_ ,enum vFnUpdate upMethod_, ADP &agent_);
	int chooseGreedyAction(int currentState_);
	int eGreedy(double ** Q_, int state_);
	int greedy(double ** Q_, int state_);
	int searchMax(double *vector_, int maxNum_);

	location getState();

	void initQ_s_a(double sa_value_);
	void initQ_s_a();
	void initPolicy();

	int isTerminal(location state_, WindyGridworld grid_);
	int isTerminal(location state_, CliffWalking grid_);

	location stdMoves(int move_);
	location kingsMoves(int move_);
	location kingsMove_pause(int move_);

	void sarsa(int s, int a, int r, int s_, int a_, ADP &agent);
	void QLearning(int s, int a, int r, int s_, int a_, ADP &agent);
	
	void setPolicy();
	void setFinalPolicy();
	void setState(location now_);
	void setState(int state_);

	void setmaxNumActions(int numActions_);

	void vFnUpdate(int s, int a, int r, int s_, int a_, ADP &agent,enum vFnUpdate vFnUpMethod);
	void vFnUpdateLast(int s, int a, int r, int s_, int a_, ADP &agent,enum vFnUpdate vFnUpMethod);

	location takeAction(int action_,location state_, WindyGridworld grid_, enum windType wind_);
	location takeAction(int action_, int state_, WindyGridworld grid_, enum windType wind_);
	location takeAction(int action_, int state_, WindyGridworld grid_, enum moveType type_, enum windType wind_);
	location takeAction(int action_,location state_, WindyGridworld grid_, enum moveType type_, enum windType wind_);
	location takeAction(int action_, int state_, CliffWalking grid_, enum moveType type_);

	void printAction(location currentState_);
	void printPolicy();
	void printState();
};

*/
