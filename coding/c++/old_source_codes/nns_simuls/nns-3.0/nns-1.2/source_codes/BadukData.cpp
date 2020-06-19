#include  "BadukData.hpp"

string		BadukData::player_;
int			BadukData::lengthOfABatchOfData_;
string		BadukData::dataType_;
int			BadukData::boardSizeX_;
int			BadukData::boardSizeY_;
int			BadukData::totalNumOfTargetData_;
bool        BadukData::isConfigured_;

//==============================================================================
//                        Static Public functions
//==============================================================================

// IMPORTANT! RUN THIS FUNCTION BEFORE THIS CLASS IS CONSTRUCTED!!!
void		BadukData::configure( Config& configObj )
{
  assert( configObj.get_isConfigured_() );

  player_ 		= configObj.get_simulationsObj_().get_player_();
  boardSizeX_   = configObj.get_simulationsObj_().get_boardSize_();
  boardSizeY_   = configObj.get_simulationsObj_().get_boardSize_();
  dataType_     = configObj.get_dataObj_().get_dataType_();
  if ( dataType_ == "board_status_sequences" )
  {
    if ( boardSizeX_ == 2 )
    {
      // Optimal moves by black or white
      if ( player_ == "black" )      lengthOfABatchOfData_ = 8;
      else if ( player_ == "white" ) lengthOfABatchOfData_ = 12;
    }
    else if ( boardSizeX_ == 3 )
    {
      // Optimal moves by black or white
      if ( player_ == "black" )      lengthOfABatchOfData_ = -1;
      else if ( player_ == "white" ) lengthOfABatchOfData_ = -1;
    }
  }
  else if ( dataType_ == "single_valued_function" )
  {
    if ( boardSizeX_ == 2 )
      lengthOfABatchOfData_ = 7;
    else if ( boardSizeX_ == 3 )
      lengthOfABatchOfData_ = -1;
  }
  else if ( dataType_ == "multi_valued_function" )
  {
    if ( boardSizeX_ == 2 )
      lengthOfABatchOfData_ = 16;
    else if ( boardSizeX_ == 3 )
      lengthOfABatchOfData_ = -1;
  }
  totalNumOfTargetData_ = boardSizeX_ * boardSizeY_ * lengthOfABatchOfData_;

  isConfigured_ = true;
  assert( (totalNumOfTargetData_ > 0) );
}

int			BadukData::get_boardSizeX_()
{
  return boardSizeX_;
}

int			BadukData::get_boardSizeY_()
{
  return boardSizeY_;
}

int			BadukData::get_lengthOfABatchOfData_()
{
  return lengthOfABatchOfData_;
}

int			BadukData::get_totalNumOfTargetData_()
{
  return totalNumOfTargetData_;
}

bool     	BadukData::get_isConfigured_()
{
  return isConfigured_;
}

// IMPORTANT! RUN THIS FUNCTION BEFORE THIS CLASS IS CONSTRUCTED!!!

//==============================================================================
//                            Public functions
//==============================================================================


BadukData::BadukData()
{
  assert( isConfigured_ );
  initialize();
}

BadukData::~BadukData()
{
  destroy_aPrioriBoard_( boardSizeX_, boardSizeY_, lengthOfABatchOfData_ );
  destroy_aPosterioriBoard_( boardSizeX_, boardSizeY_, lengthOfABatchOfData_);
}

// Design issue: I don't need to take boardSizeX_, boardSizeY_, lengthOfABatchOfData_
//   as the input arguments to the functions constructData and createData along with
//   the sub-functions of them because these variables are the protected variables
//   of the base class of BadukData or class BadukData.
//     However it is more intuitive to read the code, so I'll just put the input arguments
//   to the functions.
void
BadukData::initialize()
{
  // Either boardSizeX_ or boardSizeY_ shouldn't be zero.
  // Variables boardSizeX_, boardSizeY_, lengthOfABatchOfData_ should be configured in class BadukData
  // before this function is called. Refer to BadukData::configure(...).
  assert
  (
    ( boardSizeX_ > 0 ) && ( boardSizeY_ > 0 ) && ( lengthOfABatchOfData_ > 0 )
  );

  int numOfConstructedData;

  constructData( boardSizeX_, boardSizeY_, lengthOfABatchOfData_ );
  numOfConstructedData = createData( boardSizeX_, boardSizeY_, lengthOfABatchOfData_ );
  logCreatedData( boardSizeX_, boardSizeY_, lengthOfABatchOfData_ );

  isInitialized_ = true;
}
bool
BadukData::get_isInitialized_()
{
  return isInitialized_;
}

int***
BadukData::get_aPrioriBoard_()
{
  return aPrioriBoard_;
}

int***
BadukData::get_aPosterioriBoard_()
{
  return aPosterioriBoard_;
}

//==============================================================================
//                            Protected functions
//==============================================================================
// Private is enough, but set these functions as protected for future usage.

// Create two sets of board settings just to test the NeuralNets.
// Assume 6x6
void
BadukData::createTestInputData()
{
  int l;
  for ( l = 0; l < lengthOfABatchOfData_; l++ )
  {  
    initializeTestInputData( l );
  }
}

void
BadukData::initializeTestInputData( int l )
{
  for ( int x = 0; x < boardSizeX_; x++ )
  {
    for ( int y = 0; y < boardSizeY_; y++ )
    {
      aPrioriBoard_[ x ][ y ][ l ] = 0;
    }
  }
  is_aPrioriBoard_initialized_ = true;
}


// Create two sets of board settings just to test the NeuralNets.
void
BadukData::createTestTargetData()
{
  int l;
  for ( l = 0; l < lengthOfABatchOfData_; l++ )
  {  
    initializeTestTargetData( l );
  }
}

void
BadukData::initializeTestTargetData( int l )
{
  for ( int x = 0; x < boardSizeX_; x++ )
  {
    for ( int y = 0; y < boardSizeY_; y++ )
    {
      aPosterioriBoard_[ x ][ y ][ l ] = 0;
    }
  }
  is_aPosterioriBoard_initialized_ = true;
}

//==============================================================================
//                            Private functions
//==============================================================================

void
BadukData::constructData( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData )
{
  assert
  (
    ( boardSizeX > 0 ) && ( boardSizeY > 0 ) && ( lengthOfABatchOfData > 0 )
  );
  // What are aPrioriBoard_ and aPosterioriBoard_? I forgot...
  construct_aPrioriBoard_( boardSizeX, boardSizeY, lengthOfABatchOfData );
  construct_aPosterioriBoard_( boardSizeX, boardSizeY, lengthOfABatchOfData );
}

void
BadukData::construct_aPrioriBoard_( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData )
{
  // Either boardSizeX or boardSizeY shouldn't be zero.
  assert(
          ( boardSizeX > 0 ) && ( boardSizeY > 0 ) && ( lengthOfABatchOfData > 0 )
        );
  // Why a dynamic array, not a vector? Woops, I forgot the reason. :P
  // aPrioriBoard_[ boardSizeX ][ boardSizeY ][ lengthOfABatchOfData ]
  aPrioriBoard_ = new int **[ boardSizeX ];
  for ( int i = 0; i < boardSizeX; i++ )
  {
    aPrioriBoard_[ i ] = new int*[ boardSizeY ];
    for ( int j = 0; j < boardSizeY; j++ )
    {
      aPrioriBoard_[ i ][ j ] = new int[ lengthOfABatchOfData ];
    }
  }
}

// This function works both for scalar and vector inputs.
// The only difference in practice is scalar input has boardSizeX=1.

void
BadukData::construct_aPosterioriBoard_( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData )
{
  // Either boardSizeX or boardSizeY shouldn't be zero.
  assert(
          ( boardSizeX > 0 ) && ( boardSizeY > 0 ) && ( lengthOfABatchOfData > 0 )
        );

  // aPosterioriBoard_[ boardSizeX ][ boardSizeY ][ lengthOfABatchOfData ]
  aPosterioriBoard_ = new int **[ boardSizeX ];
  for ( int i = 0; i < boardSizeX; i++ )
  {
    aPosterioriBoard_[ i ] = new int*[ boardSizeY ];
    for ( int j = 0; j < boardSizeY; j++ )
    {
      aPosterioriBoard_[ i ][ j ] = new int[ lengthOfABatchOfData ];
    }
  }
}

double
BadukData::createData( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData )
{
  assert
  (
    ( boardSizeX > 0 ) && ( boardSizeY > 0 ) && ( lengthOfABatchOfData > 0 )
  );

  int numOfConstructedData;

  initializeBoards( boardSizeX, boardSizeY, lengthOfABatchOfData );  // Set both aPrioriBoard_ & aPosterioriBoard_ to zero.

  // An input to NeuralNets is a vector for CSRN because of the feedback term from the neighboring nodes.
  if ( boardSizeX == 2 )  // Use 2x2 networks for a cell
  {
    if ( dataType_ == "board_status_sequences" )
    {
      if ( player_ == "black" )
    	numOfConstructedData = setData_brd_status_seqs_2x2_optimal_black( boardSizeX, boardSizeY, lengthOfABatchOfData );
      else if ( player_ == "white" )
    	numOfConstructedData = setData_brd_status_seqs_2x2_optimal_white( boardSizeX, boardSizeY, lengthOfABatchOfData );
    }
    else if ( dataType_ == "single_valued_function" )
      numOfConstructedData = setData_2x2_single_valued_fn( boardSizeX, boardSizeY, lengthOfABatchOfData );
    else if ( dataType_ == "multi_valued_function" )
      numOfConstructedData = setData_2x2_multi_valued_fn( boardSizeX, boardSizeY, lengthOfABatchOfData );
  }
  else if ( boardSizeX == 3 )  // Use 3x3 networks for a cell
  {
    numOfConstructedData = setData_3x3( boardSizeX, boardSizeY, lengthOfABatchOfData );  // This is not completed.
  }
  assert( !( lengthOfABatchOfData - numOfConstructedData ) );  // lengthOfABatchOfData should be equal to numOfConstructedData.

  return numOfConstructedData;
}

// Initialize both aPrioriBoard_ & aPosterioriBoard_ to zero. The board size doesn't matter.

void
BadukData::initializeBoards( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData )
{
  assert
  (
    ( boardSizeX > 0 ) && ( boardSizeY > 0 ) && ( lengthOfABatchOfData > 0 )
  );

  int initialValue;
  
  initialValue = 0;
  for ( int x = 0; x < boardSizeX; x++ )
  {
    for ( int y = 0; y < boardSizeY; y++ )
    {
      for ( int l = 0; l < lengthOfABatchOfData; l++ )
      {
        aPrioriBoard_[ x ][ y ][ l ]  = initialValue;
        aPosterioriBoard_[ x ][ y ][ l ] = initialValue;
      }
    }
  }
  is_aPrioriBoard_initialized_  = true;
  is_aPosterioriBoard_initialized_ = true;
}

// Set data only 1. Use a masking for -1.
// The following implementation isn't the smartest, but it doesn't really
// matter because the 2x2 data set is used for the testing purposes.
double
BadukData::setData_2x2_single_valued_fn( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData )
{
  assert( !( is_aPrioriBoard_initialized_ && is_aPosterioriBoard_initialized_) );
  assert
  (
    ( boardSizeX > 0 ) && ( boardSizeY > 0 ) && ( lengthOfABatchOfData > 0 )
  );

  // Use dummy variables to avoid mistakes.
  int x, y, l;
  int stringSize, mark;
  int numOfConstructedData;

  mark = 1;                            // Set data only 1. Use a masking for -1.
  l = 0;

  ///////////////
  stringSize = 0;
  for ( x = 0; x < boardSizeX; x++ )
  {
    for ( y = 0; y < boardSizeY; y++ )
    {
      aPrioriBoard_[ x ][ y ][ l ]  = 0;
      aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
    }
  }
  l++;
  ///////////////
  stringSize = 1;
  for ( x = 0; x < boardSizeX; x++ )
  {
    for ( y = 0; y < boardSizeY; y++ )
    {
      aPrioriBoard_[ x ][ y ][ l ]  = mark;
      aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
      l++;
    }
  }
  ///////////////
  x = 0; y = 0;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  x = 1; y = 1;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  l++;

  x = 0; y = 1;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  x = 1; y = 0;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  l++;
  
  numOfConstructedData = l;
  return numOfConstructedData;
}

// Set data only 1. Use a masking for -1.
// The following implementation isn't the smartest, but it doesn't really
// matter because the 2x2 data set is used for the testing purposes.
double
BadukData::setData_2x2_multi_valued_fn( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData )
{
  assert( (is_aPrioriBoard_initialized_ && is_aPosterioriBoard_initialized_) );
  assert
  (
    ( boardSizeX > 0 ) && ( boardSizeY > 0 ) && ( lengthOfABatchOfData > 0 )
  );

  // Use dummy variables to avoid mistakes.
  int x, y, l;
  int stringSize, mark;
  int numOfConstructedData;

  mark = 1;                            // Set data only 1. Use a masking for -1.
  l = 0;

  ///////////////
  stringSize = 0;
  for ( x = 0; x < boardSizeX; x++ )
  {
    for ( y = 0; y < boardSizeY; y++ )
    {
      aPrioriBoard_[ x ][ y ][ l ]  = 0;
      aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
    }
  }
  l++;
  ///////////////
  stringSize = 1;
  for ( x = 0; x < boardSizeX; x++ )
  {
    for ( y = 0; y < boardSizeY; y++ )
    {
      aPrioriBoard_[ x ][ y ][ l ]  = mark;
      aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
      l++;
    }
  }
  ///////////////
  x = 0; y = 0;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  x = 1; y = 1;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  l++;

  x = 0; y = 1;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  x = 1; y = 0;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  l++;
  ///////////////
  stringSize = 2;

  x = 0; y = 0;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  x = 0; y = 1;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  l++;

  x = 0; y = 1;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  x = 1; y = 1;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  l++;

  x = 1; y = 1;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  x = 1; y = 0;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  l++;

  x = 0; y = 0;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  x = 1; y = 0;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  l++;  
  ///////////////
  stringSize = 3;

  x = 0; y = 0;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  x = 1; y = 0;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  x = 0; y = 1;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  l++;

  x = 1; y = 0;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  x = 0; y = 1;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  x = 1; y = 1;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  l++;

  x = 0; y = 0;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  x = 1; y = 0;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  x = 1; y = 1;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  l++;

  x = 0; y = 0;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  x = 0; y = 1;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  x = 1; y = 1;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  l++;
  ///////////////
  stringSize = 4;

  x = 0; y = 0;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  x = 0; y = 1;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  x = 1; y = 0;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  x = 1; y = 1;
  aPrioriBoard_[ x ][ y ][ l ]  = mark;
  aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
  l++;
  
  numOfConstructedData = l;
  return numOfConstructedData;
}

// TODO:
// Change the input and target data to a linked list eventually.
// Proceed without changing the data structure for the moment.
//
// The following is an arbitrary number assigned to a board status.
// I don't know what number assignments are optimal.
// Empty: 0, Black: 1, White: 2
//
//
// The cell index is a decimal converted "xy" in binary.
//     ________
//   1 | 1 | 3 |
// y   |-------|
//   0 | 0 | 2 |
//     ---------
//       0   1
//         x

double
BadukData::setData_brd_status_seqs_2x2_optimal_black( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData )
{
  assert( (is_aPrioriBoard_initialized_ && is_aPosterioriBoard_initialized_) );
  assert
  (
    ( boardSizeX > 0 ) && ( boardSizeY > 0 ) && ( lengthOfABatchOfData > 0 )
  );

  int index;
  int numOfConstructedData;

  index = 0;
  aPosterioriBoard_[ 0 ][ 0 ][ index ] = 1;

  index++;
  aPrioriBoard_[ 0 ][ 0 ][ index ]  = 1;
  aPosterioriBoard_[ 0 ][ 0 ][ index ] = 1;
  aPosterioriBoard_[ 1 ][ 1 ][ index ] = 1;

  index++;
  aPrioriBoard_[ 0 ][ 0 ][ index ]  = 1;
  aPrioriBoard_[ 0 ][ 1 ][ index ]  = 2;
  aPosterioriBoard_[ 0 ][ 0 ][ index ] = 1;
  aPosterioriBoard_[ 1 ][ 1 ][ index ] = 1;

  index++;
  aPrioriBoard_[ 0 ][ 0 ][ index ]  = 1;
  aPrioriBoard_[ 1 ][ 0 ][ index ]  = 2;
  aPosterioriBoard_[ 0 ][ 0 ][ index ] = 1;
  aPosterioriBoard_[ 1 ][ 1 ][ index ] = 1;

  index++;
  aPrioriBoard_[ 0 ][ 0 ][ index ]  = 1;
  aPrioriBoard_[ 1 ][ 1 ][ index ]  = 1;
  aPosterioriBoard_[ 0 ][ 0 ][ index ] = 1;
  aPosterioriBoard_[ 1 ][ 1 ][ index ] = 1;

  index++;
  aPrioriBoard_[ 0 ][ 0 ][ index ]  = 1;
  aPrioriBoard_[ 0 ][ 1 ][ index ]  = 2;
  aPrioriBoard_[ 1 ][ 1 ][ index ]  = 2;
  aPosterioriBoard_[ 0 ][ 0 ][ index ]  = 1;
  aPosterioriBoard_[ 0 ][ 1 ][ index ]  = 2;
  aPosterioriBoard_[ 1 ][ 1 ][ index ]  = 2;

  index++;
  aPrioriBoard_[ 0 ][ 0 ][ index ]  = 1;
  aPrioriBoard_[ 1 ][ 0 ][ index ]  = 2;
  aPrioriBoard_[ 1 ][ 1 ][ index ]  = 2;
  aPosterioriBoard_[ 0 ][ 0 ][ index ]  = 1;
  aPosterioriBoard_[ 1 ][ 0 ][ index ]  = 2;
  aPosterioriBoard_[ 1 ][ 1 ][ index ]  = 2;

  index++;
  aPrioriBoard_[ 0 ][ 1 ][ index ]  = 2;
  aPrioriBoard_[ 1 ][ 0 ][ index ]  = 2;
  aPrioriBoard_[ 1 ][ 1 ][ index ]  = 2;
  aPosterioriBoard_[ 0 ][ 1 ][ index ]  = 2;
  aPosterioriBoard_[ 1 ][ 0 ][ index ]  = 2;
  aPosterioriBoard_[ 1 ][ 1 ][ index ]  = 2;

  // index starts from 0, so 1 needs to be added for numOfConstructedData_
  index++;

  numOfConstructedData = index;
  return numOfConstructedData;
}

double
BadukData::setData_brd_status_seqs_2x2_optimal_white( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData )
{
  assert( (is_aPrioriBoard_initialized_ && is_aPosterioriBoard_initialized_) );
  assert
  (
    ( boardSizeX > 0 ) && ( boardSizeY > 0 ) && ( lengthOfABatchOfData > 0 )
  );

  int index;
  int numOfConstructedData;

  index = 0;
  aPosterioriBoard_[ 0 ][ 0 ][ index ] = 2;

  index++;
  aPrioriBoard_[ 0 ][ 0 ][ index ]  = 1;
  aPosterioriBoard_[ 0 ][ 0 ][ index ] = 1;
  aPosterioriBoard_[ 1 ][ 1 ][ index ] = 2;

  index++;
  aPrioriBoard_[ 0 ][ 0 ][ index ] = 1;
  aPrioriBoard_[ 1 ][ 1 ][ index ] = 2;
  aPosterioriBoard_[ 0 ][ 0 ][ index ] = 1;
  aPosterioriBoard_[ 1 ][ 1 ][ index ] = 2;

  index++;
  aPrioriBoard_[ 0 ][ 0 ][ index ]  = 2;
  aPrioriBoard_[ 0 ][ 1 ][ index ]  = 1;
  aPosterioriBoard_[ 0 ][ 0 ][ index ]  = 2;
  aPosterioriBoard_[ 1 ][ 1 ][ index ] = 2;

  index++;
  aPrioriBoard_[ 0 ][ 0 ][ index ]  = 2;
  aPrioriBoard_[ 1 ][ 0 ][ index ]  = 1;
  aPosterioriBoard_[ 0 ][ 0 ][ index ]  = 2;
  aPosterioriBoard_[ 1 ][ 1 ][ index ] = 2;

  index++;
  aPrioriBoard_[ 0 ][ 0 ][ index ]  = 2;
  aPrioriBoard_[ 1 ][ 1 ][ index ] = 2;
  aPosterioriBoard_[ 0 ][ 0 ][ index ]  = 2;
  aPosterioriBoard_[ 1 ][ 1 ][ index ] = 2;

  index++;
  aPrioriBoard_[ 0 ][ 0 ][ index ] = 1;
  aPrioriBoard_[ 0 ][ 1 ][ index ] = 1;
  aPrioriBoard_[ 1 ][ 1 ][ index ] = 2;
  aPosterioriBoard_[ 0 ][ 0 ][ index ] = 1;
  aPosterioriBoard_[ 0 ][ 1 ][ index ] = 1;
  aPosterioriBoard_[ 1 ][ 1 ][ index ] = 2;

  index++;
  aPrioriBoard_[ 0 ][ 0 ][ index ] = 1;
  aPrioriBoard_[ 1 ][ 0 ][ index ] = 1;
  aPrioriBoard_[ 1 ][ 1 ][ index ] = 2;
  aPosterioriBoard_[ 0 ][ 0 ][ index ] = 1;
  aPosterioriBoard_[ 1 ][ 0 ][ index ] = 1;
  aPosterioriBoard_[ 1 ][ 1 ][ index ] = 2;

  index++;
  aPrioriBoard_[ 0 ][ 0 ][ index ] = 1;
  aPrioriBoard_[ 0 ][ 1 ][ index ] = 1;
  aPrioriBoard_[ 1 ][ 0 ][ index ] = 1;
  aPosterioriBoard_[ 0 ][ 0 ][ index ] = 1;
  aPosterioriBoard_[ 0 ][ 1 ][ index ] = 1;
  aPosterioriBoard_[ 1 ][ 0 ][ index ] = 1;

  index++;
  aPrioriBoard_[ 0 ][ 0 ][ index ] = 2;
  aPrioriBoard_[ 0 ][ 1 ][ index ] = 1;
  aPrioriBoard_[ 1 ][ 1 ][ index ] = 1;
  aPosterioriBoard_[ 0 ][ 0 ][ index ] = 2;
  aPosterioriBoard_[ 0 ][ 1 ][ index ] = 1;
  aPosterioriBoard_[ 1 ][ 1 ][ index ] = 1;

  index++;
  aPrioriBoard_[ 0 ][ 0 ][ index ] = 2;
  aPrioriBoard_[ 1 ][ 0 ][ index ] = 1;
  aPrioriBoard_[ 1 ][ 1 ][ index ] = 1;
  aPosterioriBoard_[ 0 ][ 0 ][ index ] = 2;
  aPosterioriBoard_[ 1 ][ 0 ][ index ] = 1;
  aPosterioriBoard_[ 1 ][ 1 ][ index ] = 1;

  index++;
  aPrioriBoard_[ 0 ][ 1 ][ index ] = 1;
  aPrioriBoard_[ 1 ][ 0 ][ index ] = 1;
  aPrioriBoard_[ 1 ][ 1 ][ index ] = 1;
  aPosterioriBoard_[ 0 ][ 1 ][ index ] = 1;
  aPosterioriBoard_[ 1 ][ 0 ][ index ] = 1;
  aPosterioriBoard_[ 1 ][ 1 ][ index ] = 1;

  // index starts from 0, so 1 needs to be added for numOfConstructedData_
  index++;

  numOfConstructedData = index;
  return numOfConstructedData;
}

////////////////////////////////////////////////////////////////////////////////

// Set data only 1. Use a masking for -1.
double
BadukData::setData_3x3( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData )
{
  assert
  (
    ( boardSizeX > 0 ) && ( boardSizeY > 0 ) && ( lengthOfABatchOfData > 0 )
  );
  // Use dummy variables to avoid mistakes.
  int x, y, l;
  int stringSize, mark;
  int numOfConstructedData;

  mark = 1;                            // Set data only 1. Use a masking for -1.

  /////////////////////////
  //   stringSize = 1;   //
  /////////////////////////
  stringSize = 1;
  l = 0;
  for ( x = 0; x < boardSizeX; x++ )
  {
    for ( y = 0; y < boardSizeY; y++ )
    {
      aPrioriBoard_[ x ][ y ][ l ]  = mark;
      aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
      l++;
    }
  }
  /////////////////////////
  //   stringSize = 2;   //
  /////////////////////////
  stringSize = 1;
  l = 0;
  for ( x = 0; x < boardSizeX; x++ )
  {
    for ( y = 0; y < boardSizeY; y++ )
    {
      aPrioriBoard_[ x ][ y ][ l ]  = mark;
      aPosterioriBoard_[ x ][ y ][ l ] = stringSize;
      l++;
    }
  }

  // TODO: This is just to avoid the assert error.
  //       Correct this when I actually work on othe 3x3 data.
  numOfConstructedData = lengthOfABatchOfData;
  return numOfConstructedData;
}

void
BadukData::logCreatedData( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData )
{
  assert
  (
    ( boardSizeX > 0 ) && ( boardSizeY > 0 ) && ( lengthOfABatchOfData > 0 )
  );
  // Note numOfConstructedData sould be equal to lengthOfABatchOfData by now.

  if ( boardSizeX == 2 )  // Use 2x2 networks for a cell
  {
    logCreatedData_2x2( boardSizeX, boardSizeY, lengthOfABatchOfData );
  }
  else if ( boardSizeX == 3 )  // Use 3x3 networks for a cell
  {
    // Under construction
  }
}

// Display the coordinate of board status for convenience in the trace file.
// Show the output in the order of, e.g. 2x2
//    1 [1,0] [1,1]
//  y
//    0 [0,0] [1,0]
//        0     1
//           x

void
BadukData::logCreatedData_2x2( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData )
{

  tout << "void BadukData::logCreatedData_2x2( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData )" << endl;

  assert( ( boardSizeX > 0 ) && ( boardSizeY > 0 ) && ( lengthOfABatchOfData > 0 ) );

  tout << "  Cell Locations [x,y]\n";
  for ( int y = boardSizeY-1; y >=0 ; y-- )
  {
	tout << "    y=" << y << " ";
    for ( int x = 0; x < boardSizeX_; x++ )
      tout << "["<< x <<","<< y << "]";
    tout << endl;
  }
  tout << "       ";
  for ( int x = 0; x < boardSizeX_; x++ )
    tout << "  x=" << x;
  tout << endl;

  // lengthOfABatchOfData should be equal to numOfConstructedData.
  tout << "  inputData\n";
  for ( int y = boardSizeY-1; y >=0 ; y-- )
  {
	tout << "    ";
	for ( int d = 0; d < lengthOfABatchOfData; d++ )
    {
      for ( int x = 0; x < boardSizeX_; x++ )
      {
        tout << aPrioriBoard_[ x ][ y ][ d ] << " ";
      }
      tout << " ";
    }
    tout << endl;
  }

  tout << "  targetData\n";
  for ( int y = boardSizeY-1; y >=0 ; y-- )
  {
	tout << "    ";
	for ( int d = 0; d < lengthOfABatchOfData; d++ )
    {
      for ( int x = 0; x < boardSizeX_; x++ )
      {
        tout << aPosterioriBoard_[ x ][ y ][ d ] << " ";
      }
      tout << " ";
    }
    tout << endl;
  }
}

void
BadukData::destroy_aPrioriBoard_( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData )
{
  assert(
	      ( boardSizeX > 0 ) && ( boardSizeY > 0 ) && ( lengthOfABatchOfData > 0 )
        );

  for ( int i = 0; i < 2; i++ )
  {
    for ( int j = 0; j < 2; j++ )
    {
      delete [] *(*(aPrioriBoard_+i)+j);
    }
    delete [] *(aPrioriBoard_+i);
  }
  delete [] aPrioriBoard_;
}

void
BadukData::destroy_aPosterioriBoard_( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData )
{
  for ( int i = 0; i < 2; i++ )
  {
    for ( int j = 0; j < 2; j++ )
    {
      delete [] *(*(aPosterioriBoard_+i)+j);
    }
    delete [] *(aPosterioriBoard_+i);
  }
  delete [] aPosterioriBoard_;
}
