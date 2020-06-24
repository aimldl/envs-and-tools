#include  "ConfigReinLearning.hpp"
#include  "ConfigUtilFns.hpp"

#include  <cstring>  // for size_t
#include  <cstdlib>  // for atoi, atof

//==============================================================================
//                        Static Public functions
//==============================================================================
//==============================================================================
//                            Public functions
//==============================================================================

ConfigReinLearning::ConfigReinLearning()
  :
 isGotoBookmark_( false ),
 gridWorldSize_found_( false ),
 gridWorldStartPosition_found_( false ),
 gridWorldEndPosition_found_( false ),
 gridWorldCliffPattern_( 0 ),                  gridWorldCliffPattern_found_( false ),
 maxNumberOfEpisodes_( 0 ),                    maxNumberOfEpisodes_found_( false ),
 rewardStructure_found_( false ),
 alpha_( 0.0 ),                                alpha_found_( false ),
 gamma_( 0.0 ),                                gamma_found_( false ),
 epsilon_( 0.0 ),                              epsilon_found_( false ),
 moveOption_( "" ),                            moveOption_found_( false ),
 updateMethod_( "" ),                          updateMethod_found_( false ),
 actionCriterion_( "" ),                       actionCriterion_found_( false )
{
  gridWorldSize_[0] = -1;
  gridWorldSize_[1] = -1;

  gridWorldStartPosition_[0] = -1;
  gridWorldStartPosition_[1] = -1;

  gridWorldEndPosition_[0] = -1;
  gridWorldEndPosition_[1] = -1;
}

ConfigReinLearning::~ConfigReinLearning()
{
}

bool
ConfigReinLearning::process
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
  if ( !strcmpNoCase( name, "2d_grid_world_size" ) )
  {
	string tmpString;

    validNameFlag = 1;
    if ( gridWorldSize_found_ == true )
    {
      alreadyFoundFlag = 1;
      isGotoBookmark_ = true;
      goto bookmark;
    }
    if ( inputObj >> tmpString || inputObj.eof() )
    {
      tout << "  Set '" << name << "' to '" << tmpString << "'" << endl;
      extractGridWorldSize_( tmpString );
      tmpString.clear();
      validValueFlag = 1;
      gridWorldSize_found_ = true;
    }
    isGotoBookmark_ = true;
    goto bookmark;
  }
  //==========================================================================
  if ( !strcmpNoCase( name, "2d_grid_world_start_position" ) )
  {
	string tmpString;

    validNameFlag = 1;
    if ( gridWorldStartPosition_found_ == true )
    {
      alreadyFoundFlag = 1;
      isGotoBookmark_ = true;
      goto bookmark;
    }
    if ( inputObj >> tmpString || inputObj.eof() )
    {
      tout << "  Set '" << name << "' to '" << tmpString << "'" << endl;
      extractGridWorldStartPosition_( tmpString );
      tmpString.clear();
      validValueFlag = 1;
      gridWorldStartPosition_found_ = true;
    }
    isGotoBookmark_ = true;
    goto bookmark;
  }
  //==========================================================================
  if ( !strcmpNoCase( name, "2d_grid_world_end_position" ) )
  {
	string tmpString;

    validNameFlag = 1;
    if ( gridWorldEndPosition_found_ == true )
    {
      alreadyFoundFlag = 1;
      isGotoBookmark_ = true;
      goto bookmark;
    }
    if ( inputObj >> tmpString || inputObj.eof() )
    {
      tout << "  Set '" << name << "' to '" << tmpString << "'" << endl;
      extractGridWorldEndPosition_( tmpString );
      tmpString.clear();
      validValueFlag = 1;
      gridWorldEndPosition_found_ = true;
    }
    isGotoBookmark_ = true;
    goto bookmark;
  }
  //==========================================================================
  if ( !strcmpNoCase( name, "2d_grid_world_cliff_pattern" ) )
  {
    validNameFlag = 1;
    if ( gridWorldCliffPattern_found_ == true )
    {
      alreadyFoundFlag = 1;
      isGotoBookmark_ = true;
      goto bookmark;
    }
    if ( inputObj >> gridWorldCliffPattern_ || inputObj.eof() )
    {
      tout << "  Set '" << name << "' to '" << gridWorldCliffPattern_ << "'" << endl;
      validValueFlag = 1;
      gridWorldCliffPattern_found_ = true;
    }
    isGotoBookmark_ = true;
    goto bookmark;
  }
  //==========================================================================
  if ( !strcmpNoCase( name, "rl_max_episode" ) )
  {
    validNameFlag = 1;
    if ( maxNumberOfEpisodes_found_ == true )
    {
      alreadyFoundFlag = 1;
      isGotoBookmark_ = true;
      goto bookmark;
    }
    if ( inputObj >> maxNumberOfEpisodes_ || inputObj.eof() )
    {
      tout << "  Set '" << name << "' to '" << maxNumberOfEpisodes_ << "'" << endl;
      validValueFlag = 1;
      maxNumberOfEpisodes_found_ = true;
    }
    isGotoBookmark_ = true;
    goto bookmark;
  }
  //==========================================================================
  if ( !strcmpNoCase( name, "rl_reward_structure" ) )
  {
	string tmpString;

    validNameFlag = 1;
    if ( rewardStructure_found_ == true )
    {
      alreadyFoundFlag = 1;
      isGotoBookmark_ = true;
      goto bookmark;
    }
    if ( inputObj >> tmpString || inputObj.eof() )
    {
      tout << "  Set '" << name << "' to '" << tmpString << "'" << endl;
      extractRewardStructure_( tmpString );
      tmpString.clear();
      validValueFlag = 1;
      rewardStructure_found_ = true;
    }
    isGotoBookmark_ = true;
    goto bookmark;
  }
  //==========================================================================
  if ( !strcmpNoCase( name, "rl_alpha" ) )
  {
    validNameFlag = 1;
    if ( alpha_found_ == true )
    {
      alreadyFoundFlag = 1;
      isGotoBookmark_ = true;
      goto bookmark;
    }
    if ( inputObj >> alpha_ || inputObj.eof() )
    {
      tout << "  Set '" << name << "' to '" << alpha_ << "'" << endl;
      validValueFlag = 1;
      alpha_found_ = true;
    }
    isGotoBookmark_ = true;
    goto bookmark;
  }
  //==========================================================================
  if ( !strcmpNoCase( name, "rl_gamma" ) )
  {
    validNameFlag = 1;
    if ( gamma_found_ == true )
    {
      alreadyFoundFlag = 1;
      isGotoBookmark_ = true;
      goto bookmark;
    }
    if ( inputObj >> gamma_ || inputObj.eof() )
    {
      tout << "  Set '" << name << "' to '" << gamma_ << "'" << endl;
      validValueFlag = 1;
      gamma_found_ = true;
    }
    isGotoBookmark_ = true;
    goto bookmark;
  }
  //==========================================================================
  if ( !strcmpNoCase( name, "rl_epsilon" ) )
  {
    validNameFlag = 1;
    if ( epsilon_found_ == true )
    {
      alreadyFoundFlag = 1;
      isGotoBookmark_ = true;
      goto bookmark;
    }
    if ( inputObj >> epsilon_ || inputObj.eof() )
    {
      tout << "  Set '" << name << "' to '" << epsilon_ << "'" << endl;
      validValueFlag = 1;
      epsilon_found_ = true;
    }
    isGotoBookmark_ = true;
    goto bookmark;
  }
  //==========================================================================
    if ( !strcmpNoCase( name, "rl_move_option" ) )
    {
      validNameFlag = 1;
      if ( moveOption_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> moveOption_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << moveOption_ << "'" << endl;
        validate_moveOption_();
        validValueFlag = 1;
        moveOption_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }
    //==========================================================================
      if ( !strcmpNoCase( name, "rl_update_method" ) )
      {
        validNameFlag = 1;
        if ( updateMethod_found_ == true )
        {
          alreadyFoundFlag = 1;
          isGotoBookmark_ = true;
          goto bookmark;
        }
        if ( inputObj >> updateMethod_ || inputObj.eof() )
        {
          tout << "  Set '" << name << "' to '" << updateMethod_ << "'" << endl;
          validate_updateMethod_();
          validValueFlag = 1;
          updateMethod_found_ = true;
        }
        isGotoBookmark_ = true;
        goto bookmark;
      }
      //==========================================================================
        if ( !strcmpNoCase( name, "rl_action_criterion" ) )
        {
          validNameFlag = 1;
          if ( actionCriterion_found_ == true )
          {
            alreadyFoundFlag = 1;
            isGotoBookmark_ = true;
            goto bookmark;
          }
          if ( inputObj >> actionCriterion_ || inputObj.eof() )
          {
            tout << "  Set '" << name << "' to '" << actionCriterion_ << "'" << endl;
            validate_actionCriterion_();
            validValueFlag = 1;
            actionCriterion_found_ = true;
          }
          isGotoBookmark_ = true;
          goto bookmark;
        }
  //==========================================================================

bookmark:

return isGotoBookmark_;
}

int
ConfigReinLearning::get_gridWorldSizeX_() const
{
  return gridWorldSize_[0];
}

int
ConfigReinLearning::get_gridWorldSizeY_() const
{
  return gridWorldSize_[1];
}

int
ConfigReinLearning::get_gridWorldStartPositionX_() const
{
  return gridWorldStartPosition_[0];
}

int
ConfigReinLearning::get_gridWorldStartPositionY_() const
{
  return gridWorldStartPosition_[1];
}

int
ConfigReinLearning::get_gridWorldEndPositionX_() const
{
  return gridWorldEndPosition_[0];
}

int
ConfigReinLearning::get_gridWorldEndPositionY_() const
{
  return gridWorldEndPosition_[1];
}

int
ConfigReinLearning::get_gridWorldCliffPattern_() const
{
  return gridWorldCliffPattern_;
}

int
ConfigReinLearning::get_maxNumberOfEpisodes_() const
{
  return maxNumberOfEpisodes_;
}

vdouble
ConfigReinLearning::get_rewardVector_() const
{
  return rewardVector_;
}

double
ConfigReinLearning::get_alpha_() const
{
  return alpha_;
}

double
ConfigReinLearning::get_gamma_() const
{
  return gamma_;
}

double
ConfigReinLearning::get_epsilon_() const
{
  return epsilon_;
}

string
ConfigReinLearning::get_moveOption_() const
{
  return moveOption_;
}

string
ConfigReinLearning::get_updateMethod_() const
{
  return updateMethod_;
}

string
ConfigReinLearning::get_actionCriterion_() const
{
  return actionCriterion_;
}

//==============================================================================
//                            Protected functions
//==============================================================================
//==============================================================================
//                            Private functions
//==============================================================================

// Example of tmpString: 3x10. No space is assumed around "x".
//   gridWorldSize_[ 0 ] = 3;
//   gridWorldSize_[ 1 ] = 10;

void
ConfigReinLearning::extractGridWorldSize_( string tmpString )
{
  size_t pos;

  pos = tmpString.find( "x" );
  gridWorldSize_[ 0 ] = atoi( tmpString.substr( 0, pos ).c_str() );
  gridWorldSize_[ 1 ] = atoi( tmpString.substr( pos+1 ).c_str() );

//  cout << "gridWorldSize_=" << gridWorldSize_[ 0 ] << "x" << gridWorldSize_[ 1 ] << endl;

}

// Example of tmpString: (0,0). No space is assumed around ",".
//   gridWorldStartPosition_[ 0 ] = 0;
//   gridWorldStartPosition_[ 1 ] = 0;

void
ConfigReinLearning::extractGridWorldStartPosition_( string tmpString )
{
  size_t pos;
  string substring0, substring1;

  pos = tmpString.find( "," );

  substring0 = tmpString.substr( 0, pos ).c_str();
  substring1 = tmpString.substr( pos+1 ).c_str();

  pos = substring0.find( "(" );
  gridWorldStartPosition_[ 0 ] = atoi( substring0.substr( pos+1 ).c_str() );

  pos = substring1.find( ")" );
  gridWorldStartPosition_[ 1 ] = atoi( substring1.substr( 0, pos ).c_str() );

//  cout << "gridWorldStartPosition_=(" << gridWorldStartPosition_[ 0 ] << "," << gridWorldStartPosition_[ 1 ] << ")" << endl;

}

// Example of tmpString: (0,0). No space is assumed around ",".
//   extractgridWorldEndPosition_[ 0 ] = 0;
//   extractgridWorldEndPosition_[ 1 ] = 0;

void
ConfigReinLearning::extractGridWorldEndPosition_( string tmpString )
{
  size_t pos;
  string substring0, substring1;

  pos = tmpString.find( "," );

  substring0 = tmpString.substr( 0, pos ).c_str();
  substring1 = tmpString.substr( pos+1 ).c_str();

  pos = substring0.find( "(" );
  gridWorldEndPosition_[ 0 ] = atoi( substring0.substr( pos+1 ).c_str() );

  pos = substring1.find( ")" );
  gridWorldEndPosition_[ 1 ] = atoi( substring1.substr( 0, pos ).c_str() );

//  cout << "gridWorldEndPosition_=(" << gridWorldEndPosition_[ 0 ] << "," << gridWorldEndPosition_[ 1 ] << ")" << endl;

}

void
ConfigReinLearning::extractRewardStructure_( string tmpString )
{
  rewardVector_ = strUtilObj_.separateSubstringsByColumns( tmpString );
}

void
ConfigReinLearning::validate_moveOption_()
{
  if ( !( moveOption_ == "standard_move" || moveOption_ == "kings_move" || moveOption_ == "kings_move_with_pause" ) )
  {
    cerr << "Error in class ConfigReinLearning. Unknown value: \n"
         << "moveOption_ = " << moveOption_ << endl;
    exit( 1 );
  }
}

void
ConfigReinLearning::validate_updateMethod_()
{
  if ( !( updateMethod_ == "sarsa" || updateMethod_ == "qlearning" ) )
  {
    cerr << "Error in class ConfigReinLearning. Unknown value: \n"
         << "updateMethod_ = " << updateMethod_ << endl;
    exit( 1 );
  }
}

void
ConfigReinLearning::validate_actionCriterion_()
{
  if ( !( actionCriterion_ == "greedy"
       || actionCriterion_ == "egreedy"
        ) )
  {
    cerr << "Error in class ConfigReinLearning. Unknown value: \n"
         << "actionCriterion_ = " << actionCriterion_ << endl;
    exit( 1 );
  }
}
