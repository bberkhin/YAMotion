/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_GRAMMARY_H_INCLUDED
# define YY_YY_GRAMMARY_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     FUNCTION = 258,
     FOR = 259,
     FOREACH = 260,
     DO = 261,
     WHILE = 262,
     IF = 263,
     ELIF = 264,
     ELSE = 265,
     BREAK = 266,
     CONTINUE = 267,
     RETURN = 268,
     INCLUDE = 269,
     LOCAL = 270,
     REPEAT = 271,
     CONST = 272,
     TOPEN = 273,
     TCLOSE = 274,
     MM = 275,
     MIL = 276,
     IN = 277,
     DEG = 278,
     RAD = 279,
     IDENT = 280,
     STRING = 281,
     NUMBER = 282,
     FLOAT = 283,
     BXORASSIGN = 284,
     BANDASSIGN = 285,
     BORASSIGN = 286,
     SUBORASSIGN = 287,
     ADDORASSIGN = 288,
     SHRASSIGN = 289,
     SHLASSIGN = 290,
     MODASSIGN = 291,
     DIVASSIGN = 292,
     MULASSIGN = 293,
     ADDASSIGN = 294,
     SUBASSIGN = 295,
     LOR = 296,
     LAND = 297,
     NE = 298,
     EQ = 299,
     GE = 300,
     LE = 301,
     GT = 302,
     LT = 303,
     SHR = 304,
     SHL = 305,
     SUBOR = 306,
     ADDOR = 307,
     DEC = 308,
     INC = 309,
     UPM = 310,
     UID = 311
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 76 "grammary.y"

	wchar_t		*str;
	double		d;
	int		i;
	node_t		*node;


/* Line 2058 of yacc.c  */
#line 121 "grammary.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_GRAMMARY_H_INCLUDED  */
