#include  "Main.hpp"

// The comments on this file has been moved to Main.hpp.
// Convention:
//   classObj		Obj is for a class with only one instance of the class.

int
main( int argc, char* argv[] )
{
/*
  MPI::init();
  init rank = MPI.WORLD_COMM.GetRank(); // Maybe GetRank()
*/

  // Part 1. Process command-line arguments & configuration
  Myiostream::setDefaultValues();
  CommandLineArguments cmdLineArgsObj( argc, argv );
  ShellCommands        shellCmdsObj( "display_cwd" );
  Config               configObj( shellCmdsObj.get_cwd_() );
  configObj.close_configFile();  // All the parameter in configFile is stored in class COnfiguration.

  if ( configObj.get_simulationsObj_().get_taskType_() == "learn_optimal_moves" )
  {
    // Part 2. Configure classes
    Myiostream::configure( configObj );
    BadukData::configure( configObj );
    Cnn::configure( configObj );  // NeuralNetworks & Neuron are configured here.

    // Part 3. Main part
    BadukData badukDataObj;
    Cnn       cnnObj( badukDataObj );

    cnnObj.runSimulation( configObj.get_simulationsObj_().get_showProgressBar_(),
    		              badukDataObj.get_boardSizeX_(), badukDataObj.get_boardSizeY_(),
    		              badukDataObj.get_lengthOfABatchOfData_() );
    cnnObj.logErrors( badukDataObj.get_boardSizeX_(), badukDataObj.get_boardSizeY_() );

    // Part 4. Postprocess & run GNU plot & gv if neccessary.
    if ( configObj.get_simulationsObj_().get_postprocess_() )
    {
      ApiPostprocess postprocessObj;
      postprocessObj.run();  // Run nns_postprocess in directory bin.
    }
    if ( configObj.get_gnuPlotObj_().get_run_() )
    {
      ApiGnuplot gnuplotObj;
      gnuplotObj.run();  // Run gnuplot and gv
    }
    Myiostream::closeAllIosInstances( 4 );
  }
  else if ( configObj.get_simulationsObj_().get_taskType_() == "plot_act_fn_mod_3" )
  {
	  cout << "Plotting the modulo-3 activation function" << endl;
	  Neuron neuronObj("test");
	  neuronObj.test_moduloThreeFunction( -10.0, 0.1, 10.0 );
	  // TODO: Fix the stack overflow problem on the above line. The error message is
	  //       "No source available for "free() at ...".
  }
  else if ( configObj.get_simulationsObj_().get_taskType_() == "test_ter2bin" )
  {
	  NumberConversion noConversion;
	  noConversion.test_ter2dec();
  }
  else if ( configObj.get_simulationsObj_().get_taskType_() == "test_cliff_walking" )
  {
    Myiostream::configure( configObj );
    CliffWalkingProblem::configure( configObj );

    CliffWalkingProblem    cliffwalkingObj;

    cliffwalkingObj.initialize();
    cliffwalkingObj.runSimulation( configObj.get_simulationsObj_().get_showProgressBar_() );
    cliffwalkingObj.logResults();
  }
  else if ( configObj.get_simulationsObj_().get_taskType_() == "td_go" )
  {
    Myiostream::configure( configObj );
    RLGoEngine::configure( configObj );
    RLGoEngine  rlgoObj;

    rlgoObj.initialize();
    rlgoObj.runSimulation( configObj.get_simulationsObj_().get_showProgressBar_() );
  }

  return 0;
}
