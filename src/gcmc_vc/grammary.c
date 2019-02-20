/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 19 "grammary.y"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "utils.h"
#include "grammartypes.h"
#include "builtin.h"
#include "interpreter.h"

#define YYDEBUG 1

#define myassert(x)	do { \
				if(!(x)) { \
					yyfatal("Assertion failed:(%s:%d): %s", __FILE__, __LINE__, #x); \
				} \
			} while(0);
int yylex(void);

static wchar_t *funcname;

static node_t *newnode(int type);
static node_t *alist_new(wchar_t *id, int isref, node_t *e);
static node_t *alist_add(node_t *l, wchar_t *id, int isref, node_t *e);
static node_t *lvar_new(wchar_t *id, node_t *e);
static node_t *cvar_new(wchar_t *id, node_t *e);
static node_t *elist_new(node_t *e);
static node_t *elist_add(node_t *l, node_t *e);
static node_t *vlist_new(node_t *v);
static node_t *vlist_add(node_t *l, node_t *v);
static node_t *vec_new(node_t *e, int allownull);
static node_t *vec_add(node_t *v, node_t *e);
static node_t *node_new_assign(node_t *lv, int op, node_t *rv);
static node_t *node_new(int op, node_t *e);
static node_t *node_add(node_t *tailnode, node_t *newnode);
static node_t *expr_new(node_t *l, node_t *r, int op);
static node_t *expr_new_unary(node_t *id, int op);
static node_t *expr_new_tern(node_t *c, node_t *l, node_t *r, int op);
static node_t *expr_new_call(wchar_t *id, node_t *e);
static node_t *expr_new_id(wchar_t *id);
static node_t *expr_new_idx(node_t *d, node_t *e);
static node_t *expr_new_idxid(node_t *d, wchar_t *id);
static node_t *expr_new_int(int i, int unit);
static node_t *expr_new_flt(double d, int unit);
static node_t *expr_new_str(wchar_t *str);
static node_t *pushtag(node_t *n);
static node_t *poptag(void);
static node_t *gethead(node_t *n);
static void checkfuncname(const wchar_t *fn);
static void check_useless(const node_t *n);
static void check_const_expr(const node_t *n);
static void check_boolean_expr(const node_t *n);

node_t *scripthead;


/* Line 371 of yacc.c  */
#line 125 "grammary.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "grammary.h".  */
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
/* Line 387 of yacc.c  */
#line 76 "grammary.y"

	wchar_t		*str;
	double		d;
	int		i;
	node_t		*node;


/* Line 387 of yacc.c  */
#line 232 "grammary.c"
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

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 260 "grammary.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  87
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1516

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  77
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  216
/* YYNRULES -- Number of states.  */
#define YYNSTATES  356

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   311

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    66,     2,     2,     2,    63,    48,     2,
      72,    73,    61,    57,    75,    58,    70,    62,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    43,    74,
       2,    29,     2,    42,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    69,     2,    76,    47,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    46,     2,    67,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    44,    45,    49,    50,
      51,    52,    53,    54,    55,    56,    59,    60,    64,    65,
      68,    71
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     6,     9,    11,    14,    16,    22,
      28,    33,    37,    40,    43,    46,    50,    54,    56,    58,
      62,    66,    70,    73,    75,    76,    78,    82,    88,    92,
      93,    96,    99,   100,   102,   104,   108,   112,   115,   118,
     119,   122,   123,   125,   127,   128,   130,   132,   134,   136,
     138,   140,   143,   146,   148,   158,   168,   176,   183,   189,
     194,   198,   201,   211,   219,   229,   237,   244,   250,   255,
     259,   262,   274,   286,   296,   305,   312,   318,   323,   326,
     334,   342,   348,   353,   357,   360,   370,   380,   389,   397,
     404,   410,   415,   418,   426,   434,   440,   445,   448,   457,
     470,   483,   494,   502,   508,   513,   517,   520,   524,   527,
     530,   534,   537,   540,   543,   546,   547,   550,   558,   566,
     572,   577,   581,   584,   589,   590,   592,   594,   598,   602,
     605,   608,   611,   614,   617,   621,   625,   629,   633,   637,
     641,   645,   649,   653,   657,   661,   665,   669,   673,   677,
     681,   685,   689,   693,   697,   701,   707,   709,   714,   718,
     720,   723,   726,   728,   730,   732,   735,   738,   741,   744,
     748,   752,   756,   760,   764,   768,   772,   776,   780,   784,
     788,   792,   796,   800,   804,   808,   812,   816,   820,   824,
     828,   832,   836,   840,   844,   848,   849,   851,   853,   855,
     857,   859,   860,   862,   867,   870,   873,   878,   880,   884,
     887,   891,   895,   897,   901,   905,   907
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      78,     0,    -1,    -1,    79,    -1,    79,     1,    -1,    80,
      -1,    79,    80,    -1,   100,    -1,    14,    72,    26,    73,
      74,    -1,    14,    72,    26,    73,     1,    -1,    14,    72,
      26,     1,    -1,    14,    72,     1,    -1,    14,     1,    -1,
      91,    74,    -1,    91,     1,    -1,    15,    87,    74,    -1,
      17,    81,    74,    -1,    74,    -1,    82,    -1,    81,    75,
      82,    -1,    25,    29,   106,    -1,    25,    29,     1,    -1,
      25,     1,    -1,     1,    -1,    -1,    84,    -1,    86,    25,
      85,    -1,    84,    75,    86,    25,    85,    -1,    84,    75,
       1,    -1,    -1,    29,   106,    -1,    29,     1,    -1,    -1,
      48,    -1,    88,    -1,    87,    75,    88,    -1,    87,    75,
       1,    -1,    25,    89,    -1,    25,     1,    -1,    -1,    29,
     106,    -1,    -1,    79,    -1,   106,    -1,    -1,    91,    -1,
       5,    -1,    16,    -1,     4,    -1,     7,    -1,     6,    -1,
       3,    25,    -1,     3,     1,    -1,   106,    -1,    93,    72,
     106,    74,    25,    73,    18,    90,    19,    -1,    93,    72,
     106,    74,    25,    73,    18,    90,     1,    -1,    93,    72,
     106,    74,    25,    73,     1,    -1,    93,    72,   106,    74,
      25,     1,    -1,    93,    72,   106,    74,     1,    -1,    93,
      72,   106,     1,    -1,    93,    72,     1,    -1,    93,     1,
      -1,    94,    72,   106,    74,    25,    73,    18,    90,    19,
      -1,    94,    72,   106,    73,    18,    90,    19,    -1,    94,
      72,   106,    74,    25,    73,    18,    90,     1,    -1,    94,
      72,   106,    74,    25,    73,     1,    -1,    94,    72,   106,
      74,    25,     1,    -1,    94,    72,   106,    74,     1,    -1,
      94,    72,   106,     1,    -1,    94,    72,     1,    -1,    94,
       1,    -1,    95,    72,    92,    74,    99,    74,    92,    73,
      18,    90,    19,    -1,    95,    72,    92,    74,    99,    74,
      92,    73,    18,    90,     1,    -1,    95,    72,    92,    74,
      99,    74,    92,    73,     1,    -1,    95,    72,    92,    74,
      99,    74,    92,     1,    -1,    95,    72,    92,    74,    99,
       1,    -1,    95,    72,    92,    74,     1,    -1,    95,    72,
      92,     1,    -1,    95,     1,    -1,    96,    72,    99,    73,
      18,    90,    19,    -1,    96,    72,    99,    73,    18,    90,
       1,    -1,    96,    72,    99,    73,     1,    -1,    96,    72,
      99,     1,    -1,    96,    72,     1,    -1,    96,     1,    -1,
      97,    18,    90,    19,     7,    72,    99,    73,    74,    -1,
      97,    18,    90,    19,     7,    72,    99,    73,     1,    -1,
      97,    18,    90,    19,     7,    72,    99,     1,    -1,    97,
      18,    90,    19,     7,    72,     1,    -1,    97,    18,    90,
      19,     7,     1,    -1,    97,    18,    90,    19,     1,    -1,
      97,    18,    90,     1,    -1,    97,     1,    -1,    98,    72,
      83,    73,    18,    90,    19,    -1,    98,    72,    83,    73,
      18,    90,     1,    -1,    98,    72,    83,    73,     1,    -1,
      98,    72,    83,     1,    -1,    98,     1,    -1,     8,    72,
      99,    73,    18,    90,    19,   101,    -1,     8,    72,    99,
      73,    18,    90,    19,   101,    10,    18,    90,    19,    -1,
       8,    72,    99,    73,    18,    90,    19,   101,    10,    18,
      90,     1,    -1,     8,    72,    99,    73,    18,    90,    19,
     101,    10,     1,    -1,     8,    72,    99,    73,    18,    90,
       1,    -1,     8,    72,    99,    73,     1,    -1,     8,    72,
      99,     1,    -1,     8,    72,     1,    -1,     8,     1,    -1,
      13,   106,    74,    -1,    13,    74,    -1,    13,     1,    -1,
      13,   106,     1,    -1,    11,    74,    -1,    11,     1,    -1,
      12,    74,    -1,    12,     1,    -1,    -1,   101,   102,    -1,
       9,    72,    99,    73,    18,    90,    19,    -1,     9,    72,
      99,    73,    18,    90,     1,    -1,     9,    72,    99,    73,
       1,    -1,     9,    72,    99,     1,    -1,     9,    72,     1,
      -1,     9,     1,    -1,    25,    72,   104,    73,    -1,    -1,
     105,    -1,   106,    -1,   105,    75,   106,    -1,   105,    75,
       1,    -1,   105,     1,    -1,    57,   106,    -1,    58,   106,
      -1,    66,   106,    -1,    67,   106,    -1,    72,   106,    73,
      -1,   106,    57,   106,    -1,   106,    60,   106,    -1,   106,
      58,   106,    -1,   106,    59,   106,    -1,   106,    61,   106,
      -1,   106,    62,   106,    -1,   106,    63,   106,    -1,   106,
      50,   106,    -1,   106,    49,   106,    -1,   106,    53,   106,
      -1,   106,    54,   106,    -1,   106,    51,   106,    -1,   106,
      52,   106,    -1,   106,    45,   106,    -1,   106,    44,   106,
      -1,   106,    56,   106,    -1,   106,    55,   106,    -1,   106,
      48,   106,    -1,   106,    46,   106,    -1,   106,    47,   106,
      -1,   106,    42,   106,    43,   106,    -1,   103,    -1,   106,
      69,   106,    76,    -1,   106,    70,    25,    -1,    25,    -1,
      27,   107,    -1,    28,   107,    -1,    26,    -1,   111,    -1,
     109,    -1,    65,   106,    -1,    64,   106,    -1,   106,    65,
      -1,   106,    64,    -1,   106,    29,   106,    -1,   106,    40,
     106,    -1,   106,    34,   106,    -1,   106,    41,   106,    -1,
     106,    33,   106,    -1,   106,    39,   106,    -1,   106,    38,
     106,    -1,   106,    37,   106,    -1,   106,    36,   106,    -1,
     106,    35,   106,    -1,   106,    32,   106,    -1,   106,    31,
     106,    -1,   106,    30,   106,    -1,   106,    29,     1,    -1,
     106,    40,     1,    -1,   106,    34,     1,    -1,   106,    41,
       1,    -1,   106,    33,     1,    -1,   106,    39,     1,    -1,
     106,    38,     1,    -1,   106,    37,     1,    -1,   106,    36,
       1,    -1,   106,    35,     1,    -1,   106,    32,     1,    -1,
     106,    31,     1,    -1,   106,    30,     1,    -1,    -1,    20,
      -1,    21,    -1,    22,    -1,    23,    -1,    24,    -1,    -1,
      75,    -1,    18,   110,   108,    19,    -1,    18,    19,    -1,
      18,     1,    -1,    18,   110,   108,     1,    -1,   106,    -1,
     110,    75,   106,    -1,    69,    76,    -1,    69,   112,    76,
      -1,    69,   112,     1,    -1,   113,    -1,   112,    75,   113,
      -1,   112,    75,     1,    -1,    58,    -1,   106,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   117,   117,   118,   119,   122,   123,   126,   127,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   146,   147,
     150,   151,   152,   153,   156,   157,   160,   161,   162,   165,
     166,   167,   170,   171,   174,   175,   176,   179,   180,   183,
     184,   187,   188,   191,   194,   195,   198,   201,   204,   207,
     210,   213,   219,   222,   225,   231,   232,   233,   234,   235,
     236,   237,   238,   244,   250,   251,   252,   253,   254,   255,
     256,   257,   264,   265,   266,   267,   268,   269,   270,   271,
     276,   277,   278,   279,   280,   281,   286,   287,   288,   289,
     290,   291,   292,   293,   300,   301,   302,   303,   304,   310,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   334,   335,   338,   339,   340,
     341,   342,   343,   346,   349,   350,   353,   354,   355,   356,
     359,   360,   361,   362,   363,   364,   365,   366,   367,   368,
     369,   370,   371,   372,   373,   374,   375,   376,   377,   378,
     379,   380,   381,   382,   383,   384,   385,   386,   387,   388,
     389,   390,   391,   392,   393,   394,   395,   396,   397,   398,
     399,   400,   401,   402,   403,   404,   405,   406,   407,   408,
     409,   410,   411,   412,   413,   414,   415,   416,   417,   418,
     419,   420,   421,   422,   423,   426,   427,   428,   429,   430,
     431,   434,   435,   438,   439,   440,   441,   444,   445,   448,
     449,   450,   453,   454,   455,   458,   459
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FUNCTION", "FOR", "FOREACH", "DO",
  "WHILE", "IF", "ELIF", "ELSE", "BREAK", "CONTINUE", "RETURN", "INCLUDE",
  "LOCAL", "REPEAT", "CONST", "TOPEN", "TCLOSE", "MM", "MIL", "IN", "DEG",
  "RAD", "IDENT", "STRING", "NUMBER", "FLOAT", "'='", "BXORASSIGN",
  "BANDASSIGN", "BORASSIGN", "SUBORASSIGN", "ADDORASSIGN", "SHRASSIGN",
  "SHLASSIGN", "MODASSIGN", "DIVASSIGN", "MULASSIGN", "ADDASSIGN",
  "SUBASSIGN", "'?'", "':'", "LOR", "LAND", "'|'", "'^'", "'&'", "NE",
  "EQ", "GE", "LE", "GT", "LT", "SHR", "SHL", "'+'", "'-'", "SUBOR",
  "ADDOR", "'*'", "'/'", "'%'", "DEC", "INC", "'!'", "'~'", "UPM", "'['",
  "'.'", "UID", "'('", "')'", "';'", "','", "']'", "$accept", "file",
  "lines", "line", "cvars", "cvar", "optarglist", "arglist", "optv",
  "optref", "locals", "local", "optassgn", "optstmts", "stmt", "optstmt",
  "foreach", "repeat", "for", "while", "do", "function", "boolexpr",
  "compound", "optelif", "elif", "call", "optargs", "args", "expr",
  "optunit", "optcomma", "veclist", "vlist", "vector", "nums", "anynum", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    61,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,    63,    58,   296,   297,   124,    94,    38,   298,
     299,   300,   301,   302,   303,   304,   305,    43,    45,   306,
     307,    42,    47,    37,   308,   309,    33,   126,   310,    91,
      46,   311,    40,    41,    59,    44,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    77,    78,    78,    78,    79,    79,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    81,    81,
      82,    82,    82,    82,    83,    83,    84,    84,    84,    85,
      85,    85,    86,    86,    87,    87,    87,    88,    88,    89,
      89,    90,    90,    91,    92,    92,    93,    94,    95,    96,
      97,    98,    98,    99,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   101,   101,   102,   102,   102,
     102,   102,   102,   103,   104,   104,   105,   105,   105,   105,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   107,   107,   107,   107,   107,
     107,   108,   108,   109,   109,   109,   109,   110,   110,   111,
     111,   111,   112,   112,   112,   113,   113
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     2,     1,     2,     1,     5,     5,
       4,     3,     2,     2,     2,     3,     3,     1,     1,     3,
       3,     3,     2,     1,     0,     1,     3,     5,     3,     0,
       2,     2,     0,     1,     1,     3,     3,     2,     2,     0,
       2,     0,     1,     1,     0,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     9,     9,     7,     6,     5,     4,
       3,     2,     9,     7,     9,     7,     6,     5,     4,     3,
       2,    11,    11,     9,     8,     6,     5,     4,     2,     7,
       7,     5,     4,     3,     2,     9,     9,     8,     7,     6,
       5,     4,     2,     7,     7,     5,     4,     2,     8,    12,
      12,    10,     7,     5,     4,     3,     2,     3,     2,     2,
       3,     2,     2,     2,     2,     0,     2,     7,     7,     5,
       4,     3,     2,     4,     0,     1,     1,     3,     3,     2,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     5,     1,     4,     3,     1,
       2,     2,     1,     1,     1,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     1,     1,     1,     1,
       1,     0,     1,     4,     2,     2,     4,     1,     3,     2,
       3,     3,     1,     3,     3,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,    48,    46,    50,    49,     0,     0,     0,     0,
       0,     0,    47,     0,     0,   159,   162,   195,   195,     0,
       0,     0,     0,     0,     0,     0,     0,    17,     0,     0,
       5,     0,     0,     0,     0,     0,     0,     0,     7,   156,
      43,   164,   163,    52,    51,   106,     0,   112,   111,   114,
     113,   109,   108,     0,    12,     0,     0,     0,    34,    23,
       0,     0,    18,   205,   204,   207,   201,   124,   196,   197,
     198,   199,   200,   160,   161,   130,   131,   166,   165,   132,
     133,   215,   209,   216,     0,   212,     0,     1,     4,     6,
      14,    13,    61,     0,    70,     0,    78,    44,    84,     0,
      92,    41,    97,    24,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   168,   167,
       0,     0,   105,     0,    53,   110,   107,    11,     0,    38,
       0,    37,    15,     0,    22,     0,    16,     0,   202,     0,
       0,     0,   126,   211,     0,   210,   134,    60,     0,    69,
       0,    45,     0,    83,     0,    42,     0,    33,     0,    25,
       0,   182,   169,   194,   181,   193,   180,   192,   179,   186,
     173,   184,   171,   191,   178,   190,   177,   189,   176,   188,
     175,   187,   174,   183,   170,   185,   172,     0,   149,   148,
     153,   154,   152,   143,   142,   146,   147,   144,   145,   151,
     150,   135,   137,   138,   136,   139,   140,   141,     0,   158,
     104,     0,    10,     0,    40,    36,    35,    21,    20,    19,
     208,   206,   203,   123,   129,     0,   214,   213,    59,     0,
      68,     0,     0,    77,     0,    82,     0,    91,     0,    96,
       0,     0,    29,     0,   157,   103,    41,     9,     8,   128,
     127,    58,     0,    41,    67,     0,    76,     0,    81,    41,
      90,     0,    95,    41,    28,     0,     0,    26,   155,     0,
      57,     0,     0,    66,     0,    75,    44,     0,    89,     0,
       0,    29,    31,    30,   102,   115,    56,    41,    63,    65,
      41,     0,    80,    79,    88,     0,    94,    93,    27,    98,
       0,     0,    74,     0,    87,     0,     0,     0,   116,    55,
      54,    64,    62,    73,    41,    86,    85,   122,     0,   101,
      41,     0,   121,     0,     0,    72,    71,   120,     0,   100,
      99,   119,    41,     0,   118,   117
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    28,   175,    30,    61,    62,   178,   179,   287,   180,
      57,    58,   151,   176,    31,   172,    32,    33,    34,    35,
      36,    37,   143,    38,   319,   328,    39,   160,   161,    40,
      73,   159,    41,    66,    42,    84,    85
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -137
static const yytype_int16 yypact[] =
{
     488,    24,  -137,  -137,  -137,  -137,     5,     8,    20,   234,
      17,    11,  -137,    26,   506,   -41,  -137,   140,   140,  1124,
    1124,  1124,  1124,  1124,  1124,  1090,  1124,  -137,    43,   206,
    -137,    55,    82,   143,   157,   165,    70,   166,  -137,  -137,
    1303,  -137,  -137,  -137,  -137,  -137,   522,  -137,  -137,  -137,
    -137,  -137,  -137,   351,  -137,    22,     6,   -33,  -137,  -137,
      21,     0,  -137,  -137,  -137,  1303,   -42,  1124,  -137,  -137,
    -137,  -137,  -137,  -137,  -137,    83,    83,    83,    83,    83,
      83,  1124,  -137,  1303,     3,  -137,  1216,  -137,  -137,  -137,
    -137,  -137,  -137,   540,  -137,   575,  -137,  1124,  -137,   595,
    -137,   488,  -137,    -1,   630,   648,   664,   682,   717,   737,
     772,   790,   806,   824,   859,   879,   914,  1124,  1124,  1124,
    1124,  1124,  1124,  1124,  1124,  1124,  1124,  1124,  1124,  1124,
    1124,  1124,  1124,  1124,  1124,  1124,  1124,  1124,  -137,  -137,
    1124,    13,  -137,    19,  1303,  -137,  -137,  -137,    63,  -137,
    1124,  -137,  -137,    27,  -137,   932,  -137,    26,  1124,    25,
      -8,    18,  1303,  -137,   948,  -137,  -137,  -137,   416,  -137,
     286,  -137,    58,  -137,    65,   488,    38,  -137,    66,   -29,
      51,  -137,  1303,  -137,  1303,  -137,  1303,  -137,  1303,  -137,
    1303,  -137,  1303,  -137,  1303,  -137,  1303,  -137,  1303,  -137,
    1303,  -137,  1303,  -137,  1303,  -137,  1303,  1261,   130,  1357,
    1381,  1404,  1426,  1446,  1446,   306,   306,   306,   306,   369,
     369,   457,   457,   457,   457,   240,   240,   240,  1168,  -137,
    -137,   226,  -137,    59,  1303,  -137,  -137,  -137,  1303,  -137,
    1303,  -137,  -137,  -137,  -137,   966,  -137,  -137,  -137,    28,
    -137,   132,    29,  -137,  1001,  -137,   250,  -137,    33,  -137,
     256,     7,    40,  1124,  -137,  -137,   488,  -137,  -137,  -137,
    1303,  -137,    67,   488,  -137,    69,  -137,    60,  -137,   488,
    -137,   167,  -137,   488,  -137,   171,  1021,  -137,  1332,    44,
    -137,   265,   146,  -137,   268,  -137,  1124,   150,  -137,  1056,
     207,    40,  -137,  1303,  -137,  -137,  -137,   488,  -137,  -137,
     488,    72,  -137,  -137,  -137,    84,  -137,  -137,  -137,   163,
     224,   227,  -137,   275,  -137,    61,   169,   278,  -137,  -137,
    -137,  -137,  -137,  -137,   488,  -137,  -137,  -137,  1074,  -137,
     488,   229,  -137,    86,   246,  -137,  -137,  -137,   284,  -137,
    -137,  -137,   488,   248,  -137,  -137
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -137,  -137,   197,   -27,  -137,    46,  -137,  -137,   -96,   -19,
    -137,    97,  -137,  -136,   -94,   -43,  -137,  -137,  -137,  -137,
    -137,  -137,   -98,  -137,  -137,  -137,  -137,  -137,  -137,    -9,
     237,  -137,  -137,  -137,  -137,  -137,    92
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -126
static const yytype_int16 yytable[] =
{
      53,   174,    89,   171,   163,    65,    45,   149,   284,    47,
      75,    76,    77,    78,    79,    80,    83,    86,    54,   244,
     230,    49,   154,   147,   -32,    43,   241,    59,   235,   271,
     274,    67,   -32,   158,   280,   150,    56,   144,   229,   257,
     281,   152,   153,    87,   242,   304,   261,   177,   148,    44,
     155,    60,    56,   272,   275,   177,    90,   258,   162,   253,
     267,   295,   335,   305,   232,   243,   255,   259,   290,   286,
     293,   100,    76,   322,   156,   157,   262,    46,   164,   165,
     -39,   -39,    48,    92,   168,   324,   170,   347,   101,    55,
     144,  -125,   231,   245,    50,   182,   184,   186,   188,   190,
     192,   194,   196,   198,   200,   202,   204,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,    91,
     289,   228,   254,   268,   296,   336,   233,   292,   256,   260,
     291,   234,   294,   297,    94,   323,   238,   300,    89,   240,
     273,   312,   140,   141,    93,    83,   277,   325,    96,   348,
      68,    69,    70,    71,    72,   308,    98,   102,   298,   313,
     337,   320,   326,   327,   321,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   301,    29,   341,   140,
     141,   315,   171,   239,   344,   318,    -3,    88,   316,     1,
       2,     3,     4,     5,     6,    95,   353,     7,     8,     9,
      10,    11,    12,    13,    14,   329,   317,   265,   331,    97,
     345,    15,    16,    17,    18,    51,   270,    99,   103,   299,
     343,   338,   285,   330,   266,   144,   332,   349,   346,   354,
     236,   278,    14,   311,   288,    74,   247,   282,     0,    15,
      16,    17,    18,    19,    20,   350,   306,   355,   279,   309,
      21,    22,    23,    24,   283,    25,   333,   303,    26,   339,
      27,     0,     0,   307,     0,   351,   310,   250,     0,     0,
     144,    19,    20,   334,     0,     0,   340,     0,    21,    22,
      23,    24,   352,    25,   138,   139,    26,     0,    52,   140,
     141,     0,     0,     0,     0,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   144,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   145,     0,     0,   140,   141,     0,     0,   251,
     252,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,     0,     0,     0,   140,   141,     0,     0,     0,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,     0,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   248,     0,     0,
     140,   141,     0,     0,     0,   146,   131,   132,   133,   134,
     135,   136,   137,   138,   139,     0,     0,     0,   140,   141,
       0,     0,     0,     0,     0,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,     0,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,     0,     0,     0,   140,   141,     0,     0,     0,
     249,     1,     2,     3,     4,     5,     6,     0,     0,     7,
       8,     9,    10,    11,    12,    13,    14,    63,     0,     0,
       0,     0,     0,    15,    16,    17,    18,     0,   135,   136,
     137,   138,   139,   142,    14,    64,   140,   141,     0,     0,
       0,    15,    16,    17,    18,     0,     0,     0,     0,     0,
      14,   167,     0,     0,     0,    19,    20,    15,    16,    17,
      18,     0,    21,    22,    23,    24,     0,    25,    14,     0,
      26,     0,    27,    19,    20,    15,    16,    17,    18,     0,
      21,    22,    23,    24,     0,    25,   169,     0,    26,    19,
      20,     0,     0,     0,     0,     0,    21,    22,    23,    24,
       0,    25,     0,    14,    26,     0,   173,    19,    20,     0,
      15,    16,    17,    18,    21,    22,    23,    24,     0,    25,
       0,     0,    26,    14,     0,     0,     0,     0,     0,     0,
      15,    16,    17,    18,     0,     0,     0,     0,     0,     0,
       0,   181,    19,    20,     0,     0,     0,     0,     0,    21,
      22,    23,    24,     0,    25,     0,     0,    26,    14,   183,
       0,     0,    19,    20,     0,    15,    16,    17,    18,    21,
      22,    23,    24,     0,    25,   185,    14,    26,     0,     0,
       0,     0,     0,    15,    16,    17,    18,     0,     0,     0,
       0,     0,    14,   187,     0,     0,     0,    19,    20,    15,
      16,    17,    18,     0,    21,    22,    23,    24,     0,    25,
      14,     0,    26,     0,     0,    19,    20,    15,    16,    17,
      18,     0,    21,    22,    23,    24,     0,    25,   189,     0,
      26,    19,    20,     0,     0,     0,     0,     0,    21,    22,
      23,    24,     0,    25,     0,    14,    26,     0,   191,    19,
      20,     0,    15,    16,    17,    18,    21,    22,    23,    24,
       0,    25,     0,     0,    26,    14,     0,     0,     0,     0,
       0,     0,    15,    16,    17,    18,     0,     0,     0,     0,
       0,     0,     0,   193,    19,    20,     0,     0,     0,     0,
       0,    21,    22,    23,    24,     0,    25,     0,     0,    26,
      14,   195,     0,     0,    19,    20,     0,    15,    16,    17,
      18,    21,    22,    23,    24,     0,    25,   197,    14,    26,
       0,     0,     0,     0,     0,    15,    16,    17,    18,     0,
       0,     0,     0,     0,    14,   199,     0,     0,     0,    19,
      20,    15,    16,    17,    18,     0,    21,    22,    23,    24,
       0,    25,    14,     0,    26,     0,     0,    19,    20,    15,
      16,    17,    18,     0,    21,    22,    23,    24,     0,    25,
     201,     0,    26,    19,    20,     0,     0,     0,     0,     0,
      21,    22,    23,    24,     0,    25,     0,    14,    26,     0,
     203,    19,    20,     0,    15,    16,    17,    18,    21,    22,
      23,    24,     0,    25,     0,     0,    26,    14,     0,     0,
       0,     0,     0,     0,    15,    16,    17,    18,     0,     0,
       0,     0,     0,     0,     0,   205,    19,    20,     0,     0,
       0,     0,     0,    21,    22,    23,    24,     0,    25,     0,
       0,    26,    14,   237,     0,     0,    19,    20,     0,    15,
      16,    17,    18,    21,    22,    23,    24,     0,    25,   246,
      14,    26,     0,     0,     0,     0,     0,    15,    16,    17,
      18,     0,     0,     0,     0,     0,    14,   269,     0,     0,
       0,    19,    20,    15,    16,    17,    18,     0,    21,    22,
      23,    24,     0,    25,    14,     0,    26,     0,     0,    19,
      20,    15,    16,    17,    18,     0,    21,    22,    23,    24,
       0,    25,   276,     0,    26,    19,    81,     0,     0,     0,
       0,     0,    21,    22,    23,    24,     0,    25,     0,    14,
      26,     0,   302,    19,    20,     0,    15,    16,    17,    18,
      21,    22,    23,    24,     0,    25,     0,     0,    26,    14,
       0,     0,     0,     0,     0,     0,    15,    16,    17,    18,
       0,     0,     0,     0,     0,     0,     0,   314,    19,    20,
       0,     0,     0,     0,     0,    21,    22,    23,    24,     0,
      25,     0,     0,    26,    14,   342,     0,     0,    19,    20,
       0,    15,    16,    17,    18,    21,    22,    23,    24,     0,
      25,     0,    14,    26,     0,     0,     0,     0,     0,    15,
      16,    17,    18,     0,     0,     0,     0,     0,    14,     0,
       0,     0,     0,    19,    20,    15,    16,    17,    18,     0,
      21,    22,    23,    24,     0,    25,     0,     0,    26,     0,
       0,    19,    20,     0,     0,     0,     0,     0,    21,    22,
      23,    24,    14,    25,     0,     0,    26,    19,    81,    15,
      16,    17,    18,     0,    21,    22,    23,    24,     0,    25,
       0,     0,    26,     0,     0,     0,    82,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    19,    20,     0,     0,     0,     0,     0,    21,    22,
      23,    24,     0,    25,     0,     0,    26,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,     0,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,     0,     0,     0,   140,   141,     0,
       0,     0,     0,     0,   264,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,     0,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,     0,     0,     0,   140,   141,     0,     0,   166,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   263,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,     0,     0,     0,
     140,   141,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,     0,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,     0,
       0,     0,   140,   141,   117,     0,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,     0,     0,
       0,   140,   141,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,     0,     0,     0,   140,   141,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,     0,     0,     0,
     140,   141,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
       0,     0,     0,   140,   141,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,     0,     0,     0,   140,   141,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,     0,     0,     0,   140,   141
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-137)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       9,    99,    29,    97,     1,    14,     1,     1,     1,     1,
      19,    20,    21,    22,    23,    24,    25,    26,     1,     1,
       1,     1,     1,     1,    25,     1,     1,     1,     1,     1,
       1,    72,    25,    75,     1,    29,    25,    46,    25,     1,
       7,    74,    75,     0,    19,     1,    75,    48,    26,    25,
      29,    25,    25,    25,    25,    48,     1,    19,    67,     1,
       1,     1,     1,    19,     1,    73,     1,     1,     1,    29,
       1,     1,    81,     1,    74,    75,    25,    72,    75,    76,
      74,    75,    74,     1,    93,     1,    95,     1,    18,    72,
      99,    73,    73,    75,    74,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,    74,
     266,   140,    74,    74,    74,    74,    73,   273,    73,    73,
      73,   150,    73,   279,     1,    73,   155,   283,   175,   158,
      18,     1,    69,    70,    72,   164,   254,    73,     1,    73,
      20,    21,    22,    23,    24,    19,     1,     1,     1,    19,
       1,   307,     9,    10,   310,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    25,     0,   334,    69,
      70,   299,   296,   157,   340,   301,     0,     1,     1,     3,
       4,     5,     6,     7,     8,    72,   352,    11,    12,    13,
      14,    15,    16,    17,    18,     1,    19,     1,     1,    72,
       1,    25,    26,    27,    28,     1,   245,    72,    72,    72,
     338,    72,   261,    19,    18,   254,    19,     1,    19,     1,
     153,     1,    18,   296,   263,    18,   164,     1,    -1,    25,
      26,    27,    28,    57,    58,    19,     1,    19,    18,     1,
      64,    65,    66,    67,    18,    69,     1,   286,    72,     1,
      74,    -1,    -1,    18,    -1,     1,    18,     1,    -1,    -1,
     299,    57,    58,    18,    -1,    -1,    18,    -1,    64,    65,
      66,    67,    18,    69,    64,    65,    72,    -1,    74,    69,
      70,    -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,   338,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,     1,    -1,    -1,    69,    70,    -1,    -1,    73,
      74,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    -1,    -1,    -1,    69,    70,    -1,    -1,    -1,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,     1,    -1,    -1,
      69,    70,    -1,    -1,    -1,    74,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    -1,    -1,    -1,    69,    70,
      -1,    -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    -1,    -1,    -1,    69,    70,    -1,    -1,    -1,
      74,     3,     4,     5,     6,     7,     8,    -1,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,     1,    -1,    -1,
      -1,    -1,    -1,    25,    26,    27,    28,    -1,    61,    62,
      63,    64,    65,     1,    18,    19,    69,    70,    -1,    -1,
      -1,    25,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      18,     1,    -1,    -1,    -1,    57,    58,    25,    26,    27,
      28,    -1,    64,    65,    66,    67,    -1,    69,    18,    -1,
      72,    -1,    74,    57,    58,    25,    26,    27,    28,    -1,
      64,    65,    66,    67,    -1,    69,     1,    -1,    72,    57,
      58,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,
      -1,    69,    -1,    18,    72,    -1,     1,    57,    58,    -1,
      25,    26,    27,    28,    64,    65,    66,    67,    -1,    69,
      -1,    -1,    72,    18,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    57,    58,    -1,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    -1,    69,    -1,    -1,    72,    18,     1,
      -1,    -1,    57,    58,    -1,    25,    26,    27,    28,    64,
      65,    66,    67,    -1,    69,     1,    18,    72,    -1,    -1,
      -1,    -1,    -1,    25,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    18,     1,    -1,    -1,    -1,    57,    58,    25,
      26,    27,    28,    -1,    64,    65,    66,    67,    -1,    69,
      18,    -1,    72,    -1,    -1,    57,    58,    25,    26,    27,
      28,    -1,    64,    65,    66,    67,    -1,    69,     1,    -1,
      72,    57,    58,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    -1,    69,    -1,    18,    72,    -1,     1,    57,
      58,    -1,    25,    26,    27,    28,    64,    65,    66,    67,
      -1,    69,    -1,    -1,    72,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    57,    58,    -1,    -1,    -1,    -1,
      -1,    64,    65,    66,    67,    -1,    69,    -1,    -1,    72,
      18,     1,    -1,    -1,    57,    58,    -1,    25,    26,    27,
      28,    64,    65,    66,    67,    -1,    69,     1,    18,    72,
      -1,    -1,    -1,    -1,    -1,    25,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    18,     1,    -1,    -1,    -1,    57,
      58,    25,    26,    27,    28,    -1,    64,    65,    66,    67,
      -1,    69,    18,    -1,    72,    -1,    -1,    57,    58,    25,
      26,    27,    28,    -1,    64,    65,    66,    67,    -1,    69,
       1,    -1,    72,    57,    58,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    -1,    69,    -1,    18,    72,    -1,
       1,    57,    58,    -1,    25,    26,    27,    28,    64,    65,
      66,    67,    -1,    69,    -1,    -1,    72,    18,    -1,    -1,
      -1,    -1,    -1,    -1,    25,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    57,    58,    -1,    -1,
      -1,    -1,    -1,    64,    65,    66,    67,    -1,    69,    -1,
      -1,    72,    18,     1,    -1,    -1,    57,    58,    -1,    25,
      26,    27,    28,    64,    65,    66,    67,    -1,    69,     1,
      18,    72,    -1,    -1,    -1,    -1,    -1,    25,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    18,     1,    -1,    -1,
      -1,    57,    58,    25,    26,    27,    28,    -1,    64,    65,
      66,    67,    -1,    69,    18,    -1,    72,    -1,    -1,    57,
      58,    25,    26,    27,    28,    -1,    64,    65,    66,    67,
      -1,    69,     1,    -1,    72,    57,    58,    -1,    -1,    -1,
      -1,    -1,    64,    65,    66,    67,    -1,    69,    -1,    18,
      72,    -1,     1,    57,    58,    -1,    25,    26,    27,    28,
      64,    65,    66,    67,    -1,    69,    -1,    -1,    72,    18,
      -1,    -1,    -1,    -1,    -1,    -1,    25,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    57,    58,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    -1,
      69,    -1,    -1,    72,    18,     1,    -1,    -1,    57,    58,
      -1,    25,    26,    27,    28,    64,    65,    66,    67,    -1,
      69,    -1,    18,    72,    -1,    -1,    -1,    -1,    -1,    25,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    18,    -1,
      -1,    -1,    -1,    57,    58,    25,    26,    27,    28,    -1,
      64,    65,    66,    67,    -1,    69,    -1,    -1,    72,    -1,
      -1,    57,    58,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    18,    69,    -1,    -1,    72,    57,    58,    25,
      26,    27,    28,    -1,    64,    65,    66,    67,    -1,    69,
      -1,    -1,    72,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    57,    58,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    -1,    69,    -1,    -1,    72,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    -1,    -1,    -1,    69,    70,    -1,
      -1,    -1,    -1,    -1,    76,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    -1,    -1,    -1,    69,    70,    -1,    -1,    73,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    -1,    -1,    -1,
      69,    70,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    -1,
      -1,    -1,    69,    70,    42,    -1,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    -1,    -1,
      -1,    69,    70,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    -1,    -1,    -1,    69,    70,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    -1,    -1,    -1,
      69,    70,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      -1,    -1,    -1,    69,    70,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    -1,    -1,    -1,    69,    70,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    -1,    -1,    -1,    69,    70
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    11,    12,    13,
      14,    15,    16,    17,    18,    25,    26,    27,    28,    57,
      58,    64,    65,    66,    67,    69,    72,    74,    78,    79,
      80,    91,    93,    94,    95,    96,    97,    98,   100,   103,
     106,   109,   111,     1,    25,     1,    72,     1,    74,     1,
      74,     1,    74,   106,     1,    72,    25,    87,    88,     1,
      25,    81,    82,     1,    19,   106,   110,    72,    20,    21,
      22,    23,    24,   107,   107,   106,   106,   106,   106,   106,
     106,    58,    76,   106,   112,   113,   106,     0,     1,    80,
       1,    74,     1,    72,     1,    72,     1,    72,     1,    72,
       1,    18,     1,    72,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      69,    70,     1,    99,   106,     1,    74,     1,    26,     1,
      29,    89,    74,    75,     1,    29,    74,    75,    75,   108,
     104,   105,   106,     1,    75,    76,    73,     1,   106,     1,
     106,    91,    92,     1,    99,    79,    90,    48,    83,    84,
      86,     1,   106,     1,   106,     1,   106,     1,   106,     1,
     106,     1,   106,     1,   106,     1,   106,     1,   106,     1,
     106,     1,   106,     1,   106,     1,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,    25,
       1,    73,     1,    73,   106,     1,    88,     1,   106,    82,
     106,     1,    19,    73,     1,    75,     1,   113,     1,    74,
       1,    73,    74,     1,    74,     1,    73,     1,    19,     1,
      73,    75,    25,    43,    76,     1,    18,     1,    74,     1,
     106,     1,    25,    18,     1,    25,     1,    99,     1,    18,
       1,     7,     1,    18,     1,    86,    29,    85,   106,    90,
       1,    73,    90,     1,    73,     1,    74,    90,     1,    72,
      90,    25,     1,   106,     1,    19,     1,    18,    19,     1,
      18,    92,     1,    19,     1,    99,     1,    19,    85,   101,
      90,    90,     1,    73,     1,    73,     9,    10,   102,     1,
      19,     1,    19,     1,    18,     1,    74,     1,    72,     1,
      18,    90,     1,    99,    90,     1,    19,     1,    73,     1,
      19,     1,    18,    90,     1,    19
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 117 "grammary.y"
    { ; }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 118 "grammary.y"
    { scripthead = gethead((yyvsp[(1) - (1)].node)); }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 119 "grammary.y"
    { yyerror("Syntax error"); }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 122 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 123 "grammary.y"
    { (yyval.node) = node_add((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 126 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 127 "grammary.y"
    {
			/* Include files is a language construct */
			/* We should get here without a lookahead symbol */
			assert(yychar == YYEMPTY);
			handle_include((yyvsp[(3) - (5)].str));	/* Setup flex */
			free((yyvsp[(3) - (5)].str));
			(yyval.node) = NULL;
		}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 135 "grammary.y"
    { (yyval.node) = NULL; yyerror("';' expected"); }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 136 "grammary.y"
    { (yyval.node) = NULL; yyerror("')' expected"); }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 137 "grammary.y"
    { (yyval.node) = NULL; yyerror("String with include filename expected"); }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 138 "grammary.y"
    { (yyval.node) = NULL; yyerror("'(' expected"); }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 139 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 140 "grammary.y"
    { (yyval.node) = NULL; yyerror("';' expected"); }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 141 "grammary.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 142 "grammary.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 143 "grammary.y"
    { (yyval.node) = NULL; }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 146 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 147 "grammary.y"
    { (yyval.node) = node_add((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 150 "grammary.y"
    { (yyval.node) = cvar_new((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].node)); }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 151 "grammary.y"
    { (yyval.node) = NULL; yyerror("Expression expected"); }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 152 "grammary.y"
    { (yyval.node) = NULL; yyerror("'=' expected"); }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 153 "grammary.y"
    { (yyval.node) = NULL; yyerror("Identifier expected"); }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 156 "grammary.y"
    { (yyval.node) = NULL; }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 157 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 160 "grammary.y"
    { (yyval.node) = alist_new((yyvsp[(2) - (3)].str), (yyvsp[(1) - (3)].i), (yyvsp[(3) - (3)].node)); }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 161 "grammary.y"
    { (yyval.node) = alist_add((yyvsp[(1) - (5)].node), (yyvsp[(4) - (5)].str), (yyvsp[(3) - (5)].i), (yyvsp[(5) - (5)].node)); }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 162 "grammary.y"
    { (yyval.node) = NULL; yyerror("Identifier expected"); }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 165 "grammary.y"
    { (yyval.node) = NULL; }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 166 "grammary.y"
    { (yyval.node) = (yyvsp[(2) - (2)].node); }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 167 "grammary.y"
    { (yyval.node) = NULL; yyerror("Constant expression expected"); }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 170 "grammary.y"
    { (yyval.i) = 0; }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 171 "grammary.y"
    { (yyval.i) = 1; }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 174 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 175 "grammary.y"
    { (yyval.node) = node_add((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 176 "grammary.y"
    { (yyval.node) = NULL; yyerror("Identifier expected"); }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 179 "grammary.y"
    { (yyval.node) = lvar_new((yyvsp[(1) - (2)].str), (yyvsp[(2) - (2)].node)); }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 180 "grammary.y"
    { (yyval.node) = NULL; yyerror("Assignment expected"); }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 183 "grammary.y"
    { (yyval.node) = NULL; }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 184 "grammary.y"
    { (yyval.node) = (yyvsp[(2) - (2)].node); }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 187 "grammary.y"
    { (yyval.node) = NULL; }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 188 "grammary.y"
    { (yyval.node) = gethead((yyvsp[(1) - (1)].node)); }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 191 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); check_const_expr((yyvsp[(1) - (1)].node)); }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 194 "grammary.y"
    { (yyval.node) = NULL; }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 195 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 198 "grammary.y"
    { pushtag(newnode(NT_FOREACH)); }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 201 "grammary.y"
    { pushtag(newnode(NT_REPEAT)); }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 204 "grammary.y"
    { pushtag(newnode(NT_FOR)); }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 207 "grammary.y"
    { pushtag(newnode(NT_WHILE)); }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 210 "grammary.y"
    { pushtag(newnode(NT_DOWHILE)); }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 213 "grammary.y"
    {
			if(funcname)
				yyerror("Function in functions not supported");
			checkfuncname((yyvsp[(2) - (2)].str));
			(yyval.str) = funcname = (yyvsp[(2) - (2)].str);
		}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 219 "grammary.y"
    { (yyval.str) = NULL; yyerror("Function name expected"); }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 222 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); check_boolean_expr((yyval.node)); }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 225 "grammary.y"
    {
			(yyval.node) = poptag();
			(yyval.node)->lfe.src = (yyvsp[(3) - (9)].node);
			(yyval.node)->lfe.dst = (yyvsp[(5) - (9)].str);
			(yyval.node)->lfe.stmts = (yyvsp[(8) - (9)].node);
		}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 231 "grammary.y"
    { (yyval.node) = NULL; yyerror("'}' expected"); }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 232 "grammary.y"
    { (yyval.node) = NULL; yyerror("'{' expected"); }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 233 "grammary.y"
    { (yyval.node) = NULL; yyerror("')' expected"); }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 234 "grammary.y"
    { (yyval.node) = NULL; yyerror("Identifier expected"); }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 235 "grammary.y"
    { (yyval.node) = NULL; yyerror("';' expected"); }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 236 "grammary.y"
    { (yyval.node) = NULL; yyerror("Vectorlist expression expected"); }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 237 "grammary.y"
    { (yyval.node) = NULL; yyerror("'(' expected"); }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 238 "grammary.y"
    {
			(yyval.node) = poptag();
			(yyval.node)->lfe.src = (yyvsp[(3) - (9)].node);
			(yyval.node)->lfe.dst = (yyvsp[(5) - (9)].str);
			(yyval.node)->lfe.stmts = (yyvsp[(8) - (9)].node);
		}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 244 "grammary.y"
    {
			(yyval.node) = poptag();
			(yyval.node)->lfe.src = (yyvsp[(3) - (7)].node);
			(yyval.node)->lfe.dst = NULL;
			(yyval.node)->lfe.stmts = (yyvsp[(6) - (7)].node);
		}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 250 "grammary.y"
    { (yyval.node) = NULL; yyerror("'}' expected"); }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 251 "grammary.y"
    { (yyval.node) = NULL; yyerror("'{' expected"); }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 252 "grammary.y"
    { (yyval.node) = NULL; yyerror("')' expected"); }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 253 "grammary.y"
    { (yyval.node) = NULL; yyerror("Identifier expected"); }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 254 "grammary.y"
    { (yyval.node) = NULL; yyerror("';' or ')' expected"); }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 255 "grammary.y"
    { (yyval.node) = NULL; yyerror("Integer expression expected"); }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 256 "grammary.y"
    { (yyval.node) = NULL; yyerror("'(' expected"); }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 257 "grammary.y"
    {
			(yyval.node) = poptag();
			(yyval.node)->lfor.init = (yyvsp[(3) - (11)].node);
			(yyval.node)->lfor.cond = (yyvsp[(5) - (11)].node);
			(yyval.node)->lfor.inc = (yyvsp[(7) - (11)].node);
			(yyval.node)->lfor.stmts = (yyvsp[(10) - (11)].node);
		}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 264 "grammary.y"
    { (yyval.node) = NULL; yyerror("'}' expected"); }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 265 "grammary.y"
    { (yyval.node) = NULL; yyerror("'{' expected"); }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 266 "grammary.y"
    { (yyval.node) = NULL; yyerror("')' expected"); }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 267 "grammary.y"
    { (yyval.node) = NULL; yyerror("';' expected"); }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 268 "grammary.y"
    { (yyval.node) = NULL; yyerror("Conditional expression expected"); }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 269 "grammary.y"
    { (yyval.node) = NULL; yyerror("';' expected"); }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 270 "grammary.y"
    { (yyval.node) = NULL; yyerror("'(' expected"); }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 271 "grammary.y"
    {
			(yyval.node) = poptag();
			(yyval.node)->lfor.cond = (yyvsp[(3) - (7)].node);
			(yyval.node)->lfor.stmts = (yyvsp[(6) - (7)].node);
		}
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 276 "grammary.y"
    { (yyval.node) = NULL; yyerror("'}' expected"); }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 277 "grammary.y"
    { (yyval.node) = NULL; yyerror("'{' expected"); }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 278 "grammary.y"
    { (yyval.node) = NULL; yyerror("')' expected"); }
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 279 "grammary.y"
    { (yyval.node) = NULL; yyerror("Conditional expression expected"); }
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 280 "grammary.y"
    { (yyval.node) = NULL; yyerror("'(' expected"); }
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 281 "grammary.y"
    {
			(yyval.node) = poptag();
			(yyval.node)->lfor.cond = (yyvsp[(7) - (9)].node);
			(yyval.node)->lfor.stmts = (yyvsp[(3) - (9)].node);
		}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 286 "grammary.y"
    { (yyval.node) = NULL; yyerror("';' expected"); }
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 287 "grammary.y"
    { (yyval.node) = NULL; yyerror("')' expected"); }
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 288 "grammary.y"
    { (yyval.node) = NULL; yyerror("Conditional expression expected"); }
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 289 "grammary.y"
    { (yyval.node) = NULL; yyerror("'(' expected"); }
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 290 "grammary.y"
    { (yyval.node) = NULL; yyerror("'while' expected"); }
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 291 "grammary.y"
    { (yyval.node) = NULL; yyerror("'}' expected"); }
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 292 "grammary.y"
    { (yyval.node) = NULL; yyerror("'{' expected"); }
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 293 "grammary.y"
    {
			(yyval.node) = newnode(NT_FUNCTION);
			(yyval.node)->func.id = (yyvsp[(1) - (7)].str);
			(yyval.node)->func.args = (yyvsp[(3) - (7)].node);
			(yyval.node)->func.body = (yyvsp[(6) - (7)].node);
			funcname = NULL;
		}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 300 "grammary.y"
    { (yyval.node) = NULL; yyerror("'}' expected"); funcname = NULL; }
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 301 "grammary.y"
    { (yyval.node) = NULL; yyerror("'{' expected"); funcname = NULL; }
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 302 "grammary.y"
    { (yyval.node) = NULL; yyerror("')' expected"); funcname = NULL; }
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 303 "grammary.y"
    { (yyval.node) = NULL; yyerror("'(' expected"); funcname = NULL; }
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 304 "grammary.y"
    {
			(yyval.node) = newnode(NT_IF);
			(yyval.node)->cond.cond = (yyvsp[(3) - (8)].node);
			(yyval.node)->cond.ifclause = (yyvsp[(6) - (8)].node);
			(yyval.node)->cond.elifclauses = gethead((yyvsp[(8) - (8)].node));
		}
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 310 "grammary.y"
    {
			(yyval.node) = newnode(NT_IF);
			(yyval.node)->cond.cond = (yyvsp[(3) - (12)].node);
			(yyval.node)->cond.ifclause = (yyvsp[(6) - (12)].node);
			(yyval.node)->cond.elifclauses = gethead((yyvsp[(8) - (12)].node));
			(yyval.node)->cond.elseclause = (yyvsp[(11) - (12)].node);
		}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 317 "grammary.y"
    { (yyval.node) = NULL; yyerror("'}' expected"); }
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 318 "grammary.y"
    { (yyval.node) = NULL; yyerror("'{' expected"); }
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 319 "grammary.y"
    { (yyval.node) = NULL; yyerror("'}' expected"); }
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 320 "grammary.y"
    { (yyval.node) = NULL; yyerror("'{' expected"); }
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 321 "grammary.y"
    { (yyval.node) = NULL; yyerror("')' expected"); }
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 322 "grammary.y"
    { (yyval.node) = NULL; yyerror("Conditional expression expected"); }
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 323 "grammary.y"
    { (yyval.node) = NULL; yyerror("'(' expected"); }
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 324 "grammary.y"
    { (yyval.node) = node_new(NT_RETURN, (yyvsp[(2) - (3)].node)); }
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 325 "grammary.y"
    { (yyval.node) = node_new(NT_RETURN, NULL); }
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 326 "grammary.y"
    { (yyval.node) = NULL; yyerror("Expression or ';' expected"); }
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 327 "grammary.y"
    { (yyval.node) = NULL; yyerror("';' expected"); }
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 328 "grammary.y"
    { (yyval.node) = node_new(NT_BREAK, NULL); }
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 329 "grammary.y"
    { (yyval.node) = NULL; yyerror("';' expected"); }
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 330 "grammary.y"
    { (yyval.node) = node_new(NT_CONTINUE, NULL); }
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 331 "grammary.y"
    { (yyval.node) = NULL; yyerror("';' expected"); }
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 334 "grammary.y"
    { (yyval.node) = NULL; }
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 335 "grammary.y"
    { (yyval.node) = (yyvsp[(2) - (2)].node); if((yyvsp[(1) - (2)].node)) { (yyvsp[(1) - (2)].node)->next = (yyvsp[(2) - (2)].node); (yyvsp[(2) - (2)].node)->prev = (yyvsp[(1) - (2)].node);} }
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 338 "grammary.y"
    { (yyval.node) = newnode(NT_ELIF); (yyval.node)->cond.cond = (yyvsp[(3) - (7)].node); (yyval.node)->cond.ifclause = (yyvsp[(6) - (7)].node); }
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 339 "grammary.y"
    { (yyval.node) = NULL; yyerror("'}' expected"); }
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 340 "grammary.y"
    { (yyval.node) = NULL; yyerror("'{' expected"); }
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 341 "grammary.y"
    { (yyval.node) = NULL; yyerror("')' expected"); }
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 342 "grammary.y"
    { (yyval.node) = NULL; yyerror("Conditional expression expected"); }
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 343 "grammary.y"
    { (yyval.node) = NULL; yyerror("'(' expected"); }
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 346 "grammary.y"
    { (yyval.node) = expr_new_call((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].node)); }
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 349 "grammary.y"
    { (yyval.node) = NULL; }
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 350 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 353 "grammary.y"
    { (yyval.node) = elist_new((yyvsp[(1) - (1)].node)); }
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 354 "grammary.y"
    { (yyval.node) = elist_add((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 355 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (3)].node); yyerror("Expression expected after ','"); }
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 356 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); yyerror("',' expected"); }
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 359 "grammary.y"
    { (yyval.node) = (yyvsp[(2) - (2)].node); }
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 360 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(2) - (2)].node), expr_new_int(-1, UNIT_NONE), OP_MUL); }
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 361 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(2) - (2)].node), NULL, OP_NOT); }
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 362 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(2) - (2)].node), NULL, OP_BNOT); }
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 363 "grammary.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); (yyval.node)->expr.inparen = 1; }
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 364 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_ADD); }
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 365 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_ADDOR); }
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 366 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_SUB); }
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 367 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_SUBOR); }
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 368 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_MUL); }
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 369 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_DIV); }
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 370 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_MOD); }
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 371 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_EQ); }
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 372 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_NE); }
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 373 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_GT); }
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 374 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_LT); }
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 375 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_GE); }
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 376 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_LE); }
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 377 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_LAND); }
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 378 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_LOR); }
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 379 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_SHL); }
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 380 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_SHR); }
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 381 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_BAND); }
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 382 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_BOR); }
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 383 "grammary.y"
    { (yyval.node) = expr_new((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_BXOR); }
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 384 "grammary.y"
    {(yyval.node) = expr_new_tern((yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), OP_CONDEXPR); }
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 385 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 386 "grammary.y"
    { (yyval.node) = expr_new_idx((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node)); }
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 387 "grammary.y"
    { (yyval.node) = expr_new_idxid((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].str)); }
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 388 "grammary.y"
    { (yyval.node) = expr_new_id((yyvsp[(1) - (1)].str)); }
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 389 "grammary.y"
    { (yyval.node) = expr_new_int((yyvsp[(1) - (2)].i), (yyvsp[(2) - (2)].i)); }
    break;

  case 161:
/* Line 1792 of yacc.c  */
#line 390 "grammary.y"
    { (yyval.node) = expr_new_flt((yyvsp[(1) - (2)].d), (yyvsp[(2) - (2)].i)); }
    break;

  case 162:
/* Line 1792 of yacc.c  */
#line 391 "grammary.y"
    { (yyval.node) = expr_new_str((yyvsp[(1) - (1)].str)); }
    break;

  case 163:
/* Line 1792 of yacc.c  */
#line 392 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 164:
/* Line 1792 of yacc.c  */
#line 393 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 165:
/* Line 1792 of yacc.c  */
#line 394 "grammary.y"
    { (yyval.node) = expr_new_unary((yyvsp[(2) - (2)].node), OP_PREINC); }
    break;

  case 166:
/* Line 1792 of yacc.c  */
#line 395 "grammary.y"
    { (yyval.node) = expr_new_unary((yyvsp[(2) - (2)].node), OP_PREDEC); }
    break;

  case 167:
/* Line 1792 of yacc.c  */
#line 396 "grammary.y"
    { (yyval.node) = expr_new_unary((yyvsp[(1) - (2)].node), OP_POSTINC); check_useless((yyval.node)); }
    break;

  case 168:
/* Line 1792 of yacc.c  */
#line 397 "grammary.y"
    { (yyval.node) = expr_new_unary((yyvsp[(1) - (2)].node), OP_POSTDEC); check_useless((yyval.node)); }
    break;

  case 169:
/* Line 1792 of yacc.c  */
#line 398 "grammary.y"
    { (yyval.node) = node_new_assign((yyvsp[(1) - (3)].node), OP_ASSIGN, (yyvsp[(3) - (3)].node)); }
    break;

  case 170:
/* Line 1792 of yacc.c  */
#line 399 "grammary.y"
    { (yyval.node) = node_new_assign((yyvsp[(1) - (3)].node), OP_ADDASSIGN, (yyvsp[(3) - (3)].node)); }
    break;

  case 171:
/* Line 1792 of yacc.c  */
#line 400 "grammary.y"
    { (yyval.node) = node_new_assign((yyvsp[(1) - (3)].node), OP_ADDORASSIGN, (yyvsp[(3) - (3)].node)); }
    break;

  case 172:
/* Line 1792 of yacc.c  */
#line 401 "grammary.y"
    { (yyval.node) = node_new_assign((yyvsp[(1) - (3)].node), OP_SUBASSIGN, (yyvsp[(3) - (3)].node)); }
    break;

  case 173:
/* Line 1792 of yacc.c  */
#line 402 "grammary.y"
    { (yyval.node) = node_new_assign((yyvsp[(1) - (3)].node), OP_SUBORASSIGN, (yyvsp[(3) - (3)].node)); }
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 403 "grammary.y"
    { (yyval.node) = node_new_assign((yyvsp[(1) - (3)].node), OP_MULASSIGN, (yyvsp[(3) - (3)].node)); }
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 404 "grammary.y"
    { (yyval.node) = node_new_assign((yyvsp[(1) - (3)].node), OP_DIVASSIGN, (yyvsp[(3) - (3)].node)); }
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 405 "grammary.y"
    { (yyval.node) = node_new_assign((yyvsp[(1) - (3)].node), OP_MODASSIGN, (yyvsp[(3) - (3)].node)); }
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 406 "grammary.y"
    { (yyval.node) = node_new_assign((yyvsp[(1) - (3)].node), OP_SHLASSIGN, (yyvsp[(3) - (3)].node)); }
    break;

  case 178:
/* Line 1792 of yacc.c  */
#line 407 "grammary.y"
    { (yyval.node) = node_new_assign((yyvsp[(1) - (3)].node), OP_SHRASSIGN, (yyvsp[(3) - (3)].node)); }
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 408 "grammary.y"
    { (yyval.node) = node_new_assign((yyvsp[(1) - (3)].node), OP_BORASSIGN, (yyvsp[(3) - (3)].node)); }
    break;

  case 180:
/* Line 1792 of yacc.c  */
#line 409 "grammary.y"
    { (yyval.node) = node_new_assign((yyvsp[(1) - (3)].node), OP_BANDASSIGN, (yyvsp[(3) - (3)].node)); }
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 410 "grammary.y"
    { (yyval.node) = node_new_assign((yyvsp[(1) - (3)].node), OP_BXORASSIGN, (yyvsp[(3) - (3)].node)); }
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 411 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (3)].node); yyerror("Expression expected after '='"); }
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 412 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (3)].node); yyerror("Expression expected after '+='"); }
    break;

  case 184:
/* Line 1792 of yacc.c  */
#line 413 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (3)].node); yyerror("Expression expected after '+|='"); }
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 414 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (3)].node); yyerror("Expression expected after '-='"); }
    break;

  case 186:
/* Line 1792 of yacc.c  */
#line 415 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (3)].node); yyerror("Expression expected after '-|='"); }
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 416 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (3)].node); yyerror("Expression expected after '*='"); }
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 417 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (3)].node); yyerror("Expression expected after '/='"); }
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 418 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (3)].node); yyerror("Expression expected after '%%='"); }
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 419 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (3)].node); yyerror("Expression expected after '<<='"); }
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 420 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (3)].node); yyerror("Expression expected after '>>='"); }
    break;

  case 192:
/* Line 1792 of yacc.c  */
#line 421 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (3)].node); yyerror("Expression expected after '|='"); }
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 422 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (3)].node); yyerror("Expression expected after '&='"); }
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 423 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (3)].node); yyerror("Expression expected after '^='"); }
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 426 "grammary.y"
    { (yyval.i) = UNIT_NONE; }
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 427 "grammary.y"
    { (yyval.i) = UNIT_MM; }
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 428 "grammary.y"
    { (yyval.i) = _UNIT_MIL; }
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 429 "grammary.y"
    { (yyval.i) = UNIT_IN; }
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 430 "grammary.y"
    { (yyval.i) = UNIT_DEG; }
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 431 "grammary.y"
    { (yyval.i) = UNIT_RAD; }
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 438 "grammary.y"
    { (yyval.node) = (yyvsp[(2) - (4)].node); }
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 439 "grammary.y"
    { (yyval.node) = vlist_new(NULL); }
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 440 "grammary.y"
    { (yyval.node) = NULL; yyerror("'}' expected"); }
    break;

  case 206:
/* Line 1792 of yacc.c  */
#line 441 "grammary.y"
    { (yyval.node) = (yyvsp[(2) - (4)].node); yyerror("'}' expected"); }
    break;

  case 207:
/* Line 1792 of yacc.c  */
#line 444 "grammary.y"
    { (yyval.node) = vlist_new((yyvsp[(1) - (1)].node)); }
    break;

  case 208:
/* Line 1792 of yacc.c  */
#line 445 "grammary.y"
    { (yyval.node) = vlist_add((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 209:
/* Line 1792 of yacc.c  */
#line 448 "grammary.y"
    { (yyval.node) = vec_new(NULL, 0); }
    break;

  case 210:
/* Line 1792 of yacc.c  */
#line 449 "grammary.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 450 "grammary.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); yyerror("']' expected"); }
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 453 "grammary.y"
    { (yyval.node) = vec_new((yyvsp[(1) - (1)].node), 1); }
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 454 "grammary.y"
    { (yyval.node) = vec_add((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 455 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (3)].node); yyerror("Scalar expression or '-' expected"); }
    break;

  case 215:
/* Line 1792 of yacc.c  */
#line 458 "grammary.y"
    { (yyval.node) = NULL; }
    break;

  case 216:
/* Line 1792 of yacc.c  */
#line 459 "grammary.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;


/* Line 1792 of yacc.c  */
#line 3384 "grammary.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 462 "grammary.y"

static node_t *newnode(int type)
{
	node_t *n = (node_t *)calloc(1, sizeof(node_t));
	myassert(n != NULL);
	n->type = (node_et)type;
	n->linenr = prevlinenr;
	n->charnr = prevcharnr;
	n->filename = filename;
	return n;
}

static node_t *newnlist(node_t *n, int i)
{
	n->nlist.na = i;
	n->nlist.nodes = (struct __node_t	**)calloc(i, sizeof(n->nlist.nodes[0]));
	myassert(n->nlist.nodes != NULL);
	return n;
}

static node_t *newalist(node_t *n, int i)
{
	n->alist.na = i;
	n->alist.args = (arg_t *)calloc(i, sizeof(n->alist.args[0]));
	myassert(n->alist.args != NULL);
	return n;
}

static node_t *alist_new(wchar_t *id, int isref, node_t *e)
{
	node_t *n = newnode(NT_ARGLIST);
	myassert(!e || (e && !isref));
	newalist(n, 4);
	n->alist.n = 1;
	n->alist.args[0].id = id;
	n->alist.args[0].isref = isref;
	n->alist.args[0].expr = e;
	return n;
}

static node_t *alist_add(node_t *l, wchar_t *id, int isref, node_t *e)
{
	int i;
	int havedef = 0;
	myassert(l->type == NT_ARGLIST);
	myassert(!e || (e && !isref));
	testalloc((void **)&l->alist.args, l->alist.n, &l->alist.na, sizeof(l->alist.args[0]));
	for(i = 0; i < l->alist.n; i++) {
		if(!wcscmp(id, l->alist.args[i].id)) {
			yyerror("Argument %d's name '%ls' already used in argument %d", l->alist.n+1, id, i+1);
			return l;
		}
		if(l->alist.args[i].expr)
			havedef = 1;
	}

	if(!e && havedef)
		yyerror("Argument %d (%ls) must include default value", l->alist.n+1, id);

	if(e && isref)
		yyerror("Argument %d (%ls) cannot be both a reference and have a default value", l->alist.n+1, id);

	l->alist.args[l->alist.n].id = id;
	l->alist.args[l->alist.n].isref = isref;
	l->alist.args[l->alist.n].expr = e;
	l->alist.n++;
	return l;
}

static node_t *lvar_new(wchar_t *id, node_t *e)
{
	node_t *n = newnode(NT_LOCAL);
	n->lvar.id = id;
	n->lvar.init = e;
	return n;
}

static node_t *cvar_new(wchar_t *id, node_t *e)
{
	node_t *n = newnode(NT_CONST);
	n->cvar.id = id;
	n->cvar.init = e;
	return n;
}

static node_t *elist_new(node_t *e)
{
	node_t *n = newnode(NT_EXPRLIST);
	newnlist(n, 4);
	n->nlist.n = 1;
	n->nlist.nodes[0] = e;
	return n;
}

static node_t *elist_add(node_t *l, node_t *e)
{
	myassert(e->type == NT_EXPR);
	myassert(l->type == NT_EXPRLIST);
	testalloc((void **)&l->nlist.nodes, l->nlist.n, &l->nlist.na, sizeof(l->nlist.nodes[0]));
	l->nlist.nodes[l->nlist.n] = e;
	l->nlist.n++;
	return l;
}

static node_t *vlist_new(node_t *v)
{
	myassert(v == NULL || v->type == NT_EXPR);
	node_t *n = newnode(NT_EXPR);
	n->expr.op = OP_VECTORLIST;
	n->expr.nlist.na = 4;
	n->expr.nlist.nodes = (struct __node_t **)calloc(4, sizeof(n->expr.nlist.nodes[0]));
	myassert(n->expr.nlist.nodes != NULL);
	if(v) {
		n->expr.nlist.n = 1;
		n->expr.nlist.nodes[0] = v;
	}
	return n;
}

static node_t *vlist_add(node_t *l, node_t *v)
{
	myassert(l->type == NT_EXPR);
	myassert(l->expr.op == OP_VECTORLIST);
	myassert(v->type == NT_EXPR);
	testalloc((void **)&l->expr.nlist.nodes, l->expr.nlist.n, &l->expr.nlist.na, sizeof(l->expr.nlist.nodes[0]));
	l->expr.nlist.nodes[l->expr.nlist.n] = v;
	l->expr.nlist.n++;
	return l;
}

static node_t *vec_new(node_t *e, int allownull)
{
	node_t *n = newnode(NT_EXPR);
	n->expr.op = OP_VECTOR;
	n->expr.nlist.na = 4;
	n->expr.nlist.nodes = (struct __node_t **)calloc(4, sizeof(n->expr.nlist.nodes[0]));
	myassert(n->expr.nlist.nodes != NULL);
	if(allownull || e) {
		n->expr.nlist.n = 1;
		n->expr.nlist.nodes[0] = e;
	}
	return n;
}

static node_t *vec_add(node_t *v, node_t *e)
{
	myassert(v->type == NT_EXPR);
	myassert(v->expr.op == OP_VECTOR);
	testalloc((void **)&v->expr.nlist.nodes, v->expr.nlist.n, &v->expr.nlist.na, sizeof(v->expr.nlist.nodes[0]));
	v->expr.nlist.nodes[v->expr.nlist.n] = e;
	v->expr.nlist.n++;
	return v;
}

static node_t *node_new_assign(node_t *lv, int op, node_t *rv)
{
	node_t *n = newnode(NT_EXPR);
	n->expr.op = (op_et)op;
	n->expr.left = lv;
	n->expr.right = rv;
	check_useless(n);
	return n;
}

static node_t *node_new(int nt, node_t *e)
{
	node_t *n = newnode(nt);
	n->eref = e;
	return n;
}

static node_t *node_add(node_t *tailnode, node_t *newnode)
{
	node_t *nnhead = newnode;
	node_t *nntail = newnode;

	/* Find real head and tail of the new node(s) */
	if(newnode) {
		while(nnhead->prev)
			nnhead = nnhead->prev;
		while(nntail->next)
			nntail = nntail->next;
	}

	if(!tailnode)
		return nntail;	/* Always return the real tail */

	/* Find the tail's real tail */
	while(tailnode->next)
		tailnode = tailnode->next;

	if(!newnode)
		return tailnode;

	/* Crosslink to append new nodes */
	tailnode->next = nnhead;
	nnhead->prev = tailnode;
	return nntail;	/* Return the real tail of the combined list */
}

static node_t *expr_new(node_t *l, node_t *r, int op)
{
	node_t *n = newnode(NT_EXPR);
	myassert(l != NULL);
	n->expr.op = (op_et)op;
	n->expr.left = l;
	n->expr.right = r;
	return n;
}

static node_t *expr_new_unary(node_t *id, int op)
{
	node_t *n = newnode(NT_EXPR);
	n->expr.op = (op_et)op;
	n->expr.left = id;
	return n;
}

static node_t *expr_new_tern(node_t *c, node_t *l, node_t *r, int op)
{
	node_t *n = newnode(NT_EXPR);
	myassert(c != NULL);
	myassert(l != NULL);
	myassert(r != NULL);
	n->expr.op = (op_et)op;
	n->expr.cond = c;
	n->expr.left = l;
	n->expr.right = r;
	return n;
}

static node_t *expr_new_call(wchar_t *id, node_t *e)
{
	node_t *n = newnode(NT_EXPR);
	myassert(e == NULL || e->type == NT_EXPRLIST);
	n->expr.id = id;
	n->expr.args = e;
	n->expr.op = OP_CALL;
	return n;
}

static node_t *expr_new_id(wchar_t *id)
{
	node_t *n = newnode(NT_EXPR);
	n->expr.op = OP_DEREF;
	n->expr.id = id;
	if(!wcscmp(L"__global_offset", n->expr.id) || !wcscmp(L"__global_position", n->expr.id))
		rtwarning(n, "Using internal variable '%ls' strongly discouraged", n->expr.id);
	return n;
}

static node_t *expr_new_idx(node_t *d, node_t *e)
{
	node_t *n = newnode(NT_EXPR);
	n->expr.op = OP_INDEX;
	n->expr.left = d;
	n->expr.right = e;
	return n;
}

static const wchar_t axisnames[] = L"xyzabcuvw";

static node_t *expr_new_idxid(node_t *d, wchar_t *id)
{
	node_t *n = newnode(NT_EXPR);
	assert(id != NULL);
	n->expr.op = OP_INDEXID;
	n->expr.left = d;
	const wchar_t *cptr = wcschr(axisnames, id[0]);
	if(!cptr || 1 != wcslen(id))
		yyerror("Index can only be an axis name");
	n->expr.right = expr_new_int(cptr - axisnames, UNIT_NONE);
	free(id);
	return n;
}

static node_t *expr_new_int(int i, int unit)
{
	node_t *n = newnode(NT_EXPR);
	if(unit == _UNIT_MIL) {
		n->expr.op = OP_FLOAT;
		n->expr.d = (double)i / 1000.0;
		n->expr.unit = UNIT_IN;
	} else {
		n->expr.op = OP_INT;
		n->expr.i = i;
		n->expr.unit = (unit_et)unit;
	}
	return n;
}

static node_t *expr_new_flt(double d, int unit)
{
	node_t *n = newnode(NT_EXPR);
	n->expr.op = OP_FLOAT;
	if(unit == _UNIT_MIL) {
		d /= 1000.0;
		unit = UNIT_IN;
	}
	n->expr.d = d;
	n->expr.unit = (unit_et)unit;
	return n;
}

static node_t *expr_new_str(wchar_t *str)
{
	node_t *n = newnode(NT_EXPR);
	n->expr.op = OP_STRING;
	n->expr.str.chs = str;
	n->expr.str.n = wcslen(str);
	n->expr.str.na = n->expr.str.n + 1;
	return n;
}

static node_t **nodestack;
static int nnodestack;
static int nanodestack;

static node_t *pushtag(node_t *n)
{
	if(!nodestack) {
		nodestack = (node_t **)calloc(16, sizeof(*nodestack));
		assert(nodestack != NULL);
		nnodestack = 0;
		nanodestack = 16;
	} else if(nnodestack >= nanodestack) {
		nodestack = (node_t **)realloc(nodestack, nanodestack * 2 * sizeof(*nodestack));
		assert(nodestack != NULL);
		nanodestack *= 2;
	}
	nodestack[nnodestack] = n;
	nnodestack++;
	return n;
}

static node_t *poptag(void)
{
	assert(nnodestack > 0);
	nnodestack--;
	return nodestack[nnodestack];
}

static node_t *gethead(node_t *n)
{
	if(!n)
		return NULL;
	while(n->prev)
		n = n->prev;
	return n;
}

void node_delete(node_t *head)
{
	node_t *n, *next;
	int i;

	assert(nnodestack == 0);

	if(nodestack) {
		free(nodestack);
		nodestack = NULL;
	}

	if(!head)
		return;

	for(n = head; n; n = next) {
		next = n->next;
		switch(n->type) {
		case NT_EXPRLIST:
			for(i = 0; i < n->nlist.n; i++)
				node_delete(n->nlist.nodes[i]);
			free(n->nlist.nodes);
			break;
		case NT_ARGLIST:
			for(i = 0; i < n->alist.n; i++) {
				node_delete(n->alist.args[i].expr);
				free(n->alist.args[i].id);
			}
			free(n->alist.args);
			break;
		case NT_RETURN:
			node_delete(n->eref);
			break;
		case NT_LOCAL:
			node_delete(n->lvar.init);
			free(n->lvar.id);
			break;
		case NT_CONST:
			node_delete(n->cvar.init);
			free(n->cvar.id);
			break;
		case NT_BREAK:
		case NT_CONTINUE:
		case NT_INVALID:
			break;
		case NT_EXPR:
			node_delete(n->expr.left);
			node_delete(n->expr.right);
			switch(n->expr.op) {
			case OP_NULL:
				break;
			case OP_ADD:
			case OP_ADDOR:
			case OP_SUB:
			case OP_SUBOR:
			case OP_MUL:
			case OP_DIV:
			case OP_MOD:
			case OP_LOR:
			case OP_LAND:
			case OP_BOR:
			case OP_BXOR:
			case OP_BAND:
			case OP_BNOT:
			case OP_EQ:
			case OP_NE:
			case OP_GT:
			case OP_LT:
			case OP_GE:
			case OP_LE:
			case OP_SHL:
			case OP_SHR:
			case OP_NOT:
			case OP_INT:
			case OP_FLOAT:
				break;
			case OP_CONDEXPR:
				node_delete(n->expr.cond);
				break;
			case OP_CALL:
				node_delete(n->expr.args);
				free(n->expr.id);
				break;
			case OP_ASSIGN:
			case OP_ADDASSIGN:
			case OP_ADDORASSIGN:
			case OP_SUBASSIGN:
			case OP_SUBORASSIGN:
			case OP_MULASSIGN:
			case OP_DIVASSIGN:
			case OP_MODASSIGN:
			case OP_SHLASSIGN:
			case OP_SHRASSIGN:
			case OP_BORASSIGN:
			case OP_BANDASSIGN:
			case OP_BXORASSIGN:
			case OP_INDEX:
			case OP_INDEXID:
				break;
			case OP_STRING:
				free(n->expr.str.chs);
				break;
			case OP_DEREF:
				free(n->expr.id);
				break;
			case OP_PREINC:
			case OP_PREDEC:
			case OP_POSTINC:
			case OP_POSTDEC:
				break;
			case OP_VECTOR:
			case OP_VECTORLIST:
				for(i = 0; i < n->expr.nlist.n; i++)
					node_delete(n->expr.nlist.nodes[i]);
				free(n->expr.nlist.nodes);
				break;
			}
			break;
		case NT_IF:
			node_delete(n->cond.cond);
			node_delete(n->cond.ifclause);
			node_delete(n->cond.elifclauses);
			node_delete(n->cond.elseclause);
			break;
		case NT_ELIF:
			node_delete(n->cond.cond);
			node_delete(n->cond.ifclause);
			break;
		case NT_FOR:
		case NT_WHILE:
		case NT_DOWHILE:
			node_delete(n->lfor.stmts);
			node_delete(n->lfor.init);
			node_delete(n->lfor.cond);
			node_delete(n->lfor.inc);
			break;
		case NT_FOREACH:
		case NT_REPEAT:
			node_delete(n->lfe.stmts);
			node_delete(n->lfe.src);
			if(n->lfe.dst)
				free(n->lfe.dst);
			break;
		case NT_FUNCTION:
			node_delete(n->func.args);
			node_delete(n->func.body);
			free(n->func.id);
			break;
		}
		free(n);
	}
}

static const wchar_t **funcs;
static int nfuncs;
static int nafuncs;

const builtins_t *find_builtin(const wchar_t *s);

static void checkfuncname(const wchar_t *fn)
{
	int i;
	if(find_builtin(fn)) {
		yyerror("Function name '%ls' reserved as built-in function", fn);
		return;
	}
	for(i = 0; i < nfuncs; i++) {
		if(!wcscmp(fn , funcs[i])) {
			yyerror("Function name '%ls' is already defined", fn);
			return;
		}
	}
	testalloc((void **)&funcs, nfuncs, &nafuncs, sizeof(*funcs));
	funcs[nfuncs] = fn;
	nfuncs++;
}

void parser_cleanup(void)
{
	if(funcs) {
		free(funcs);
		funcs = NULL;
		nafuncs = nfuncs = 0;
	}
}

static int findderef(const node_t *n)
{
	const node_t *lv;
	/* Check if lvalue (left) is dereference-able */
	assert(n->expr.left != NULL);
	if(n->expr.inparen)
		return -1;
	for(lv = n->expr.left; lv; lv = lv->expr.left) {
		myassert(n->type == NT_EXPR);
		if(lv->expr.inparen)
			return -1;
		if(!lv->expr.left)
			break;
	}
	assert(lv != NULL);
	if(lv->expr.op == OP_DEREF) {
		if(!wcscmp(L"__global_offset", lv->expr.id) || !wcscmp(L"__global_position", lv->expr.id))
			yyerror("Assigning to read-only variable '%ls' not allowed", lv->expr.id);
		return 1;		/* Deref operation works on IDENT --> OK */
	}
	return -1;
}

static void check_useless(const node_t *n)
{
	assert(n != NULL);
	myassert(n->type == NT_EXPR);

	switch(n->expr.op) {
	case OP_CALL:
		/* Calls are fine */
		return;
	case OP_POSTINC:
	case OP_POSTDEC:
		/* Post inc/dec on a constant has no effect */
		if(findderef(n) >= 0)
			return;
		yyerror("Statement post-%s on a constant has no effect", n->expr.op == OP_POSTINC ? "increment" : "decrement");
		break;
	case OP_ASSIGN:
	case OP_ADDASSIGN:
	case OP_ADDORASSIGN:
	case OP_SUBASSIGN:
	case OP_SUBORASSIGN:
	case OP_MULASSIGN:
	case OP_DIVASSIGN:
	case OP_MODASSIGN:
	case OP_SHLASSIGN:
	case OP_SHRASSIGN:
	case OP_BORASSIGN:
	case OP_BANDASSIGN:
	case OP_BXORASSIGN:
		if(findderef(n) >= 0 && !n->expr.inparen)
			return;
		/* Fallthrough */
	default:
		yyerror("Lvalue not a variable, cannot be dereferenced");
		return;
	}
}

static void check_const_expr(const node_t *n)
{
	if(!n)
		return;

	myassert(n->type == NT_EXPR);

	switch(n->expr.op) {
	case OP_CALL:
		/* Calls are fine */
		return;
	case OP_ASSIGN:
	case OP_ADDASSIGN:
	case OP_ADDORASSIGN:
	case OP_SUBASSIGN:
	case OP_SUBORASSIGN:
	case OP_MULASSIGN:
	case OP_DIVASSIGN:
	case OP_MODASSIGN:
	case OP_SHLASSIGN:
	case OP_SHRASSIGN:
	case OP_BORASSIGN:
	case OP_BANDASSIGN:
	case OP_BXORASSIGN:
		/* We already check assignments */
		return;
	case OP_PREINC:
	case OP_PREDEC:
	case OP_POSTINC:
	case OP_POSTDEC:
		if(findderef(n) >= 0)
			return;
		/* Fallthrough */
	default:
		yyerror("Statement has no effect");
		return;
	}
}

static void check_boolean_expr(const node_t *n)
{
	assert(n != NULL);
	myassert(n->type == NT_EXPR);

	switch(n->expr.op) {
	case OP_CALL:
		return;
	case OP_ASSIGN:
	case OP_ADDASSIGN:
	case OP_ADDORASSIGN:
	case OP_SUBASSIGN:
	case OP_SUBORASSIGN:
	case OP_MULASSIGN:
	case OP_DIVASSIGN:
	case OP_MODASSIGN:
	case OP_SHLASSIGN:
	case OP_SHRASSIGN:
	case OP_BORASSIGN:
	case OP_BANDASSIGN:
	case OP_BXORASSIGN:
		if(!n->expr.inparen) {
			rtwarning(n, "Assignment in boolean expression may be an inadvertent error, use () to force");
			return;
		}
	default:
		if(n->expr.left)
			check_boolean_expr(n->expr.left);
		if(n->expr.right)
			check_boolean_expr(n->expr.right);
	}
}
