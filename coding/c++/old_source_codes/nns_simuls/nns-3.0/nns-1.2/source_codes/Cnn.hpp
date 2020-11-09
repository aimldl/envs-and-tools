#ifndef  __CNN_HPP_
#define  __CNN_HPP_

#include  "BadukData.hpp"
#include  "Cell.hpp"
#include  "Error.hpp"
#include  "MyStringUtilFunctions.hpp"  // For str2ints
#include  "Pso.hpp"

using namespace  std;

//==============================================================================
//                              Type Definitions
//==============================================================================
typedef vector<Error4Cnn> vcnnerr;

//==============================================================================
//                              Class Declaration
//==============================================================================
class      Cnn: public SimObject
{
public:
	       Cnn();
           Cnn( BadukData& badukDataObj );
           ~Cnn();
  static
  void     configure( Config& configObj );  // IMPORTANT! RUN THESE FUNCTIONS BEFORE THIS CLASS IS CONSTRUCTED!!!
  void     initialize( BadukData& badukDataObj );
  void     runSimulation( bool showProgressBar, int boardSizeX, int boardSizeY, int lengthOfABatchOfData );
  void     logErrors( int boardSizeX, int boardSizeY );

private:
  void     initialize_cells_( string trainingAlgorithm, int boardSizeX, int boardSizeY, int lengthOfABatchOfData );
  int      determine_numOfAdjacencies( int x, int y, int boardSizeX, int boardSizeY );
  void     setMeshTopology( int boardSizeX, int boardSizeY );
  void     splitBadukDataIntoDataInCells( BadukData& badukDataObj, int boardSizeX, int boardSizeY, int lengthOfABatchOfData );
  void     allocateMemory_aBatchOfCnnOutput_( int boardSizeX, int boardSizeY, int lengthOfABatchOfData );
  void     saveInitialWeightsInCells( int boardSizeX, int boardSizeY );
  void     showNeighborsInCells( int boardSizeX, int boardSizeY );
  void     showDataInCells( int boardSizeX, int boardSizeY, int lengthOfABatchOfData );

  void     update_aBatchOfCnnOutput_( int boardSizeX, int boardSizeY, int lengthOfABatchOfData );
  void     matchInitialWeightsWtTrainingAlgo();

  void     computeInitialErrors( int boardSizeX, int boardSizeY, int lengthOfABatchOfData );

  bool     isInitialWeightMatchDoneInAllCells( int boardSizeX, int boardSizeY );

  static
  bool     isConfigDone_;
  static
  int      maxEpochs_o_;
  static
  double   targetSystemError_;
  static
  bool     matchNnInitialWeightsToTrainingAlgo_;
  static
  string   errorMetric_;  // Either abs_error or mse
  static
  string   trainingAlgorithm_;

  bool     isTopologySet_;
  bool     isBadukDataReformatted_;
  double***
           aBatchOfCnnOutput_;  // A variable introduced to correctly synchronize all the cells for emulating CNN correctly.
  Cell**   cells_;
  vdouble  systemError_;
  vcnnerr  error_;
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================
