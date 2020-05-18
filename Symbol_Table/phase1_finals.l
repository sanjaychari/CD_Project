%option yylineno
/*Definition Section*/
%{
#include<stdio.h>
#include<string.h>
#include "symtable.c"
//#include "y.tab.h"
int lineno=1;
int indent=0;
int iscomment=0;
char functions[100][30];
int top_func=-1;
int search_functions(char* name)
{
	for(int i=0;i<=top_func;i++)
	{
		if(strcmp(name,functions[i])==0)
			return i;
	}
	return -1;
}
int previndent=0;
%}


/*Rule Section*/

%%
#(.*) {if(iscomment==0){}};					
"\'\'\'" {if(iscomment==0){iscomment=1;} else{iscomment=0;}};
"\"\"\"" {if(iscomment==0){iscomment=1;} else{iscomment=0;}};	
"print" {if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Keyword");}};
"in" {if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Keyword");}};
"range" {if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Keyword");}};
"xrange" {if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Keyword");}};
"list"|"set"|"dict" {if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Keyword");}};
"and"|"break"|"class"|"del"|"elif" {if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Keyword");}};
"else"|"except"|"exec"|"finally"|"for"|"from"|"global" {if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Keyword");}};
"if"|"import"|"is"|"lambda"|"not"|"or" {if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Keyword");}};
"return"|"try"|"while"|"with"|"yield" {if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Keyword");}};
"def" {if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Keyword");isfunc=1;}};
[0-9]+                  {if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Literal");strcpy(symt.table[find_index(currid,isparam,isfunc)].id_value,yytext);}};
[_a-zA-Z][_a-zA-Z0-9]*  {if(iscomment==0){if(find_index(yytext,isparam,isfunc)==-1 && search_functions(yytext)==-1){top++;strcpy(symt.table[top].name,yytext);if(isfunc==1 && isparam==0){strcpy(symt.table[top].class,"Function");strcpy(functions[++top_func],yytext);} if(isparam==1){strcpy(symt.table[top].class,"Parameter");} 
						 if(isfunc==0&&isparam==0){strcpy(symt.table[top].class,"Variable");} symt.table[top].scope=indent;symt.table[top].declared=lineno;symt.table[top].latest_occurence=lineno;} else if(search_functions(yytext)!=-1 && find_index(yytext,isparam,isfunc)==-1){symt.table[find_index(yytext,isparam,1)].latest_occurence=lineno;} else{symt.table[find_index(yytext,isparam,isfunc)].latest_occurence=lineno;} fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Identifier");strcpy(currid,yytext);}};
"\t"                   {if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Tab");indent++;}};
"\n"					{indent=0;previndent=indent;lineno++;};
" "						{if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Whitespace");}};
":"						{if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Colon");if(isfunc==1){isfunc=0;isparam=0;}}};
"="                     {if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Equals");}};
"+"                     {if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Plus");}};
"-"                      {if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Minus");}};
"*"                      {if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Multiply");}};
"/"                     {if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Divide");}};
"("|"["|"{"                      {if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"LBracket");if(isfunc==1){isparam=1;}}};
")"|"]"|"}"                      {if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"RBracket");if(isfunc==1){isparam=0;}}};
"<"|">"|"!"				{if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Comparison");}};
";"                      {if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Semicolon");}};
","						{if(iscomment==0){fprintf(yyout,"%-20s\t%20-d\t%20-s\n",yytext,lineno,"Comma");}};
\"([^\"\n])*\"          {if(iscomment==0){fprintf(yyout,yytext);}};
\'([^\'\n])*\'          {if(iscomment==0){fprintf(yyout,yytext);}}; 
.						{printf("\nInvalid Token : %s",yytext);exit(1);}; 
%%

/*call the yywrap function*/
int yywrap()
{
return 1;
}



/*Auxiliary function*/
/*Driver function*/

int main()
{
yyin=fopen("TestInput1.txt","r");
yyout=fopen("tokens.txt","w");
fprintf(yyout,"%-20s\t%20-s\t%20-s\n","Token","Line Number","Type");
/*call the yylex function.*/
yylex();
print_table();
//for(int i=0;i<=top_func;i++)
//	printf("%s\n",functions[i]);
return 0;
}