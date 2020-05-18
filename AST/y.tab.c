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
#define YYLSP_NEEDED 1



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_EndOfFile = 258,
     T_Return = 259,
     T_Number = 260,
     T_True = 261,
     T_False = 262,
     T_ID = 263,
     T_Print = 264,
     T_Cln = 265,
     T_NL = 266,
     T_EQL = 267,
     T_NEQ = 268,
     T_EQ = 269,
     T_GT = 270,
     T_LT = 271,
     T_EGT = 272,
     T_ELT = 273,
     T_Or = 274,
     T_And = 275,
     T_Not = 276,
     ID = 277,
     ND = 278,
     DD = 279,
     T_String = 280,
     Trip_Quote = 281,
     T_If = 282,
     T_Elif = 283,
     T_While = 284,
     T_Else = 285,
     T_Import = 286,
     T_Break = 287,
     T_Pass = 288,
     T_MN = 289,
     T_PL = 290,
     T_DV = 291,
     T_ML = 292,
     T_OP = 293,
     T_CP = 294,
     T_OB = 295,
     T_CB = 296,
     T_Def = 297,
     T_Comma = 298,
     T_Range = 299,
     T_List = 300
   };
#endif
/* Tokens.  */
#define T_EndOfFile 258
#define T_Return 259
#define T_Number 260
#define T_True 261
#define T_False 262
#define T_ID 263
#define T_Print 264
#define T_Cln 265
#define T_NL 266
#define T_EQL 267
#define T_NEQ 268
#define T_EQ 269
#define T_GT 270
#define T_LT 271
#define T_EGT 272
#define T_ELT 273
#define T_Or 274
#define T_And 275
#define T_Not 276
#define ID 277
#define ND 278
#define DD 279
#define T_String 280
#define Trip_Quote 281
#define T_If 282
#define T_Elif 283
#define T_While 284
#define T_Else 285
#define T_Import 286
#define T_Break 287
#define T_Pass 288
#define T_MN 289
#define T_PL 290
#define T_DV 291
#define T_ML 292
#define T_OP 293
#define T_CP 294
#define T_OB 295
#define T_CB 296
#define T_Def 297
#define T_Comma 298
#define T_Range 299
#define T_List 300




/* Copy the first part of user declarations.  */
#line 1 "grammar.y"


	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include<stdarg.h>

	extern int yylineno;
	extern int depth;
	extern int top();
	extern int pop();
	
	int currentScope = 1, previousScope = 1;
	
	int *arrayScope = NULL;
	
	typedef struct record
	{
		char *type;
		char *name;
		int decLineNo;
		int lastUseLine;
	} record;

	typedef struct STable
	{
		int no;
		int noOfElems;
		int scope;
		record *Elements;
		int Parent;
		
	} STable;
	
	typedef struct ASTNode
	{
    /*Operator*/
    char *NType;
    int noOps;
    struct ASTNode** NextLevel;
    
    /*Identifier or Const*/
    record *id;
	
	} node;
  
  typedef struct Quad
  {
  	char *Result;
  	char *A1;
  	char *A2;
  	char *Oper;
  } Quad;

	STable *symbolTables = NULL;
	int sIndex = -1, aIndex = -1, tabCount = 0, tIndex=0, lIndex=0;
	node *rootNode;
	char *argsList = NULL;
	char *tVar, *nVar; 
	
	/*-----------------------------Declarations----------------------------------*/
	
	record* findRecord(const char *name, const char *type, int scope);
  node *createID_Const(char *value, char *type, int scope);
  int power(int base, int exp);
  void updateCScope(int scope);
  void resetDepth();
	int scopeBasedTableSearch(int scope);
	void initNewTable(int scope);
	void init();
	int searchRecordInScope(const char* type, const char *name, int index);
	void insertRecord(const char* type, const char *name, int lineNo, int scope);
	int searchRecordInScope(const char* type, const char *name, int index);
	void checkList(const char *name, int lineNo, int scope);
	void printSTable();
	void freeAll();
	void addToList(char *newVal);
	void clearArgsList();
	
	/*------------------------------------------------------------------------------*/
	
  void codeGenOp(node *opNode)
  {
  	if(!strcmp(opNode->NType, "If"))
  	{
  	
  	}
	}
	
	void codeGenValue(char *type, char *value)
	{
		
	}
	 
  node *createID_Const(char *type, char *value, int scope)
  {
    node *newNode;
    newNode = (node*)calloc(1, sizeof(node));
    newNode->NType = NULL;
    newNode->noOps = -1;
    newNode->id = findRecord(value, type, scope);
    return newNode;
  }

  node *createOp(char *oper, int noOps, ...)
  {
    va_list params;
    node *newNode;
    int i;
    newNode = (node*)calloc(1, sizeof(node));
    
    newNode->NextLevel = (node**)calloc(noOps, sizeof(node*));
    
    newNode->NType = (char*)malloc(strlen(oper)+1);
    strcpy(newNode->NType, oper);
    newNode->noOps = noOps;
    va_start(params, noOps);
    
    for (i = 0; i < noOps; i++)
      newNode->NextLevel[i] = va_arg(params, node*);
    
    va_end(params);
    return newNode;
  }
  
  void addToList(char *newVal)
  {
    strcat(argsList, ", ");
    strcat(argsList, newVal);
  }
  
  void clearArgsList()
  {
    strcpy(argsList, "");
  }
  
	int power(int base, int exp)
	{
		int i =0, res = 1;
		for(i; i<exp; i++)
		{
			res *= base;
		}
		return res;
	}
	
	void updateCScope(int scope)
	{
		currentScope = scope;
	}
	
	void resetDepth()
	{
		while(top()) pop();
		depth = 10;
	}
	
	int scopeBasedTableSearch(int scope)
	{
		int i = sIndex;
		for(i; i > -1; i--)
		{
			if(symbolTables[i].scope == scope)
			{
				return i;
			}
		}
		return -1;
	}
	
	void initNewTable(int scope)
	{
		arrayScope[scope]++;
		sIndex++;
		symbolTables[sIndex].no = sIndex;
		symbolTables[sIndex].scope = power(scope, arrayScope[scope]);
		symbolTables[sIndex].noOfElems = 0;		
		symbolTables[sIndex].Elements = (record*)calloc(20, sizeof(record));
		
		symbolTables[sIndex].Parent = scopeBasedTableSearch(currentScope);
		
	}
	
	void init()
	{
		symbolTables = (STable*)calloc(100, sizeof(STable));
		arrayScope = (int*)calloc(10, sizeof(int));
		initNewTable(1);
		argsList = (char *)malloc(100);
		strcpy(argsList, "");
		tVar = (char*)calloc(5, sizeof(char));
		tVar = (char*)calloc(5, sizeof(char));
		strcpy(tVar, "T");
		
	}

	int searchRecordInScope(const char* type, const char *name, int index)
	{
		int i =0;
		for(i=0; i<symbolTables[index].noOfElems; i++)
		{
			if((strcmp(symbolTables[index].Elements[i].type, type)==0) && (strcmp(symbolTables[index].Elements[i].name, name)==0))
			{
				return i;
			}	
		}
		return -1;
	}
		
	void modifyRecordID(const char *type, const char *name, int lineNo, int scope)
	{
		int i =0;
		int index = scopeBasedTableSearch(scope);
		if(index==0)
		{
			for(i=0; i<symbolTables[index].noOfElems; i++)
			{
				
				if(strcmp(symbolTables[index].Elements[i].type, type)==0 && (strcmp(symbolTables[index].Elements[i].name, name)==0))
				{
					symbolTables[index].Elements[i].lastUseLine = lineNo;
					return;
				}	
			}
			printf("Identifier '%s' at line %d Not Declared\n", name, yylineno);
			exit(1);
		}
		
		for(i=0; i<symbolTables[index].noOfElems; i++)
		{
			if(strcmp(symbolTables[index].Elements[i].type, type)==0 && (strcmp(symbolTables[index].Elements[i].name, name)==0))
			{
				symbolTables[index].Elements[i].lastUseLine = lineNo;
				return;
			}	
		}
		return modifyRecordID(type, name, lineNo, symbolTables[symbolTables[index].Parent].scope);
	}
	
	void insertRecord(const char* type, const char *name, int lineNo, int scope)
	{ 
		int FScope = power(scope, arrayScope[scope]);
		int index = scopeBasedTableSearch(FScope);
		int recordIndex = searchRecordInScope(type, name, index);
		if(recordIndex==-1)
		{
			
			symbolTables[index].Elements[symbolTables[index].noOfElems].type = (char*)calloc(30, sizeof(char));
			symbolTables[index].Elements[symbolTables[index].noOfElems].name = (char*)calloc(20, sizeof(char));
		
			strcpy(symbolTables[index].Elements[symbolTables[index].noOfElems].type, type);	
			strcpy(symbolTables[index].Elements[symbolTables[index].noOfElems].name, name);
			symbolTables[index].Elements[symbolTables[index].noOfElems].decLineNo = lineNo;
			symbolTables[index].Elements[symbolTables[index].noOfElems].lastUseLine = lineNo;
			symbolTables[index].noOfElems++;

		}
		else
		{
			symbolTables[index].Elements[recordIndex].lastUseLine = lineNo;
		}
	}
	
	void checkList(const char *name, int lineNo, int scope)
	{
		int index = scopeBasedTableSearch(scope);
		int i;
		if(index==0)
		{
			
			for(i=0; i<symbolTables[index].noOfElems; i++)
			{
				
				if(strcmp(symbolTables[index].Elements[i].type, "ListTypeID")==0 && (strcmp(symbolTables[index].Elements[i].name, name)==0))
				{
					symbolTables[index].Elements[i].lastUseLine = lineNo;
					return;
				}	

				else if(strcmp(symbolTables[index].Elements[i].name, name)==0)
				{
					printf("Identifier '%s' at line %d Not Indexable\n", name, yylineno);
					exit(1);

				}

			}
			printf("Identifier '%s' at line %d Not Declared as an Indexable Type\n", name, yylineno);
			exit(1);
		}
		
		for(i=0; i<symbolTables[index].noOfElems; i++)
		{
			if(strcmp(symbolTables[index].Elements[i].type, "ListTypeID")==0 && (strcmp(symbolTables[index].Elements[i].name, name)==0))
			{
				symbolTables[index].Elements[i].lastUseLine = lineNo;
				return;
			}
			
			else if(strcmp(symbolTables[index].Elements[i].name, name)==0)
			{
				printf("Identifier '%s' at line %d Not Indexable\n", name, yylineno);
				exit(1);

			}
		}
		
		return checkList(name, lineNo, symbolTables[symbolTables[index].Parent].scope);

	}
	
	record* findRecord(const char *name, const char *type, int scope)
	{
		int i =0;
		int index = scopeBasedTableSearch(scope);
		if(index==0)
		{
			for(i=0; i<symbolTables[index].noOfElems; i++)
			{
				
				if(strcmp(symbolTables[index].Elements[i].type, type)==0 && (strcmp(symbolTables[index].Elements[i].name, name)==0))
				{
					return &(symbolTables[index].Elements[i]);
				}	
			}
			printf("Identifier '%s' at line %d Not Declared\n", name, yylineno);
			exit(1);
		}
		
		for(i=0; i<symbolTables[index].noOfElems; i++)
		{
			if(strcmp(symbolTables[index].Elements[i].type, type)==0 && (strcmp(symbolTables[index].Elements[i].name, name)==0))
			{
				return &(symbolTables[index].Elements[i]);
			}	
		}
		return findRecord(name, type, symbolTables[symbolTables[index].Parent].scope);
	}

	void printSTable()
	{
		int i = 0, j = 0;
		
		printf("----------------------------All Symbol Tables----------------------------");
		printf("\nScope\tName\tType\t\tDeclaration\tLast Used Line\n");
		for(i=0; i<=sIndex; i++)
		{
			for(j=0; j<symbolTables[i].noOfElems; j++)
			{
				printf("(%d, %d)\t%s\t%s\t%d\t\t%d\n", symbolTables[i].Parent, symbolTables[i].scope, symbolTables[i].Elements[j].name, symbolTables[i].Elements[j].type, symbolTables[i].Elements[j].decLineNo,  symbolTables[i].Elements[j].lastUseLine);
			}
		}
		
		printf("-------------------------------------------------------------------------\n");
	}
	
	void printAST(node *root)
	{
	  if(root == NULL)
	  {
	    return;
	  }
	  
	  if(root->noOps >= 0)
	  {
	    /*int i;
	    for(i = 0; i < tabCount; i++)
	    {
	      printf("  ");
	    }*/
	    
	    printf("%s\n", root->NType);
	    
	    //tabCount++;
	    for(int i=0; i < root->noOps; i++)
	    {
	      printAST(root->NextLevel[i]);
	    }
	    //printf("\n");
	    //tabCount--;
	  }
	  
	  if(root->noOps == -1)
	  {
	    int i = 0;
	    /*for(i = 0; i < tabCount; i++)
	    {
	      printf("  ");
	    }*/
	    
	    printf("%s ", root->id->name);
	  }	  
	}
	
	void freeAll()
	{
		int i = 0, j = 0;
		for(i=0; i<=sIndex; i++)
		{
			for(j=0; j<symbolTables[i].noOfElems; j++)
			{
				free(symbolTables[i].Elements[j].name);
				free(symbolTables[i].Elements[j].type);	
			}

			free(symbolTables[i].Elements);
		}

		free(symbolTables);
	}
	


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
typedef union YYSTYPE
#line 414 "grammar.y"
{char *text; int depth; struct ASTNode* node;}
/* Line 193 of yacc.c.  */
#line 601 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 626 "y.tab.c"

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
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   208

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNRULES -- Number of states.  */
#define YYNSTATES  136

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     8,    10,    12,    14,    16,    18,
      23,    26,    27,    32,    34,    36,    38,    40,    42,    44,
      46,    48,    50,    52,    56,    60,    64,    68,    72,    76,
      80,    84,    88,    92,    96,    98,   100,   104,   106,   108,
     111,   115,   118,   120,   122,   124,   128,   132,   136,   141,
     146,   148,   150,   152,   154,   156,   161,   167,   169,   175,
     179,   184,   186,   187,   193,   198,   201,   202,   206,   207,
     210,   211,   214,   215,   216,   225
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      47,     0,    -1,    -1,    48,    52,     3,    -1,     5,    -1,
      25,    -1,     8,    -1,    49,    -1,    51,    -1,     8,    40,
      49,    41,    -1,    11,    52,    -1,    -1,    65,    11,    53,
      52,    -1,    65,    -1,    60,    -1,    61,    -1,    59,    -1,
      63,    -1,    55,    -1,    56,    -1,    64,    -1,    62,    -1,
      50,    -1,    55,    35,    55,    -1,    55,    34,    55,    -1,
      55,    37,    55,    -1,    55,    36,    55,    -1,    38,    55,
      39,    -1,    57,    19,    57,    -1,    55,    16,    55,    -1,
      57,    20,    57,    -1,    55,    15,    55,    -1,    55,    18,
      55,    -1,    55,    17,    55,    -1,    57,    -1,    58,    -1,
      55,    14,    55,    -1,     6,    -1,     7,    -1,    21,    58,
      -1,    38,    56,    39,    -1,    31,     8,    -1,    33,    -1,
      32,    -1,     4,    -1,     8,    12,    55,    -1,     8,    12,
      56,    -1,     8,    12,    80,    -1,     8,    12,    40,    41,
      -1,     9,    38,    49,    39,    -1,    54,    -1,    66,    -1,
      78,    -1,    67,    -1,    70,    -1,    27,    56,    10,    71,
      -1,    27,    56,    10,    71,    68,    -1,    69,    -1,    28,
      56,    10,    71,    68,    -1,    30,    10,    71,    -1,    29,
      56,    10,    71,    -1,    54,    -1,    -1,    11,    22,    72,
      65,    73,    -1,    11,    23,    65,    73,    -1,    11,    74,
      -1,    -1,    24,    75,    65,    -1,    -1,     8,    77,    -1,
      -1,    43,     8,    -1,    -1,    -1,    42,     8,    79,    38,
      76,    39,    10,    71,    -1,     8,    38,    76,    39,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   430,   430,   430,   432,   433,   435,   436,   436,   439,
     441,   441,   441,   441,   443,   444,   445,   446,   447,   448,
     449,   450,   452,   453,   454,   455,   456,   457,   460,   461,
     462,   463,   464,   465,   466,   468,   469,   470,   471,   473,
     474,   476,   477,   478,   479,   481,   482,   483,   484,   486,
     488,   489,   490,   492,   493,   496,   497,   499,   500,   502,
     504,   506,   507,   507,   509,   510,   512,   512,   513,   515,
     516,   518,   518,   520,   520,   522
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_EndOfFile", "T_Return", "T_Number",
  "T_True", "T_False", "T_ID", "T_Print", "T_Cln", "T_NL", "T_EQL",
  "T_NEQ", "T_EQ", "T_GT", "T_LT", "T_EGT", "T_ELT", "T_Or", "T_And",
  "T_Not", "ID", "ND", "DD", "T_String", "Trip_Quote", "T_If", "T_Elif",
  "T_While", "T_Else", "T_Import", "T_Break", "T_Pass", "T_MN", "T_PL",
  "T_DV", "T_ML", "T_OP", "T_CP", "T_OB", "T_CB", "T_Def", "T_Comma",
  "T_Range", "T_List", "$accept", "StartDebugger", "@1", "constant",
  "term", "list_index", "StartParse", "@2", "basic_stmt", "arith_exp",
  "bool_exp", "bool_term", "bool_factor", "import_stmt", "pass_stmt",
  "break_stmt", "return_stmt", "assign_stmt", "print_stmt",
  "finalStatements", "cmpd_stmt", "if_stmt", "elif_stmts", "else_stmt",
  "while_stmt", "start_suite", "@3", "suite", "end_suite", "@4", "args",
  "args_list", "func_def", "@5", "func_call", 0
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
     295,   296,   297,   298,   299,   300
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    48,    47,    49,    49,    50,    50,    50,    51,
      52,    53,    52,    52,    54,    54,    54,    54,    54,    54,
      54,    54,    55,    55,    55,    55,    55,    55,    56,    56,
      56,    56,    56,    56,    56,    57,    57,    57,    57,    58,
      58,    59,    60,    61,    62,    63,    63,    63,    63,    64,
      65,    65,    65,    66,    66,    67,    67,    68,    68,    69,
      70,    71,    72,    71,    73,    73,    75,    74,    74,    76,
      76,    77,    77,    79,    78,    80
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     1,     1,     1,     1,     1,     4,
       2,     0,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     3,     1,     1,     2,
       3,     2,     1,     1,     1,     3,     3,     3,     4,     4,
       1,     1,     1,     1,     1,     4,     5,     1,     5,     3,
       4,     1,     0,     5,     4,     2,     0,     3,     0,     2,
       0,     2,     0,     0,     8,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,    44,     4,    37,    38,     6,     0,
       0,     0,     5,     0,     0,     0,    43,    42,     0,     0,
       7,    22,     8,     0,    50,    18,    19,    34,    35,    16,
      14,    15,    21,    17,    20,    13,    51,    53,    54,    52,
       0,     0,     0,    10,     0,    39,     6,     0,     0,     0,
      41,     0,     0,    73,     3,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    11,     6,     0,    45,
      46,    47,     0,     0,     0,     0,    27,    40,     0,     0,
      36,    31,    29,    33,    32,    24,    23,    26,    25,     0,
      28,    30,     0,    70,    48,     9,    49,     0,    61,    55,
      60,    70,     0,    12,    72,     0,    62,     0,     0,    56,
      57,     0,     0,    69,    75,     0,     0,     0,     0,    71,
       0,     0,    59,     0,    68,    63,     0,    74,     0,    66,
      65,    58,     0,     0,    64,    67
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    20,    21,    22,    23,    92,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,   109,   110,    38,    99,   115,   125,   130,   133,
     105,   113,    39,    78,    71
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -99
static const yytype_int16 yypact[] =
{
     -99,    16,    66,   -99,   -99,   -99,   -99,   -99,    -4,   -20,
      66,    -1,   -99,   153,   153,    20,   -99,   -99,   153,    30,
     -99,   -99,   -99,    29,   -99,    47,   -99,    21,   -99,   -99,
     -99,   -99,   -99,   -99,   -99,    58,   -99,   -99,   -99,   -99,
      95,     9,     9,   -99,   153,   -99,    36,    47,    70,    75,
     -99,   169,    51,   -99,   -99,     1,     1,     1,     1,     1,
       1,     1,     1,     1,   153,   153,   -99,   -25,    64,    47,
     -99,   -99,    65,    53,   144,   144,   -99,   -99,    69,     1,
     -12,   -12,   -12,   -12,   -12,    19,    19,   -99,   -99,   158,
     -99,   -99,    66,   107,   -99,   -99,   -99,    96,   -99,    -9,
     -99,   107,    88,   -99,    74,    80,   -99,   153,   111,   -99,
     -99,    89,   121,   -99,   -99,   105,   129,   144,   130,   -99,
     120,   144,   -99,   144,    44,   -99,    -9,   -99,   105,   -99,
     -99,   -99,   120,   105,   -99,   -99
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -99,   -99,   -99,    37,   -99,   -99,    -6,   -99,   -64,   -13,
     -11,    24,   131,   -99,   -99,   -99,   -99,   -99,   -99,   -98,
     -99,   -99,    15,   -99,   -99,   -63,   -99,    12,   -99,   -99,
      45,   -99,   -99,   -99,   -99
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      47,    47,    48,    49,    43,    51,     5,    52,    40,    46,
      98,    98,   100,    93,     5,    41,     3,   120,    42,   107,
      11,   108,    60,    61,    62,    63,    12,    69,    50,    70,
     132,    47,    54,    52,    12,   135,    41,    44,    53,    79,
      64,    65,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    89,    98,   122,    62,    63,    98,   126,    98,
     127,    55,    56,    57,    58,    59,   102,   128,   129,    66,
       4,     5,     6,     7,     8,     9,    41,    10,    72,    73,
      74,    60,    61,    62,    63,    75,   103,    11,    90,    91,
      77,    12,    96,    13,    47,    14,   116,    15,    16,    17,
       5,     6,     7,    67,    18,    94,    95,   101,    19,     4,
       5,     6,     7,     8,     9,   104,    11,   112,   106,   114,
      12,   117,    60,    61,    62,    63,    11,    76,   118,   119,
      12,   124,    13,    18,    14,    68,    15,    16,    17,   121,
     123,   131,    45,    18,   134,     0,   111,    19,     4,     5,
       6,     7,     8,     9,     0,    97,     0,     0,     5,     6,
       7,    46,     0,     0,     0,    11,     0,     0,     0,    12,
       0,     0,    55,     0,    11,    15,    16,    17,    12,     0,
       0,     0,    18,    55,    56,    57,    58,    59,     0,     0,
       0,    18,    60,    61,    62,    63,     0,     0,     0,     0,
       0,     0,     0,    60,    61,    62,    63,     0,    76
};

static const yytype_int16 yycheck[] =
{
      13,    14,    13,    14,    10,    18,     5,    18,    12,     8,
      74,    75,    75,    38,     5,    40,     0,   115,    38,    28,
      21,    30,    34,    35,    36,    37,    25,    40,     8,    40,
     128,    44,     3,    44,    25,   133,    40,    38,     8,    38,
      19,    20,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,   117,   117,    36,    37,   121,   121,   123,
     123,    14,    15,    16,    17,    18,    79,    23,    24,    11,
       4,     5,     6,     7,     8,     9,    40,    11,    41,    42,
      10,    34,    35,    36,    37,    10,    92,    21,    64,    65,
      39,    25,    39,    27,   107,    29,   107,    31,    32,    33,
       5,     6,     7,     8,    38,    41,    41,    38,    42,     4,
       5,     6,     7,     8,     9,     8,    21,    43,    22,    39,
      25,    10,    34,    35,    36,    37,    21,    39,    39,     8,
      25,    11,    27,    38,    29,    40,    31,    32,    33,    10,
      10,   126,    11,    38,   132,    -1,   101,    42,     4,     5,
       6,     7,     8,     9,    -1,    11,    -1,    -1,     5,     6,
       7,     8,    -1,    -1,    -1,    21,    -1,    -1,    -1,    25,
      -1,    -1,    14,    -1,    21,    31,    32,    33,    25,    -1,
      -1,    -1,    38,    14,    15,    16,    17,    18,    -1,    -1,
      -1,    38,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    -1,    39
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    47,    48,     0,     4,     5,     6,     7,     8,     9,
      11,    21,    25,    27,    29,    31,    32,    33,    38,    42,
      49,    50,    51,    52,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    70,    78,
      12,    40,    38,    52,    38,    58,     8,    55,    56,    56,
       8,    55,    56,     8,     3,    14,    15,    16,    17,    18,
      34,    35,    36,    37,    19,    20,    11,     8,    40,    55,
      56,    80,    49,    49,    10,    10,    39,    39,    79,    38,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      57,    57,    53,    38,    41,    41,    39,    11,    54,    71,
      71,    38,    55,    52,     8,    76,    22,    28,    30,    68,
      69,    76,    43,    77,    39,    72,    56,    10,    39,     8,
      65,    10,    71,    10,    11,    73,    71,    71,    23,    24,
      74,    68,    65,    75,    73,    65
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
		  Type, Value, Location); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
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
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

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
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



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

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

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
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

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
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
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
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 430 "grammar.y"
    {init();}
    break;

  case 3:
#line 430 "grammar.y"
    {printf("\nValid Python Syntax\n"); printSTable(); printAST((yyvsp[(2) - (3)].node)); freeAll(); exit(0);}
    break;

  case 4:
#line 432 "grammar.y"
    {insertRecord("Constant", (yyvsp[(1) - (1)].text), (yylsp[(1) - (1)]).first_line, currentScope); (yyval.node) = createID_Const("Constant", (yyvsp[(1) - (1)].text), currentScope);}
    break;

  case 5:
#line 433 "grammar.y"
    {insertRecord("Constant", (yyvsp[(1) - (1)].text), (yylsp[(1) - (1)]).first_line, currentScope); (yyval.node) = createID_Const("Constant", (yyvsp[(1) - (1)].text), currentScope);}
    break;

  case 6:
#line 435 "grammar.y"
    {modifyRecordID("Identifier", (yyvsp[(1) - (1)].text), (yylsp[(1) - (1)]).first_line, currentScope); (yyval.node) = createID_Const("Identifier", (yyvsp[(1) - (1)].text), currentScope);}
    break;

  case 9:
#line 439 "grammar.y"
    {checkList((yyvsp[(1) - (4)].text), (yylsp[(1) - (4)]).first_line, currentScope); (yyval.node) = createOp("ListIndex", 1, (yyvsp[(3) - (4)].node));}
    break;

  case 10:
#line 441 "grammar.y"
    {(yyval.node) = (yyvsp[(2) - (2)].node);}
    break;

  case 11:
#line 441 "grammar.y"
    {resetDepth();}
    break;

  case 12:
#line 441 "grammar.y"
    {(yyval.node) = createOp("NewScope", 2, (yyvsp[(1) - (4)].node), (yyvsp[(4) - (4)].node));}
    break;

  case 13:
#line 441 "grammar.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);}
    break;

  case 14:
#line 443 "grammar.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);}
    break;

  case 15:
#line 444 "grammar.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);}
    break;

  case 16:
#line 445 "grammar.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);}
    break;

  case 17:
#line 446 "grammar.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);}
    break;

  case 18:
#line 447 "grammar.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);}
    break;

  case 19:
#line 448 "grammar.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);}
    break;

  case 20:
#line 449 "grammar.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);}
    break;

  case 21:
#line 450 "grammar.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);}
    break;

  case 22:
#line 452 "grammar.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);}
    break;

  case 23:
#line 453 "grammar.y"
    {(yyval.node) = createOp("+", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 24:
#line 454 "grammar.y"
    {(yyval.node) = createOp("-", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 25:
#line 455 "grammar.y"
    {(yyval.node) = createOp("*", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 26:
#line 456 "grammar.y"
    {(yyval.node) = createOp("/", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 27:
#line 457 "grammar.y"
    {(yyval.node) = (yyvsp[(2) - (3)].node);}
    break;

  case 28:
#line 460 "grammar.y"
    {(yyval.node) = createOp("or", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 29:
#line 461 "grammar.y"
    {(yyval.node) = createOp("<", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 30:
#line 462 "grammar.y"
    {(yyval.node) = createOp("and", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 31:
#line 463 "grammar.y"
    {(yyval.node) = createOp(">", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 32:
#line 464 "grammar.y"
    {(yyval.node) = createOp("<=", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 33:
#line 465 "grammar.y"
    {(yyval.node) = createOp(">=", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 34:
#line 466 "grammar.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);}
    break;

  case 35:
#line 468 "grammar.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 36:
#line 469 "grammar.y"
    {(yyval.node) = createOp("==", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 37:
#line 470 "grammar.y"
    {insertRecord("Constant", "True", (yylsp[(1) - (1)]).first_line, currentScope); (yyval.node) = createID_Const("Constant", "True", currentScope);}
    break;

  case 38:
#line 471 "grammar.y"
    {insertRecord("Constant", "False", (yylsp[(1) - (1)]).first_line, currentScope); (yyval.node) = createID_Const("Constant", "False", currentScope);}
    break;

  case 39:
#line 473 "grammar.y"
    {(yyval.node) = createOp("!", 1, (yyvsp[(2) - (2)].node));}
    break;

  case 40:
#line 474 "grammar.y"
    {(yyval.node) = (yyvsp[(2) - (3)].node);}
    break;

  case 41:
#line 476 "grammar.y"
    {insertRecord("PackageName", (yyvsp[(2) - (2)].text), (yylsp[(2) - (2)]).first_line, currentScope); (yyval.node) = createOp("import", 1, createID_Const("PackageName", (yyvsp[(2) - (2)].text), currentScope));}
    break;

  case 42:
#line 477 "grammar.y"
    {(yyval.node) = createOp("pass", 0);}
    break;

  case 43:
#line 478 "grammar.y"
    {(yyval.node) = createOp("break", 0);}
    break;

  case 44:
#line 479 "grammar.y"
    {(yyval.node) = createOp("return", 0);}
    break;

  case 45:
#line 481 "grammar.y"
    {insertRecord("Identifier", (yyvsp[(1) - (3)].text), (yylsp[(1) - (3)]).first_line, currentScope); (yyval.node) = createOp("=", 2, createID_Const("Identifier", (yyvsp[(1) - (3)].text), currentScope), (yyvsp[(3) - (3)].node));}
    break;

  case 46:
#line 482 "grammar.y"
    {insertRecord("Identifier", (yyvsp[(1) - (3)].text), (yylsp[(1) - (3)]).first_line, currentScope); (yyval.node) = createOp("=", 2, createID_Const("Identifier", (yyvsp[(1) - (3)].text), currentScope), (yyvsp[(3) - (3)].node));}
    break;

  case 47:
#line 483 "grammar.y"
    {insertRecord("Identifier", (yyvsp[(1) - (3)].text), (yylsp[(1) - (3)]).first_line, currentScope); (yyval.node) = createOp("=", 2, createID_Const("Identifier", (yyvsp[(1) - (3)].text), currentScope), (yyvsp[(3) - (3)].node));}
    break;

  case 48:
#line 484 "grammar.y"
    {insertRecord("ListTypeID", (yyvsp[(1) - (4)].text), (yylsp[(1) - (4)]).first_line, currentScope); (yyval.node) = createID_Const("ListTypeID", (yyvsp[(1) - (4)].text), currentScope);}
    break;

  case 49:
#line 486 "grammar.y"
    {(yyval.node) = createOp("Print", 1, (yyvsp[(3) - (4)].node));}
    break;

  case 50:
#line 488 "grammar.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 51:
#line 489 "grammar.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 52:
#line 490 "grammar.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 53:
#line 492 "grammar.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 54:
#line 493 "grammar.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 55:
#line 496 "grammar.y"
    {(yyval.node) = createOp("If", 2, (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));}
    break;

  case 56:
#line 497 "grammar.y"
    {(yyval.node) = createOp("If", 3, (yyvsp[(2) - (5)].node), (yyvsp[(4) - (5)].node), (yyvsp[(5) - (5)].node));}
    break;

  case 57:
#line 499 "grammar.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 58:
#line 500 "grammar.y"
    {(yyval.node) = createOp("Elif", 3, (yyvsp[(2) - (5)].node), (yyvsp[(4) - (5)].node), (yyvsp[(5) - (5)].node));}
    break;

  case 59:
#line 502 "grammar.y"
    {(yyval.node) = createOp("Else", 1, (yyvsp[(3) - (3)].node));}
    break;

  case 60:
#line 504 "grammar.y"
    {(yyval.node) = createOp("While", 2, (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));}
    break;

  case 61:
#line 506 "grammar.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 62:
#line 507 "grammar.y"
    {initNewTable((yyvsp[(2) - (2)].depth)+1); updateCScope((yyvsp[(2) - (2)].depth)+1);}
    break;

  case 63:
#line 507 "grammar.y"
    {(yyval.node) = createOp("BeginBlock", 2, (yyvsp[(4) - (5)].node), (yyvsp[(5) - (5)].node));}
    break;

  case 64:
#line 509 "grammar.y"
    {(yyval.node) = createOp("Next", 2, (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node));}
    break;

  case 65:
#line 510 "grammar.y"
    {(yyval.node) = (yyvsp[(2) - (2)].node);}
    break;

  case 66:
#line 512 "grammar.y"
    {updateCScope((yyvsp[(1) - (1)].depth)+1);}
    break;

  case 67:
#line 512 "grammar.y"
    {(yyval.node) = createOp("EndBlock", 1, (yyvsp[(3) - (3)].node));}
    break;

  case 68:
#line 513 "grammar.y"
    {(yyval.node) = createOp("EndBlock", 0);}
    break;

  case 69:
#line 515 "grammar.y"
    {addToList((yyvsp[(1) - (2)].text)); (yyval.node) = createOp("Arguments", 1, argsList); clearArgsList();}
    break;

  case 70:
#line 516 "grammar.y"
    {(yyval.node) = createOp("Void", 0);}
    break;

  case 71:
#line 518 "grammar.y"
    {addToList((yyvsp[(1) - (2)].text));}
    break;

  case 73:
#line 520 "grammar.y"
    {insertRecord("Func_Name", (yyvsp[(2) - (2)].text), (yylsp[(2) - (2)]).first_line, currentScope);}
    break;

  case 74:
#line 520 "grammar.y"
    {(yyval.node) = createOp((yyvsp[(2) - (8)].text), 2, (yyvsp[(5) - (8)].node), (yyvsp[(8) - (8)].node));}
    break;

  case 75:
#line 522 "grammar.y"
    {(yyval.node) = createOp((yyvsp[(1) - (4)].text), 1, (yyvsp[(3) - (4)].node));}
    break;


/* Line 1267 of yacc.c.  */
#line 2339 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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

  yyerror_range[0] = yylloc;

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
		      yytoken, &yylval, &yylloc);
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

  yyerror_range[0] = yylsp[1-yylen];
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

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
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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


#line 524 "grammar.y"


int yyerror(char *msg)
{
	printf("\nSyntax Error at Line %d, Column : %d\n",  yylineno, yylloc.last_column);
	exit(0);
}

int main()
{
	yyparse();
	return 0;
}


