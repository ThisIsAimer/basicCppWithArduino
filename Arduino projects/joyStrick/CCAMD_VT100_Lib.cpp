///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// README /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

*/


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "CCAMD_VT100_Lib.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DEFINES, MACROS, etc. //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TYPES //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PROTOTYPES /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GLOBALS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VT100 terminal globals
const char VT100_ESCAPE_SEQ_STRING[ ] = { VT100_ESCAPE_CODE, '[', 0 }; 

// buffer for building strings...assume terminal is 80x24 or less, so 96 characters should be enough 
char vtStringBuffer[ 96 ];              

// useful commands
const char VT100_HIDE_CURSOR[] = "?25l";
const char VT100_SHOW_CURSOR[] = "?25h";

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS/METHODS///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VT100_DrawBlockLineAtCursor( char blockChar, int lineLength, int lineFill )
{
/*   
  DESCRIPTION:  This function draws a line of graphic characters from the current terminal cursor location, so it
                the responsibility of caller to handle cursor positioning before and after (for now).
  PARAMETERS:          
     
  RETURN:       Nothing.   
*/
 
// create string  
memset( vtStringBuffer, blockChar, lineLength );

// now, fill end with spaces to overwrite previous render

memset( vtStringBuffer + lineLength , ' ' , lineFill );

// null terminate
vtStringBuffer[ lineLength + lineFill ] = 0;

// now draw line...
Serial.print( vtStringBuffer );

} // end VT100_DrawBlockLineAtCursor

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VT100_PrintArtASCII( char *string )
{

/*   
  DESCRIPTION:  This function draws "ASCII" art. The problem is that with modern text editors, 
                so much text translation goes on that you can't insert extended ASCII codes into 
                the source without them being converted to UTF8 or other multibyte formats, so it's
                hard to "draw" art in the editor and keep a 1-1 relationship between characters and bytes.
                Therefore, this helper function takes an ASCII-art image using some single byte normal characters
                like 1,2,3,4 (1 for light block, 4 for solid block) and maps them to different shaded blocks in the extended ASCII code page 437 
                from the IBM PC which are dithered blocks, great for making images. Also, the function
                allows the art to draw normal characters such as 1,2,3,4 by using a special character to 
                toggle "translation mode", the character '$' toggles the modes, so if you want to print a
                '1' for example and not have it translated into a dithered block, then you use '$' to control
                this.
  
  PARAMETERS:   Character string to print.       
     
  RETURN:       Nothing.   
*/



/*
#define ASCII_BLOCK_DITHERED_LIGHT  176
#define ASCII_BLOCK_DITHERED_MEDIUM 177
#define ASCII_BLOCK_DITHERED_DARK   178
#define ASCII_BLOCK_SOLID           219
*/

static int renderMode = 0; // tracks if we are in ASCII art mode or text mode

// Print string out to ASCII VT100 UART with transcoding of characters
for ( int32_t stringIndex = 0; stringIndex < (int32_t)strlen( string ); stringIndex++ )
    {
          
    // Test which render mode we are in?

    if ( renderMode == 0 )
      {
      switch( string[ stringIndex ] )  
            {
            case '1': Serial.write( ASCII_BLOCK_DITHERED_LIGHT ); break;
            case '2': Serial.write( ASCII_BLOCK_DITHERED_MEDIUM ); break;
            case '3': Serial.write( ASCII_BLOCK_DITHERED_DARK ); break;
            case '4': Serial.write( ASCII_BLOCK_SOLID ); break;
            
            case '$': // Toggle render mode
                  {
                  if ( !renderMode ) 
                    renderMode = 1;
                  } break;
        
            default: Serial.write( string[ stringIndex ]  ); break;
  
            } // end switch
  
      } // end if
    else
      { // Normal mode, do not draw ASCII art
  
      // Toggle out of text mode?
      if ( string[ stringIndex ] == '$' )
        renderMode = 0;
      else  
        Serial.write( string[ stringIndex ]  );
      
      } // end else

    } // end for stringIndex

// Finish line
Serial.println("");

} // end VT100_PrintArtASCII

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VT100_Logo( void )
{
/*
DESCRIPTION:    This function simply "draws" a cool startup logo using ASCII art.
PARAMETERS:     None.
RETURNS:        Nothing.
*/

// a little fun with ASCII art. The characters 1,2,3, and 4 are translated to block dithered 
// characters (1 = light, 4 = solid) by the VT100_PrintArtASCII() function, so we can draw cool images!

VT100_PrintArtASCII("___________________________________________________________________");
VT100_PrintArtASCII("");

VT100_PrintArtASCII("");
VT100_PrintArtASCII("");
VT100_PrintArtASCII("Terminal opening!      "); 
VT100_PrintArtASCII("___________________________________________________________________");

} // end VT100_Logo

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VT100_SendCmd( char *cmdString )
{
/*
DESCRIPTION:    This function sends a VT100 command by pre-pending "ESC [ " followed by the command
PARAMETERS:     None.
RETURNS:        Nothing.
*/

// build command up by pre-pending escape sequence 
sprintf( vtStringBuffer, "%s%s", VT100_ESCAPE_SEQ_STRING, cmdString );
 
// and now finish by writting the VT100 command
Serial.print( vtStringBuffer ); 

} // end VT100_SendCmd

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VT100_Init( void )
{
/*
DESCRIPTION:    Initializes terminal to power on mode.
PARAMETERS:     None.
RETURNS:        Nothing.
*/


// ESC c
char cmdStr[] = { VT100_ESCAPE_CODE, 'c', 0 };

Serial.print( cmdStr );

} // end VT100_Init

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VT100_ClearScreen( void )
{
/*
DESCRIPTION:    Clears the screen.
PARAMETERS:     None.
RETURNS:        Nothing.
*/

// ESC [ 3 j
char cmdStr[] = { VT100_ESCAPE_CODE, '[', '2', 'J', 0 };

Serial.print( cmdStr );

} // end VT100_ClearScreen

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VT100_SetCursor( unsigned char line, unsigned char column )
{
/*
DESCRIPTION:    Places cursor at sent column and line.

PARAMETERS:     line - vertical screen line to place the cursor at.
                column - horizontal screen column to place the cursor at.
RETURNS:        Nothing.
*/

// ESC [ Pl ; Pc H

char cmdStr[ 16 ];

// build the string
sprintf( cmdStr, "%c[%d;%dH",VT100_ESCAPE_CODE, line, column);

// send to USART
Serial.print( cmdStr );

} // end VT100_SetCursor

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VT100_SetAttr( unsigned char attr )
{
/*
DESCRIPTION:    Changes te2t attribute, only works on some terminals.
PARAMETERS:     attr - the attribute to change the text mode to.
RETURNS:        Nothing.
*/

char cmdStr[ 16 ];

// build the string
sprintf( cmdStr, "%c[%dm",VT100_ESCAPE_CODE,attr);

// ESC [ Ps m
Serial.print( cmdStr );

} // end VT100_SetAttr

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VT100_Boot()
{
/*
DESCRIPTION:    "Fake" boot of our virtual VT100 terminal -- just for fun!
PARAMETERS:     None.
RETURNS:        Nothing.
*/

VT100_Init( );
VT100_ClearScreen( );
VT100_SetCursor(0,0); 
VT100_Logo();

} // end VT100_Boot

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HACKING CODE ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
