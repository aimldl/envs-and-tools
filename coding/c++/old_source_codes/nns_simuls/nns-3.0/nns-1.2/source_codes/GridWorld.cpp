#include  "GridWorld.hpp"

//==============================================================================
//                            Static Variables
//==============================================================================

int
GridWorld::size_[2];

int
GridWorld::cliffPattern_;

Location
GridWorld::startPosition_;

Location
GridWorld::endPosition_;

Location
GridWorld::position_;

int
GridWorld::numOfGrids_;

//==============================================================================
//                        Static Public functions
//==============================================================================
// IMPORTANT! RUN THESE FUNCTIONS BEFORE THIS CLASS IS CONSTRUCTED!!!
void
GridWorld::configure( Config& configObj )
{
  size_[0]           = configObj.get_rlObj_().get_gridWorldSizeX_();
  size_[1]           = configObj.get_rlObj_().get_gridWorldSizeY_();

  startPosition_.x   = configObj.get_rlObj_().get_gridWorldStartPositionX_();
  startPosition_.y   = configObj.get_rlObj_().get_gridWorldStartPositionY_();

  endPosition_.x     = configObj.get_rlObj_().get_gridWorldEndPositionX_();
  endPosition_.y     = configObj.get_rlObj_().get_gridWorldEndPositionY_();

  cliffPattern_      = configObj.get_rlObj_().get_gridWorldCliffPattern_();

  // startPosition_ & endPosition_ should be within the boundary of the grid world.
  assert( isWithinBoundary( startPosition_ ) );
  assert( isWithinBoundary( endPosition_ ) );

  position_ = startPosition_;
}

bool
GridWorld::isWithinBoundary( Location currentLocation )
{
  assert( (size_[0] > 0 ) );
  assert( (size_[1] > 0 ) );

  int x = currentLocation.x;
  int y = currentLocation.y;

  if ( x < 0 || x >= size_[0] )
    return false;

  if ( y < 0 || y >= size_[1] )
    return false;

  return true;
}

//==============================================================================
//                        Static Private functions
//==============================================================================
//==============================================================================
//                            Public functions
//==============================================================================

GridWorld::GridWorld()
{
  is_cliff_set = false;
}

GridWorld::~GridWorld()
{
}

void
GridWorld::set_numOfGrids_( Location startPosition, Location endPosition )
{
  numOfGrids_ = size_[0] * size_[1];  // gridWorldSizeX_ * gridWorldSizeY_

  assert( numOfGrids_ > 0 ); // numOfGrids_ shall not be 1.
}

void
GridWorld::initialize()
{
  set_numOfGrids_( startPosition_, endPosition_ );
  initialize_cliff_();
}

void
GridWorld::show_position_()
{
  position_.show();
}

bool
GridWorld::set_position_( Location move )
{
  position_ += move;
  position_.show();

  return isWithinBoundary( position_ );
}

int
GridWorld::get_size_( int index ) const
{
  assert( index == 0 || index == 1 );

  return size_[ index ];
}

int
GridWorld::get_numOfGrids_() const
{
  return numOfGrids_;
}

Location
GridWorld::get_startPosition_() const
{
  return startPosition_;
}


bool
GridWorld::isCliff( Location currentLocation )
{
  assert( is_cliff_set );
  if ( isWithinBoundary( currentLocation ) )
    return cliff_[currentLocation.x][currentLocation.y];
  else
	return false;
}

bool
GridWorld::isCliff( int x, int y )
{
  assert ( is_cliff_set );

  return cliff_[x][y];
}

bool
GridWorld::isDestination( Location currentLocation )
{
  return (currentLocation == endPosition_);  // Two locations identical?
}

bool
GridWorld::isDestination( int x, int y )
{
  if ( ( x == endPosition_.x ) && ( y == endPosition_.y ) )
    return true;
  else
    return false;
}

bool
GridWorld::isSource( int x, int y )
{
  if ( ( x == startPosition_.x ) && ( y == startPosition_.y ) )
    return true;
  else
    return false;
}

//==============================================================================
//                            Protected functions
//==============================================================================
//==============================================================================
//                            Private functions
//==============================================================================

void
GridWorld::initialize_cliff_()
{
  assert( (size_[0]>0) && (size_[1]>0) );

  cliff_ = new bool* [size_[0]];
  for ( int x = 0; x < size_[0]; x++ )
    cliff_[x] = new bool [size_[1]];

  set_cliff_( cliffPattern_ );
}

void
GridWorld::set_cliff_( int cliffPattern )
{
  assert( cliffPattern_ >= 0 );

  for ( int x = 0; x < size_[0]; x++ )
    for ( int y = 0; y < size_[1]; y++ )
      cliff_[x][y] = false;

  if ( cliffPattern == 0 )  // No cliff
  {
    tout << "There is no cliff in the grid world." << endl;
  }
  else if ( cliffPattern == 1 )  // Straight line from the source node
  {
    for ( int x = startPosition_.x+1; x < endPosition_.x; x++ )
      cliff_[x][startPosition_.y] = true;
  }
  else
  {
    cerr << "cliffPattern=" << cliffPattern << " has not been implemented yet." << endl;
    exit(1);
  }
  is_cliff_set =  true;
}

void
GridWorld::show_cliff_()
{
  assert( (size_[0]>0) && (size_[1]>0) );
  assert ( is_cliff_set );

  tout << "void GridWorld::show_cliff_()" << endl;
  for ( int y = size_[1]-1; y >= 0 ; y-- )
  {
    for ( int x = 0; x < size_[0]; x++ )
      cout << cliff_[x][y] << " ";
    cout << endl;
  }
}
