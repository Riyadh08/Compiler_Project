
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "ryad.y"

    #include <stdio.h>
    #include <string.h>
    #include <math.h>
    #include <stdlib.h>

    int yylex();
    int yyerror(char* s);
  
    #define var_allowed 100
    int case_matched = 0;
    int VAR_CNT = 0, FUNC_CNT = 0;
    #define func_allowed 100
    int func_flag = 0, curr_function = 0, curr_parameter = 0, func_rejec = 0;

    typedef struct {
        char *name;
        int type;
        int length;
        int *ival;   //for the integer variable
        double *dval;  //for the double variable  
        char **sval;  //for string variable, pointer to pointer character array
    } info;    //storing the variable information
    info *varptr;  //the size is later given in the main function

    typedef struct {
        char *fname;
        info *fptr;
        int var_cnt;
    } stackfun;
    stackfun *funcptr;  //the size is later given in the main function

    int check_unique(char *name) {  //check for duplicate variable name
        for(int i = 0; i < VAR_CNT; ++i) {
            if(strcmp(varptr[i].name, name) == 0) {
                return -1;   //not unique
            }
        }
        return 1;  //unique
    } 

    int variable_index(char *name) {  //return the variable index
        for(int i = 0; i < VAR_CNT; ++i) {
            if(strcmp(varptr[i].name, name) == 0) {
                return i;
            }
        }
        return -1;    //when the variable is not declared
    }

    int function_index(char *name){
        for(int i = 0; i < FUNC_CNT; ++i) {
            if(strcmp(funcptr[i].fname, name) == 0) {
                return i;
            }
        }
        return -1;
    }

    void variable_info(char *n, int t, int l, int p, void *v) {  //store variable information
        varptr[p].name = n;
        varptr[p].type = t;
        varptr[p].length = l;
        if(t == 1) { //1 for integer
            int *value = (int *) v;
            varptr[p].ival = malloc(l * sizeof(int));
            for(int i = 0; i < l; ++i) {
                varptr[p].ival[i] = value[i];
            }
            printf("Variable initialized: %s is Integer, Value: %d\n", varptr[p].name, *varptr[p].ival);
        } else if(t == 2) { //2 for float
            double *value = (double *) v;
            varptr[p].dval = malloc(l * sizeof(double));
            for(int i = 0; i < l; ++i) {
                varptr[p].dval[i] = value[i];
            }
            printf("Variable initialized: %s is Flaoting Point Number, Value: %lf\n", varptr[p].name, *varptr[p].dval);
        } else if(t == 3) {  //3 for string
            char **s = ((char**) v);
            varptr[p].sval = malloc(l * sizeof(char**));
            for(int i = 0; i < l; ++i) {
                varptr[p].sval[i] = s[i];
            }
            printf("Variable initialized: %s is String, Value: %s\n", varptr[p].name, *varptr[p].sval);
        }
    }
    
    void read_value(char *name, int p) {
        int index = variable_index(name);
        if (index == -1) {
            printf("Variable \"%s\" doesn't exist.\n", name);
        } else {
            if(p >= varptr[index].length) {
                printf("Maximum Number of Variables Used.\n");
            } else {
                if (varptr[index].type == 2) { //2 for float
                    printf("Enter Input for float variable %s: \n", name);
                    scanf("%lf", &varptr[index].dval[p]);
                } else if (varptr[index].type == 1) { //1 for integer
                    printf("Enter Input for integer variable %s: \n", name);
                    scanf("%d", &varptr[index].ival[p]);
                } else if(varptr[index].type == 3) { //3 for string
                    printf("Enter Input for string variable %s: \n", name);
                    char str [1000];
                    //scanf("%s", str);
                    //varptr[index].sval[p] = str;
                }
            }
        }
    }
    void print_value(char *name) {
        int index = variable_index(name);
        if(index == -1) {
            printf("Variable \"%s\" doesn't exist.\n", name);
        } else {
             
                printf("Value of %s is: ", name);
                if(varptr[index].type == 1) {   //1 for integer
                    printf("%d\n", varptr[index].ival[0]);
                } else if(varptr[index].type == 2) {   //2 for float
                    printf("%lf\n", varptr[index].dval[0]);
                } else if(varptr[index].type == 3) {   //3 for string
                    printf("%s\n", varptr[index].sval[0]);
                }
            
        }
    }
    
    


/* Line 189 of yacc.c  */
#line 205 "ryad.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     VARIABLE = 258,
     INPUT = 259,
     PRINT = 260,
     DISPLAY = 261,
     START = 262,
     FINISH = 263,
     BY = 264,
     MAIN = 265,
     NUMBER_TYPE = 266,
     DECIMAL_TYPE = 267,
     STRING_TYPE = 268,
     NUMBER_VALUE = 269,
     DECIMAL_VALUE = 270,
     STRING_VALUE = 271,
     AND = 272,
     OR = 273,
     XOR = 274,
     NOT = 275,
     INC = 276,
     DEC = 277,
     LT = 278,
     GT = 279,
     EQL = 280,
     NEQL = 281,
     LEQL = 282,
     GEQL = 283,
     ONLY_INC = 284,
     ONLY_DEC = 285,
     POW = 286,
     SIN = 287,
     COS = 288,
     TAN = 289,
     LOG10 = 290,
     LOG2 = 291,
     LN = 292,
     SQRT = 293,
     DEF = 294,
     CALL = 295,
     IF = 296,
     EL_IF = 297,
     ELSE = 298,
     FOR = 299,
     IN = 300,
     WHILE = 301,
     SWITCH = 302,
     CASE = 303,
     DEFAULT = 304,
     HEADER = 305,
     S_COMMENT = 306,
     M_COMMENT = 307,
     EOL = 308
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 135 "ryad.y"
       //defines the types of tokens that the grammar can recognize
	int integer;
	double floating_num;
	char *string;



/* Line 214 of yacc.c  */
#line 302 "ryad.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 314 "ryad.tab.c"

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
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   725

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  119
/* YYNRULES -- Number of states.  */
#define YYNSTATES  271

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    58,     2,     2,
      61,    62,    56,    54,    63,    55,     2,    57,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    66,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    64,     2,    65,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    59,     2,    60,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,    13,    16,    18,    21,    23,    25,    27,
      28,    29,    32,    34,    38,    40,    42,    45,    48,    51,
      53,    55,    57,    59,    62,    65,    68,    73,    78,    82,
      84,    89,    93,    95,    98,   100,   110,   112,   114,   116,
     118,   119,   123,   125,   128,   131,   137,   139,   143,   145,
     147,   148,   167,   172,   175,   177,   185,   190,   198,   203,
     208,   213,   218,   223,   228,   237,   245,   247,   256,   261,
     269,   272,   275,   278,   282,   284,   288,   290,   294,   296,
     300,   302,   306,   308,   312,   314,   316,   318,   320,   323,
     326,   329,   332,   336,   340,   344,   348,   352,   356,   360,
     364,   368,   372,   376,   380,   384,   388,   392,   395,   398,
     401,   405,   410,   415,   420,   425,   430,   435,   440,   443
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      68,     0,    -1,    70,    69,    70,    79,    70,    10,    59,
      72,    60,    -1,    69,    50,    -1,    50,    -1,    70,    71,
      -1,    71,    -1,    51,    -1,    52,    -1,    -1,    -1,    72,
      73,    -1,    53,    -1,    73,    53,    73,    -1,    51,    -1,
      52,    -1,    77,    53,    -1,    75,    53,    -1,    97,    53,
      -1,    95,    -1,    89,    -1,    90,    -1,    93,    -1,    85,
      53,    -1,    74,    53,    -1,   105,    53,    -1,     6,    61,
      16,    62,    -1,     5,    61,    76,    62,    -1,    76,    63,
       3,    -1,     3,    -1,     4,    61,    78,    62,    -1,    78,
      63,     3,    -1,     3,    -1,    79,    80,    -1,    80,    -1,
      81,    39,    82,    61,    83,    62,    59,    73,    60,    -1,
      11,    -1,    12,    -1,    13,    -1,     3,    -1,    -1,    83,
      63,    84,    -1,    84,    -1,    11,     3,    -1,    12,     3,
      -1,    40,    86,    61,    87,    62,    -1,     3,    -1,    87,
      63,    88,    -1,    88,    -1,     3,    -1,    -1,    44,    61,
       3,    45,    64,     7,   104,    63,     8,   104,    63,     9,
     104,    65,    62,    59,    73,    60,    -1,    47,    59,    91,
      60,    -1,    91,    92,    -1,    92,    -1,    48,    61,   104,
      62,    59,    73,    60,    -1,    49,    59,    73,    60,    -1,
      46,    61,    94,    62,    59,    73,    60,    -1,     3,    21,
      23,   104,    -1,     3,    21,    27,   104,    -1,     3,    21,
      26,   104,    -1,     3,    22,    24,   104,    -1,     3,    22,
      28,   104,    -1,     3,    22,    26,   104,    -1,    41,    61,
     104,    62,    59,    95,    60,    96,    -1,    41,    61,   104,
      62,    59,    95,    60,    -1,   104,    -1,    42,    61,   104,
      62,    59,    95,    60,    96,    -1,    43,    59,    95,    60,
      -1,    42,    61,   104,    62,    59,    95,    60,    -1,    11,
     102,    -1,    12,   100,    -1,    13,    98,    -1,    98,    63,
      99,    -1,    99,    -1,     3,    66,    16,    -1,     3,    -1,
     100,    63,   101,    -1,   101,    -1,     3,    66,   104,    -1,
       3,    -1,   102,    63,   103,    -1,   103,    -1,     3,    66,
     104,    -1,     3,    -1,    14,    -1,    15,    -1,     3,    -1,
      54,   104,    -1,    55,   104,    -1,    21,   104,    -1,    22,
     104,    -1,   104,    54,   104,    -1,   104,    55,   104,    -1,
     104,    56,   104,    -1,   104,    57,   104,    -1,   104,    58,
     104,    -1,   104,    31,   104,    -1,   104,    25,   104,    -1,
     104,    26,   104,    -1,   104,    23,   104,    -1,   104,    24,
     104,    -1,   104,    27,   104,    -1,   104,    28,   104,    -1,
     104,    17,   104,    -1,   104,    18,   104,    -1,   104,    19,
     104,    -1,    20,   104,    -1,     3,    21,    -1,     3,    22,
      -1,    61,   104,    62,    -1,    32,    61,   104,    62,    -1,
      33,    61,   104,    62,    -1,    34,    61,   104,    62,    -1,
      35,    61,   104,    62,    -1,    36,    61,   104,    62,    -1,
      37,    61,   104,    62,    -1,    38,    61,   104,    62,    -1,
       3,    29,    -1,     3,    30,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   172,   172,   177,   180,   185,   186,   189,   190,   191,
     193,   194,   198,   199,   200,   201,   202,   203,   204,   205,
     208,   209,   210,   211,   212,   213,   217,   222,   225,   228,
     235,   240,   243,   247,   248,   252,   263,   264,   265,   269,
     284,   285,   286,   290,   300,   313,   323,   336,   337,   341,
     353,   357,   375,   380,   381,   384,   393,   399,   411,   426,
     441,   456,   471,   486,   504,   511,   516,   522,   529,   532,
     539,   540,   541,   545,   546,   549,   559,   566,   567,   570,
     579,   587,   588,   592,   601,   608,   611,   614,   625,   628,
     631,   634,   637,   640,   643,   646,   649,   653,   657,   661,
     665,   668,   671,   674,   678,   682,   686,   690,   694,   705,
     716,   719,   722,   725,   728,   731,   734,   737,   742,   752
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VARIABLE", "INPUT", "PRINT", "DISPLAY",
  "START", "FINISH", "BY", "MAIN", "NUMBER_TYPE", "DECIMAL_TYPE",
  "STRING_TYPE", "NUMBER_VALUE", "DECIMAL_VALUE", "STRING_VALUE", "AND",
  "OR", "XOR", "NOT", "INC", "DEC", "LT", "GT", "EQL", "NEQL", "LEQL",
  "GEQL", "ONLY_INC", "ONLY_DEC", "POW", "SIN", "COS", "TAN", "LOG10",
  "LOG2", "LN", "SQRT", "DEF", "CALL", "IF", "EL_IF", "ELSE", "FOR", "IN",
  "WHILE", "SWITCH", "CASE", "DEFAULT", "HEADER", "S_COMMENT", "M_COMMENT",
  "EOL", "'+'", "'-'", "'*'", "'/'", "'%'", "'{'", "'}'", "'('", "')'",
  "','", "'['", "']'", "'='", "$accept", "starting_symbol", "headers",
  "comments", "comment", "statements", "statement", "display", "print",
  "output_variable", "input", "input_variable", "functions",
  "function_declare", "return_types", "function_name", "function_variable",
  "single_variable", "function_call", "user_function_name", "parameters",
  "single_parameter", "for_loop", "switch_statement", "cases", "case",
  "while_loop", "while_conditions", "if_blocks", "elif_block",
  "declarations", "str_vars", "str_var", "dec_vars", "dec_var", "num_vars",
  "num_var", "expr", "only_inc_dec", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,    43,    45,    42,    47,    37,   123,
     125,    40,    41,    44,    91,    93,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    67,    68,    69,    69,    70,    70,    71,    71,    71,
      72,    72,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    74,    75,    76,    76,
      77,    78,    78,    79,    79,    80,    81,    81,    81,    82,
      83,    83,    83,    84,    84,    85,    86,    87,    87,    88,
      88,    89,    90,    91,    91,    92,    92,    93,    94,    94,
      94,    94,    94,    94,    95,    95,    95,    96,    96,    96,
      97,    97,    97,    98,    98,    99,    99,   100,   100,   101,
     101,   102,   102,   103,   103,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   105,   105
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     9,     2,     1,     2,     1,     1,     1,     0,
       0,     2,     1,     3,     1,     1,     2,     2,     2,     1,
       1,     1,     1,     2,     2,     2,     4,     4,     3,     1,
       4,     3,     1,     2,     1,     9,     1,     1,     1,     1,
       0,     3,     1,     2,     2,     5,     1,     3,     1,     1,
       0,    18,     4,     2,     1,     7,     4,     7,     4,     4,
       4,     4,     4,     4,     8,     7,     1,     8,     4,     7,
       2,     2,     2,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     1,     1,     1,     2,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       3,     4,     4,     4,     4,     4,     4,     4,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       9,     7,     8,     0,     0,     6,     1,     4,     9,     5,
       3,     0,    36,    37,    38,     9,    34,     0,     0,    33,
       0,     0,    39,     0,    10,    40,     0,     0,     0,     0,
      42,    87,     0,     0,     0,     0,     0,     0,    85,    86,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    14,    15,    12,     0,     0,
       2,     0,    11,     0,     0,     0,     0,    20,    21,    22,
      19,     0,    66,     0,    43,    44,     0,     0,   108,   109,
     118,   119,     0,     0,     0,    84,    70,    82,    80,    71,
      78,    76,    72,    74,    87,   107,    90,    91,     0,     0,
       0,     0,     0,     0,     0,    46,     0,     0,     0,     0,
       0,    88,    89,     0,     0,    24,    17,    16,    23,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    25,     0,    41,    32,     0,
      29,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,     0,     0,     0,
       0,     0,     0,     0,    54,   110,    13,   104,   105,   106,
     100,   101,    98,    99,   102,   103,    97,    92,    93,    94,
      95,    96,     0,    30,     0,    27,     0,    26,    83,    81,
      79,    77,    75,    73,   111,   112,   113,   114,   115,   116,
     117,    49,     0,    48,     0,     0,     0,     0,     0,     0,
       0,    52,    53,    35,    31,    28,    45,    50,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    47,
       0,     0,    58,    60,    59,    61,    63,    62,     0,     0,
      56,    65,     0,    57,     0,     0,     0,    64,     0,     0,
       0,     0,     0,    55,     0,     0,     0,     0,    68,     0,
       0,     0,     0,     0,    69,     0,    67,     0,     0,     0,
      51
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     8,     4,     5,    26,    62,    63,    64,   141,
      65,   139,    15,    16,    17,    23,    29,    30,    66,   106,
     202,   203,    67,    68,   163,   164,    69,   160,    70,   247,
      71,    92,    93,    89,    90,    86,    87,    72,    73
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -196
static const yytype_int16 yypact[] =
{
      25,  -196,  -196,    24,    73,  -196,  -196,  -196,    80,  -196,
    -196,    -7,  -196,  -196,  -196,    -7,  -196,   -26,     2,  -196,
      29,    -2,  -196,    37,  -196,   105,   107,    40,    71,    72,
    -196,    79,    46,    53,    65,   135,   143,   160,  -196,  -196,
     235,   235,   235,    91,   116,   117,   118,   125,   126,   127,
     163,   128,   129,   131,   134,  -196,  -196,  -196,   235,   235,
    -196,   235,   123,   141,   142,   147,   148,  -196,  -196,  -196,
    -196,   150,   658,   156,  -196,  -196,   152,   105,  -196,  -196,
    -196,  -196,   199,   213,   201,   153,   155,  -196,   154,   159,
    -196,   157,   161,  -196,   115,   667,   658,   658,   235,   235,
     235,   235,   235,   235,   235,  -196,   171,   235,   232,   233,
     101,    39,    39,   331,   193,  -196,  -196,  -196,  -196,  -196,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,  -196,   193,  -196,  -196,    93,
    -196,   102,   179,   235,   135,   235,   143,   226,   160,   373,
     388,   430,   445,   487,   502,   544,   240,   559,   206,   149,
     190,   192,   200,   -18,  -196,  -196,   123,   667,   667,   667,
     -17,   -17,   -17,   -17,   -17,   -17,   658,    39,    39,   227,
     227,   227,   -44,  -196,   258,  -196,   259,  -196,   658,  -196,
     658,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,
    -196,  -196,   110,  -196,   204,   196,   -16,    78,   205,   235,
     193,  -196,  -196,  -196,  -196,  -196,  -196,   240,    14,   270,
     235,   235,   235,   235,   235,   235,   193,   601,   -33,  -196,
     218,   235,   658,   658,   658,   658,   658,   658,   -27,   207,
    -196,   132,   274,  -196,   193,   225,   220,  -196,   279,    13,
     235,    14,   235,  -196,   616,   234,   316,   236,  -196,   256,
      14,   235,   243,   257,   132,   242,  -196,   247,   193,    18,
    -196
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -196,  -196,  -196,    64,     4,  -196,  -111,  -196,  -196,  -196,
    -196,  -196,  -196,   292,  -196,  -196,  -196,   231,  -196,  -196,
    -196,    92,  -196,  -196,  -196,   158,  -196,  -196,  -195,    52,
    -196,  -196,   162,  -196,   172,  -196,   173,   -40,  -196
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      95,    96,    97,   166,    12,    13,    14,   220,     9,   114,
     221,   222,    21,    20,   129,     9,   213,    94,   111,   112,
     114,   113,     9,   230,     6,   182,   114,   240,    38,    39,
     161,   162,    22,   243,    40,    41,    42,   130,   131,   132,
     133,   134,   211,    74,     1,     2,    43,    44,    45,    46,
      47,    48,    49,     1,     2,    51,   255,    24,   149,   150,
     151,   152,   153,   154,   155,   262,   114,   157,    58,    59,
     129,   114,    11,   253,    75,    61,     1,     2,   270,    18,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   132,   133,   134,    25,   228,
      78,    79,   223,   188,   224,   190,   225,    82,    80,    81,
      31,    32,    33,    34,    83,   238,    27,    28,    35,    36,
      37,    38,    39,     7,     1,     2,    84,    40,    41,    42,
      10,     1,     2,   249,    76,    77,    78,    79,    85,    43,
      44,    45,    46,    47,    48,    49,    88,    50,    51,   161,
     162,    52,    98,    53,    54,   183,   184,   269,    55,    56,
      57,    58,    59,    91,   185,   186,   105,    60,    61,   227,
     206,   207,   216,   217,   245,   246,   114,    99,   100,   101,
     232,   233,   234,   235,   236,   237,   102,   103,   104,   107,
     108,   242,   109,   110,   115,   116,    31,    32,    33,    34,
     117,   118,   138,   119,    35,    36,    37,    38,    39,   135,
     254,   136,   256,    40,    41,    42,   140,   142,   144,   143,
     145,   263,   146,   147,   148,    43,    44,    45,    46,    47,
      48,    49,   156,    50,    51,   158,   159,    52,    94,    53,
      54,   187,   192,   201,    55,    56,    57,    58,    59,    38,
      39,   205,   208,   209,    61,    40,    41,    42,   129,   210,
     219,   214,   215,   218,   226,   261,   244,    43,    44,    45,
      46,    47,    48,    49,   120,   121,   122,   231,   241,   251,
     123,   124,   125,   126,   127,   128,   250,   252,   129,    58,
      59,   120,   121,   122,   258,   260,    61,   123,   124,   125,
     126,   127,   128,   264,   267,   129,   268,    19,   137,   229,
     193,   130,   131,   132,   133,   134,   266,   189,   191,     0,
       0,   212,   265,     0,     0,     0,     0,     0,   130,   131,
     132,   133,   134,   120,   121,   122,     0,   248,     0,   123,
     124,   125,   126,   127,   128,     0,     0,   129,   120,   121,
     122,     0,     0,     0,   123,   124,   125,   126,   127,   128,
       0,     0,   129,     0,     0,     0,     0,     0,     0,     0,
     130,   131,   132,   133,   134,     0,     0,     0,     0,   259,
       0,     0,     0,     0,     0,   130,   131,   132,   133,   134,
     120,   121,   122,   165,     0,     0,   123,   124,   125,   126,
     127,   128,     0,     0,   129,   120,   121,   122,     0,     0,
       0,   123,   124,   125,   126,   127,   128,     0,     0,   129,
       0,     0,     0,     0,     0,     0,     0,   130,   131,   132,
     133,   134,     0,     0,     0,   194,     0,     0,     0,     0,
       0,     0,   130,   131,   132,   133,   134,   120,   121,   122,
     195,     0,     0,   123,   124,   125,   126,   127,   128,     0,
       0,   129,   120,   121,   122,     0,     0,     0,   123,   124,
     125,   126,   127,   128,     0,     0,   129,     0,     0,     0,
       0,     0,     0,     0,   130,   131,   132,   133,   134,     0,
       0,     0,   196,     0,     0,     0,     0,     0,     0,   130,
     131,   132,   133,   134,   120,   121,   122,   197,     0,     0,
     123,   124,   125,   126,   127,   128,     0,     0,   129,   120,
     121,   122,     0,     0,     0,   123,   124,   125,   126,   127,
     128,     0,     0,   129,     0,     0,     0,     0,     0,     0,
       0,   130,   131,   132,   133,   134,     0,     0,     0,   198,
       0,     0,     0,     0,     0,     0,   130,   131,   132,   133,
     134,   120,   121,   122,   199,     0,     0,   123,   124,   125,
     126,   127,   128,     0,     0,   129,   120,   121,   122,     0,
       0,     0,   123,   124,   125,   126,   127,   128,     0,     0,
     129,     0,     0,     0,     0,     0,     0,     0,   130,   131,
     132,   133,   134,     0,     0,     0,   200,     0,     0,     0,
       0,     0,     0,   130,   131,   132,   133,   134,   120,   121,
     122,   204,     0,     0,   123,   124,   125,   126,   127,   128,
       0,     0,   129,   120,   121,   122,     0,     0,     0,   123,
     124,   125,   126,   127,   128,     0,     0,   129,     0,     0,
       0,     0,     0,     0,     0,   130,   131,   132,   133,   134,
       0,     0,     0,   239,     0,     0,     0,     0,     0,     0,
     130,   131,   132,   133,   134,   120,   121,   122,   257,     0,
       0,   123,   124,   125,   126,   127,   128,     0,     0,   129,
     123,   124,   125,   126,   127,   128,     0,     0,   129,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   130,   131,   132,   133,   134,     0,     0,     0,
       0,   130,   131,   132,   133,   134
};

static const yytype_int16 yycheck[] =
{
      40,    41,    42,   114,    11,    12,    13,    23,     4,    53,
      26,    27,    10,    39,    31,    11,    60,     3,    58,    59,
      53,    61,    18,   218,     0,   136,    53,    60,    14,    15,
      48,    49,     3,    60,    20,    21,    22,    54,    55,    56,
      57,    58,    60,     3,    51,    52,    32,    33,    34,    35,
      36,    37,    38,    51,    52,    41,   251,    59,    98,    99,
     100,   101,   102,   103,   104,   260,    53,   107,    54,    55,
      31,    53,     8,    60,     3,    61,    51,    52,    60,    15,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,    56,    57,    58,    61,   210,
      21,    22,    24,   143,    26,   145,    28,    61,    29,    30,
       3,     4,     5,     6,    61,   226,    11,    12,    11,    12,
      13,    14,    15,    50,    51,    52,    61,    20,    21,    22,
      50,    51,    52,   244,    62,    63,    21,    22,     3,    32,
      33,    34,    35,    36,    37,    38,     3,    40,    41,    48,
      49,    44,    61,    46,    47,    62,    63,   268,    51,    52,
      53,    54,    55,     3,    62,    63,     3,    60,    61,   209,
      21,    22,    62,    63,    42,    43,    53,    61,    61,    61,
     220,   221,   222,   223,   224,   225,    61,    61,    61,    61,
      61,   231,    61,    59,    53,    53,     3,     4,     5,     6,
      53,    53,     3,    53,    11,    12,    13,    14,    15,    53,
     250,    59,   252,    20,    21,    22,     3,    16,    63,    66,
      66,   261,    63,    66,    63,    32,    33,    34,    35,    36,
      37,    38,    61,    40,    41,     3,     3,    44,     3,    46,
      47,    62,    16,     3,    51,    52,    53,    54,    55,    14,
      15,    45,    62,    61,    61,    20,    21,    22,    31,    59,
      64,     3,     3,    59,    59,     9,    59,    32,    33,    34,
      35,    36,    37,    38,    17,    18,    19,     7,    60,    59,
      23,    24,    25,    26,    27,    28,    61,     8,    31,    54,
      55,    17,    18,    19,    60,    59,    61,    23,    24,    25,
      26,    27,    28,    60,    62,    31,    59,    15,    77,   217,
     148,    54,    55,    56,    57,    58,   264,   144,   146,    -1,
      -1,   163,    65,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    17,    18,    19,    -1,    63,    -1,    23,
      24,    25,    26,    27,    28,    -1,    -1,    31,    17,    18,
      19,    -1,    -1,    -1,    23,    24,    25,    26,    27,    28,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,    63,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      17,    18,    19,    62,    -1,    -1,    23,    24,    25,    26,
      27,    28,    -1,    -1,    31,    17,    18,    19,    -1,    -1,
      -1,    23,    24,    25,    26,    27,    28,    -1,    -1,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    17,    18,    19,
      62,    -1,    -1,    23,    24,    25,    26,    27,    28,    -1,
      -1,    31,    17,    18,    19,    -1,    -1,    -1,    23,    24,
      25,    26,    27,    28,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    -1,
      -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    17,    18,    19,    62,    -1,    -1,
      23,    24,    25,    26,    27,    28,    -1,    -1,    31,    17,
      18,    19,    -1,    -1,    -1,    23,    24,    25,    26,    27,
      28,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    -1,    -1,    -1,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    17,    18,    19,    62,    -1,    -1,    23,    24,    25,
      26,    27,    28,    -1,    -1,    31,    17,    18,    19,    -1,
      -1,    -1,    23,    24,    25,    26,    27,    28,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    17,    18,
      19,    62,    -1,    -1,    23,    24,    25,    26,    27,    28,
      -1,    -1,    31,    17,    18,    19,    -1,    -1,    -1,    23,
      24,    25,    26,    27,    28,    -1,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    17,    18,    19,    62,    -1,
      -1,    23,    24,    25,    26,    27,    28,    -1,    -1,    31,
      23,    24,    25,    26,    27,    28,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    51,    52,    68,    70,    71,     0,    50,    69,    71,
      50,    70,    11,    12,    13,    79,    80,    81,    70,    80,
      39,    10,     3,    82,    59,    61,    72,    11,    12,    83,
      84,     3,     4,     5,     6,    11,    12,    13,    14,    15,
      20,    21,    22,    32,    33,    34,    35,    36,    37,    38,
      40,    41,    44,    46,    47,    51,    52,    53,    54,    55,
      60,    61,    73,    74,    75,    77,    85,    89,    90,    93,
      95,    97,   104,   105,     3,     3,    62,    63,    21,    22,
      29,    30,    61,    61,    61,     3,   102,   103,     3,   100,
     101,     3,    98,    99,     3,   104,   104,   104,    61,    61,
      61,    61,    61,    61,    61,     3,    86,    61,    61,    61,
      59,   104,   104,   104,    53,    53,    53,    53,    53,    53,
      17,    18,    19,    23,    24,    25,    26,    27,    28,    31,
      54,    55,    56,    57,    58,    53,    59,    84,     3,    78,
       3,    76,    16,    66,    63,    66,    63,    66,    63,   104,
     104,   104,   104,   104,   104,   104,    61,   104,     3,     3,
      94,    48,    49,    91,    92,    62,    73,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,    73,    62,    63,    62,    63,    62,   104,   103,
     104,   101,    16,    99,    62,    62,    62,    62,    62,    62,
      62,     3,    87,    88,    62,    45,    21,    22,    62,    61,
      59,    60,    92,    60,     3,     3,    62,    63,    59,    64,
      23,    26,    27,    24,    26,    28,    59,   104,    73,    88,
      95,     7,   104,   104,   104,   104,   104,   104,    73,    62,
      60,    60,   104,    60,    59,    42,    43,    96,    63,    73,
      61,    59,     8,    60,   104,    95,   104,    62,    60,    63,
      59,     9,    95,   104,    60,    65,    96,    62,    59,    73,
      60
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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

/* Prevent warnings from -Wmissing-prototypes.  */
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  if (yyn == YYPACT_NINF)
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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

/* Line 1455 of yacc.c  */
#line 172 "ryad.y"
    {
        printf("Compiled Successfully\n");
    ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 177 "ryad.y"
    {
        printf("Header Found!\n");
    ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 180 "ryad.y"
    {
        printf("Header Found!\n");
    ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 193 "ryad.y"
    {;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 205 "ryad.y"
    {
        printf("IF BLOCKS return: %d\n", (yyvsp[(1) - (1)].integer));
    ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 217 "ryad.y"
    {
        printf("%s\n", (yyvsp[(3) - (4)].string));
    ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 222 "ryad.y"
    {;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 225 "ryad.y"
    {
        print_value((yyvsp[(3) - (3)].string));
    ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 228 "ryad.y"
    {
        print_value((yyvsp[(1) - (1)].string));

    ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 235 "ryad.y"
    {
    ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 240 "ryad.y"
    {
        read_value((yyvsp[(3) - (3)].string), 0);
    ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 243 "ryad.y"
    {
        read_value((yyvsp[(1) - (1)].string), 0);
    ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 252 "ryad.y"
    {
        if(func_flag){
         printf("Function successfully declared\n"); 
         func_flag=0;
    }
    else {
        printf("Error:Function creation failed\n");
    }
;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 269 "ryad.y"
    {
        int index = function_index((yyvsp[(1) - (1)].string));
        if (index != -1) {
            printf("Error: Function '%s' already declared.\n", (yyvsp[(1) - (1)].string));
        } else {
            func_flag =1 ;
            printf("Function declaration start: %s\n", (yyvsp[(1) - (1)].string));
            funcptr[FUNC_CNT].fname = malloc((strlen((yyvsp[(1) - (1)].string)) + 1) * sizeof(char));
            strcpy(funcptr[FUNC_CNT].fname, (yyvsp[(1) - (1)].string));
            funcptr[FUNC_CNT].var_cnt = 0;
            funcptr[FUNC_CNT].fptr = malloc(4 * sizeof(stackfun));
            FUNC_CNT++;
        }
    ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 290 "ryad.y"
    {
        if (FUNC_CNT > 0) {
            int index = funcptr[FUNC_CNT - 1].var_cnt;
            int value = 0;
            variable_info((yyvsp[(2) - (2)].string), 1, 1, VAR_CNT, &value);
            funcptr[FUNC_CNT - 1].fptr[index] = varptr[VAR_CNT];
            VAR_CNT++;
            funcptr[FUNC_CNT - 1].var_cnt++;
        }
    ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 300 "ryad.y"
    {
        if (FUNC_CNT > 0) {
            int index = funcptr[FUNC_CNT - 1].var_cnt;
            double value = 0;
            variable_info((yyvsp[(2) - (2)].string), 2, 1, VAR_CNT, &value);
            funcptr[FUNC_CNT - 1].fptr[index] = varptr[VAR_CNT];
            VAR_CNT++;
        funcptr[FUNC_CNT - 1].var_cnt++;
        }
    ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 313 "ryad.y"
    {
        if(func_rejec) {
            printf("Function Not Declared.\n");
        } else {
            printf("Function Successfully Called.\n");
        }
    ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 323 "ryad.y"
    {
        int index = function_index((yyvsp[(1) - (1)].string));
        if(index == -1) {
            printf("Function Doesn't Exist.\n");
        } else {
            curr_function = index;
            curr_parameter = 0;
            func_rejec = 0;
        }
    ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 341 "ryad.y"
    {
        int index = variable_index((yyvsp[(1) - (1)].string));
        if(curr_parameter >= funcptr[curr_function].var_cnt) {
            printf("Way too many arguments.\n");
            func_rejec = 1;
        } else if(funcptr[curr_function].fptr[curr_parameter].type != varptr[index].type) {
            printf("Data Types Don't Match.\n");
            func_rejec = 1;
        } else {
            curr_parameter++;
        }
    ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 357 "ryad.y"
    {
        printf("For Loop Block\n");
        int from = (yyvsp[(7) - (18)].floating_num);
        int end = (yyvsp[(10) - (18)].floating_num);
        int by = (yyvsp[(13) - (18)].floating_num);
        int dif = end - from;
        if(dif * by < 0) {
            printf("For Loop Condition wasn't satisfied\n");
        } else {
            int c = 1;
            for(int i = from; i <= end; i += by) {
                printf("For Loop Iteration: %d\n", c);
                c++;
            }
        }
    ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 375 "ryad.y"
    {
        printf("Switch statement ended\n");
    ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 384 "ryad.y"
    {
        int condition = (fabs((yyvsp[(3) - (7)].floating_num)) > 1e-9);   
        if(condition) {
            case_matched = 1;
            printf("Case Matched.\n");
        } else {
            //printf("Condition Didn't match in IF Block.\n");
        }
    ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 393 "ryad.y"
    {
        if(!case_matched) {
            printf("Default matched\n");
        }
    ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 399 "ryad.y"
    {
        printf("WHILE BLOCK\n");
        int whilecheckbool = 0;
        for(int i = 1; i < (yyvsp[(3) - (7)].floating_num); ++i) {
            whilecheckbool = 1;
            printf("WHILE Loop Iteration: %d\n", i);
        }
        if(!whilecheckbool) {
            printf("While Loop Condition wasn't satisfied\n");
        }
    ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 411 "ryad.y"
    {
        int index = variable_index((yyvsp[(1) - (4)].string));
        if(index == -1) {
            printf("Variable \"%s\" doesn't exist.\n", (yyvsp[(1) - (4)].string));
        } else if(varptr[index].type != 1) { //1 for integer
            printf("Variable should be NUMBER Type.\n");
        } else {
            int value = varptr[index].ival[0];
            if(value > (yyvsp[(4) - (4)].floating_num)) {
                (yyval.floating_num) = -1;
            } else {
                (yyval.floating_num) = (int) (yyvsp[(4) - (4)].floating_num) - value;
            }
        }
    ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 426 "ryad.y"
    {
        int index = variable_index((yyvsp[(1) - (4)].string));
        if(index == -1) {
            printf("Variable \"%s\" doesn't exist.\n", (yyvsp[(1) - (4)].string));
        } else if(varptr[index].type != 1) { //1 for integer
            printf("Variable should be NUMBER Type.\n");
        } else {
            int value = varptr[index].ival[0];
            if(value > (yyvsp[(4) - (4)].floating_num)) {
                (yyval.floating_num) = -1;
            } else {
                (yyval.floating_num) = (int) (yyvsp[(4) - (4)].floating_num) - value + 1;
            }
        }
    ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 441 "ryad.y"
    {
        int index = variable_index((yyvsp[(1) - (4)].string));
        if(index == -1) {
            printf("Variable \"%s\" doesn't exist.\n", (yyvsp[(1) - (4)].string));
        } else if(varptr[index].type != 1) { //1 for integer
            printf("Variable should be NUMBER Type.\n");
        } else {
            int value = varptr[index].ival[0];
            if(value > (yyvsp[(4) - (4)].floating_num)) {
                (yyval.floating_num) = -1;
            } else {
                (yyval.floating_num) = (int) (yyvsp[(4) - (4)].floating_num) - value;
            }
        }
    ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 456 "ryad.y"
    {
        int index = variable_index((yyvsp[(1) - (4)].string));
        if(index == -1) {
            printf("Variable \"%s\" doesn't exist.\n", (yyvsp[(1) - (4)].string));
        } else if(varptr[index].type != 1) { //1 for integer
            printf("Variable should be NUMBER Type.\n");
        } else {
            int value = varptr[index].ival[0];
            if(value < (yyvsp[(4) - (4)].floating_num)) {
                (yyval.floating_num) = -1;
            } else {
                (yyval.floating_num) = value - (int) (yyvsp[(4) - (4)].floating_num);
            }
        }
    ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 471 "ryad.y"
    {
        int index = variable_index((yyvsp[(1) - (4)].string));
        if(index == -1) {
            printf("Variable \"%s\" doesn't exist.\n", (yyvsp[(1) - (4)].string));
        } else if(varptr[index].type != 1) { //1 for integer
            printf("Variable should be NUMBER Type.\n");
        } else {
            int value = varptr[index].ival[0];
            if(value < (yyvsp[(4) - (4)].floating_num)) {
                (yyval.floating_num) = -1;
            } else {
                (yyval.floating_num) = value - (int) (yyvsp[(4) - (4)].floating_num) + 1;
            }
        }
    ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 486 "ryad.y"
    {
        int index = variable_index((yyvsp[(1) - (4)].string));
        if(index == -1) {
            printf("Variable \"%s\" doesn't exist.\n", (yyvsp[(1) - (4)].string));
        } else if(varptr[index].type != 1) { //1 for integer
            printf("Variable should be NUMBER Type.\n");
        } else {
            int value = varptr[index].ival[0];
            if(value < (yyvsp[(4) - (4)].floating_num)) {
                (yyval.floating_num) = -1;
            } else {
                (yyval.floating_num) = value - (int) (yyvsp[(4) - (4)].floating_num);
            }
        }
    ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 504 "ryad.y"
    {
        if ((yyvsp[(3) - (8)].floating_num)) {
            (yyval.integer) = (yyvsp[(6) - (8)].integer); 
        } else {
            (yyval.integer) = (yyvsp[(8) - (8)].integer); 
        }
    ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 511 "ryad.y"
    {
        if ((yyvsp[(3) - (7)].floating_num)) {
            (yyval.integer) = (yyvsp[(6) - (7)].integer);
        }
    ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 516 "ryad.y"
    {  //expr %prec LOWER_THAN_ELSE
        (yyval.integer) = (yyvsp[(1) - (1)].floating_num);
    ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 522 "ryad.y"
    {
          if ((yyvsp[(3) - (8)].floating_num)) {
            (yyval.integer) = (yyvsp[(6) - (8)].integer); 
        } else {
            (yyval.integer) = (yyvsp[(8) - (8)].integer); 
        }
    ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 529 "ryad.y"
    {
        (yyval.integer) = (yyvsp[(3) - (4)].integer);
    ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 532 "ryad.y"
    {
        if ((yyvsp[(3) - (7)].floating_num)) {
            (yyval.integer) = (yyvsp[(6) - (7)].integer);
        }
    ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 549 "ryad.y"
    {
        int exists = check_unique((yyvsp[(1) - (3)].string));
        if(exists == -1) {
            printf("Variable \"%s\" already exists.\n", (yyvsp[(1) - (3)].string));
        } else {
            char *value = (yyvsp[(3) - (3)].string);
            variable_info((yyvsp[(1) - (3)].string), 3, 1, VAR_CNT, &value);
            VAR_CNT++;
        }
    ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 559 "ryad.y"
    {
        //char *value = "";
        //variable_info($1, 3, 1, VAR_CNT, &value);
        //VAR_CNT++; 
        printf("Error: String declaration without initialization\n");
    ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 570 "ryad.y"
    {
        if(check_unique((yyvsp[(1) - (3)].string)) == -1) {
            printf("Variable \"%s\" already exists.\n", (yyvsp[(1) - (3)].string));
        } else {
            double value = (yyvsp[(3) - (3)].floating_num);
            variable_info((yyvsp[(1) - (3)].string), 2, 1, VAR_CNT, &value);
            VAR_CNT++;
        }
    ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 579 "ryad.y"
    {
        printf("Error: Float declaration without initialization\n");
        // double value = 0.0;
        //variable_info($1, 2, 1, VAR_CNT, &value);
        //VAR_CNT++; 
    ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 592 "ryad.y"
    {
        if(check_unique((yyvsp[(1) - (3)].string)) == 1) {
            int value = (yyvsp[(3) - (3)].floating_num);
            variable_info((yyvsp[(1) - (3)].string), 1, 1, VAR_CNT, &value);
            VAR_CNT++;
        } else {
            printf("Variable \"%s\" already exists.\n", (yyvsp[(1) - (3)].string));
        }
    ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 601 "ryad.y"
    {  
        printf("Error: Integer declaration without initialization\n");
    ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 608 "ryad.y"
    {
        (yyval.floating_num) = (yyvsp[(1) - (1)].integer);
    ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 611 "ryad.y"
    {
        (yyval.floating_num) = (yyvsp[(1) - (1)].floating_num);
    ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 614 "ryad.y"
    {
        int i = variable_index((yyvsp[(1) - (1)].string));
        if(i == -1) {
            printf("Variable \"%s\" doesn't exist.\n", (yyvsp[(1) - (1)].string));
            (yyval.floating_num) = 0;
        } else if(varptr[i].type == 1) { //1 for integer
            (yyval.floating_num) = varptr[i].ival[0];
        } else if(varptr[i].type == 2) { //2 for float
            (yyval.floating_num) = varptr[i].dval[0];
        }
    ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 625 "ryad.y"
    {
        (yyval.floating_num) = (yyvsp[(2) - (2)].floating_num);
    ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 628 "ryad.y"
    {
        (yyval.floating_num) = -(yyvsp[(2) - (2)].floating_num);
    ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 631 "ryad.y"
    {
        (yyval.floating_num) = (yyvsp[(2) - (2)].floating_num);
    ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 634 "ryad.y"
    {
        (yyval.floating_num) = (yyvsp[(2) - (2)].floating_num);
    ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 637 "ryad.y"
    {
        (yyval.floating_num) = (yyvsp[(1) - (3)].floating_num) + (yyvsp[(3) - (3)].floating_num);
    ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 640 "ryad.y"
    {
        (yyval.floating_num) = (yyvsp[(1) - (3)].floating_num) - (yyvsp[(3) - (3)].floating_num);
    ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 643 "ryad.y"
    {
        (yyval.floating_num) = (yyvsp[(1) - (3)].floating_num) * (yyvsp[(3) - (3)].floating_num);
    ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 646 "ryad.y"
    {
        (yyval.floating_num) = (yyvsp[(1) - (3)].floating_num) / (yyvsp[(3) - (3)].floating_num);
    ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 649 "ryad.y"
    {

        (yyval.floating_num) = (int)(yyvsp[(1) - (3)].floating_num) % (int)(yyvsp[(3) - (3)].floating_num);
    ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 653 "ryad.y"
    {

        (yyval.floating_num) = pow((yyvsp[(1) - (3)].floating_num), (yyvsp[(3) - (3)].floating_num));
    ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 658 "ryad.y"
    {
        (yyval.floating_num) = ((yyvsp[(1) - (3)].floating_num) == (yyvsp[(3) - (3)].floating_num));
    ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 662 "ryad.y"
    {
        (yyval.floating_num) = ((yyvsp[(1) - (3)].floating_num) != (yyvsp[(3) - (3)].floating_num));
    ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 665 "ryad.y"
    {
        (yyval.floating_num) = ((yyvsp[(1) - (3)].floating_num) < (yyvsp[(3) - (3)].floating_num));
    ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 668 "ryad.y"
    {
        (yyval.floating_num) = ((yyvsp[(1) - (3)].floating_num) > (yyvsp[(3) - (3)].floating_num));
    ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 671 "ryad.y"
    {
        (yyval.floating_num) = ((yyvsp[(1) - (3)].floating_num) <= (yyvsp[(3) - (3)].floating_num));
    ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 675 "ryad.y"
    {
        (yyval.floating_num) = ((yyvsp[(1) - (3)].floating_num) >= (yyvsp[(3) - (3)].floating_num));
    ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 679 "ryad.y"
    {
        (yyval.floating_num) = ( (yyvsp[(1) - (3)].floating_num) && (yyvsp[(3) - (3)].floating_num));
    ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 683 "ryad.y"
    {
        (yyval.floating_num) = ((yyvsp[(1) - (3)].floating_num) || (yyvsp[(3) - (3)].floating_num));
    ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 687 "ryad.y"
    {
        (yyval.floating_num) = ((int)(yyvsp[(1) - (3)].floating_num) ^ (int)(yyvsp[(3) - (3)].floating_num));
    ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 691 "ryad.y"
    {
        (yyval.floating_num) = !(yyvsp[(2) - (2)].floating_num);
    ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 695 "ryad.y"
    {
        int index = variable_index((yyvsp[(1) - (2)].string));
        if(index == -1) {
            printf("Variable \"%s\" doesn't exist.\n", (yyvsp[(1) - (2)].string));
        } else if(varptr[index].type != 1) { //1 for integer
            printf("Can't Increment Incompatible Types.\n");
        } else {
            (yyval.floating_num) = varptr[index].ival[0] + 1;
        }
    ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 706 "ryad.y"
    {
        int index = variable_index((yyvsp[(1) - (2)].string));
        if(index == -1) {
            printf("Variable \"%s\" doesn't exist.\n", (yyvsp[(1) - (2)].string));
        } else if(varptr[index].type != 1) { //1 for integer
            printf("Can't Increment Incompatible Types.\n");
        } else {
            (yyval.floating_num) = varptr[index].ival[0] - 1;
        }
    ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 716 "ryad.y"
    {
        (yyval.floating_num) = (yyvsp[(2) - (3)].floating_num);
    ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 719 "ryad.y"
    {
        (yyval.floating_num) = sin((yyvsp[(3) - (4)].floating_num));
    ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 722 "ryad.y"
    {
        (yyval.floating_num) = cos((yyvsp[(3) - (4)].floating_num));
    ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 725 "ryad.y"
    {
        (yyval.floating_num) = tan((yyvsp[(3) - (4)].floating_num));
    ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 728 "ryad.y"
    {
        (yyval.floating_num) = log10((yyvsp[(3) - (4)].floating_num));
    ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 731 "ryad.y"
    {
        (yyval.floating_num) = log2((yyvsp[(3) - (4)].floating_num));
    ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 734 "ryad.y"
    {
        (yyval.floating_num) = log((yyvsp[(3) - (4)].floating_num));
    ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 737 "ryad.y"
    {
        (yyval.floating_num) = sqrt((yyvsp[(3) - (4)].floating_num));
    ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 742 "ryad.y"
    {
        int index = variable_index((yyvsp[(1) - (2)].string));
        if(index == -1) {
            printf("Variable \"%s\" doesn't exist.\n", (yyvsp[(1) - (2)].string));
        } else if(varptr[index].type != 1) { //1 for integer
            printf("Can't Increment Incompatible Types.\n");
        } else {
            varptr[index].ival[0]++;
        }
    ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 752 "ryad.y"
    {
        int index = variable_index((yyvsp[(1) - (2)].string));
        if(index == -1) {
            printf("Variable \"%s\" doesn't exist.\n", (yyvsp[(1) - (2)].string));
        } else if(varptr[index].type != 1) { //1 for integer
            printf("Can't Increment Incompatible Types.\n");
        } else {
            varptr[index].ival[0]--;
        }
    ;}
    break;



/* Line 1455 of yacc.c  */
#line 2752 "ryad.tab.c"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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



/* Line 1675 of yacc.c  */
#line 765 "ryad.y"

int main() {
    FILE *yyin = freopen("input.txt", "r", stdin);
    FILE *yyout = freopen("output.txt", "w", stdout);
    varptr = malloc(var_allowed * sizeof(info));
    funcptr = malloc(func_allowed * sizeof(stackfun));
    yyparse();
    free(varptr);
    free(funcptr);
    fclose(yyin);
    fclose(yyout);
    return 0;
}
