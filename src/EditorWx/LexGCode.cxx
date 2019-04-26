// Scintilla source code edit control
/** @file LexForth.cxx
 ** Lexer for FORTH
 **/
// Copyright 1998-2003 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <ctype.h>

#include "LexGCode.h"

#include "..\..\src\stc\scintilla\include\ILexer.h"
#include "..\..\src\stc\scintilla\include\Scintilla.h"
#include "..\..\src\stc\scintilla\include\SciLexer.h"

#include "..\..\src\stc\scintilla\lexlib\WordList.h"
#include "..\..\src\stc\scintilla\lexlib\LexAccessor.h"
#include "..\..\src\stc\scintilla\lexlib\Accessor.h"
#include "..\..\src\stc\scintilla\lexlib\StyleContext.h"
#include "..\..\src\stc\scintilla\lexlib\CharacterSet.h"
#include "..\..\src\stc\scintilla\lexlib\LexerModule.h"

#ifdef SCI_NAMESPACE
using namespace Scintilla;
#endif

static int  get_letter_style(char ch )
{
	ch = toupper(ch);
	switch (ch)
    {
        case 'M': return SCE_GCODE_M;
        case 'G': return SCE_GCODE_G;
        case 'X':
        case 'Y':
        case 'Z':
        case 'A':
        case 'B':
        case 'C':
            return SCE_GCODE_COORDINATE;
		case 'D':
		case 'E':
		case 'F':
		case 'I':
		case 'J':
		case 'K':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'U':
		case 'V':
		case 'W':      
        case 'L':
		case 'H':
		case 'T':
		case 'N':
		  return SCE_GCODE_PARAM;
    }
   return SCE_GCODE_DEFAULT;
}


static bool isALetter(int ch)
{
	return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

static inline bool IsANumChar(int ch) {
	return (ch < 0x80) && (IsADigit(ch) || ch == '.' || ch == 'e' || ch == 'E');
}

static inline bool IsASpaceChar(int ch) {
	return (ch < 0x80) && isspace(ch);
}

static inline bool IsRealVal(int ch)
{
	return  (ch < 0x80) &&  (IsADigit(ch) || ch == '.' || ch == '-');
}

static void ColouriseGCodeDoc(Sci_PositionU startPos, Sci_Position length, int initStyle, WordList *keywordLists[],
	Accessor &styler)
{
	WordList &keywords= *keywordLists[0];
	CharacterSet operators(CharacterSet::setNone, "][*/=+<>");
	StyleContext sc(startPos, length, initStyle, styler);

	for (; sc.More(); sc.Forward())
	{
		// Determine if the current state should terminate.
		if (sc.state == SCE_GCODE_COMMENT) {
			if (sc.atLineEnd) {
				sc.SetState(SCE_GCODE_DEFAULT);
			}
		}
		else if (sc.state == SCE_GCODE_COMMENT_ML) 
		{
			if (sc.ch == ')') {
				sc.ForwardSetState(SCE_GCODE_DEFAULT);
			}
		}
		else if (sc.state == SCE_GCODE_NUMBER)
		{
			if (!IsANumChar(sc.ch))
				sc.SetState(SCE_GCODE_DEFAULT);
		}
		else if (sc.state == SCE_GCODE_VAR)
		{
			if ( !IsADigit(sc.ch) )//sc.ch == ']')
			{
				sc.SetState(SCE_GCODE_DEFAULT);
			}
		}
		else if ((sc.state == SCE_GCODE_IDENTIFIER))
		{
			if (!isALetter(sc.ch))
			{
				char s[124];
				sc.GetCurrent(s, sizeof(s));
				if (keywords.InList(s))
				{
					sc.ChangeState(SCE_GCODE_WORD); 				// It's a keyword, change its state
				}
				sc.SetState(SCE_GCODE_DEFAULT);
			}
		}
		else if ( sc.state != SCE_GCODE_DEFAULT )
			sc.SetState(SCE_GCODE_DEFAULT);
		
		// Determine if a new state should be entered.
		if (sc.state == SCE_GCODE_DEFAULT  )
		{
			if (sc.ch == '/' && sc.chNext == '/') {
				sc.SetState(SCE_GCODE_COMMENT);
			}
			else if (sc.ch == '(') {
				//&& sc.atLineStart || IsASpaceChar(sc.chPrev)) &&
				//(sc.atLineEnd || IsASpaceChar(sc.chNext))) {
				sc.SetState(SCE_GCODE_COMMENT_ML);
			} 
			else if (IsASCII(sc.ch) &&
				(IsADigit(sc.ch) || ((sc.ch == '.' || sc.ch == '-') && IsASCII(sc.chNext) && IsADigit(sc.chNext)))
				) {
				sc.SetState(SCE_GCODE_NUMBER);
			}
			//else if (sc.ch == '[')
			//{
			//	sc.SetState(SCE_GCODE_VAR);
			//}
			else if ((sc.ch == '#') && IsADigit(sc.chNext))
			{
				sc.SetState(SCE_GCODE_VAR);
				while (sc.More() && IsADigit(sc.chNext) )
					sc.Forward();
			}
			else if (operators.Contains(sc.ch))
			{
				sc.SetState(SCE_GCODE_OPERATORS); 
			}
			else 
			{
				int newState = get_letter_style(sc.ch);		
				if (newState == SCE_GCODE_G && IsADigit(sc.chNext))
				{
					sc.SetState(newState);
					while (sc.More() && (IsADigit(sc.chNext) || (sc.chNext == '.')))
						sc.Forward();
				}
				else if (newState == SCE_GCODE_M && IsADigit(sc.chNext))
				{
					sc.SetState(newState);
					while (sc.More() && IsADigit(sc.chNext))
						sc.Forward();
				}
				else if ((newState != SCE_GCODE_DEFAULT) && (IsRealVal(sc.chNext) || (sc.chNext == '#') || (sc.chNext=='[') ))
				{
					sc.SetState(newState);
					//sc.ForwardSetState((sc.chNext == '#') ? SCE_GCODE_VAR : SCE_GCODE_NUMBER);
				}
				else if (isALetter(sc.ch))
				{
					sc.SetState(SCE_GCODE_IDENTIFIER);
				}
			}
		}

	}
	sc.Complete();
}

static void FoldGcodeDoc(Sci_PositionU, Sci_Position, int, WordList *[],
						Accessor &) {
}

static const char * const gcodeWordLists[] = {
			"control keywords",
			"keywords",
			"definition words",
			"prewords with one argument",
			"prewords with two arguments",
			"string definition keywords",
			0,
		};

LexerModule lmGcode(SCLEX_GCODE, ColouriseGCodeDoc, "G Code", FoldGcodeDoc, gcodeWordLists);


