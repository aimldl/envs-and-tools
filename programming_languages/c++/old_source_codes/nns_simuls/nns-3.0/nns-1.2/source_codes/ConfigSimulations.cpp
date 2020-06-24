#include  "ConfigSimulations.hpp"
#include  "ConfigUtilFns.hpp"

//==============================================================================
//                            Public functions
//==============================================================================

ConfigSimulations::ConfigSimulations()
  :
  isGotoBookmark_( false ),
  taskType_( "none" ),          taskType_found_( false ),
  boardSize_( 19 ),             boardSize_found_( false ),
  postprocess_( false ),        postprocess_found_( false ),
  showProgressBar_( true ),     showProgressBar_found_( false ),
  player_( "black" ),           player_found_( false ),
  trace4dbg_( false ),          trace4dbg_found_( false )
{
}

ConfigSimulations::~ConfigSimulations()
{
}

bool
ConfigSimulations::process
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
    if ( !strcmpNoCase( name, "simul_task_type" ) )
    {
      validNameFlag = 1;
      if ( taskType_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> taskType_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << taskType_ << "'" << endl;
        validate_taskType_();
        validValueFlag = 1;
        taskType_found_ = true;
      }
      isGotoBookmark_ = true;      
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "simul_boardSize" ) )
    {
      validNameFlag = 1;
      if ( boardSize_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> boardSize_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << boardSize_ << "'" << endl;
        validValueFlag = 1;
        boardSize_found_ = true;
      }
      isGotoBookmark_ = true;      
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "simul_postprocess" ) )
    {
      validNameFlag = 1;
      if ( postprocess_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> postprocess_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << postprocess_ << "'" << endl;
        validValueFlag = 1;
        postprocess_found_ = true;
      }
      isGotoBookmark_ = true;      
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "simul_show_progress_bar" ) )
    {
      validNameFlag = 1;
      if ( showProgressBar_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> showProgressBar_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << showProgressBar_ << "'" << endl;
        validValueFlag = 1;
        showProgressBar_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }
    //==========================================================================
    if ( !strcmpNoCase( name, "simul_player" ) )
    {
      validNameFlag = 1;
      if ( player_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> player_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << player_ << "'" << endl;
        validate_player_();
        validValueFlag = 1;
        player_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
        if ( !strcmpNoCase( name, "simul_trace4debug" ) )
        {
          validNameFlag = 1;
          if ( trace4dbg_found_ == true )
          {
            alreadyFoundFlag = 1;
            isGotoBookmark_ = true;
            goto bookmark;
          }
          if ( inputObj >> trace4dbg_ || inputObj.eof() )
          {
            tout << "  Set '" << name << "' to '" << trace4dbg_ << "'" << endl;
            validValueFlag = 1;
            trace4dbg_found_ = true;
          }
          isGotoBookmark_ = true;
          goto bookmark;
        }

    //==========================================================================
  bookmark:

  return isGotoBookmark_;
}

string
ConfigSimulations::get_taskType_() const
{
  return taskType_;
}

int
ConfigSimulations::get_boardSize_() const
{
  return boardSize_;
}

bool
ConfigSimulations::get_postprocess_() const
{
  return postprocess_;
}

bool
ConfigSimulations::get_showProgressBar_() const
{
  return showProgressBar_;
}

string
ConfigSimulations::get_player_() const
{
  return player_;
}

bool
ConfigSimulations::get_trace4dbg_() const
{
  return trace4dbg_;
}

bool
ConfigSimulations::get_trace4dbg_found_() const
{
  return trace4dbg_found_;
}

//==============================================================================
//                            Protected functions
//==============================================================================

//==============================================================================
//                            Private functions
//==============================================================================

void
ConfigSimulations::validate_taskType_()
{
  if ( ! (
		    ( taskType_ == "string_count_problem")
		 || ( taskType_ == "learn_optimal_moves")
		 || ( taskType_ == "plot_act_fn_mod_3")
		 || ( taskType_ == "test_ter2bin")
		 || ( taskType_ == "test_cliff_walking")
		 || ( taskType_ == "td_go")
		 )
     )
  {
    cerr << "Error in class ConfigSimulations. Unknown value: \n"
         << "simul_task_type = " << taskType_ << "."
         << endl;
    exit( 1 );
  }
}

void
ConfigSimulations::validate_player_()
{
  if (
	   ! ( (player_ == "black") || (player_ == "white") )
     )
  {
    cerr << "Error in class ConfigSimulations. Unknown value: \n"
         << "simul_player = " << player_
         << endl;
    exit( 1 );
  }
}
