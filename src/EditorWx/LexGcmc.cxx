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

static void ColouriseGcmcDoc(Sci_PositionU startPos, Sci_Position length, int initStyle, WordList *keywordLists[],
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
			if (sc.ch == '*' && sc.chNext == '/') {
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
			if ( sc.ch == ']')
			{
				sc.SetState(SCE_GCODE_DEFAULT);
			}
		}
		else if ((sc.state == SCE_GCODE_IDENTIFIER) && !isALetter(sc.ch) )
		{
			char s[124];
			sc.GetCurrent(s, sizeof(s));
			if (keywords.InList(s))
			{
				sc.ChangeState(SCE_GCODE_WORD1); 				// It's a keyword, change its state
			}
			sc.SetState(SCE_GCODE_DEFAULT);
		}
		else if ( sc.state != SCE_GCODE_DEFAULT )
			sc.SetState(SCE_GCODE_DEFAULT);
		
		// Determine if a new state should be entered.
		if (sc.state == SCE_GCODE_DEFAULT  )
		{
			if (sc.ch == '/' && sc.chNext == '/') {
				sc.SetState(SCE_GCODE_COMMENT);
			}
			else if (sc.ch == '/' && sc.chNext == '*') {
				sc.SetState(SCE_GCODE_COMMENT_ML);
			} 
			else if (IsASCII(sc.ch) &&
				(IsADigit(sc.ch) || ((sc.ch == '.' || sc.ch == '-') && IsASCII(sc.chNext) && IsADigit(sc.chNext)))
				) {
				sc.SetState(SCE_GCODE_NUMBER);
			}
			else if (sc.ch == '[')
			{
				sc.SetState(SCE_GCODE_VAR);
			}
			else if (operators.Contains(sc.ch))
			{
				sc.SetState(SCE_GCODE_OPERATORS); 
			}
			else  if (isALetter(sc.ch))
			{
				sc.SetState(SCE_GCODE_IDENTIFIER);
			}
		}

	}
	sc.Complete();
}

static void FoldGcmcDoc(Sci_PositionU, Sci_Position, int, WordList *[],
						Accessor &) {
}

static const char * const gcmcWordLists[] = {
			"control keywords",
			"keywords",
			"definition words",
			"prewords with one argument",
			"prewords with two arguments",
			"string definition keywords",
			0,
		};

LexerModule lmGcmc(SCLEX_GCMC, ColouriseGcmcDoc, "GCMC", FoldGcmcDoc, gcmcWordLists);


