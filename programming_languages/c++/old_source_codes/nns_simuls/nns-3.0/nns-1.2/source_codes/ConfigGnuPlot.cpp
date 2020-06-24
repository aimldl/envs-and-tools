#include  "ConfigGnuPlot.hpp"
#include  "ConfigUtilFns.hpp"

//==============================================================================
//                            Public functions
//==============================================================================

ConfigGnuPlot::ConfigGnuPlot()
  :
  isGotoBookmark_( false ),
  run_( 0 ),                               run_found_( false ),
  rangeXFrom_( -1.0 ),                     rangeXFrom_found_( false ),
  rangeXTo_( -1.0 ),                       rangeXTo_found_( false ),
  rangeXIncrement_( -1.0 ),                rangeXIncrement_found_( false ),
  graphTitle_( "Default Title" ),          graphTitle_found_( false )
{

}

ConfigGnuPlot::~ConfigGnuPlot()
{
}

bool
ConfigGnuPlot::process
(
  const char* name,
  ifstream&   inputObj,
  int&        validNameFlag,
  int&        validValueFlag,
  int&        alreadyFoundFlag 
)
{
  isGotoBookmark_ = false;
  
    //==========================================================================
    if ( !strcmpNoCase( name, "gnuplot_run" ) )
    {
      validNameFlag = 1;
      if ( run_found_ == true )      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> run_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << run_ << "'" << endl;
        validValueFlag = 1;
        run_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "gnuplot_range_x_from" ) )
    {
      validNameFlag = 1;
      if ( rangeXFrom_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> rangeXFrom_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << rangeXFrom_ << "'" << endl;
        validValueFlag = 1;
        rangeXFrom_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "gnuplot_range_x_to" ) )
    {
      validNameFlag = 1;
      if ( rangeXTo_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> rangeXTo_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << rangeXTo_ << "'" << endl;
        validValueFlag = 1;
        rangeXTo_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "gnuplot_range_x_increment" ) )
    {
      validNameFlag = 1;
      if ( rangeXIncrement_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> rangeXIncrement_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << rangeXIncrement_ << "'" << endl;
        validValueFlag = 1;
        rangeXIncrement_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "gnuplot_title" ) )
    {
      validNameFlag = 1;
      if ( graphTitle_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> graphTitle_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << graphTitle_ << "'" << endl;
        validValueFlag = 1;
        graphTitle_found_ = true;
      }
      isGotoBookmark_ = true;      
      goto bookmark;
    }

    //==========================================================================
 
  bookmark:

  return isGotoBookmark_;
}

string
ConfigGnuPlot::get_graphTitle_() const
{
  return graphTitle_;
}

int
ConfigGnuPlot::get_run_() const
{
  return run_;
}

//==============================================================================
//                            Protected functions
//==============================================================================

//==============================================================================
//                            Private functions
//==============================================================================


