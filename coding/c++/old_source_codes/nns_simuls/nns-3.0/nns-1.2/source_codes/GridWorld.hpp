#ifndef  __GRIDWORLD_HPP_
#define  __GRIDWORLD_HPP_

#include  "Config.hpp"
#include  "Myiostream.hpp"
#include  "Location.hpp"

using namespace std;

//==============================================================================
//                              Type Definitions
//==============================================================================
typedef enum  { UP=0,DOWN,LEFT,RIGHT } move;

//==============================================================================
//                             Forward Declaration
//==============================================================================
//class      Config;

//==============================================================================
//                              Class Declaration
//==============================================================================

class      GridWorld : public Myiostream
{
public:
           GridWorld();
          ~GridWorld();

  static
  void     configure( Config& configObj );  // IMPORTANT! RUN THESE FUNCTIONS BEFORE THIS CLASS IS CONSTRUCTED!!!
  static
  bool     isWithinBoundary( Location currentLocation );

  void     initialize();
  void     show_position_();
  void     show_cliff_();
  bool     isCliff( Location currentLocation );
  bool     isCliff( int x, int y );
  bool     isDestination( Location currentLocation );
  bool     isDestination( int x, int y );
  bool     isSource( int x, int y );
  bool     set_position_( Location move );
  int      get_size_( int index ) const;
  Location get_startPosition_() const;
  int      get_numOfGrids_() const;

private:
  void     initialize_cliff_();
  void     set_cliff_( int cliffPattern );
  void     set_numOfGrids_( Location startPosition, Location endPosition );

  static
  int      size_[2];  // size_[0] for x; size_[1] for y
  static
  int      cliffPattern_;
  static
  Location startPosition_;
  static
  Location endPosition_;
  static
  Location position_;  // This is the current position.
  static
  int      numOfGrids_;

  bool**   cliff_;
  bool     is_cliff_set;
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================
// This is a 2-D grid world.
