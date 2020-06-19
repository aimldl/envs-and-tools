#include  "ConfigData.hpp"
#include  "ConfigUtilFns.hpp"

//==============================================================================
//                            Public functions
//==============================================================================

ConfigData::ConfigData()
  :
  isGotoBookmark_( false ),
  inputConfig_( "none" ),           inputConfig_found_( false ),
  targetConfig_( "none" ),          targetConfig_found_( false ),
  dataRepresentation_( "ternary" ), dataRepresentation_found_( false ),
  dataRepresentationOffset_( 1.0 ), dataRepresentationOffset_found_( false ),
  dataType_( "single_valued" ),     dataType_found_( false )
{

}

ConfigData::~ConfigData()
{
}

bool
ConfigData::process
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
    if ( !strcmpNoCase( name, "data_input_config" ) )
    {
      validNameFlag = 1;
      if ( inputConfig_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> inputConfig_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << inputConfig_ << "'" << endl;
        validValueFlag = 1;
        inputConfig_found_ = true;
      }
      isGotoBookmark_ = true;      
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "data_target_config" ) )
    {
      validNameFlag = 1;
      if ( targetConfig_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> targetConfig_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << targetConfig_ << "'" << endl;
        validValueFlag = 1;
        targetConfig_found_ = true;
      }
      isGotoBookmark_ = true;      
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "data_representation" ) )
    {
      validNameFlag = 1;
      if ( dataRepresentation_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> dataRepresentation_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << dataRepresentation_ << "'" << endl;
        validate_dataRepresentation_();
        validValueFlag = 1;
        dataRepresentation_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }
    //==========================================================================
    if ( !strcmpNoCase( name, "data_representation_offset" ) )
    {
      validNameFlag = 1;
      if ( dataRepresentationOffset_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> dataRepresentationOffset_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << dataRepresentationOffset_ << "'" << endl;
        validate_dataRepresentationOffset_();
        validValueFlag = 1;
        dataRepresentationOffset_found_ = true;
      }

      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "data_type" ) )
    {
      validNameFlag = 1;
      if ( dataType_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> dataType_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << dataType_ << "'" << endl;
        validate_dataType_();
        validValueFlag = 1;
        dataType_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
 
  bookmark:

  return isGotoBookmark_;
}

string
ConfigData::get_inputConfig_() const
{
  return inputConfig_;
}

string
ConfigData::get_targetConfig_() const
{
  return targetConfig_;
}

string
ConfigData::get_dataRepresentation_() const
{
  return dataRepresentation_;
}

double
ConfigData::get_dataRepresentationOffset_() const
{
  return dataRepresentationOffset_;
}

string
ConfigData::get_dataType_() const
{
  return dataType_;
}

//==============================================================================
//                            Protected functions
//==============================================================================

//==============================================================================
//                            Private functions
//==============================================================================

void
ConfigData::validate_dataRepresentation_()
{
  if ( dataRepresentation_ != "ternary" )
  {
    cerr << "Error in class ConfigData. Unknown value: \n"
         << "data_representation = " << dataRepresentation_ << "."
         << endl;
    exit( 1 );
  }
}

void
ConfigData::validate_dataRepresentationOffset_()
{
  if ( dataRepresentationOffset_ != -1.0 && dataRepresentationOffset_ != 0.0 && dataRepresentationOffset_ != 1.0 )
  {
    cerr << "Error in class ConfigData. Unknown value: \n"
         << "data_representation_offset = " << dataRepresentationOffset_ << "."
         << endl;
    exit( 1 );
  }
}

void
ConfigData::validate_dataType_()
{
  if (
       dataType_ != "single_valued_function"
         &&
       dataType_ != "multi_valued_function"
           &&
       dataType_ != "board_status_sequences"
     )
  {
    cerr << "Error in class ConfigData. Unknown value: \n"
         << "data_type = " << dataType_ << "."
         << endl;
    exit( 1 );
  }
}
