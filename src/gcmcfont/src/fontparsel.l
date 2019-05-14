/*
 * G-code meta compiler - Font conversion
 *
 * Copyright (C) 2015  B. Stultiens
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
%option noinput nounput noyywrap
%option 8bit never-interactive

%{
#include "config.h"

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#else
#define YY_NO_UNISTD_H
#endif
#include <ctype.h>
#include <assert.h>

#include "utils.h"
#include "glyphdata.h"
#include "fontparsey.h"
#include "gcmcfont.h"
 
/* This is here to cast the result to ssize_t so that the "< 0" comparison works */
/* The rest is a copy of the generated scanner code */
#define YY_INPUT(buf,result,max_size) \
	errno = 0; \
	while((size_t)(result = read( fileno(yyin), (char *) buf, max_size )) < 0) { \
		if(errno != EINTR) { \
			YY_FATAL_ERROR("input in flex scanner failed"); \
			break; \
		} \
		errno = 0; \
		clearerr(yyin); \
	}

int linenr = 1;
int charnr = 1;
int prevlinenr = 1;
int prevcharnr = 1;
const char *filename;

/* Always update the current character position within a line */
#define YY_USER_ACTION	do { prevlinenr = linenr; prevcharnr = charnr; charnr += yyleng; } while(0);

#pragma warning(disable:4996)

%}

/* Some shortcut definitions */
ws	[ \f\t\r]
n	[0-9]
h	[0-9a-fA-F]

%%
#.*			;	/* Skip comments */
{ws}+			;	/* Skip whitespace */
glyph			return tGLYPH;
left			return tLEFT;
right			return tRIGHT;
stroke			return tSTROKE;
[a-zA-Z_][a-zA-Z_0-9]*	{ yyerror("Unrecognized word '%s'", yytext); }
[+-]?0[xX]{h}+		{ yylval.i = strtol(yytext, NULL, 16); return tNUMBER; }
[+-]?0[xX]		{ yyerror("Invalid hexadecimal value"); }
[+-]?{n}+		{ yylval.i = strtol(yytext, NULL, 10); return tNUMBER; }
[+-]			{ yyerror("Invalid number"); }
[[\]{}(),]		return *yytext;
\n			linenr++; charnr = 1;
.			{
				/* Catch all rule to find any unmatched text */
				yyerror("internal: Unmatched text '%c' (0x%02x)", isprint((unsigned char)*yytext) ? *yytext : '.', *yytext);
			}
%%

