#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>
#include "ttoken.h"
#include "langscan.h"
#define MAX_LENGTH 8
#define ERROROUT -1
#ifndef SCANL_H
#define SCANL_H
void printErr(int err, int row, int column){
	int errNo = 0 - err;
	fprintf(stderr,"ERROR: scanner.h: FSADriver: %s on row %d at character %d.\n", errorTexts[errNo], row, column);
}
Ttoken tokenSetter(int tkID, char* tkStr, int tkRow, int tkCol){
	Ttoken token;
	token.tokenID = tkID;
	int i;
	for(i = 0; i < strlen(tkStr); i++){
		token.tokenInstance[i] = tkStr[i];
	}
	for(; i < MAX_LENGTH + 1; i++){
		token.tokenInstance[i] = '\0';
	}
	token.row = tkRow;
	token.column = tkCol;
	return token;
}
Ttoken FSADriver(FILE* fName, char* nextChar, int row, int* col){//Arg exists for making col int a ptr
	int column = *col;  //saves the position of the first character in line
	state_t state = s1; //0 = state1 here
	state_t nextState;  //lookahead
	char tokString[9] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0'};
//string not malloc'd because it was behaving poorly when being passed back

	//while token incomplete
	while(state != FINAL){
		//consult next row of the table in langscan.h based on state
		nextState = FSAStates[state][selector(nextChar[0])];
		//if error state achieved
		if(nextState < s1){
			printErr(nextState, row, *col);
			exit(-1);
		}
		//in case of comments, skip to the end of the line
		if(nextState == s30){	
			return(tokenSetter(-1, "n/a", row, column));
		}
		//ensure length of token isn't overrun
		if(strlen(tokString) > 7){
			nextState = FINAL;
		}
		//when token is complete
		if(nextState == FINAL){
			//if ID, check for keywords
			if(state == s2){
				return(tokenSetter(kwFinder(tokString),tokString,row,column));
			}
			//else find what other token it is
			else{
				return(tokenSetter(tokFinder(state), tokString, row, column));
			}
		}
		//if token isn;t complete
		else{
			//progress state, add to string, check next character
			state = nextState;
			strcat(tokString,nextChar);
			nextChar[0] = fgetc(fName);
			//ensure line doesn't go out of bounds
			if(*col == INT_MAX){
				fprintf(stderr, "ERROR: scanner.h: FSADriver: Line too long (character count)");
				exit(-1);
			}
			//increment column
			*col = *col + 1;
		}
	}
	//errorstate
	return tokenSetter(-2, "n/a", -1, -1);	
}
//row and column should start at 0
Ttoken filter(FILE* fName, char* c, int* row, int* col){
	Ttoken* token = malloc(sizeof(Ttoken));
	token->tokenID = -3;
	if(*row == 1 && *col == 0){
		c[0] = fgetc(fName);
		*col = *col + 1;
	}
	while (c[0] != EOF) {
		if(!isspace(c[0])){
			*token = FSADriver(fName, c, *row, col);
		}
		if(c[0] == '\n'){
			if(*row == INT_MAX){
				fprintf(stderr, "ERROR: scanner.h: Filter: File too long (row count)");
				exit(-1);
			}
			*row = *row + 1;
			*col = 1;
		}
		if(isspace(c[0])){
			c[0] = fgetc(fName);
		}
		//skip to end of line if a comment
		if(token->tokenID == -1){
			while(c[0] != '\n' && c[0] != EOF){
				c[0] = fgetc(fName);
			}
		}
		//increment row if end of line reached
		if(token->tokenID >= 0){
			return tokenSetter(token->tokenID, token->tokenInstance, token->row, token->column);
		}
		else{
			return tokenSetter(-2, "n/a", -1, -1);	
		}		
	}
	if (c[0] == EOF){
		*token = FSADriver(fName, c, *row, col);	
		return tokenSetter(token->tokenID, token->tokenInstance, token->row, token->column);
	}
	return tokenSetter(-2, "n/a", -1, -1);	
}
void testScanner(FILE* fName){
	int *col = malloc(sizeof(int));
	int *row = malloc(sizeof(int));
	Ttoken *token = malloc(sizeof(Ttoken));
	*col = 0;
	*row = 1;
	char c[2] = {'\0','\0'};				//iterator
	while(token->tokenID != EOFTK){
		*token = filter(fName, c, row, col);
		if(token->tokenID >= 0 ){
			fprintf(stdout, "%s,   %s,   row %d,  character %d.\n",tokenNames[token->tokenID], token->tokenInstance, token->row,token->column);
		}
	}
}
#endif
