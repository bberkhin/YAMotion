/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 19 "grammary.y"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "gcmc_alloc.h"

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

GCMC_TLS static wchar_t *funcname;

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

GCMC_TLS node_t *scripthead;


#line 128 "grammary.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "grammary.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_FUNCTION = 3,                   /* FUNCTION  */
  YYSYMBOL_FOR = 4,                        /* FOR  */
  YYSYMBOL_FOREACH = 5,                    /* FOREACH  */
  YYSYMBOL_DO = 6,                         /* DO  */
  YYSYMBOL_WHILE = 7,                      /* WHILE  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_ELIF = 9,                       /* ELIF  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_BREAK = 11,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 12,                  /* CONTINUE  */
  YYSYMBOL_RETURN = 13,                    /* RETURN  */
  YYSYMBOL_INCLUDE = 14,                   /* INCLUDE  */
  YYSYMBOL_LOCAL = 15,                     /* LOCAL  */
  YYSYMBOL_REPEAT = 16,                    /* REPEAT  */
  YYSYMBOL_CONST = 17,                     /* CONST  */
  YYSYMBOL_TOPEN = 18,                     /* TOPEN  */
  YYSYMBOL_TCLOSE = 19,                    /* TCLOSE  */
  YYSYMBOL_MM = 20,                        /* MM  */
  YYSYMBOL_MIL = 21,                       /* MIL  */
  YYSYMBOL_IN = 22,                        /* IN  */
  YYSYMBOL_DEG = 23,                       /* DEG  */
  YYSYMBOL_RAD = 24,                       /* RAD  */
  YYSYMBOL_IDENT = 25,                     /* IDENT  */
  YYSYMBOL_STRING = 26,                    /* STRING  */
  YYSYMBOL_NUMBER = 27,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 28,                     /* FLOAT  */
  YYSYMBOL_29_ = 29,                       /* '='  */
  YYSYMBOL_SUBASSIGN = 30,                 /* SUBASSIGN  */
  YYSYMBOL_ADDASSIGN = 31,                 /* ADDASSIGN  */
  YYSYMBOL_MULASSIGN = 32,                 /* MULASSIGN  */
  YYSYMBOL_DIVASSIGN = 33,                 /* DIVASSIGN  */
  YYSYMBOL_MODASSIGN = 34,                 /* MODASSIGN  */
  YYSYMBOL_SHLASSIGN = 35,                 /* SHLASSIGN  */
  YYSYMBOL_SHRASSIGN = 36,                 /* SHRASSIGN  */
  YYSYMBOL_ADDORASSIGN = 37,               /* ADDORASSIGN  */
  YYSYMBOL_SUBORASSIGN = 38,               /* SUBORASSIGN  */
  YYSYMBOL_BORASSIGN = 39,                 /* BORASSIGN  */
  YYSYMBOL_BANDASSIGN = 40,                /* BANDASSIGN  */
  YYSYMBOL_BXORASSIGN = 41,                /* BXORASSIGN  */
  YYSYMBOL_42_ = 42,                       /* '?'  */
  YYSYMBOL_43_ = 43,                       /* ':'  */
  YYSYMBOL_LOR = 44,                       /* LOR  */
  YYSYMBOL_LAND = 45,                      /* LAND  */
  YYSYMBOL_46_ = 46,                       /* '|'  */
  YYSYMBOL_47_ = 47,                       /* '^'  */
  YYSYMBOL_48_ = 48,                       /* '&'  */
  YYSYMBOL_EQ = 49,                        /* EQ  */
  YYSYMBOL_NE = 50,                        /* NE  */
  YYSYMBOL_LT = 51,                        /* LT  */
  YYSYMBOL_GT = 52,                        /* GT  */
  YYSYMBOL_LE = 53,                        /* LE  */
  YYSYMBOL_GE = 54,                        /* GE  */
  YYSYMBOL_SHL = 55,                       /* SHL  */
  YYSYMBOL_SHR = 56,                       /* SHR  */
  YYSYMBOL_57_ = 57,                       /* '+'  */
  YYSYMBOL_58_ = 58,                       /* '-'  */
  YYSYMBOL_ADDOR = 59,                     /* ADDOR  */
  YYSYMBOL_SUBOR = 60,                     /* SUBOR  */
  YYSYMBOL_61_ = 61,                       /* '*'  */
  YYSYMBOL_62_ = 62,                       /* '/'  */
  YYSYMBOL_63_ = 63,                       /* '%'  */
  YYSYMBOL_INC = 64,                       /* INC  */
  YYSYMBOL_DEC = 65,                       /* DEC  */
  YYSYMBOL_66_ = 66,                       /* '!'  */
  YYSYMBOL_67_ = 67,                       /* '~'  */
  YYSYMBOL_UPM = 68,                       /* UPM  */
  YYSYMBOL_69_ = 69,                       /* '['  */
  YYSYMBOL_70_ = 70,                       /* '.'  */
  YYSYMBOL_UID = 71,                       /* UID  */
  YYSYMBOL_72_ = 72,                       /* '('  */
  YYSYMBOL_73_ = 73,                       /* ')'  */
  YYSYMBOL_74_ = 74,                       /* ';'  */
  YYSYMBOL_75_ = 75,                       /* ','  */
  YYSYMBOL_76_ = 76,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 77,                  /* $accept  */
  YYSYMBOL_file = 78,                      /* file  */
  YYSYMBOL_lines = 79,                     /* lines  */
  YYSYMBOL_line = 80,                      /* line  */
  YYSYMBOL_cvars = 81,                     /* cvars  */
  YYSYMBOL_cvar = 82,                      /* cvar  */
  YYSYMBOL_optarglist = 83,                /* optarglist  */
  YYSYMBOL_arglist = 84,                   /* arglist  */
  YYSYMBOL_optv = 85,                      /* optv  */
  YYSYMBOL_optref = 86,                    /* optref  */
  YYSYMBOL_locals = 87,                    /* locals  */
  YYSYMBOL_local = 88,                     /* local  */
  YYSYMBOL_optassgn = 89,                  /* optassgn  */
  YYSYMBOL_optstmts = 90,                  /* optstmts  */
  YYSYMBOL_stmt = 91,                      /* stmt  */
  YYSYMBOL_optstmt = 92,                   /* optstmt  */
  YYSYMBOL_foreach = 93,                   /* foreach  */
  YYSYMBOL_repeat = 94,                    /* repeat  */
  YYSYMBOL_for = 95,                       /* for  */
  YYSYMBOL_while = 96,                     /* while  */
  YYSYMBOL_do = 97,                        /* do  */
  YYSYMBOL_function = 98,                  /* function  */
  YYSYMBOL_boolexpr = 99,                  /* boolexpr  */
  YYSYMBOL_compound = 100,                 /* compound  */
  YYSYMBOL_optelif = 101,                  /* optelif  */
  YYSYMBOL_elif = 102,                     /* elif  */
  YYSYMBOL_call = 103,                     /* call  */
  YYSYMBOL_optargs = 104,                  /* optargs  */
  YYSYMBOL_args = 105,                     /* args  */
  YYSYMBOL_expr = 106,                     /* expr  */
  YYSYMBOL_optunit = 107,                  /* optunit  */
  YYSYMBOL_optcomma = 108,                 /* optcomma  */
  YYSYMBOL_veclist = 109,                  /* veclist  */
  YYSYMBOL_vlist = 110,                    /* vlist  */
  YYSYMBOL_vector = 111,                   /* vector  */
  YYSYMBOL_nums = 112,                     /* nums  */
  YYSYMBOL_anynum = 113                    /* anynum  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;



/* Unqualified %code blocks.  */
#line 78 "grammary.y"

int yylex(YYSTYPE *lvalp);

#line 280 "grammary.c"

#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
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
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  356

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   311


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   123,   123,   124,   125,   128,   129,   132,   133,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   152,   153,
     156,   157,   158,   159,   162,   163,   166,   167,   168,   171,
     172,   173,   176,   177,   180,   181,   182,   185,   186,   189,
     190,   193,   194,   197,   200,   201,   204,   207,   210,   213,
     216,   219,   225,   228,   231,   237,   238,   239,   240,   241,
     242,   243,   244,   250,   256,   257,   258,   259,   260,   261,
     262,   263,   270,   271,   272,   273,   274,   275,   276,   277,
     282,   283,   284,   285,   286,   287,   292,   293,   294,   295,
     296,   297,   298,   299,   306,   307,   308,   309,   310,   316,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   340,   341,   344,   345,   346,
     347,   348,   349,   352,   355,   356,   359,   360,   361,   362,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   432,   433,   434,   435,   436,
     437,   440,   441,   444,   445,   446,   447,   450,   451,   454,
     455,   456,   459,   460,   461,   464,   465
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "FUNCTION", "FOR",
  "FOREACH", "DO", "WHILE", "IF", "ELIF", "ELSE", "BREAK", "CONTINUE",
  "RETURN", "INCLUDE", "LOCAL", "REPEAT", "CONST", "TOPEN", "TCLOSE", "MM",
  "MIL", "IN", "DEG", "RAD", "IDENT", "STRING", "NUMBER", "FLOAT", "'='",
  "SUBASSIGN", "ADDASSIGN", "MULASSIGN", "DIVASSIGN", "MODASSIGN",
  "SHLASSIGN", "SHRASSIGN", "ADDORASSIGN", "SUBORASSIGN", "BORASSIGN",
  "BANDASSIGN", "BXORASSIGN", "'?'", "':'", "LOR", "LAND", "'|'", "'^'",
  "'&'", "EQ", "NE", "LT", "GT", "LE", "GE", "SHL", "SHR", "'+'", "'-'",
  "ADDOR", "SUBOR", "'*'", "'/'", "'%'", "INC", "DEC", "'!'", "'~'", "UPM",
  "'['", "'.'", "UID", "'('", "')'", "';'", "','", "']'", "$accept",
  "file", "lines", "line", "cvars", "cvar", "optarglist", "arglist",
  "optv", "optref", "locals", "local", "optassgn", "optstmts", "stmt",
  "optstmt", "foreach", "repeat", "for", "while", "do", "function",
  "boolexpr", "compound", "optelif", "elif", "call", "optargs", "args",
  "expr", "optunit", "optcomma", "veclist", "vlist", "vector", "nums",
  "anynum", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-137)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-126)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
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

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
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
     198,   199,   200,   160,   161,   130,   131,   165,   166,   132,
     133,   215,   209,   216,     0,   212,     0,     1,     4,     6,
      14,    13,    61,     0,    70,     0,    78,    44,    84,     0,
      92,    41,    97,    24,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   167,   168,
       0,     0,   105,     0,    53,   110,   107,    11,     0,    38,
       0,    37,    15,     0,    22,     0,    16,     0,   202,     0,
       0,     0,   126,   211,     0,   210,   134,    60,     0,    69,
       0,    45,     0,    83,     0,    42,     0,    33,     0,    25,
       0,   182,   169,   185,   172,   183,   170,   187,   174,   188,
     175,   189,   176,   190,   177,   191,   178,   184,   171,   186,
     173,   192,   179,   193,   180,   194,   181,     0,   149,   148,
     153,   154,   152,   142,   143,   145,   144,   147,   146,   150,
     151,   135,   137,   136,   138,   139,   140,   141,     0,   158,
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

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -137,  -137,   197,   -27,  -137,    46,  -137,  -137,   -96,   -19,
    -137,    97,  -137,  -136,   -94,   -43,  -137,  -137,  -137,  -137,
    -137,  -137,   -98,  -137,  -137,  -137,  -137,  -137,  -137,    -9,
     237,  -137,  -137,  -137,  -137,  -137,    92
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    28,   175,    30,    61,    62,   178,   179,   287,   180,
      57,    58,   151,   176,    31,   172,    32,    33,    34,    35,
      36,    37,   143,    38,   319,   328,    39,   160,   161,    40,
      73,   159,    41,    66,    42,    84,    85
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
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

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
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

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
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

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
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


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* file: %empty  */
#line 123 "grammary.y"
                                { ; }
#line 1722 "grammary.c"
    break;

  case 3: /* file: lines  */
#line 124 "grammary.y"
                                { scripthead = gethead((yyvsp[0].node)); }
#line 1728 "grammary.c"
    break;

  case 4: /* file: lines error  */
#line 125 "grammary.y"
                                { yyerror("Syntax error"); }
#line 1734 "grammary.c"
    break;

  case 5: /* lines: line  */
#line 128 "grammary.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1740 "grammary.c"
    break;

  case 6: /* lines: lines line  */
#line 129 "grammary.y"
                                { (yyval.node) = node_add((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1746 "grammary.c"
    break;

  case 7: /* line: compound  */
#line 132 "grammary.y"
                                        { (yyval.node) = (yyvsp[0].node); }
#line 1752 "grammary.c"
    break;

  case 8: /* line: INCLUDE '(' STRING ')' ';'  */
#line 133 "grammary.y"
                                        {
			/* Include files is a language construct */
			/* We should get here without a lookahead symbol */
			assert(yychar == YYEMPTY);
			handle_include((yyvsp[-2].str));	/* Setup flex */
			free((yyvsp[-2].str));
			(yyval.node) = NULL;
		}
#line 1765 "grammary.c"
    break;

  case 9: /* line: INCLUDE '(' STRING ')' error  */
#line 141 "grammary.y"
                                        { (yyval.node) = NULL; yyerror("';' expected"); }
#line 1771 "grammary.c"
    break;

  case 10: /* line: INCLUDE '(' STRING error  */
#line 142 "grammary.y"
                                        { (yyval.node) = NULL; yyerror("')' expected"); }
#line 1777 "grammary.c"
    break;

  case 11: /* line: INCLUDE '(' error  */
#line 143 "grammary.y"
                                        { (yyval.node) = NULL; yyerror("String with include filename expected"); }
#line 1783 "grammary.c"
    break;

  case 12: /* line: INCLUDE error  */
#line 144 "grammary.y"
                                        { (yyval.node) = NULL; yyerror("'(' expected"); }
#line 1789 "grammary.c"
    break;

  case 13: /* line: stmt ';'  */
#line 145 "grammary.y"
                                        { (yyval.node) = (yyvsp[-1].node); }
#line 1795 "grammary.c"
    break;

  case 14: /* line: stmt error  */
#line 146 "grammary.y"
                                        { (yyval.node) = NULL; yyerror("';' expected"); }
#line 1801 "grammary.c"
    break;

  case 15: /* line: LOCAL locals ';'  */
#line 147 "grammary.y"
                                        { (yyval.node) = (yyvsp[-1].node); }
#line 1807 "grammary.c"
    break;

  case 16: /* line: CONST cvars ';'  */
#line 148 "grammary.y"
                                        { (yyval.node) = (yyvsp[-1].node); }
#line 1813 "grammary.c"
    break;

  case 17: /* line: ';'  */
#line 149 "grammary.y"
                                        { (yyval.node) = NULL; }
#line 1819 "grammary.c"
    break;

  case 18: /* cvars: cvar  */
#line 152 "grammary.y"
                                        { (yyval.node) = (yyvsp[0].node); }
#line 1825 "grammary.c"
    break;

  case 19: /* cvars: cvars ',' cvar  */
#line 153 "grammary.y"
                                        { (yyval.node) = node_add((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1831 "grammary.c"
    break;

  case 20: /* cvar: IDENT '=' expr  */
#line 156 "grammary.y"
                                        { (yyval.node) = cvar_new((yyvsp[-2].str), (yyvsp[0].node)); }
#line 1837 "grammary.c"
    break;

  case 21: /* cvar: IDENT '=' error  */
#line 157 "grammary.y"
                                        { (yyval.node) = NULL; yyerror("Expression expected"); }
#line 1843 "grammary.c"
    break;

  case 22: /* cvar: IDENT error  */
#line 158 "grammary.y"
                                        { (yyval.node) = NULL; yyerror("'=' expected"); }
#line 1849 "grammary.c"
    break;

  case 23: /* cvar: error  */
#line 159 "grammary.y"
                                        { (yyval.node) = NULL; yyerror("Identifier expected"); }
#line 1855 "grammary.c"
    break;

  case 24: /* optarglist: %empty  */
#line 162 "grammary.y"
                                        { (yyval.node) = NULL; }
#line 1861 "grammary.c"
    break;

  case 25: /* optarglist: arglist  */
#line 163 "grammary.y"
                                        { (yyval.node) = (yyvsp[0].node); }
#line 1867 "grammary.c"
    break;

  case 26: /* arglist: optref IDENT optv  */
#line 166 "grammary.y"
                                        { (yyval.node) = alist_new((yyvsp[-1].str), (yyvsp[-2].i), (yyvsp[0].node)); }
#line 1873 "grammary.c"
    break;

  case 27: /* arglist: arglist ',' optref IDENT optv  */
#line 167 "grammary.y"
                                        { (yyval.node) = alist_add((yyvsp[-4].node), (yyvsp[-1].str), (yyvsp[-2].i), (yyvsp[0].node)); }
#line 1879 "grammary.c"
    break;

  case 28: /* arglist: arglist ',' error  */
#line 168 "grammary.y"
                                        { (yyval.node) = NULL; yyerror("Identifier expected"); }
#line 1885 "grammary.c"
    break;

  case 29: /* optv: %empty  */
#line 171 "grammary.y"
                                        { (yyval.node) = NULL; }
#line 1891 "grammary.c"
    break;

  case 30: /* optv: '=' expr  */
#line 172 "grammary.y"
                                        { (yyval.node) = (yyvsp[0].node); }
#line 1897 "grammary.c"
    break;

  case 31: /* optv: '=' error  */
#line 173 "grammary.y"
                                        { (yyval.node) = NULL; yyerror("Constant expression expected"); }
#line 1903 "grammary.c"
    break;

  case 32: /* optref: %empty  */
#line 176 "grammary.y"
                                        { (yyval.i) = 0; }
#line 1909 "grammary.c"
    break;

  case 33: /* optref: '&'  */
#line 177 "grammary.y"
                                        { (yyval.i) = 1; }
#line 1915 "grammary.c"
    break;

  case 34: /* locals: local  */
#line 180 "grammary.y"
                                        { (yyval.node) = (yyvsp[0].node); }
#line 1921 "grammary.c"
    break;

  case 35: /* locals: locals ',' local  */
#line 181 "grammary.y"
                                        { (yyval.node) = node_add((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1927 "grammary.c"
    break;

  case 36: /* locals: locals ',' error  */
#line 182 "grammary.y"
                                        { (yyval.node) = NULL; yyerror("Identifier expected"); }
#line 1933 "grammary.c"
    break;

  case 37: /* local: IDENT optassgn  */
#line 185 "grammary.y"
                                        { (yyval.node) = lvar_new((yyvsp[-1].str), (yyvsp[0].node)); }
#line 1939 "grammary.c"
    break;

  case 38: /* local: IDENT error  */
#line 186 "grammary.y"
                                        { (yyval.node) = NULL; yyerror("Assignment expected"); }
#line 1945 "grammary.c"
    break;

  case 39: /* optassgn: %empty  */
#line 189 "grammary.y"
                                { (yyval.node) = NULL; }
#line 1951 "grammary.c"
    break;

  case 40: /* optassgn: '=' expr  */
#line 190 "grammary.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1957 "grammary.c"
    break;

  case 41: /* optstmts: %empty  */
#line 193 "grammary.y"
                                { (yyval.node) = NULL; }
#line 1963 "grammary.c"
    break;

  case 42: /* optstmts: lines  */
#line 194 "grammary.y"
                                { (yyval.node) = gethead((yyvsp[0].node)); }
#line 1969 "grammary.c"
    break;

  case 43: /* stmt: expr  */
#line 197 "grammary.y"
                                { (yyval.node) = (yyvsp[0].node); check_const_expr((yyvsp[0].node)); }
#line 1975 "grammary.c"
    break;

  case 44: /* optstmt: %empty  */
#line 200 "grammary.y"
                                { (yyval.node) = NULL; }
#line 1981 "grammary.c"
    break;

  case 45: /* optstmt: stmt  */
#line 201 "grammary.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1987 "grammary.c"
    break;

  case 46: /* foreach: FOREACH  */
#line 204 "grammary.y"
                                { pushtag(newnode(NT_FOREACH)); }
#line 1993 "grammary.c"
    break;

  case 47: /* repeat: REPEAT  */
#line 207 "grammary.y"
                                { pushtag(newnode(NT_REPEAT)); }
#line 1999 "grammary.c"
    break;

  case 48: /* for: FOR  */
#line 210 "grammary.y"
                                { pushtag(newnode(NT_FOR)); }
#line 2005 "grammary.c"
    break;

  case 49: /* while: WHILE  */
#line 213 "grammary.y"
                                { pushtag(newnode(NT_WHILE)); }
#line 2011 "grammary.c"
    break;

  case 50: /* do: DO  */
#line 216 "grammary.y"
                                { pushtag(newnode(NT_DOWHILE)); }
#line 2017 "grammary.c"
    break;

  case 51: /* function: FUNCTION IDENT  */
#line 219 "grammary.y"
                                {
			if(funcname)
				yyerror("Function in functions not supported");
			checkfuncname((yyvsp[0].str));
			(yyval.str) = funcname = (yyvsp[0].str);
		}
#line 2028 "grammary.c"
    break;

  case 52: /* function: FUNCTION error  */
#line 225 "grammary.y"
                                { (yyval.str) = NULL; yyerror("Function name expected"); }
#line 2034 "grammary.c"
    break;

  case 53: /* boolexpr: expr  */
#line 228 "grammary.y"
                                { (yyval.node) = (yyvsp[0].node); check_boolean_expr((yyval.node)); }
#line 2040 "grammary.c"
    break;

  case 54: /* compound: foreach '(' expr ';' IDENT ')' TOPEN optstmts TCLOSE  */
#line 231 "grammary.y"
                                                                        {
			(yyval.node) = poptag();
			(yyval.node)->lfe.src = (yyvsp[-6].node);
			(yyval.node)->lfe.dst = (yyvsp[-4].str);
			(yyval.node)->lfe.stmts = (yyvsp[-1].node);
		}
#line 2051 "grammary.c"
    break;

  case 55: /* compound: foreach '(' expr ';' IDENT ')' TOPEN optstmts error  */
#line 237 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("'}' expected"); }
#line 2057 "grammary.c"
    break;

  case 56: /* compound: foreach '(' expr ';' IDENT ')' error  */
#line 238 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("'{' expected"); }
#line 2063 "grammary.c"
    break;

  case 57: /* compound: foreach '(' expr ';' IDENT error  */
#line 239 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("')' expected"); }
#line 2069 "grammary.c"
    break;

  case 58: /* compound: foreach '(' expr ';' error  */
#line 240 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("Identifier expected"); }
#line 2075 "grammary.c"
    break;

  case 59: /* compound: foreach '(' expr error  */
#line 241 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("';' expected"); }
#line 2081 "grammary.c"
    break;

  case 60: /* compound: foreach '(' error  */
#line 242 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("Vectorlist expression expected"); }
#line 2087 "grammary.c"
    break;

  case 61: /* compound: foreach error  */
#line 243 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("'(' expected"); }
#line 2093 "grammary.c"
    break;

  case 62: /* compound: repeat '(' expr ';' IDENT ')' TOPEN optstmts TCLOSE  */
#line 244 "grammary.y"
                                                                        {
			(yyval.node) = poptag();
			(yyval.node)->lfe.src = (yyvsp[-6].node);
			(yyval.node)->lfe.dst = (yyvsp[-4].str);
			(yyval.node)->lfe.stmts = (yyvsp[-1].node);
		}
#line 2104 "grammary.c"
    break;

  case 63: /* compound: repeat '(' expr ')' TOPEN optstmts TCLOSE  */
#line 250 "grammary.y"
                                                                {
			(yyval.node) = poptag();
			(yyval.node)->lfe.src = (yyvsp[-4].node);
			(yyval.node)->lfe.dst = NULL;
			(yyval.node)->lfe.stmts = (yyvsp[-1].node);
		}
#line 2115 "grammary.c"
    break;

  case 64: /* compound: repeat '(' expr ';' IDENT ')' TOPEN optstmts error  */
#line 256 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("'}' expected"); }
#line 2121 "grammary.c"
    break;

  case 65: /* compound: repeat '(' expr ';' IDENT ')' error  */
#line 257 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("'{' expected"); }
#line 2127 "grammary.c"
    break;

  case 66: /* compound: repeat '(' expr ';' IDENT error  */
#line 258 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("')' expected"); }
#line 2133 "grammary.c"
    break;

  case 67: /* compound: repeat '(' expr ';' error  */
#line 259 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("Identifier expected"); }
#line 2139 "grammary.c"
    break;

  case 68: /* compound: repeat '(' expr error  */
#line 260 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("';' or ')' expected"); }
#line 2145 "grammary.c"
    break;

  case 69: /* compound: repeat '(' error  */
#line 261 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("Integer expression expected"); }
#line 2151 "grammary.c"
    break;

  case 70: /* compound: repeat error  */
#line 262 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("'(' expected"); }
#line 2157 "grammary.c"
    break;

  case 71: /* compound: for '(' optstmt ';' boolexpr ';' optstmt ')' TOPEN optstmts TCLOSE  */
#line 263 "grammary.y"
                                                                                {
			(yyval.node) = poptag();
			(yyval.node)->lfor.init = (yyvsp[-8].node);
			(yyval.node)->lfor.cond = (yyvsp[-6].node);
			(yyval.node)->lfor.inc = (yyvsp[-4].node);
			(yyval.node)->lfor.stmts = (yyvsp[-1].node);
		}
#line 2169 "grammary.c"
    break;

  case 72: /* compound: for '(' optstmt ';' boolexpr ';' optstmt ')' TOPEN optstmts error  */
#line 270 "grammary.y"
                                                                                { (yyval.node) = NULL; yyerror("'}' expected"); }
#line 2175 "grammary.c"
    break;

  case 73: /* compound: for '(' optstmt ';' boolexpr ';' optstmt ')' error  */
#line 271 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("'{' expected"); }
#line 2181 "grammary.c"
    break;

  case 74: /* compound: for '(' optstmt ';' boolexpr ';' optstmt error  */
#line 272 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("')' expected"); }
#line 2187 "grammary.c"
    break;

  case 75: /* compound: for '(' optstmt ';' boolexpr error  */
#line 273 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("';' expected"); }
#line 2193 "grammary.c"
    break;

  case 76: /* compound: for '(' optstmt ';' error  */
#line 274 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("Conditional expression expected"); }
#line 2199 "grammary.c"
    break;

  case 77: /* compound: for '(' optstmt error  */
#line 275 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("';' expected"); }
#line 2205 "grammary.c"
    break;

  case 78: /* compound: for error  */
#line 276 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("'(' expected"); }
#line 2211 "grammary.c"
    break;

  case 79: /* compound: while '(' boolexpr ')' TOPEN optstmts TCLOSE  */
#line 277 "grammary.y"
                                                                        {
			(yyval.node) = poptag();
			(yyval.node)->lfor.cond = (yyvsp[-4].node);
			(yyval.node)->lfor.stmts = (yyvsp[-1].node);
		}
#line 2221 "grammary.c"
    break;

  case 80: /* compound: while '(' boolexpr ')' TOPEN optstmts error  */
#line 282 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("'}' expected"); }
#line 2227 "grammary.c"
    break;

  case 81: /* compound: while '(' boolexpr ')' error  */
#line 283 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("'{' expected"); }
#line 2233 "grammary.c"
    break;

  case 82: /* compound: while '(' boolexpr error  */
#line 284 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("')' expected"); }
#line 2239 "grammary.c"
    break;

  case 83: /* compound: while '(' error  */
#line 285 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("Conditional expression expected"); }
#line 2245 "grammary.c"
    break;

  case 84: /* compound: while error  */
#line 286 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("'(' expected"); }
#line 2251 "grammary.c"
    break;

  case 85: /* compound: do TOPEN optstmts TCLOSE WHILE '(' boolexpr ')' ';'  */
#line 287 "grammary.y"
                                                                        {
			(yyval.node) = poptag();
			(yyval.node)->lfor.cond = (yyvsp[-2].node);
			(yyval.node)->lfor.stmts = (yyvsp[-6].node);
		}
#line 2261 "grammary.c"
    break;

  case 86: /* compound: do TOPEN optstmts TCLOSE WHILE '(' boolexpr ')' error  */
#line 292 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("';' expected"); }
#line 2267 "grammary.c"
    break;

  case 87: /* compound: do TOPEN optstmts TCLOSE WHILE '(' boolexpr error  */
#line 293 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("')' expected"); }
#line 2273 "grammary.c"
    break;

  case 88: /* compound: do TOPEN optstmts TCLOSE WHILE '(' error  */
#line 294 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("Conditional expression expected"); }
#line 2279 "grammary.c"
    break;

  case 89: /* compound: do TOPEN optstmts TCLOSE WHILE error  */
#line 295 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("'(' expected"); }
#line 2285 "grammary.c"
    break;

  case 90: /* compound: do TOPEN optstmts TCLOSE error  */
#line 296 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("'while' expected"); }
#line 2291 "grammary.c"
    break;

  case 91: /* compound: do TOPEN optstmts error  */
#line 297 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("'}' expected"); }
#line 2297 "grammary.c"
    break;

  case 92: /* compound: do error  */
#line 298 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("'{' expected"); }
#line 2303 "grammary.c"
    break;

  case 93: /* compound: function '(' optarglist ')' TOPEN optstmts TCLOSE  */
#line 299 "grammary.y"
                                                                {
			(yyval.node) = newnode(NT_FUNCTION);
			(yyval.node)->func.id = (yyvsp[-6].str);
			(yyval.node)->func.args = (yyvsp[-4].node);
			(yyval.node)->func.body = (yyvsp[-1].node);
			funcname = NULL;
		}
#line 2315 "grammary.c"
    break;

  case 94: /* compound: function '(' optarglist ')' TOPEN optstmts error  */
#line 306 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("'}' expected"); funcname = NULL; }
#line 2321 "grammary.c"
    break;

  case 95: /* compound: function '(' optarglist ')' error  */
#line 307 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("'{' expected"); funcname = NULL; }
#line 2327 "grammary.c"
    break;

  case 96: /* compound: function '(' optarglist error  */
#line 308 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("')' expected"); funcname = NULL; }
#line 2333 "grammary.c"
    break;

  case 97: /* compound: function error  */
#line 309 "grammary.y"
                                                                        { (yyval.node) = NULL; yyerror("'(' expected"); funcname = NULL; }
#line 2339 "grammary.c"
    break;

  case 98: /* compound: IF '(' boolexpr ')' TOPEN optstmts TCLOSE optelif  */
#line 310 "grammary.y"
                                                                                {
			(yyval.node) = newnode(NT_IF);
			(yyval.node)->cond.cond = (yyvsp[-5].node);
			(yyval.node)->cond.ifclause = (yyvsp[-2].node);
			(yyval.node)->cond.elifclauses = gethead((yyvsp[0].node));
		}
#line 2350 "grammary.c"
    break;

  case 99: /* compound: IF '(' boolexpr ')' TOPEN optstmts TCLOSE optelif ELSE TOPEN optstmts TCLOSE  */
#line 316 "grammary.y"
                                                                                        {
			(yyval.node) = newnode(NT_IF);
			(yyval.node)->cond.cond = (yyvsp[-9].node);
			(yyval.node)->cond.ifclause = (yyvsp[-6].node);
			(yyval.node)->cond.elifclauses = gethead((yyvsp[-4].node));
			(yyval.node)->cond.elseclause = (yyvsp[-1].node);
		}
#line 2362 "grammary.c"
    break;

  case 100: /* compound: IF '(' boolexpr ')' TOPEN optstmts TCLOSE optelif ELSE TOPEN optstmts error  */
#line 323 "grammary.y"
                                                                                        { (yyval.node) = NULL; yyerror("'}' expected"); }
#line 2368 "grammary.c"
    break;

  case 101: /* compound: IF '(' boolexpr ')' TOPEN optstmts TCLOSE optelif ELSE error  */
#line 324 "grammary.y"
                                                                                        { (yyval.node) = NULL; yyerror("'{' expected"); }
#line 2374 "grammary.c"
    break;

  case 102: /* compound: IF '(' boolexpr ')' TOPEN optstmts error  */
#line 325 "grammary.y"
                                                                                        { (yyval.node) = NULL; yyerror("'}' expected"); }
#line 2380 "grammary.c"
    break;

  case 103: /* compound: IF '(' boolexpr ')' error  */
#line 326 "grammary.y"
                                        { (yyval.node) = NULL; yyerror("'{' expected"); }
#line 2386 "grammary.c"
    break;

  case 104: /* compound: IF '(' boolexpr error  */
#line 327 "grammary.y"
                                        { (yyval.node) = NULL; yyerror("')' expected"); }
#line 2392 "grammary.c"
    break;

  case 105: /* compound: IF '(' error  */
#line 328 "grammary.y"
                                        { (yyval.node) = NULL; yyerror("Conditional expression expected"); }
#line 2398 "grammary.c"
    break;

  case 106: /* compound: IF error  */
#line 329 "grammary.y"
                                        { (yyval.node) = NULL; yyerror("'(' expected"); }
#line 2404 "grammary.c"
    break;

  case 107: /* compound: RETURN expr ';'  */
#line 330 "grammary.y"
                                        { (yyval.node) = node_new(NT_RETURN, (yyvsp[-1].node)); }
#line 2410 "grammary.c"
    break;

  case 108: /* compound: RETURN ';'  */
#line 331 "grammary.y"
                                        { (yyval.node) = node_new(NT_RETURN, NULL); }
#line 2416 "grammary.c"
    break;

  case 109: /* compound: RETURN error  */
#line 332 "grammary.y"
                                        { (yyval.node) = NULL; yyerror("Expression or ';' expected"); }
#line 2422 "grammary.c"
    break;

  case 110: /* compound: RETURN expr error  */
#line 333 "grammary.y"
                                        { (yyval.node) = NULL; yyerror("';' expected"); }
#line 2428 "grammary.c"
    break;

  case 111: /* compound: BREAK ';'  */
#line 334 "grammary.y"
                                        { (yyval.node) = node_new(NT_BREAK, NULL); }
#line 2434 "grammary.c"
    break;

  case 112: /* compound: BREAK error  */
#line 335 "grammary.y"
                                        { (yyval.node) = NULL; yyerror("';' expected"); }
#line 2440 "grammary.c"
    break;

  case 113: /* compound: CONTINUE ';'  */
#line 336 "grammary.y"
                                        { (yyval.node) = node_new(NT_CONTINUE, NULL); }
#line 2446 "grammary.c"
    break;

  case 114: /* compound: CONTINUE error  */
#line 337 "grammary.y"
                                        { (yyval.node) = NULL; yyerror("';' expected"); }
#line 2452 "grammary.c"
    break;

  case 115: /* optelif: %empty  */
#line 340 "grammary.y"
                                { (yyval.node) = NULL; }
#line 2458 "grammary.c"
    break;

  case 116: /* optelif: optelif elif  */
#line 341 "grammary.y"
                                { (yyval.node) = (yyvsp[0].node); if((yyvsp[-1].node)) { (yyvsp[-1].node)->next = (yyvsp[0].node); (yyvsp[0].node)->prev = (yyvsp[-1].node);} }
#line 2464 "grammary.c"
    break;

  case 117: /* elif: ELIF '(' boolexpr ')' TOPEN optstmts TCLOSE  */
#line 344 "grammary.y"
                                                        { (yyval.node) = newnode(NT_ELIF); (yyval.node)->cond.cond = (yyvsp[-4].node); (yyval.node)->cond.ifclause = (yyvsp[-1].node); }
#line 2470 "grammary.c"
    break;

  case 118: /* elif: ELIF '(' boolexpr ')' TOPEN optstmts error  */
#line 345 "grammary.y"
                                                        { (yyval.node) = NULL; yyerror("'}' expected"); }
#line 2476 "grammary.c"
    break;

  case 119: /* elif: ELIF '(' boolexpr ')' error  */
#line 346 "grammary.y"
                                                        { (yyval.node) = NULL; yyerror("'{' expected"); }
#line 2482 "grammary.c"
    break;

  case 120: /* elif: ELIF '(' boolexpr error  */
#line 347 "grammary.y"
                                                        { (yyval.node) = NULL; yyerror("')' expected"); }
#line 2488 "grammary.c"
    break;

  case 121: /* elif: ELIF '(' error  */
#line 348 "grammary.y"
                                                        { (yyval.node) = NULL; yyerror("Conditional expression expected"); }
#line 2494 "grammary.c"
    break;

  case 122: /* elif: ELIF error  */
#line 349 "grammary.y"
                                                        { (yyval.node) = NULL; yyerror("'(' expected"); }
#line 2500 "grammary.c"
    break;

  case 123: /* call: IDENT '(' optargs ')'  */
#line 352 "grammary.y"
                                { (yyval.node) = expr_new_call((yyvsp[-3].str), (yyvsp[-1].node)); }
#line 2506 "grammary.c"
    break;

  case 124: /* optargs: %empty  */
#line 355 "grammary.y"
                                { (yyval.node) = NULL; }
#line 2512 "grammary.c"
    break;

  case 125: /* optargs: args  */
#line 356 "grammary.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 2518 "grammary.c"
    break;

  case 126: /* args: expr  */
#line 359 "grammary.y"
                                { (yyval.node) = elist_new((yyvsp[0].node)); }
#line 2524 "grammary.c"
    break;

  case 127: /* args: args ',' expr  */
#line 360 "grammary.y"
                                { (yyval.node) = elist_add((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2530 "grammary.c"
    break;

  case 128: /* args: args ',' error  */
#line 361 "grammary.y"
                                { (yyval.node) = (yyvsp[-2].node); yyerror("Expression expected after ','"); }
#line 2536 "grammary.c"
    break;

  case 129: /* args: args error  */
#line 362 "grammary.y"
                                { (yyval.node) = (yyvsp[-1].node); yyerror("',' expected"); }
#line 2542 "grammary.c"
    break;

  case 130: /* expr: '+' expr  */
#line 365 "grammary.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 2548 "grammary.c"
    break;

  case 131: /* expr: '-' expr  */
#line 366 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[0].node), expr_new_int(-1, UNIT_NONE), OP_MUL); }
#line 2554 "grammary.c"
    break;

  case 132: /* expr: '!' expr  */
#line 367 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[0].node), NULL, OP_NOT); }
#line 2560 "grammary.c"
    break;

  case 133: /* expr: '~' expr  */
#line 368 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[0].node), NULL, OP_BNOT); }
#line 2566 "grammary.c"
    break;

  case 134: /* expr: '(' expr ')'  */
#line 369 "grammary.y"
                                { (yyval.node) = (yyvsp[-1].node); (yyval.node)->expr.inparen = 1; }
#line 2572 "grammary.c"
    break;

  case 135: /* expr: expr '+' expr  */
#line 370 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[-2].node), (yyvsp[0].node), OP_ADD); }
#line 2578 "grammary.c"
    break;

  case 136: /* expr: expr ADDOR expr  */
#line 371 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[-2].node), (yyvsp[0].node), OP_ADDOR); }
#line 2584 "grammary.c"
    break;

  case 137: /* expr: expr '-' expr  */
#line 372 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[-2].node), (yyvsp[0].node), OP_SUB); }
#line 2590 "grammary.c"
    break;

  case 138: /* expr: expr SUBOR expr  */
#line 373 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[-2].node), (yyvsp[0].node), OP_SUBOR); }
#line 2596 "grammary.c"
    break;

  case 139: /* expr: expr '*' expr  */
#line 374 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[-2].node), (yyvsp[0].node), OP_MUL); }
#line 2602 "grammary.c"
    break;

  case 140: /* expr: expr '/' expr  */
#line 375 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[-2].node), (yyvsp[0].node), OP_DIV); }
#line 2608 "grammary.c"
    break;

  case 141: /* expr: expr '%' expr  */
#line 376 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[-2].node), (yyvsp[0].node), OP_MOD); }
#line 2614 "grammary.c"
    break;

  case 142: /* expr: expr EQ expr  */
#line 377 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[-2].node), (yyvsp[0].node), OP_EQ); }
#line 2620 "grammary.c"
    break;

  case 143: /* expr: expr NE expr  */
#line 378 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[-2].node), (yyvsp[0].node), OP_NE); }
#line 2626 "grammary.c"
    break;

  case 144: /* expr: expr GT expr  */
#line 379 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[-2].node), (yyvsp[0].node), OP_GT); }
#line 2632 "grammary.c"
    break;

  case 145: /* expr: expr LT expr  */
#line 380 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[-2].node), (yyvsp[0].node), OP_LT); }
#line 2638 "grammary.c"
    break;

  case 146: /* expr: expr GE expr  */
#line 381 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[-2].node), (yyvsp[0].node), OP_GE); }
#line 2644 "grammary.c"
    break;

  case 147: /* expr: expr LE expr  */
#line 382 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[-2].node), (yyvsp[0].node), OP_LE); }
#line 2650 "grammary.c"
    break;

  case 148: /* expr: expr LAND expr  */
#line 383 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[-2].node), (yyvsp[0].node), OP_LAND); }
#line 2656 "grammary.c"
    break;

  case 149: /* expr: expr LOR expr  */
#line 384 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[-2].node), (yyvsp[0].node), OP_LOR); }
#line 2662 "grammary.c"
    break;

  case 150: /* expr: expr SHL expr  */
#line 385 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[-2].node), (yyvsp[0].node), OP_SHL); }
#line 2668 "grammary.c"
    break;

  case 151: /* expr: expr SHR expr  */
#line 386 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[-2].node), (yyvsp[0].node), OP_SHR); }
#line 2674 "grammary.c"
    break;

  case 152: /* expr: expr '&' expr  */
#line 387 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[-2].node), (yyvsp[0].node), OP_BAND); }
#line 2680 "grammary.c"
    break;

  case 153: /* expr: expr '|' expr  */
#line 388 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[-2].node), (yyvsp[0].node), OP_BOR); }
#line 2686 "grammary.c"
    break;

  case 154: /* expr: expr '^' expr  */
#line 389 "grammary.y"
                                { (yyval.node) = expr_new((yyvsp[-2].node), (yyvsp[0].node), OP_BXOR); }
#line 2692 "grammary.c"
    break;

  case 155: /* expr: expr '?' expr ':' expr  */
#line 390 "grammary.y"
                                 {(yyval.node) = expr_new_tern((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), OP_CONDEXPR); }
#line 2698 "grammary.c"
    break;

  case 156: /* expr: call  */
#line 391 "grammary.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 2704 "grammary.c"
    break;

  case 157: /* expr: expr '[' expr ']'  */
#line 392 "grammary.y"
                                { (yyval.node) = expr_new_idx((yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2710 "grammary.c"
    break;

  case 158: /* expr: expr '.' IDENT  */
#line 393 "grammary.y"
                                { (yyval.node) = expr_new_idxid((yyvsp[-2].node), (yyvsp[0].str)); }
#line 2716 "grammary.c"
    break;

  case 159: /* expr: IDENT  */
#line 394 "grammary.y"
                                { (yyval.node) = expr_new_id((yyvsp[0].str)); }
#line 2722 "grammary.c"
    break;

  case 160: /* expr: NUMBER optunit  */
#line 395 "grammary.y"
                                { (yyval.node) = expr_new_int((yyvsp[-1].i), (yyvsp[0].i)); }
#line 2728 "grammary.c"
    break;

  case 161: /* expr: FLOAT optunit  */
#line 396 "grammary.y"
                                { (yyval.node) = expr_new_flt((yyvsp[-1].d), (yyvsp[0].i)); }
#line 2734 "grammary.c"
    break;

  case 162: /* expr: STRING  */
#line 397 "grammary.y"
                                { (yyval.node) = expr_new_str((yyvsp[0].str)); }
#line 2740 "grammary.c"
    break;

  case 163: /* expr: vector  */
#line 398 "grammary.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 2746 "grammary.c"
    break;

  case 164: /* expr: veclist  */
#line 399 "grammary.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 2752 "grammary.c"
    break;

  case 165: /* expr: INC expr  */
#line 400 "grammary.y"
                                { (yyval.node) = expr_new_unary((yyvsp[0].node), OP_PREINC); }
#line 2758 "grammary.c"
    break;

  case 166: /* expr: DEC expr  */
#line 401 "grammary.y"
                                { (yyval.node) = expr_new_unary((yyvsp[0].node), OP_PREDEC); }
#line 2764 "grammary.c"
    break;

  case 167: /* expr: expr INC  */
#line 402 "grammary.y"
                                { (yyval.node) = expr_new_unary((yyvsp[-1].node), OP_POSTINC); check_useless((yyval.node)); }
#line 2770 "grammary.c"
    break;

  case 168: /* expr: expr DEC  */
#line 403 "grammary.y"
                                { (yyval.node) = expr_new_unary((yyvsp[-1].node), OP_POSTDEC); check_useless((yyval.node)); }
#line 2776 "grammary.c"
    break;

  case 169: /* expr: expr '=' expr  */
#line 404 "grammary.y"
                                { (yyval.node) = node_new_assign((yyvsp[-2].node), OP_ASSIGN, (yyvsp[0].node)); }
#line 2782 "grammary.c"
    break;

  case 170: /* expr: expr ADDASSIGN expr  */
#line 405 "grammary.y"
                                { (yyval.node) = node_new_assign((yyvsp[-2].node), OP_ADDASSIGN, (yyvsp[0].node)); }
#line 2788 "grammary.c"
    break;

  case 171: /* expr: expr ADDORASSIGN expr  */
#line 406 "grammary.y"
                                { (yyval.node) = node_new_assign((yyvsp[-2].node), OP_ADDORASSIGN, (yyvsp[0].node)); }
#line 2794 "grammary.c"
    break;

  case 172: /* expr: expr SUBASSIGN expr  */
#line 407 "grammary.y"
                                { (yyval.node) = node_new_assign((yyvsp[-2].node), OP_SUBASSIGN, (yyvsp[0].node)); }
#line 2800 "grammary.c"
    break;

  case 173: /* expr: expr SUBORASSIGN expr  */
#line 408 "grammary.y"
                                { (yyval.node) = node_new_assign((yyvsp[-2].node), OP_SUBORASSIGN, (yyvsp[0].node)); }
#line 2806 "grammary.c"
    break;

  case 174: /* expr: expr MULASSIGN expr  */
#line 409 "grammary.y"
                                { (yyval.node) = node_new_assign((yyvsp[-2].node), OP_MULASSIGN, (yyvsp[0].node)); }
#line 2812 "grammary.c"
    break;

  case 175: /* expr: expr DIVASSIGN expr  */
#line 410 "grammary.y"
                                { (yyval.node) = node_new_assign((yyvsp[-2].node), OP_DIVASSIGN, (yyvsp[0].node)); }
#line 2818 "grammary.c"
    break;

  case 176: /* expr: expr MODASSIGN expr  */
#line 411 "grammary.y"
                                { (yyval.node) = node_new_assign((yyvsp[-2].node), OP_MODASSIGN, (yyvsp[0].node)); }
#line 2824 "grammary.c"
    break;

  case 177: /* expr: expr SHLASSIGN expr  */
#line 412 "grammary.y"
                                { (yyval.node) = node_new_assign((yyvsp[-2].node), OP_SHLASSIGN, (yyvsp[0].node)); }
#line 2830 "grammary.c"
    break;

  case 178: /* expr: expr SHRASSIGN expr  */
#line 413 "grammary.y"
                                { (yyval.node) = node_new_assign((yyvsp[-2].node), OP_SHRASSIGN, (yyvsp[0].node)); }
#line 2836 "grammary.c"
    break;

  case 179: /* expr: expr BORASSIGN expr  */
#line 414 "grammary.y"
                                { (yyval.node) = node_new_assign((yyvsp[-2].node), OP_BORASSIGN, (yyvsp[0].node)); }
#line 2842 "grammary.c"
    break;

  case 180: /* expr: expr BANDASSIGN expr  */
#line 415 "grammary.y"
                                { (yyval.node) = node_new_assign((yyvsp[-2].node), OP_BANDASSIGN, (yyvsp[0].node)); }
#line 2848 "grammary.c"
    break;

  case 181: /* expr: expr BXORASSIGN expr  */
#line 416 "grammary.y"
                                { (yyval.node) = node_new_assign((yyvsp[-2].node), OP_BXORASSIGN, (yyvsp[0].node)); }
#line 2854 "grammary.c"
    break;

  case 182: /* expr: expr '=' error  */
#line 417 "grammary.y"
                                { (yyval.node) = (yyvsp[-2].node); yyerror("Expression expected after '='"); }
#line 2860 "grammary.c"
    break;

  case 183: /* expr: expr ADDASSIGN error  */
#line 418 "grammary.y"
                                { (yyval.node) = (yyvsp[-2].node); yyerror("Expression expected after '+='"); }
#line 2866 "grammary.c"
    break;

  case 184: /* expr: expr ADDORASSIGN error  */
#line 419 "grammary.y"
                                { (yyval.node) = (yyvsp[-2].node); yyerror("Expression expected after '+|='"); }
#line 2872 "grammary.c"
    break;

  case 185: /* expr: expr SUBASSIGN error  */
#line 420 "grammary.y"
                                { (yyval.node) = (yyvsp[-2].node); yyerror("Expression expected after '-='"); }
#line 2878 "grammary.c"
    break;

  case 186: /* expr: expr SUBORASSIGN error  */
#line 421 "grammary.y"
                                { (yyval.node) = (yyvsp[-2].node); yyerror("Expression expected after '-|='"); }
#line 2884 "grammary.c"
    break;

  case 187: /* expr: expr MULASSIGN error  */
#line 422 "grammary.y"
                                { (yyval.node) = (yyvsp[-2].node); yyerror("Expression expected after '*='"); }
#line 2890 "grammary.c"
    break;

  case 188: /* expr: expr DIVASSIGN error  */
#line 423 "grammary.y"
                                { (yyval.node) = (yyvsp[-2].node); yyerror("Expression expected after '/='"); }
#line 2896 "grammary.c"
    break;

  case 189: /* expr: expr MODASSIGN error  */
#line 424 "grammary.y"
                                { (yyval.node) = (yyvsp[-2].node); yyerror("Expression expected after '%%='"); }
#line 2902 "grammary.c"
    break;

  case 190: /* expr: expr SHLASSIGN error  */
#line 425 "grammary.y"
                                { (yyval.node) = (yyvsp[-2].node); yyerror("Expression expected after '<<='"); }
#line 2908 "grammary.c"
    break;

  case 191: /* expr: expr SHRASSIGN error  */
#line 426 "grammary.y"
                                { (yyval.node) = (yyvsp[-2].node); yyerror("Expression expected after '>>='"); }
#line 2914 "grammary.c"
    break;

  case 192: /* expr: expr BORASSIGN error  */
#line 427 "grammary.y"
                                { (yyval.node) = (yyvsp[-2].node); yyerror("Expression expected after '|='"); }
#line 2920 "grammary.c"
    break;

  case 193: /* expr: expr BANDASSIGN error  */
#line 428 "grammary.y"
                                { (yyval.node) = (yyvsp[-2].node); yyerror("Expression expected after '&='"); }
#line 2926 "grammary.c"
    break;

  case 194: /* expr: expr BXORASSIGN error  */
#line 429 "grammary.y"
                                { (yyval.node) = (yyvsp[-2].node); yyerror("Expression expected after '^='"); }
#line 2932 "grammary.c"
    break;

  case 195: /* optunit: %empty  */
#line 432 "grammary.y"
                                { (yyval.i) = UNIT_NONE; }
#line 2938 "grammary.c"
    break;

  case 196: /* optunit: MM  */
#line 433 "grammary.y"
                                { (yyval.i) = UNIT_MM; }
#line 2944 "grammary.c"
    break;

  case 197: /* optunit: MIL  */
#line 434 "grammary.y"
                                { (yyval.i) = _UNIT_MIL; }
#line 2950 "grammary.c"
    break;

  case 198: /* optunit: IN  */
#line 435 "grammary.y"
                                { (yyval.i) = UNIT_IN; }
#line 2956 "grammary.c"
    break;

  case 199: /* optunit: DEG  */
#line 436 "grammary.y"
                                { (yyval.i) = UNIT_DEG; }
#line 2962 "grammary.c"
    break;

  case 200: /* optunit: RAD  */
#line 437 "grammary.y"
                                { (yyval.i) = UNIT_RAD; }
#line 2968 "grammary.c"
    break;

  case 203: /* veclist: TOPEN vlist optcomma TCLOSE  */
#line 444 "grammary.y"
                                        { (yyval.node) = (yyvsp[-2].node); }
#line 2974 "grammary.c"
    break;

  case 204: /* veclist: TOPEN TCLOSE  */
#line 445 "grammary.y"
                                        { (yyval.node) = vlist_new(NULL); }
#line 2980 "grammary.c"
    break;

  case 205: /* veclist: TOPEN error  */
#line 446 "grammary.y"
                                        { (yyval.node) = NULL; yyerror("'}' expected"); }
#line 2986 "grammary.c"
    break;

  case 206: /* veclist: TOPEN vlist optcomma error  */
#line 447 "grammary.y"
                                        { (yyval.node) = (yyvsp[-2].node); yyerror("'}' expected"); }
#line 2992 "grammary.c"
    break;

  case 207: /* vlist: expr  */
#line 450 "grammary.y"
                                { (yyval.node) = vlist_new((yyvsp[0].node)); }
#line 2998 "grammary.c"
    break;

  case 208: /* vlist: vlist ',' expr  */
#line 451 "grammary.y"
                                { (yyval.node) = vlist_add((yyvsp[-2].node), (yyvsp[0].node)); }
#line 3004 "grammary.c"
    break;

  case 209: /* vector: '[' ']'  */
#line 454 "grammary.y"
                                { (yyval.node) = vec_new(NULL, 0); }
#line 3010 "grammary.c"
    break;

  case 210: /* vector: '[' nums ']'  */
#line 455 "grammary.y"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 3016 "grammary.c"
    break;

  case 211: /* vector: '[' nums error  */
#line 456 "grammary.y"
                                { (yyval.node) = (yyvsp[-1].node); yyerror("']' expected"); }
#line 3022 "grammary.c"
    break;

  case 212: /* nums: anynum  */
#line 459 "grammary.y"
                                { (yyval.node) = vec_new((yyvsp[0].node), 1); }
#line 3028 "grammary.c"
    break;

  case 213: /* nums: nums ',' anynum  */
#line 460 "grammary.y"
                                { (yyval.node) = vec_add((yyvsp[-2].node), (yyvsp[0].node)); }
#line 3034 "grammary.c"
    break;

  case 214: /* nums: nums ',' error  */
#line 461 "grammary.y"
                                { (yyval.node) = (yyvsp[-2].node); yyerror("Scalar expression or '-' expected"); }
#line 3040 "grammary.c"
    break;

  case 215: /* anynum: '-'  */
#line 464 "grammary.y"
                                { (yyval.node) = NULL; }
#line 3046 "grammary.c"
    break;

  case 216: /* anynum: expr  */
#line 465 "grammary.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 3052 "grammary.c"
    break;


#line 3056 "grammary.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 468 "grammary.y"

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

GCMC_TLS static node_t **nodestack;
GCMC_TLS static int nnodestack;
GCMC_TLS static int nanodestack;

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

GCMC_TLS static const wchar_t **funcs;
GCMC_TLS static int nfuncs;
GCMC_TLS static int nafuncs;

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
