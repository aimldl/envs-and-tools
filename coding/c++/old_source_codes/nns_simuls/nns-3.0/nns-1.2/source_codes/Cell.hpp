#ifndef  __CELL_HPP_
#define  __CELL_HPP_

#include  "SimObject.hpp"
#include  "NeuralNetworks.hpp"
#include  "Pso.hpp"
#include  "RandomVariables.hpp"

using namespace  std;

//==============================================================================
//                              Class Declaration
//==============================================================================

class      Cell: public SimObject
{
public:
           Cell();
  static
  void     configure( Config& configObj, string trainingAlgorithm );  // IMPORTANT! RUN THESE FUNCTIONS BEFORE THIS CLASS IS CONSTRUCTED!!!
  void     initialize( int cellIndex, int locationX, int locationY, int numOfAdjacencies,
		               string trainingAlgorithm, string errorMetric,
                       bool matchInitialWeights, int lengthOfABatchOfData );
  void     reshape_aBatchOfScalarInputData_to_aBatchOfVectorInputData_( int lengthOfABatchOfData );
  void     setNeighbor( Cell* instance, int index );
  void     set_isNeighborsSet_( bool value );

  double   computeInitialErrors( int lengthOfABatchOfData, string errorMetric );
  void     set_aBatchOfCellOutput_( vdouble aBatchOfScalarOutputData, int lengthOfABatchOfData );
  void     update_aBatchOfVectorInputData_by_fetchingNeighborsCellOutputs( int lengthOfABatchOfData, double*** aBatchOfCnnOutput_ );
  double   trainInBatchMode( int time_o, string errorMetric, int lengthOfABatchOfData  );

  void     show_aBatchOfScalarInputData_( int lengthOfABatchOfData );
  void     show_aBatchOfVectorInputData_( int lengthOfABatchOfData );
  void     show_aBatchOfScalarTargetData_( int lengthOfABatchOfData );;
  void     showNeighbors( int x, int y );

  int      get_index_() const;
  int      get_numOfAdjacencies_() const;
  int      get_numOfCellInputs_() const;
  bool     get_isHibernate_() const;
  bool     get_isNeighborsSet_() const;
  vdouble  get_cellError_() const;
  int      get_locationX_() const;
  int      get_locationY_() const;
  bool     get_isInitialWeightMatchDone_() const;
  double   get_aBatchOfCellOutput_( int index, int particle ) const;
  double   get_targetData_( int index ) const;
  int      get_maxEpochs_i_() const;

  NeuralNetworks&
           get_nns_();
  Pso&     get_pso_();


  double** aBatchOfVectorInputData_;
  vdouble  aBatchOfScalarInputData_;
  vdouble  aBatchOfScalarTargetData_;
  vdouble  aBatchOfScalarOutputData_;

private:
  void     doDynamicMemoryAllocation( string errorMetric, int lengthOfABatchOfData );
  vdouble  set_currentCellInput( int d, string fdInputInitialization );
  double   computeMseInBatch( int p, int lengthOfABatchOfData );

  static
  int      maxEpochs_i_;
  static
  double   targetCellError_;
  static
  string   fdInputInitialization_;
  static
  string   nnType_;

  int      index_;  // Do not delete it. This is neccessary to check the neighboring cells.
  int      locationX_;
  int      locationY_;
  int      numOfAdjacencies_;
  int      numOfCellInputs_;
  int      time_i_;  // epoch for inner lopp
  bool     isHibernate_;  // Activation delta function to hibernate the cell.
  bool     isNeighborsSet_;
  bool     isInitialWeightMatchDone_;
  vdouble  cellError_;
  double** aBatchOfCellOutput_;
  Cell**   neighbors_p_; // Always count the neighbors clockwise.
  Pso      pso_;
  NeuralNetworks
           nns_;
  RandomVariables
           rvs_;
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================

// The variables for the data are confusing.
//
// Input data:
//   A cell has two types of input data: a scalar input and a vector input.
//   The scalar input is a data assigned to the cell itself when the CNN
//   input is split into cell inputs. The vector input is a collection of
//   scalar inputs and scalar target data from the cell itself and neighboring cells.
//   In case of a 2x2 structure, each cell has two neighbors. The size of the
//   vector input is 6: 3 (scalar input of the cell itself and two neighbors) and
//   3 ( scalar target of the cell itself and two neighbors).
//
// Target data:
//   A cell has a single target data, so a batch of target data is a vector.
