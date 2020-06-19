#!/bin/awk -f
# A command to run this file
#   $ awk -f filename

{
  if ( $1 == "time_o_" ||
       $1 == "time_i_" ||
       $1 == "aBatchOfCellOutput_" ||
       $1 == "NeuralNetworks::computeError" ||
       $1 == "cellError" ||
       $1 == "systemError" ||
       $3 == "Cell::computeInitialErrors" )
  {
    print $0
  }
}


