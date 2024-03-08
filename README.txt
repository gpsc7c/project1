Option 3
langscan.h contains the FSA table
scanner.h function FSADriver is the scanner, scanner.h function filter is the filter that goes over the scanner.
filter requires row and column be passed in as pointers to integers
scanner.h function testScan is the scan tester
An Excel spreadsheet version can be found in FSAChart.xlsx, 
but would need to be removed from the server to be checked.

Author: Gregory Shelton
Started (DD/MM/YYYY): 13/02/2024
CLASS:   Code Translation
PROFESSOR: Mark Hauschild
PROJECT: Program Translation Project 1 Scanner
PURPOSE: Create a scanner with lookahead designed to be used in a compiler
HELP:	 Command is -h, or putting in more (or less)  information than is necessary.

COMPILATION METHOD: Makefile
	 Compile with make, remove compiled files with make clean
	 invoke with "./scanner [filename]"
FILES:	 
	 scanner.c is the location of main, arg intake, and help function
	 scanner.h is the location of the scanner with lookahead, filter, and scanner testing function.
	  It also includes several error handlers and token creation/generation
	 ttoken.h holds the ttoken structure and the enumeration and strings for token IDs
	 langscan.h is the location of the FSA table and numerous setters for the FSADriver function 
	 FSAChart.xlsx is a spreadsheet format of the FSA table
	 .txt files
	 aside from readme, these are tests, but readme can also function as a test. 
	  One which should fail on line 19, character 15
	 test1.txt tests ID tokens
	 test2.txt tests bad ID token
	 test3.txt tests a bad non-ID token
	 test4.txt tests all symbol tokens
	 testkw.txt tests all keywords
	 multiline.txt tests over multiple lines
	 comment.txt tests comments
	 teof.txt was used for testing EOF bugs.

