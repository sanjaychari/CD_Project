# CD_Project
# Introduction
The project showcases a mini compiler coded using lex and yacc; that compiles Python3 code. We have implemented if-elif-else constructs, while loops, and functions.

# Steps To Run
1. Run
$git clone https://github.com/sanjaychari/CD_Project $cd CD_Project
2. To view the symbol table, run $cd Symbol_table
$lex phase1_finals.l
$gcc lex.yy.c -ll
$./a.out > symbol_table.txt
10
The generated tokens can be found in tokens.txt, and the symbol table is in symbol_table.txt.
3. To view only the AST, run $cd ../AST
$lex grammar.l
$yacc -d grammar.y
$gcc lex.yy.c y.tab.c -ll $./a.out<TestInput1.txt > output.txt
4. To view AST with ICG, run $cd ../AST_With_ICG
$lex grammar.l
$yacc -d grammar.y
$gcc lex.yy.c y.tab.c -ll $./a.out<TestInput1.txt > output.txt
5. To view AST with ICG and code optimisation, run $cd ../Code_Opt
$lex grammar.l
$yacc -d grammar.y
$gcc lex.yy.c y.tab.c -ll $./a.out<input2.py > output.txt
6. To view assembly code,
 $cd ../Assembly $cat ICG.txt|python3 assembly.py>assembly.txt
