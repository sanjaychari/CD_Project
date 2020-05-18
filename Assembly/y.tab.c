/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     START = 258,
     STOP = 259,
     LABEL = 260,
     COLON = 261,
     TEMP = 262,
     EQUALS = 263,
     IF = 264,
     TRUE = 265,
     FALSE = 266,
     GOTO = 267,
     VAR = 268,
     NUM = 269,
     LESSTHAN = 270,
     GRTRTHAN = 271,
     ADD = 272,
     SUB = 273,
     MUL = 274,
     DIV = 275
   };
#endif
/* Tokens.  */
#define START 258
#define STOP 259
#define LABEL 260
#define COLON 261
#define TEMP 262
#define EQUALS 263
#define IF 264
#define TRUE 265
#define FALSE 266
#define GOTO 267
#define VAR 268
#define NUM 269
#define LESSTHAN 270
#define GRTRTHAN 271
#define ADD 272
#define SUB 273
#define MUL 274
#define DIV 275




/* Copy the first part of user declarations.  */
#line 1 "assembly.y"

    #define YYSTYPE char*
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    FILE* fp;
    int yylex();
    void yyerror(const char *);

    typedef struct Qnode{
        struct Qnode *next, *prev;
        int regIndex;
    } node;

    typedef struct regQ{
        node *front, *rear;
        int count;
    } Q;

    typedef struct hash{
        char* value; 
    } hashNode;

    node* newQNode(int regIndex){
        node* temp = (node*)malloc(sizeof(node));
        temp->next = temp->prev = NULL;
        temp->regIndex = regIndex;
        return temp;
    }

    Q* createQueue(){
        Q* q = (Q*)malloc(sizeof(Q));
        q->count = 0;
        q->front = q->rear = NULL;
        return q;
    }

    int deQueue(Q* q){
        node *temp = q->front;
        int regIndex = temp->regIndex;
        q->front = temp->next;
        q->count--;
        free(temp);
        return regIndex-1;
    }

    void hit(Q* q, int index){
        node* p = q->front;
        int pos = 0;
        while(pos!=index){
            p = p->next;
            pos++;
        }
        node *prev_node = p->prev;
        node *next_node = p->next;
        if (prev_node) prev_node->next = next_node;
        next_node->prev = prev_node;
        if(index == 0) q->front = next_node;
        p->prev = q->rear;
        q->rear->next = p;
        q->rear = p;
        p->next = NULL;
    }

    void enQueue(Q* q, int regIndex){
        node *p = (node*)malloc(sizeof(node));
        p->regIndex = regIndex;
        if(q->rear == NULL && q->front == NULL){
            p->prev = NULL;
            p->next = NULL;
            q->front = p;
            q->rear = p;
        }
        else {
            q->rear->next = p;
            p->prev = q->rear;
            q->rear = p;
            p->next = NULL;
        }
        q->count++;
    }

    int returnRegIndexFromHash(hashNode** H, char* value){
        for(int i = 0; i<14; i++){
            if(H[i]) {
                if( strcmp(value, H[i]->value)==0) return i+1;
            }
        }
        return -1;
    }

    int returnFirstFreeIndex(hashNode** H){
        int pos = -1, i = 0, found = 0;
        while(i<14 && !found){
            if(H[i] == NULL){
                found = 1;
                pos = i+1;
            } 
            i++;
        }
        return pos;
    }

    void display(Q* q, hashNode** H){
        node* p = q->front;
        int pos = 0;
        fprintf(fp,"Q - ");
        while(pos < q->count){
            fprintf(fp,"R%d ", p->regIndex);
            pos++;
            p = p->next;
        }
        fprintf(fp,"\n");
        fprintf(fp,"R - ");
        for(int i = 0; i<14; i++){
            if(H[i]) fprintf(fp,"%s ", H[i]->value);
            else fprintf(fp,"boo ");
        }
        fprintf(fp,"\n\n");
    }

    int reference(Q* q, char* value, hashNode** H){
        //fprintf(fp,"%s being referenced\n", value);
        int index = returnRegIndexFromHash(H, value);
        int reg = 0;
        if(index == -1){
            int regIndex = returnFirstFreeIndex(H);
            if(regIndex == -1){
                int freeRegister = deQueue(q);
                H[freeRegister]->value = value;
                enQueue(q, freeRegister+1);
                reg = freeRegister+1;
            }
            else{
                if(!H[regIndex-1]) H[regIndex-1] = (hashNode*)malloc(sizeof(hashNode));
                H[regIndex-1]->value = value;
                enQueue(q, regIndex);
                reg = regIndex;
            }
        }
        else{
            int pos = 0;
            node* p = q->front;
            while(pos < q->count && p->regIndex!=index){
                pos+=1;
                p = p->next;
            }
            if(pos != q->count-1) hit(q, pos);
            reg = index;
        }
        //fprintf(fp,"Value stored in R%d\n", reg);
        //display(q, H);
        return reg;
    }

    int checkPage(hashNode** H, char* value){
        for(int i = 0; i<14; i++){
            if(H[i] && strcmp(H[i]->value, value)==0){
                return 1;
            }
        }
        return 0;
    }
    
    int ln = 1;
    char* newLabel()
    {
        char *s = (char*)malloc(4*sizeof(char));
        sprintf(s,"Label%d",ln);
        ln++;
        return s;
    }

    hashNode** initialize_hash(){
        hashNode **H = (hashNode**)malloc(sizeof(hashNode*)*14);
        for(int i = 0; i<14; i++){
          H[i] = NULL;
        } 
        return H;
    }

    hashNode **H;
    Q* q;



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 332 "y.tab.c"

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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   152

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  21
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  9
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNRULES -- Number of states.  */
#define YYNSTATES  122

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   275

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,     8,    13,    14,    19,    22,    25,
      28,    29,    36,    43,    50,    57,    64,    71,    79,    87,
      95,   100,   105,   110,   115,   121,   127,   133,   139,   145,
     151,   157,   163,   169,   175,   181,   187,   193,   199,   205,
     211,   217,   223,   229,   236,   243,   250,   257,   264,   271,
     278,   285,   292,   296,   300,   302
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      22,     0,    -1,     3,    23,     4,    -1,    -1,     5,     6,
      24,    23,    -1,    -1,    12,     5,    25,    23,    -1,    26,
      23,    -1,    27,    23,    -1,    28,    23,    -1,    -1,     9,
      29,    15,    29,    12,     5,    -1,     9,    29,    15,    14,
      12,     5,    -1,     9,    14,    15,    29,    12,     5,    -1,
       9,    29,    16,    29,    12,     5,    -1,     9,    29,    16,
      14,    12,     5,    -1,     9,    14,    16,    29,    12,     5,
      -1,     9,    29,     8,     8,    29,    12,     5,    -1,     9,
      29,     8,     8,    14,    12,     5,    -1,     9,    14,     8,
       8,    29,    12,     5,    -1,     9,    29,    12,     5,    -1,
       9,    14,    12,     5,    -1,     9,    10,    12,     5,    -1,
       9,    11,    12,     5,    -1,    29,     8,    29,    17,    29,
      -1,    29,     8,    29,    17,    14,    -1,    29,     8,    14,
      17,    29,    -1,    29,     8,    14,    17,    14,    -1,    29,
       8,    29,    18,    29,    -1,    29,     8,    29,    18,    14,
      -1,    29,     8,    14,    18,    29,    -1,    29,     8,    29,
      19,    29,    -1,    29,     8,    29,    19,    14,    -1,    29,
       8,    14,    19,    29,    -1,    29,     8,    29,    20,    29,
      -1,    29,     8,    29,    20,    14,    -1,    29,     8,    14,
      20,    29,    -1,    29,     8,    29,    16,    29,    -1,    29,
       8,    29,    16,    14,    -1,    29,     8,    14,    16,    29,
      -1,    29,     8,    29,    15,    29,    -1,    29,     8,    29,
      15,    14,    -1,    29,     8,    14,    15,    29,    -1,    29,
       8,    29,     8,     8,    29,    -1,    29,     8,    29,     8,
       8,    14,    -1,    29,     8,    14,     8,     8,    29,    -1,
      29,     8,    29,    16,     8,    29,    -1,    29,     8,    29,
      16,     8,    14,    -1,    29,     8,    14,    16,     8,    29,
      -1,    29,     8,    29,    15,     8,    29,    -1,    29,     8,
      29,    15,     8,    14,    -1,    29,     8,    14,    15,     8,
      29,    -1,    29,     8,    29,    -1,    29,     8,    14,    -1,
      13,    -1,     7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   191,   191,   193,   193,   194,   194,   195,   196,   197,
     197,   199,   208,   214,   223,   232,   238,   247,   256,   262,
     271,   277,   282,   283,   286,   295,   301,   307,   311,   320,
     326,   335,   344,   350,   359,   368,   374,   383,   398,   410,
     425,   440,   452,   467,   482,   494,   509,   524,   536,   551,
     566,   578,   592,   599,   606,   606
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "START", "STOP", "LABEL", "COLON",
  "TEMP", "EQUALS", "IF", "TRUE", "FALSE", "GOTO", "VAR", "NUM",
  "LESSTHAN", "GRTRTHAN", "ADD", "SUB", "MUL", "DIV", "$accept", "Program",
  "Statement", "@1", "@2", "IfStatement", "Expression", "AssignmentExpr",
  "Variable", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    21,    22,    24,    23,    25,    23,    23,    23,    23,
      23,    26,    26,    26,    26,    26,    26,    26,    26,    26,
      26,    26,    26,    26,    27,    27,    27,    27,    27,    27,
      27,    27,    27,    27,    27,    27,    27,    27,    27,    27,
      27,    27,    27,    27,    27,    27,    27,    27,    27,    27,
      27,    27,    28,    28,    29,    29
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     0,     4,     0,     4,     2,     2,     2,
       0,     6,     6,     6,     6,     6,     6,     7,     7,     7,
       4,     4,     4,     4,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     3,     3,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    10,     0,     0,    55,     0,     0,    54,     0,    10,
      10,    10,     0,     1,     3,     0,     0,     0,     0,     5,
       2,     7,     8,     9,     0,    10,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    10,    53,    52,     4,
      22,    23,     0,    21,     0,     0,     0,    20,     0,     0,
       0,     0,     6,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    42,     0,
      39,    27,    26,    30,    33,    36,     0,     0,    41,    40,
       0,    38,    37,    25,    24,    29,    28,    32,    31,    35,
      34,     0,    13,    16,     0,     0,    12,    11,    15,    14,
      45,    51,    48,    44,    43,    50,    49,    47,    46,    19,
      18,    17
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     8,    25,    36,     9,    10,    11,    12
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -9
static const yytype_int16 yypact[] =
{
       2,    33,     6,     1,    -9,    79,     3,    -9,     5,    33,
      33,    33,    10,    -9,    -9,    -2,     8,    54,    68,    -9,
      -9,    -9,    -9,    -9,    91,    33,    18,    34,    35,    39,
     139,   139,    40,    42,    99,   101,    33,    -4,    16,    -9,
      -9,    -9,   139,    -9,    43,    51,   103,    -9,    52,    53,
      63,    65,    -9,    70,    14,    60,   111,   139,   139,   139,
      71,    87,    89,   113,   115,   123,   125,    75,    83,    86,
      95,    97,    94,   106,   114,   116,   139,   139,    -9,   139,
      -9,    -9,    -9,    -9,    -9,    -9,   127,   135,    -9,    -9,
     137,    -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,
      -9,   118,    -9,    -9,   126,   128,    -9,    -9,    -9,    -9,
      -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,
      -9,    -9
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
      -9,    -9,    -8,    -9,    -9,    -9,    -9,    -9,    -5
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      18,    21,    22,    23,    53,     1,    13,    14,    19,    20,
      26,    54,    55,    56,    57,    58,    59,    39,    24,    38,
      27,     4,    77,    40,    60,    44,    45,     7,    52,    49,
      51,    61,    62,    63,    64,    65,    66,    67,     3,    41,
       4,    71,     5,    42,    43,     6,     7,    47,    46,    78,
      80,    82,    83,    84,    85,    68,    89,    92,    94,    96,
      98,   100,    28,    69,    72,    73,    29,     4,    79,    30,
      31,   110,   111,     7,   112,    74,    32,    75,    76,    86,
      33,   114,   116,    34,    35,   118,     4,   101,   102,    15,
      16,   103,     7,    17,     4,    87,     4,    90,     4,   106,
       7,    88,     7,    91,     7,    37,     4,   104,     4,   105,
       4,   107,     7,    48,     7,    50,     7,    70,     4,   108,
       4,   109,     4,   119,     7,    81,     7,    93,     7,    95,
       4,   120,     4,   121,     4,     0,     7,    97,     7,    99,
       7,   113,     4,     0,     4,     0,     4,     0,     7,   115,
       7,   117,     7
};

static const yytype_int8 yycheck[] =
{
       5,     9,    10,    11,     8,     3,     0,     6,     5,     4,
      12,    15,    16,    17,    18,    19,    20,    25,     8,    24,
      12,     7,     8,     5,     8,    30,    31,    13,    36,    34,
      35,    15,    16,    17,    18,    19,    20,    42,     5,     5,
       7,    46,     9,     8,     5,    12,    13,     5,     8,    54,
      55,    56,    57,    58,    59,    12,    61,    62,    63,    64,
      65,    66,     8,    12,    12,    12,    12,     7,     8,    15,
      16,    76,    77,    13,    79,    12,     8,    12,     8,     8,
      12,    86,    87,    15,    16,    90,     7,    12,     5,    10,
      11,     5,    13,    14,     7,     8,     7,     8,     7,     5,
      13,    14,    13,    14,    13,    14,     7,    12,     7,    12,
       7,     5,    13,    14,    13,    14,    13,    14,     7,     5,
       7,     5,     7,     5,    13,    14,    13,    14,    13,    14,
       7,     5,     7,     5,     7,    -1,    13,    14,    13,    14,
      13,    14,     7,    -1,     7,    -1,     7,    -1,    13,    14,
      13,    14,    13
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    22,     5,     7,     9,    12,    13,    23,    26,
      27,    28,    29,     0,     6,    10,    11,    14,    29,     5,
       4,    23,    23,    23,     8,    24,    12,    12,     8,    12,
      15,    16,     8,    12,    15,    16,    25,    14,    29,    23,
       5,     5,     8,     5,    29,    29,     8,     5,    14,    29,
      14,    29,    23,     8,    15,    16,    17,    18,    19,    20,
       8,    15,    16,    17,    18,    19,    20,    29,    12,    12,
      14,    29,    12,    12,    12,    12,     8,     8,    29,     8,
      29,    14,    29,    29,    29,    29,     8,     8,    14,    29,
       8,    14,    29,    14,    29,    14,    29,    14,    29,    14,
      29,    12,     5,     5,    12,    12,     5,     5,     5,     5,
      29,    29,    29,    14,    29,    14,    29,    14,    29,     5,
       5,     5
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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
#line 191 "assembly.y"
    {YYACCEPT; }
    break;

  case 3:
#line 193 "assembly.y"
    {fprintf(fp,"%s: ", (yyvsp[(1) - (2)]));}
    break;

  case 5:
#line 194 "assembly.y"
    {fprintf(fp,"B %s\n", (yyvsp[(2) - (2)]));}
    break;

  case 11:
#line 199 "assembly.y"
    { if(!checkPage(H, (yyvsp[(2) - (6)]))){
                                                                        fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(2) - (6)]), H), (yyvsp[(2) - (6)]));
                                                                        if(!checkPage(H, (yyvsp[(4) - (6)]))){
                                                                        	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(4) - (6)]), H), (yyvsp[(4) - (6)]));
                                                                        }
                                                                      }
                                                                      fprintf(fp,"CMP R%d, R%d\n", reference(q, (yyvsp[(2) - (6)]), H), reference(q, (yyvsp[(4) - (6)]), H));
                                                                      fprintf(fp,"BLT %s\n", (yyvsp[(6) - (6)]));
                                                                    }
    break;

  case 12:
#line 208 "assembly.y"
    { if(!checkPage(H, (yyvsp[(2) - (6)]))){
                                                                        fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(2) - (6)]), H), (yyvsp[(2) - (6)]));
                                                                      }
                                                                      fprintf(fp,"CMP R%d, %s\n", reference(q, (yyvsp[(2) - (6)]), H), (yyvsp[(4) - (6)]));
                                                                      fprintf(fp,"BLT %s\n", (yyvsp[(6) - (6)]));
                                                                    }
    break;

  case 13:
#line 214 "assembly.y"
    { if(!checkPage(H, (yyvsp[(4) - (6)]))){
                                                                        fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(2) - (6)]), H), (yyvsp[(2) - (6)]));
                                                                      }
                                                                      fprintf(fp,"CMP %s, R%d\n", (yyvsp[(2) - (6)]), reference(q, (yyvsp[(4) - (6)]), H));
                                                                      fprintf(fp,"BLT %s\n", (yyvsp[(6) - (6)]));
                                                                    }
    break;

  case 14:
#line 223 "assembly.y"
    { if(!checkPage(H, (yyvsp[(2) - (6)]))){
                                                                        fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(2) - (6)]), H), (yyvsp[(2) - (6)]));
                                                                        if(!checkPage(H, (yyvsp[(4) - (6)]))){
                                                                        	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(4) - (6)]), H), (yyvsp[(4) - (6)]));
                                                                        }
                                                                      }
                                                                      fprintf(fp,"CMP R%d, R%d\n", reference(q, (yyvsp[(2) - (6)]), H), reference(q, (yyvsp[(4) - (6)]), H));
                                                                      fprintf(fp,"BGT %s\n", (yyvsp[(6) - (6)]));
                                                                    }
    break;

  case 15:
#line 232 "assembly.y"
    { if(!checkPage(H, (yyvsp[(2) - (6)]))){
                                                                        fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(2) - (6)]), H), (yyvsp[(2) - (6)]));
                                                                      }
                                                                      fprintf(fp,"CMP R%d, %s\n", reference(q, (yyvsp[(2) - (6)]), H), (yyvsp[(4) - (6)]));
                                                                      fprintf(fp,"BGT %s\n", (yyvsp[(6) - (6)]));
                                                                    }
    break;

  case 16:
#line 238 "assembly.y"
    { if(!checkPage(H, (yyvsp[(4) - (6)]))){
                                                                        fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(2) - (6)]), H), (yyvsp[(2) - (6)]));
                                                                      }
                                                                      fprintf(fp,"CMP %s, R%d\n", (yyvsp[(2) - (6)]), reference(q, (yyvsp[(4) - (6)]), H));
                                                                      fprintf(fp,"BGT %s\n", (yyvsp[(6) - (6)]));
                                                                    }
    break;

  case 17:
#line 247 "assembly.y"
    { if(!checkPage(H, (yyvsp[(2) - (7)]))){
                                                                        fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(2) - (7)]), H), (yyvsp[(2) - (7)]));
                                                                        if(!checkPage(H, (yyvsp[(5) - (7)]))){
                                                                        	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(5) - (7)]), H), (yyvsp[(5) - (7)]));
                                                                        }
                                                                      }
                                                                      fprintf(fp,"CMP R%d, R%d\n", reference(q, (yyvsp[(2) - (7)]), H), reference(q, (yyvsp[(5) - (7)]), H));
                                                                      fprintf(fp,"BLT %s\n", (yyvsp[(6) - (7)]));
                                                                    }
    break;

  case 18:
#line 256 "assembly.y"
    { if(!checkPage(H, (yyvsp[(2) - (7)]))){
                                                                        fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(2) - (7)]), H), (yyvsp[(2) - (7)]));
                                                                      }
                                                                      fprintf(fp,"CMP R%d, %s\n", reference(q, (yyvsp[(2) - (7)]), H), (yyvsp[(5) - (7)]));
                                                                      fprintf(fp,"BLT %s\n", (yyvsp[(6) - (7)]));
                                                                    }
    break;

  case 19:
#line 262 "assembly.y"
    { if(!checkPage(H, (yyvsp[(5) - (7)]))){
                                                                        fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(2) - (7)]), H), (yyvsp[(2) - (7)]));
                                                                      }
                                                                      fprintf(fp,"CMP %s, R%d\n", (yyvsp[(2) - (7)]), reference(q, (yyvsp[(5) - (7)]), H));
                                                                      fprintf(fp,"BLT %s\n", (yyvsp[(6) - (7)]));
                                                                    }
    break;

  case 20:
#line 271 "assembly.y"
    { if(!checkPage(H, (yyvsp[(2) - (4)]))){
                                                                        fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(2) - (4)]), H), (yyvsp[(2) - (4)]));
                                                                      }
                                                                      fprintf(fp,"CMP R%d, 0\n", reference(q, (yyvsp[(2) - (4)]), H));
                                                                      fprintf(fp,"BLT %s\n", (yyvsp[(4) - (4)]));
                                                                    }
    break;

  case 21:
#line 277 "assembly.y"
    { fprintf(fp,"CMP %s, 0\n", (yyvsp[(2) - (4)]));
                                                                      fprintf(fp,"BLT %s\n", (yyvsp[(4) - (4)]));
                                                                    }
    break;

  case 22:
#line 282 "assembly.y"
    {fprintf(fp,"B %s\n", (yyvsp[(4) - (4)]));}
    break;

  case 24:
#line 286 "assembly.y"
    { if(!checkPage(H, (yyvsp[(3) - (5)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(3) - (5)]), H), (yyvsp[(3) - (5)]));
  																		if(!checkPage(H, (yyvsp[(5) - (5)]))){
                                                                        	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(5) - (5)]), H), (yyvsp[(5) - (5)]));
                                                                        }
																	  }
                                                                      fprintf(fp,"ADD R%d, R%d, R%d\n", reference(q, (yyvsp[(1) - (5)]), H), reference(q, (yyvsp[(3) - (5)]), H), reference(q, (yyvsp[(5) - (5)]), H));
                                                                      fprintf(fp,"STR R%d, %s\n", reference(q, (yyvsp[(1) - (5)]), H), (yyvsp[(1) - (5)]));
                                                                    }
    break;

  case 25:
#line 295 "assembly.y"
    { if(!checkPage(H, (yyvsp[(3) - (5)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(3) - (5)]), H), (yyvsp[(3) - (5)]));
																	  }
                                                                      fprintf(fp,"ADD R%d, R%d, %s\n", reference(q, (yyvsp[(1) - (5)]), H), reference(q, (yyvsp[(3) - (5)]), H), (yyvsp[(5) - (5)]));
                                                                      fprintf(fp,"STR R%d, %s\n", reference(q, (yyvsp[(1) - (5)]), H), (yyvsp[(1) - (5)]));
                                                                    }
    break;

  case 26:
#line 301 "assembly.y"
    { if(!checkPage(H, (yyvsp[(5) - (5)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(5) - (5)]), H), (yyvsp[(5) - (5)]));
																	  }
                                                                      fprintf(fp,"ADD R%d, R%d, %s\n", reference(q, (yyvsp[(1) - (5)]), H), reference(q, (yyvsp[(5) - (5)]), H), (yyvsp[(3) - (5)]));
                                                                      fprintf(fp,"STR R%d, %s\n", reference(q, (yyvsp[(1) - (5)]), H), (yyvsp[(1) - (5)]));
                                                                    }
    break;

  case 27:
#line 307 "assembly.y"
    {fprintf(fp,"ADD R%d, %s, %s\n", reference(q, (yyvsp[(1) - (5)]), H), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]));
                                                                      fprintf(fp,"STR R%d, %s\n", reference(q, (yyvsp[(1) - (5)]), H), (yyvsp[(1) - (5)]));}
    break;

  case 28:
#line 311 "assembly.y"
    { if(!checkPage(H, (yyvsp[(3) - (5)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(3) - (5)]), H), (yyvsp[(3) - (5)]));
  																		if(!checkPage(H, (yyvsp[(5) - (5)]))){
                                                                        	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(5) - (5)]), H), (yyvsp[(5) - (5)]));
                                                                        }
																	  }
                                                                      fprintf(fp,"SUB R%d, R%d, R%d\n", reference(q, (yyvsp[(1) - (5)]), H), reference(q, (yyvsp[(3) - (5)]), H), reference(q, (yyvsp[(5) - (5)]), H));
                                                                      fprintf(fp,"STR R%d, %s\n", reference(q, (yyvsp[(1) - (5)]), H), (yyvsp[(1) - (5)]));
                                                                    }
    break;

  case 29:
#line 320 "assembly.y"
    { if(!checkPage(H, (yyvsp[(3) - (5)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(3) - (5)]), H), (yyvsp[(3) - (5)]));
																	  }
                                                                      fprintf(fp,"SUB R%d, R%d, %s\n", reference(q, (yyvsp[(1) - (5)]), H), reference(q, (yyvsp[(3) - (5)]), H), (yyvsp[(5) - (5)]));
                                                                      fprintf(fp,"STR R%d, %s\n", reference(q, (yyvsp[(1) - (5)]), H), (yyvsp[(1) - (5)]));
                                                                    }
    break;

  case 30:
#line 326 "assembly.y"
    { if(!checkPage(H, (yyvsp[(5) - (5)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(5) - (5)]), H), (yyvsp[(5) - (5)]));
																	  }
                                                                      fprintf(fp,"RSB R%d, R%d, %s\n", reference(q, (yyvsp[(1) - (5)]), H), reference(q, (yyvsp[(5) - (5)]), H), (yyvsp[(3) - (5)]));
                                                                      fprintf(fp,"STR R%d, %s\n", reference(q, (yyvsp[(1) - (5)]), H), (yyvsp[(1) - (5)]));
                                                                    }
    break;

  case 31:
#line 335 "assembly.y"
    { if(!checkPage(H, (yyvsp[(3) - (5)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(3) - (5)]), H), (yyvsp[(3) - (5)]));
  																		if(!checkPage(H, (yyvsp[(5) - (5)]))){
                                                                        	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(5) - (5)]), H), (yyvsp[(5) - (5)]));
                                                                        }
																	  }
                                                                      fprintf(fp,"MUL R%d, R%d, R%d\n", reference(q, (yyvsp[(1) - (5)]), H), reference(q, (yyvsp[(3) - (5)]), H), reference(q, (yyvsp[(5) - (5)]), H));
                                                                      fprintf(fp,"STR R%d, %s\n", reference(q, (yyvsp[(1) - (5)]), H), (yyvsp[(1) - (5)]));
                                                                    }
    break;

  case 32:
#line 344 "assembly.y"
    { if(!checkPage(H, (yyvsp[(3) - (5)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(3) - (5)]), H), (yyvsp[(3) - (5)]));
																	  }
                                                                      fprintf(fp,"MUL R%d, R%d, %s\n", reference(q, (yyvsp[(1) - (5)]), H), reference(q, (yyvsp[(3) - (5)]), H), (yyvsp[(5) - (5)]));
                                                                      fprintf(fp,"STR R%d, %s\n", reference(q, (yyvsp[(1) - (5)]), H), (yyvsp[(1) - (5)]));
                                                                    }
    break;

  case 33:
#line 350 "assembly.y"
    { if(!checkPage(H, (yyvsp[(5) - (5)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(5) - (5)]), H), (yyvsp[(5) - (5)]));
																	  }
                                                                      fprintf(fp,"MUL R%d, R%d, %s\n", reference(q, (yyvsp[(1) - (5)]), H), reference(q, (yyvsp[(5) - (5)]), H), (yyvsp[(3) - (5)]));
                                                                      fprintf(fp,"STR R%d, %s\n", reference(q, (yyvsp[(1) - (5)]), H), (yyvsp[(1) - (5)]));
                                                                    }
    break;

  case 34:
#line 359 "assembly.y"
    { if(!checkPage(H, (yyvsp[(3) - (5)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(3) - (5)]), H), (yyvsp[(3) - (5)]));
  																		if(!checkPage(H, (yyvsp[(5) - (5)]))){
                                                                        	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(5) - (5)]), H), (yyvsp[(5) - (5)]));
                                                                        }
																	  }
                                                                      fprintf(fp,"DIV R%d, R%d, R%d\n", reference(q, (yyvsp[(1) - (5)]), H), reference(q, (yyvsp[(3) - (5)]), H), reference(q, (yyvsp[(5) - (5)]), H));
                                                                      fprintf(fp,"STR R%d, %s\n", reference(q, (yyvsp[(1) - (5)]), H), (yyvsp[(1) - (5)]));
                                                                    }
    break;

  case 35:
#line 368 "assembly.y"
    { if(!checkPage(H, (yyvsp[(3) - (5)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(3) - (5)]), H), (yyvsp[(3) - (5)]));
																	  }
                                                                      fprintf(fp,"DIV R%d, R%d, %s\n", reference(q, (yyvsp[(1) - (5)]), H), reference(q, (yyvsp[(3) - (5)]), H), (yyvsp[(5) - (5)]));
                                                                      fprintf(fp,"STR R%d, %s\n", reference(q, (yyvsp[(1) - (5)]), H), (yyvsp[(1) - (5)]));
                                                                    }
    break;

  case 36:
#line 374 "assembly.y"
    { if(!checkPage(H, (yyvsp[(5) - (5)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(5) - (5)]), H), (yyvsp[(5) - (5)]));
																	  }
                                                                      fprintf(fp,"DIV R%d, %s, R%d\n", reference(q, (yyvsp[(1) - (5)]), H), (yyvsp[(3) - (5)]), reference(q, (yyvsp[(5) - (5)]), H));
                                                                      fprintf(fp,"STR R%d, %s\n", reference(q, (yyvsp[(1) - (5)]), H), (yyvsp[(1) - (5)]));
                                                                    }
    break;

  case 37:
#line 383 "assembly.y"
    { if(!checkPage(H, (yyvsp[(3) - (5)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(3) - (5)]), H), (yyvsp[(3) - (5)]));
  																		if(!checkPage(H, (yyvsp[(5) - (5)]))){
                                                                        	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(5) - (5)]), H), (yyvsp[(5) - (5)]));
                                                                        }
																	  }
                                                                      char* label1 = newLabel();
                                                                      char* label2 = newLabel();
                                                                      fprintf(fp,"CMP R%d, R%d\n", reference(q, (yyvsp[(3) - (5)]), H), reference(q, (yyvsp[(5) - (5)]), H));
                                                                      fprintf(fp,"BGT %s\n", label1);
                                                                      fprintf(fp,"MOV R%d, 0\n", reference(q, (yyvsp[(1) - (5)]), H));
                                                                      fprintf(fp,"B %s\n", label2);
                                                                      fprintf(fp,"%s :MOV R%d, 1\n", label1, reference(q, (yyvsp[(1) - (5)]), H));
                                                                      fprintf(fp,"%s :STR R%d, %s\n", label2, reference(q, (yyvsp[(1) - (5)]), H), (yyvsp[(1) - (5)]));
																	}
    break;

  case 38:
#line 398 "assembly.y"
    { if(!checkPage(H, (yyvsp[(3) - (5)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(3) - (5)]), H), (yyvsp[(3) - (5)]));
																	  }
                                                                      char* label1 = newLabel();
                                                                      char* label2 = newLabel();
                                                                      fprintf(fp,"CMP R%d, %s\n", reference(q, (yyvsp[(3) - (5)]), H), (yyvsp[(5) - (5)]));
                                                                      fprintf(fp,"BGT %s\n", label1);
                                                                      fprintf(fp,"MOV R%d, 0\n", reference(q, (yyvsp[(1) - (5)]), H));
                                                                      fprintf(fp,"B %s\n", label2);
                                                                      fprintf(fp,"%s :MOV R%d, 1\n", label1, reference(q, (yyvsp[(1) - (5)]), H));
                                                                      fprintf(fp,"%s :STR R%d, %s\n", label2, reference(q, (yyvsp[(1) - (5)]), H), (yyvsp[(1) - (5)]));
																	}
    break;

  case 39:
#line 410 "assembly.y"
    { if(!checkPage(H, (yyvsp[(5) - (5)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(5) - (5)]), H), (yyvsp[(5) - (5)]));
																	  }
                                                                      char* label1 = newLabel();
                                                                      char* label2 = newLabel();
                                                                      fprintf(fp,"CMP %s, R%d\n", (yyvsp[(3) - (5)]), reference(q, (yyvsp[(5) - (5)]), H));
                                                                      fprintf(fp,"BGT %s\n", label1);
                                                                      fprintf(fp,"MOV R%d, 0\n", reference(q, (yyvsp[(1) - (5)]), H));
                                                                      fprintf(fp,"B %s\n", label2);
                                                                      fprintf(fp,"%s :MOV R%d, 1\n", label1, reference(q, (yyvsp[(1) - (5)]), H));
                                                                      fprintf(fp,"%s :STR R%d, %s\n", label2, reference(q, (yyvsp[(1) - (5)]), H), (yyvsp[(1) - (5)]));
																	}
    break;

  case 40:
#line 425 "assembly.y"
    { if(!checkPage(H, (yyvsp[(3) - (5)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(3) - (5)]), H), (yyvsp[(3) - (5)]));
  																		if(!checkPage(H, (yyvsp[(5) - (5)]))){
                                                                        	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(5) - (5)]), H), (yyvsp[(5) - (5)]));
                                                                        }
																	  }
                                                                      char* label1 = newLabel();
                                                                      char* label2 = newLabel();
                                                                      fprintf(fp,"CMP R%d, R%d\n", reference(q, (yyvsp[(3) - (5)]), H), reference(q, (yyvsp[(5) - (5)]), H));
                                                                      fprintf(fp,"BLT %s\n", label1);
                                                                      fprintf(fp,"MOV R%d, 0\n", reference(q, (yyvsp[(1) - (5)]), H));
                                                                      fprintf(fp,"B %s\n", label2);
                                                                      fprintf(fp,"%s :MOV R%d, 1\n", label1, reference(q, (yyvsp[(1) - (5)]), H));
                                                                      fprintf(fp,"%s :STR R%d, %s\n", label2, reference(q, (yyvsp[(1) - (5)]), H), (yyvsp[(1) - (5)]));
																	}
    break;

  case 41:
#line 440 "assembly.y"
    { if(!checkPage(H, (yyvsp[(3) - (5)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(3) - (5)]), H), (yyvsp[(3) - (5)]));
																	  }
                                                                      char* label1 = newLabel();
                                                                      char* label2 = newLabel();
                                                                      fprintf(fp,"CMP R%d, %s\n", reference(q, (yyvsp[(3) - (5)]), H), (yyvsp[(5) - (5)]));
                                                                      fprintf(fp,"BLT %s\n", label1);
                                                                      fprintf(fp,"MOV R%d, 0\n", reference(q, (yyvsp[(1) - (5)]), H));
                                                                      fprintf(fp,"B %s\n", label2);
                                                                      fprintf(fp,"%s :MOV R%d, 1\n", label1, reference(q, (yyvsp[(1) - (5)]), H));
                                                                      fprintf(fp,"%s :STR R%d, %s\n", label2, reference(q, (yyvsp[(1) - (5)]), H), (yyvsp[(1) - (5)]));
																	}
    break;

  case 42:
#line 452 "assembly.y"
    { if(!checkPage(H, (yyvsp[(5) - (5)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(5) - (5)]), H), (yyvsp[(5) - (5)]));
																	  }
                                                                      char* label1 = newLabel();
                                                                      char* label2 = newLabel();
                                                                      fprintf(fp,"CMP %s, R%d\n", (yyvsp[(3) - (5)]), reference(q, (yyvsp[(5) - (5)]), H));
                                                                      fprintf(fp,"BLT %s\n", label1);
                                                                      fprintf(fp,"MOV R%d, 0\n", reference(q, (yyvsp[(1) - (5)]), H));
                                                                      fprintf(fp,"B %s\n", label2);
                                                                      fprintf(fp,"%s :MOV R%d, 1\n", label1, reference(q, (yyvsp[(1) - (5)]), H));
                                                                      fprintf(fp,"%s :STR R%d, %s\n", label2, reference(q, (yyvsp[(1) - (5)]), H), (yyvsp[(1) - (5)]));
																	}
    break;

  case 43:
#line 467 "assembly.y"
    { if(!checkPage(H, (yyvsp[(3) - (6)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(3) - (6)]), H), (yyvsp[(3) - (6)]));
  																		if(!checkPage(H, (yyvsp[(5) - (6)]))){
                                                                        	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(6) - (6)]), H), (yyvsp[(6) - (6)]));
                                                                        }
																	  }
                                                                      char* label1 = newLabel();
                                                                      char* label2 = newLabel();
                                                                      fprintf(fp,"CMP R%d, R%d\n", reference(q, (yyvsp[(3) - (6)]), H), reference(q, (yyvsp[(6) - (6)]), H));
                                                                      fprintf(fp,"BE %s\n", label1);
                                                                      fprintf(fp,"MOV R%d, 0\n", reference(q, (yyvsp[(1) - (6)]), H));
                                                                      fprintf(fp,"B %s\n", label2);
                                                                      fprintf(fp,"%s :MOV R%d, 1\n", label1, reference(q, (yyvsp[(1) - (6)]), H));
                                                                      fprintf(fp,"%s :STR R%d, %s\n", label2, reference(q, (yyvsp[(1) - (6)]), H), (yyvsp[(1) - (6)]));
																	}
    break;

  case 44:
#line 482 "assembly.y"
    { if(!checkPage(H, (yyvsp[(3) - (6)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(3) - (6)]), H), (yyvsp[(3) - (6)]));
																	  }
                                                                      char* label1 = newLabel();
                                                                      char* label2 = newLabel();
                                                                      fprintf(fp,"CMP R%d, %s\n", reference(q, (yyvsp[(3) - (6)]), H), (yyvsp[(6) - (6)]));
                                                                      fprintf(fp,"BE %s\n", label1);
                                                                      fprintf(fp,"MOV R%d, 0\n", reference(q, (yyvsp[(1) - (6)]), H));
                                                                      fprintf(fp,"B %s\n", label2);
                                                                      fprintf(fp,"%s :MOV R%d, 1\n", label1, reference(q, (yyvsp[(1) - (6)]), H));
                                                                      fprintf(fp,"%s :STR R%d, %s\n", label2, reference(q, (yyvsp[(1) - (6)]), H), (yyvsp[(1) - (6)]));
																	}
    break;

  case 45:
#line 494 "assembly.y"
    { if(!checkPage(H, (yyvsp[(6) - (6)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(6) - (6)]), H), (yyvsp[(6) - (6)]));
																	  }
                                                                      char* label1 = newLabel();
                                                                      char* label2 = newLabel();
                                                                      fprintf(fp,"CMP %s, R%d\n", (yyvsp[(3) - (6)]), reference(q, (yyvsp[(6) - (6)]), H));
                                                                      fprintf(fp,"BE %s\n", label1);
                                                                      fprintf(fp,"MOV R%d, 0\n", reference(q, (yyvsp[(1) - (6)]), H));
                                                                      fprintf(fp,"B %s\n", label2);
                                                                      fprintf(fp,"%s :MOV R%d, 1\n", label1, reference(q, (yyvsp[(1) - (6)]), H));
                                                                      fprintf(fp,"%s :STR R%d, %s\n", label2, reference(q, (yyvsp[(1) - (6)]), H), (yyvsp[(1) - (6)]));
																	}
    break;

  case 46:
#line 509 "assembly.y"
    { if(!checkPage(H, (yyvsp[(3) - (6)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(3) - (6)]), H), (yyvsp[(3) - (6)]));
  																		if(!checkPage(H, (yyvsp[(5) - (6)]))){
                                                                        	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(6) - (6)]), H), (yyvsp[(6) - (6)]));
                                                                        }
																	  }
                                                                      char* label1 = newLabel();
                                                                      char* label2 = newLabel();
                                                                      fprintf(fp,"CMP R%d, R%d\n", reference(q, (yyvsp[(3) - (6)]), H), reference(q, (yyvsp[(6) - (6)]), H));
                                                                      fprintf(fp,"BGE %s\n", label1);
                                                                      fprintf(fp,"MOV R%d, 0\n", reference(q, (yyvsp[(1) - (6)]), H));
                                                                      fprintf(fp,"B %s\n", label2);
                                                                      fprintf(fp,"%s :MOV R%d, 1\n", label1, reference(q, (yyvsp[(1) - (6)]), H));
                                                                      fprintf(fp,"%s :STR R%d, %s\n", label2, reference(q, (yyvsp[(1) - (6)]), H), (yyvsp[(1) - (6)]));
																	}
    break;

  case 47:
#line 524 "assembly.y"
    { if(!checkPage(H, (yyvsp[(3) - (6)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(3) - (6)]), H), (yyvsp[(3) - (6)]));
																	  }
                                                                      char* label1 = newLabel();
                                                                      char* label2 = newLabel();
                                                                      fprintf(fp,"CMP R%d, %s\n", reference(q, (yyvsp[(3) - (6)]), H), (yyvsp[(6) - (6)]));
                                                                      fprintf(fp,"BGE %s\n", label1);
                                                                      fprintf(fp,"MOV R%d, 0\n", reference(q, (yyvsp[(1) - (6)]), H));
                                                                      fprintf(fp,"B %s\n", label2);
                                                                      fprintf(fp,"%s :MOV R%d, 1\n", label1, reference(q, (yyvsp[(1) - (6)]), H));
                                                                      fprintf(fp,"%s :STR R%d, %s\n", label2, reference(q, (yyvsp[(1) - (6)]), H), (yyvsp[(1) - (6)]));
																	}
    break;

  case 48:
#line 536 "assembly.y"
    { if(!checkPage(H, (yyvsp[(6) - (6)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(6) - (6)]), H), (yyvsp[(6) - (6)]));
																	  }
                                                                      char* label1 = newLabel();
                                                                      char* label2 = newLabel();
                                                                      fprintf(fp,"CMP %s, R%d\n", (yyvsp[(3) - (6)]), reference(q, (yyvsp[(6) - (6)]), H));
                                                                      fprintf(fp,"BGE %s\n", label1);
                                                                      fprintf(fp,"MOV R%d, 0\n", reference(q, (yyvsp[(1) - (6)]), H));
                                                                      fprintf(fp,"B %s\n", label2);
                                                                      fprintf(fp,"%s :MOV R%d, 1\n", label1, reference(q, (yyvsp[(1) - (6)]), H));
                                                                      fprintf(fp,"%s :STR R%d, %s\n", label2, reference(q, (yyvsp[(1) - (6)]), H), (yyvsp[(1) - (6)]));
																	}
    break;

  case 49:
#line 551 "assembly.y"
    { if(!checkPage(H, (yyvsp[(3) - (6)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(3) - (6)]), H), (yyvsp[(3) - (6)]));
  																		if(!checkPage(H, (yyvsp[(5) - (6)]))){
                                                                        	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(6) - (6)]), H), (yyvsp[(6) - (6)]));
                                                                        }
																	  }
                                                                      char* label1 = newLabel();
                                                                      char* label2 = newLabel();
                                                                      fprintf(fp,"CMP R%d, R%d\n", reference(q, (yyvsp[(3) - (6)]), H), reference(q, (yyvsp[(6) - (6)]), H));
                                                                      fprintf(fp,"BLE %s\n", label1);
                                                                      fprintf(fp,"MOV R%d, 0\n", reference(q, (yyvsp[(1) - (6)]), H));
                                                                      fprintf(fp,"B %s\n", label2);
                                                                      fprintf(fp,"%s :MOV R%d, 1\n", label1, reference(q, (yyvsp[(1) - (6)]), H));
                                                                      fprintf(fp,"%s :STR R%d, %s\n", label2, reference(q, (yyvsp[(1) - (6)]), H), (yyvsp[(1) - (6)]));
																	}
    break;

  case 50:
#line 566 "assembly.y"
    { if(!checkPage(H, (yyvsp[(3) - (6)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(3) - (6)]), H), (yyvsp[(3) - (6)]));
																	  }
                                                                      char* label1 = newLabel();
                                                                      char* label2 = newLabel();
                                                                      fprintf(fp,"CMP R%d, %s\n", reference(q, (yyvsp[(3) - (6)]), H), (yyvsp[(6) - (6)]));
                                                                      fprintf(fp,"BLE %s\n", label1);
                                                                      fprintf(fp,"MOV R%d, 0\n", reference(q, (yyvsp[(1) - (6)]), H));
                                                                      fprintf(fp,"B %s\n", label2);
                                                                      fprintf(fp,"%s :MOV R%d, 1\n", label1, reference(q, (yyvsp[(1) - (6)]), H));
                                                                      fprintf(fp,"%s :STR R%d, %s\n", label2, reference(q, (yyvsp[(1) - (6)]), H), (yyvsp[(1) - (6)]));
																	}
    break;

  case 51:
#line 578 "assembly.y"
    { if(!checkPage(H, (yyvsp[(6) - (6)]))){ 
  																	  	fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(6) - (6)]), H), (yyvsp[(6) - (6)]));
																	  }
                                                                      char* label1 = newLabel();
                                                                      char* label2 = newLabel();
                                                                      fprintf(fp,"CMP %s, R%d\n", (yyvsp[(3) - (6)]), reference(q, (yyvsp[(6) - (6)]), H));
                                                                      fprintf(fp,"BLE %s\n", label1);
                                                                      fprintf(fp,"MOV R%d, 0\n", reference(q, (yyvsp[(1) - (6)]), H));
                                                                      fprintf(fp,"B %s\n", label2);
                                                                      fprintf(fp,"%s :MOV R%d, 1\n", label1, reference(q, (yyvsp[(1) - (6)]), H));
                                                                      fprintf(fp,"%s :STR R%d, %s\n", label2, reference(q, (yyvsp[(1) - (6)]), H), (yyvsp[(1) - (6)]));
																	}
    break;

  case 52:
#line 592 "assembly.y"
    { if(!checkPage(H, (yyvsp[(3) - (3)]))){
                                                fprintf(fp,"LDR R%d, %s\n", reference(q, (yyvsp[(3) - (3)]), H), (yyvsp[(3) - (3)]));
                                              }
                                              fprintf(fp,"MOV R%d, R%d\n", reference(q, (yyvsp[(1) - (3)]), H), reference(q, (yyvsp[(3) - (3)]), H));
                                              fprintf(fp,"STR R%d, %s\n", reference(q, (yyvsp[(1) - (3)]), H), (yyvsp[(1) - (3)]));
                                            }
    break;

  case 53:
#line 599 "assembly.y"
    {
                                              fprintf(fp,"MOV R%d, %s\n", reference(q, (yyvsp[(1) - (3)]), H), (yyvsp[(3) - (3)]));
                                              fprintf(fp,"STR R%d, %s\n", reference(q, (yyvsp[(1) - (3)]), H), (yyvsp[(1) - (3)]));
                                            }
    break;

  case 54:
#line 606 "assembly.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 55:
#line 606 "assembly.y"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;


/* Line 1267 of yacc.c.  */
#line 2191 "y.tab.c"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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


#line 609 "assembly.y"



void yyerror(const char *s)
{
	// fprintf(fp,"%s\n", s);
}

int main()
{
    
    fp = fopen("tcg.txt","w");
    H = initialize_hash();
    q = createQueue();
    if(!yyparse())
    {
        printf("\nVALID\n");
    }
}
