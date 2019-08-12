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
	return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch =='_');
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
	WordList &keywords1= *keywordLists[0];
	WordList &keywords2 = *keywordLists[1];
	WordList &keywords3 = *keywordLists[2];
	
	CharacterSet operators(CharacterSet::setNone, "*/=+<>");
	StyleContext sctmp(startPos, length, initStyle, styler);

	//char buf[256];
	//int i = 0;
	//for (; sctmp.More(); sctmp.Forward())
	//{
	//	if (sctmp.ch && i < 255 )
	//	 buf[i++] = sctmp.ch;
	//}

	int style = startPos == 0 ? SCE_GCMC_DEFAULT : styler.StyleAt(startPos-1);

	StyleContext sc(startPos, length, style/*SCE_GCMC_DEFAULT*/, styler);

	for (; sc.More(); sc.Forward())
	{
		// Determine if the current state should terminate.
		if (sc.state == SCE_GCMC_COMMENT) {
			if (sc.atLineEnd) {
				sc.SetState(SCE_GCMC_DEFAULT);
			}
		}
		else if (sc.state == SCE_GCMC_COMMENT_ML) 
		{
			if (sc.ch == '*' && sc.chNext == '/') 
			{
				sc.Forward();
				sc.ForwardSetState(SCE_GCMC_DEFAULT);
			}
		}
		else if (sc.state == SCE_GCMC_STRING)
		{
			if (sc.ch == '"')
			{
				sc.ForwardSetState(SCE_GCMC_DEFAULT);
			}
		}
		else if (sc.state == SCE_GCMC_NUMBER)
		{
			if (!IsANumChar(sc.ch))
				sc.SetState(SCE_GCMC_DEFAULT);
		}
		//else if (sc.state == SCE_GCMC_VAR)
		//{
		//	if ( sc.ch == ']')
		//	{
		//		sc.SetState(SCE_GCMC_DEFAULT);
		//	}
		//}
		else if ((sc.state == SCE_GCMC_IDENTIFIER)  )
		{
			if (!isALetter(sc.ch) && !IsADigit(sc.ch))
			{
				char s[124];
				sc.GetCurrent(s, sizeof(s));
				if (keywords1.InList(s))
				{
					sc.ChangeState(SCE_GCMC_WORD1); 				// It's a keyword, change its state
				}
				else if (keywords2.InList(s))
				{
					sc.ChangeState(SCE_GCMC_WORD2); 				// It's a keyword, change its state
				}
				else if (keywords3.InList(s))
				{
					sc.ChangeState(SCE_GCMC_WORD3); 				// It's a keyword, change its state
				}				
				sc.SetState(SCE_GCMC_DEFAULT);
			}
		}
		else if ( sc.state != SCE_GCMC_DEFAULT )
			sc.SetState(SCE_GCMC_DEFAULT);
		
		// Determine if a new state should be entered.
		if (sc.state == SCE_GCMC_DEFAULT  ) 
		{
			if (sc.ch == '/' && sc.chNext == '/') {
				sc.SetState(SCE_GCMC_COMMENT);
			}
			else if (sc.ch == '/' && sc.chNext == '*') {
				sc.SetState(SCE_GCMC_COMMENT_ML);
			} 
			else if (sc.ch == '"') {
				sc.SetState(SCE_GCMC_STRING);
			}
			
			else if (IsASCII(sc.ch) &&
				(IsADigit(sc.ch) || ((sc.ch == '.' || sc.ch == '-') && IsASCII(sc.chNext) && IsADigit(sc.chNext)))
				) {
				sc.SetState(SCE_GCMC_NUMBER);
			}
			else if (sc.ch == '[' || sc.ch == ']')
			{
				sc.SetState(SCE_GCMC_VAR);
			}
			else if (operators.Contains(sc.ch))
			{
				sc.SetState(SCE_GCMC_OPERATORS);
			}
			else  if (isALetter(sc.ch))
			{
				sc.SetState(SCE_GCMC_IDENTIFIER);
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


