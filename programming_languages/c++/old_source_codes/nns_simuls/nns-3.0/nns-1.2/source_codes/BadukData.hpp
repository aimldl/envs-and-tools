#ifndef  __BADUKDATA_HPP_
#define  __BADUKDATA_HPP_

#include  "SimObject.hpp"

using namespace  std;

//==============================================================================
//                              Class Declaration
//==============================================================================
class      BadukData: public SimObject
{
public:
           BadukData();
          ~BadukData();
  static
  void     configure( Config& configObj );  // IMPORTANT! RUN THESE FUNCTIONS BEFORE THIS CLASS IS CONSTRUCTED!!!
  static
  int      get_boardSizeX_();
  static
  int      get_boardSizeY_();
  static
  int      get_lengthOfABatchOfData_();
  static
  int      get_totalNumOfTargetData_();
  static
  bool     get_isConfigured_();

  void     initialize();
  bool     get_isInitialized_();
  int***   get_aPrioriBoard_();
  int***   get_aPosterioriBoard_();
  int      get_dataLength_();

protected:
  void     createTestInputData();
  void     createTestTargetData();
  void     initializeTestInputData( int l );
  void     initializeTestTargetData( int l );
  
private:
  void     constructData( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData );
  void     construct_aPrioriBoard_( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData );
  void     construct_aPosterioriBoard_( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData );

  double   createData( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData );
  void     initializeBoards( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData );  // Board means both aPrioriBoard_ and aPosterioriBoard_.
  double   setData_2x2_single_valued_fn( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData );
  double   setData_2x2_multi_valued_fn( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData );
  double   setData_brd_status_seqs_2x2_optimal_black( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData );
  double   setData_brd_status_seqs_2x2_optimal_white( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData );
  double   setData_3x3( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData );

  void     logCreatedData( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData );
  void     logCreatedData_2x2( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData );

  void     destroy_aPrioriBoard_( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData );
  void     destroy_aPosterioriBoard_( int& boardSizeX, int& boardSizeY, int& lengthOfABatchOfData );

  static
  string   player_;
  static
  int      lengthOfABatchOfData_;
  static
  string   dataType_;
  static
  int      boardSizeX_;
  static
  int      boardSizeY_;
  static
  int      totalNumOfTargetData_;
  static
  bool     isConfigured_;

  bool     isInitialized_;
  bool     is_aPrioriBoard_initialized_;
  bool     is_aPosterioriBoard_initialized_;
  int***   aPrioriBoard_;     // board status before my move. This will be the CNN input data.
  int***   aPosterioriBoard_; // aPosterioriBoard (desired board status or after my move).

};

#endif

//==============================================================================
//                                  Comments
//==============================================================================

// This class is to create "test" data. In other words, "test_problem" is assumed.
// "task_id" will be used if necessary
//
// int*** aPrioriBoard_; and int*** aPosterioriBoard_;
//   aPrioriBoard_ is the board status before my move. This will be the CNN input data.
 //  aPosterioriBoard is the desired board status or after my move. This will be the CNN target data.
//   Both aPrioriBoard_ and aPosterioriBoard_ will be casted from int to double
//   so that these data can be usable for neural networks inputs and outputs.
