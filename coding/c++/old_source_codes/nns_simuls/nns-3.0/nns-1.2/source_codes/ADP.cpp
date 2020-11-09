#include  "ADP.hpp"

ADP::ADP() {
	// Default is the stdMove
/*
	setReward(-1);
	setmaxNumActions(4);
	alpha = 0.1;
	gamma = 0.9;
	epsilon = 0.1;
*/
}
/*
ADP::ADP(enum moveType type_) {

	setReward(-1);
	alpha = 0.1;
	gamma = 0.9;
	epsilon = 0.1;

	if ( type_== stdMove ) {
		setmaxNumActions(4);
	} else if ( type_== KingsMove ) {
		setmaxNumActions(8);
	} else if ( type_== KingsMove_pause ) {
		setmaxNumActions(9);
	}
	
}

ADP::ADP(enum moveType type_, double alpha_, double gamma_, double epsilon_) {

	setReward(-1);

	setAlpha(alpha_);
	setgamma(gamma_);
	setepsilon(epsilon_);

	if ( type_== stdMove ) {
		setmaxNumActions(4);
	} else if ( type_== KingsMove ) {
		setmaxNumActions(8);
	} else if ( type_== KingsMove_pause ) {
		setmaxNumActions(9);
	}
	
}
*/

ADP::~ADP() {
	delete [] policy;
//	delete [][] Q;
}
/*
location ADP::stdMoves(int move_) {
	if ( move_ == 0 ) {			// up
		movement_.x = 0;
		movement_.y = 1;

	} else if ( move_ == 1) {	// right
		movement_.x = 1;
		movement_.y = 0;

	} else if ( move_ == 2) {	// down
		movement_.x = 0;
		movement_.y = -1;

	} else if ( move_ == 3) {	// left
		movement_.x = -1;
		movement_.y = 0;

	} else {
		cerr << "Error: location ADP::stdMoves(int move_)" <<endl;
		getch();
	}
	return movement_;
}

location ADP::kingsMoves(int move_) {
		   if ( move_ == 0 ) {	// up
		movement_.x = 0;
		movement_.y = 1;
	} else if ( move_ == 1 ) {	// upright
		movement_.x = 1;
		movement_.y = 1;
	} else if ( move_ == 2 ) {	// right
		movement_.x = 1;
		movement_.y = 0;
	} else if ( move_ == 3 ) {	// downright
		movement_.x = 1;
		movement_.y = -1;
	} else if ( move_ == 4 ) {	// down
		movement_.x = 0;
		movement_.y = -1;
	} else if ( move_ == 5 ) {	// downleft
		movement_.x = -1;
		movement_.y = -1;
	} else if ( move_ == 6 ) {	// left
		movement_.x = -1;
		movement_.y = 0;
	} else if ( move_ == 7 ) {	// upleft
		movement_.x = -1;
		movement_.y = 1;
	} else {
		cerr << "Error: location ADP::kingsMoves(int move_)" <<endl;
		getch();
	}
	return movement_;

}

location ADP::kingsMove_pause(int move_) {
		   if ( move_ == 0 ) {	// up
		movement_.x = 0;
		movement_.y = 1;
	} else if ( move_ == 1 ) {	// upright
		movement_.x = 1;
		movement_.y = 1;
	} else if ( move_ == 2 ) {	// right
		movement_.x = 1;
		movement_.y = 0;
	} else if ( move_ == 3 ) {	// downright
		movement_.x = 1;
		movement_.y = -1;
	} else if ( move_ == 4 ) {	// down
		movement_.x = 0;
		movement_.y = -1;
	} else if ( move_ == 5 ) {	// downleft
		movement_.x = -1;
		movement_.y = -1;
	} else if ( move_ == 6 ) {	// left
		movement_.x = -1;
		movement_.y = 0;
	} else if ( move_ == 7 ) {	// upleft
		movement_.x = -1;
		movement_.y = 1;
	} else if ( move_ == 8 ) {	// pause
		movement_.x = 0;
		movement_.y = 0;
	} else {
		cerr << "Error: location ADP::kingsMoves(int move_)" <<endl;
		getch();
	}
	return movement_;

}


void ADP::setState(location now_) {
	state = now_;
}

void ADP::setState(int state_) {
	state.x = X(state_,10); state.y = Y(state_,10);
}

void ADP::setmaxNumActions(int numActions_) {
	maxNumActions=numActions_;
}

location ADP::getState() {
	return state;
}

void ADP::printState() {
	cout<<"Current state is ("<<state.x<<", "<<state.y<<")"<<endl;
}

void ADP::initPolicy() {

	srand(time(NULL));
	if ( maxNumStates <= 0 ) {
		cerr<<"Error: void ADP::initPolicy(), maxNumStates not defined."<<endl;

	} else {
		policy =  new int [maxNumStates];
		// Initialize the policy randomly
		for ( int s=0;s<maxNumStates;s++) {
			policy[s]=eGreedy(Q,s);
		}
	}
}	// void ADP::initPolicy()

void ADP::printPolicy() {
	for ( int s=0;s<maxNumStates;s++) {
		cout<<"s: "<<s<<"\t";
		cout<<"p: "<<policy[s]<<endl;
	}
}


int ADP::chooseNextAction(int currentState_,enum vFnUpdate upMethod_, ADP &agent_) {

	int x_, y_;

	x_ = X(currentState_,10);
	y_ = Y(currentState_,10);

		   if ( upMethod_== SARSA ) {
		return agent_.eGreedy( agent_.Q, INDEX(x_,y_,10) );
//		return eGreedy( Q, INDEX(x_,y_,10) );
	} else if ( upMethod_ == Q_Learning ) {
		return agent_.greedy( agent_.Q, INDEX(x_,y_,10) );
//		return greedy( Q, INDEX(x_,y_,10) );
	} else {
		cerr<<"Error at int ADP::chooseNextAction(int currentState_,enum vFnUpdate upMethod_, ADP &agent_) "<<endl;
		getch();
		return 0;
	}
}




int ADP::chooseGreedyAction(int currentState_) {

	return greedy( Q, currentState_ );
}

int ADP::eGreedy(double ** Q_, int state_) {

	int action;

	srand(time(NULL));

	if ( ((double) rand()/ (double) RAND_MAX) < epsilon) {
		//action = (int) ( maxNumActions * ( (double) rand()/ (double) RAND_MAX ) );
		action = (int) maxNumActions *( (double) rand()/ (double) ( RAND_MAX+1) );

	} else {
		action=greedy( Q_, state_ );
	}

	return action;
}

int ADP::greedy(double ** Q_, int state_) {

	int action;

	action = searchMax(Q_[state_], maxNumActions);
	
	return action;
}

int ADP::searchMax(double *vector_, int maxNum_) {

	int maxCount_ (0);
	double max_ = vector_[0];
	
	for (int ii=1;ii<maxNum_;ii++) {
		if ( vector_[ii] > max_ ) {
			max_ = vector_[ii];
			maxCount_ = ii;
		}
	}
	return maxCount_;
}


void ADP::printAction(location currentState_) {
	cout<<"state: ("<<currentState_.x<<", "<<currentState_.y<<")"<<"-"<<INDEX(currentState_.x,currentState_.y,10) <<endl;
	cout<<"action: "<<policy[INDEX(currentState_.x,currentState_.y,10)]<<endl;
}

int ADP::isTerminal(location state_, WindyGridworld grid_) {
	return grid_.isDst(state_.x,state_.y);
}

int ADP::isTerminal(location state_, CliffWalking grid_) {
	return grid_.isDst(state_.x,state_.y);
}

location ADP::takeAction(int action_,location state_, WindyGridworld grid_, enum windType wind_) {

	state_=stdMoves(action_);

	return grid_.changeMyLocation(state_, wind_);
}

location ADP::takeAction(int action_, int state_, WindyGridworld grid_, enum windType wind_) {

	catesian x_, y_;

	x_ = X(state_,10);
	y_ = Y(state_,10);

	x_ += stdMoves(action_).x;
	y_ += stdMoves(action_).y;

	return grid_.wind(x_,y_, wind_);
}

location ADP::takeAction(int action_, int state_, WindyGridworld grid_, enum moveType type_, enum windType wind_) {

	catesian x_, y_;
	location state1_;

	x_ = X(state_,10);
	y_ = Y(state_,10);

	state1_=grid_.wind(x_,y_,wind_);
	
	if ( type_ == stdMove ) {
		state1_.x += stdMoves(action_).x;
		state1_.y += stdMoves(action_).y;
	} else if ( type_ == KingsMove ) {
		state1_.x += kingsMoves(action_).x;
		state1_.y += kingsMoves(action_).y;
	} else if ( type_ == KingsMove_pause ) {
		state1_.x += kingsMove_pause(action_).x;
		state1_.y += kingsMove_pause(action_).y;
	} else {
		cerr<<"Error:location ADP::takeAction(int action_, int state_, WindyGridworld grid_, enum moveType type_)"<<endl;
		getch();
	}
	return grid_.checkBoundary(state1_);
}

location ADP::takeAction(int action_,location state_, WindyGridworld grid_, enum moveType type_, enum windType wind_) {


	state_=grid_.wind(state_.x,state_.y,wind_);
	
	if ( type_ == stdMove ) {
		state_.x += stdMoves(action_).x;
		state_.y += stdMoves(action_).y;
	} else if ( type_ == KingsMove ) {
		state_.x += kingsMoves(action_).x;
		state_.y += kingsMoves(action_).y;
	} else if ( type_ == KingsMove_pause ) {
		state_.x += kingsMove_pause(action_).x;
		state_.y += kingsMove_pause(action_).y;
	} else {
		cerr<<"Error:location ADP::takeAction(int action_,location state_, WindyGridworld grid_, enum moveType type_)"<<endl;
		getch();
	}

	return state_;
}

location ADP::takeAction(int action_, int state_, CliffWalking grid_, enum moveType type_) {

	catesian x_, y_;
	location state1_;

	state1_.x = X(state_,12);
	state1_.y = Y(state_,12);

	if ( type_ == stdMove ) {
		state1_.x += stdMoves(action_).x;
		state1_.y += stdMoves(action_).y;
	} else if ( type_ == KingsMove ) {
		state1_.x += kingsMoves(action_).x;
		state1_.y += kingsMoves(action_).y;
	} else if ( type_ == KingsMove_pause ) {
		state1_.x += kingsMove_pause(action_).x;
		state1_.y += kingsMove_pause(action_).y;
	} else {
		cerr<<"Error:location ADP::takeAction(int action_, int state_, WindyGridworld grid_, enum moveType type_)"<<endl;
		getch();
	}
	return grid_.checkBoundary(state1_);
}


void ADP::setPolicy() {

	for (int s=0; s<maxNumStates; s++ ) {
		policy[s]=chooseAction(s);
	}

}

void ADP::setFinalPolicy() {
	for (int s=0; s<maxNumStates; s++ ) {
		policy[s]=chooseGreedyAction(s);
	}

}

void ADP::sarsa(int s, int a, int r, int s_, int a_, ADP &agent) {
// s,a,r,s_,a_, all in decimal
// s_ and a_ are state and action at the next epoch
	agent.Q[s][a] = agent.Q[s][a]+ alpha*(r+gamma*agent.Q[s_][a_] - agent.Q[s][a]);
}

void ADP::QLearning(int s, int a, int r, int s_, int a_, ADP &agent) {
// s,a,r,s_,a_, all in decimal
// s_ and a_ are state and action at the next epoch
// The difference from SARSA is that the next action is the greedy action.
	a_ = greedy(Q, s_);
	agent.Q[s][a] = agent.Q[s][a]+ alpha*(r+gamma*agent.Q[s_][a_] - agent.Q[s][a]);

}

void ADP::vFnUpdate(int s, int a, int r, int s_, int a_, ADP &agent,enum vFnUpdate vFnUpMethod) {

	if ( vFnUpMethod == SARSA ) {
		sarsa(s, a, r, s_, a_, agent);
	} else if ( vFnUpMethod == Q_Learning ) {
		QLearning(s, a, r, s_, a_, agent);
	}
}

void ADP::vFnUpdate(int s, int a, int r, int s_, int a_, ADP &agent,enum vFnUpdate vFnUpMethod) {


	agent.Q[s][a] = agent.Q[s][a]+ alpha*r;
	if ( vFnUpMethod == SARSA ) {
		sarsa(s, a, r, s_, a_, agent);
	} else if ( vFnUpMethod == Q_Learning ) {
		QLearning(s, a, r, s_, a_, agent);
	}


}
*/
