#ifndef  __CONFIGUTILFNS_HPP_
#define  __CONFIGUTILFNS_HPP_

// Routine to extract comments.
//   A commented line, which starts from "#", is skipped to the end of line.
//   Whitespaces are extracted by "ws".
//   Name value separators '=', ' ', ':' are extracted, too. 
static
istream&
extractComment( istream& inputStream )
{
  while ( inputStream >> ws && inputStream.peek() == '#' )
  { //skip to the end_of_line
    while( inputStream && inputStream.get() != '\n') { ; }
  }
  return inputStream;
}

// Read the name of a variable from the input stream.
// whitespaces & name-value separators  '=', ' ', ':' are extracted.
static
void 
getName( istream& inputStream, char* name_p)
{
  char ch = 0;
    
  inputStream >> extractComment;
  while
  (
    inputStream
    && !isspace( ch = inputStream.get() )
    && ch != '='
    && ch != ':'
    && ch != ';'
    && ch != EOF
  )
  { 
    *(name_p++) = ch;
  }
  *name_p = '\0';
  inputStream >> ws;
  ch = inputStream.peek();
  if( ch == '=' || ch == ':'  || ch == ';')
    inputStream.get( ch );
}

static
int 
strcmpNoCase( const char* string1_p, const char* string2_p )
{
  char ch1, ch2;
  
  while ( ( ch1 = tolower( *string1_p++ ) ) == ( ch2 = tolower( *string2_p++ ) ) )
  {
    if( ch1 == '\0')
      return 0;
  }
  return ( ch1 - ch2 );
}

#endif
