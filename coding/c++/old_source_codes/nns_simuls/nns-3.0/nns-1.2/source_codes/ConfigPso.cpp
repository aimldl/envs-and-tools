#include  "ConfigPso.hpp"
#include  "ConfigUtilFns.hpp"

//==============================================================================
//                            Public functions
//==============================================================================

ConfigPso::ConfigPso()
  :
  isGotoBookmark_( false ),
  numberOfParticles_( 1 ),           numberOfParticles_found_( false ),
  useParticleHistoryReset_( false ), useParticleHistoryReset_found_( false ),
  w_( 1.0 ),                         w_found_( false ),
  c1_( 1.0 ),                        c1_found_( false ),
  c2_( 1.0 ),                        c2_found_( false ),
  VMax_( 1.0 ),                      VMax_found_( false ),
  XMin_( 1.0 ),                      XMin_found_( false ),
  XMax_( 1.0 ),                      XMax_found_( false ),
  V_initialValue_( 0.00001 ),        V_initialValue_found_( false ),
  pBest_initialValue_( 0.0 ),        pBest_initialValue_found_( false )
//  globalBest_initialValue_( 0.0 ), globalBest_initialValue_found_( false )
{

}

ConfigPso::~ConfigPso()
{
}

bool
ConfigPso::process
(
  const char* name,
  ifstream&   inputObj,
  int&        validNameFlag,
  int&        validValueFlag,
  int&        alreadyFoundFlag 
)
{
  string temp;
  isGotoBookmark_ = false;

    //==========================================================================
    if ( !strcmpNoCase( name, "pso_number_of_particles") )
    {
      validNameFlag = 1;
      if ( numberOfParticles_found_ == true )      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> numberOfParticles_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << numberOfParticles_ << "'" << endl;
        validValueFlag = 1;
        numberOfParticles_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "pso_use_particle_history_reset") )
    {
      validNameFlag = 1;
      if ( useParticleHistoryReset_found_ == true )      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> useParticleHistoryReset_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << useParticleHistoryReset_ << "'" << endl;
        // Validation of the value is automatically done because the data type of useParticleHistoryReset_ is
        // boolean. If useParticleHistoryReset_ is other than true/false or 1/0, the program is supposed to
        // show an error message.
        validValueFlag = 1;
        useParticleHistoryReset_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "pso_w") )
    {
      validNameFlag = 1;
      if ( w_found_ == true )      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> w_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << w_ << "'" << endl;
        validValueFlag = 1;
        w_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "pso_c1") )
    {
      validNameFlag = 1;
      if ( c1_found_ == true )      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> c1_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << c1_ << "'" << endl;
        validValueFlag = 1;
        c1_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "pso_c2") )
    {
      validNameFlag = 1;
      if ( c2_found_ == true )      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> c2_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << c2_ << "'" << endl;
        validValueFlag = 1;
        c2_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "pso_v_max") )
    {
      validNameFlag = 1;
      if ( VMax_found_ == true )      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> VMax_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << VMax_ << "'" << endl;
        validValueFlag = 1;
        VMax_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "pso_x_min") )
    {
      validNameFlag = 1;
      if ( XMin_found_ == true )      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> XMin_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << XMin_ << "'" << endl;
        validValueFlag = 1;
        XMin_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "pso_x_max") )
    {
      validNameFlag = 1;
      if ( XMax_found_ == true )      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> XMax_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << XMax_ << "'" << endl;
        validValueFlag = 1;
        XMax_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "pso_v_initial_value") )
    {
      validNameFlag = 1;
      if ( V_initialValue_found_ == true )      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> V_initialValue_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << V_initialValue_ << "'" << endl;
        validValueFlag = 1;
        V_initialValue_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }
    //==========================================================================
        if ( !strcmpNoCase( name, "pso_local_best_initial_value") )
    {
      validNameFlag = 1;
      if ( pBest_initialValue_found_ == true )      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> temp || inputObj.eof() )
      {
        assert( inputObj );
        tout << "  Set '" << name << "' to '" << temp << "'=>";
        if ( temp == "inf" )
        {
          pBest_initialValue_ = numeric_limits<double>::max();
        }
        else
        {
          pBest_initialValue_ = MyStringUtilFunctions::str2double( temp );
        }
        tout << "  Set '" << name << "' to '" << "'" << pBest_initialValue_ << "'" << endl;
        validValueFlag = 1;
        pBest_initialValue_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }
 
  bookmark:

  return isGotoBookmark_;
}

int
ConfigPso::get_numberOfParticles_() const
{
  return numberOfParticles_;
}

bool
ConfigPso::get_useParticleHistoryReset_() const
{
  return useParticleHistoryReset_;
}

double
ConfigPso::get_w_() const
{
  return w_;
}

double
ConfigPso::get_c1_() const
{
  return c1_;
}

double
ConfigPso::get_c2_() const
{
  return c2_;
}

double
ConfigPso::get_VMax_() const
{
  return VMax_;
}

double
ConfigPso::get_XMin_() const
{
  return XMin_;
}

double
ConfigPso::get_XMax_() const
{
  return XMax_;
}

double
ConfigPso::get_V_initialValue_() const
{
  return V_initialValue_;
}

double
ConfigPso::get_pBest_initialValue_() const
{
  return pBest_initialValue_;
}
//  double  get_globalBest_initialValue_() const
//{
//  return globalBest_initialValue_;
//}

//==============================================================================
//                            Protected functions
//==============================================================================

//==============================================================================
//                            Private functions
//==============================================================================
