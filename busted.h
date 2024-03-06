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
const char* keys[] = {"start", "stop", "while", "repeat", "until", "label", "return", "cin", "cout", "tape", "jump", "if", "then", "pick", "create", "set", "func"};
/*char filter(FILE* fName){return '\0';}
char lookAhead(FILE* fName, char nextChar){
	nextChar = filter(fName);
	return nextChar;
}*/
void printErr(int err, int row, int column){
	int errNo = 0 - err;
	fprintf(stderr,"ERROR: scanner.h: FSADriver: %s on row %d at character %d.\n", errorTexts[errNo], row, column);
}
Ttoken tokenSetter(int tkID, char* tkStr, int tkRow, int tkCol){
	Ttoken token;
	//int i;
	token.tokenID = tkID;
	/*for(i = 0; i < MAX_LENGTH && i < strlen(tkStr); i++){
		token.tokenInstance[i] = tkStr[i];
	}
	for(; i <= MAX_LENGTH; i++){
		token.tokenInstance[i] = '\0';
	}*/
	token.tokenInstance = tkStr;
	token.row = tkRow;
	token.column = tkCol;
	return token;
}
Ttoken FSADriver(FILE* fName, char* nextChar, int row, int* col){//Arg exists for making col int a ptr
	int column = *col;
	state_t state = s1; //0 = state1 here
	state_t nextState;
	char tokString[9] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0'}/*= malloc(sizeof(char)*(MAX_LENGTH+1))*/;
	//*tokString = '\0';
	while(state != FINAL){
		nextState = FSAStates[state][selector(nextChar[0])];
		if(nextState < s1){
			printErr(nextState, row, *col);
			exit(-1);
		}
		if(nextState == s30){	
			return(tokenSetter(-1, NULL, row, column));
		}
		if(strlen(tokString) > 7){
			nextState = FINAL;
		}
		if(nextState == FINAL){
			if(state == s2){
				return(tokenSetter(kwFinder(tokString),tokString,row,column));
			}
			else{
				return(tokenSetter(tokFinder(state), tokString, row, column));
			}
		}
		else{
			state = nextState;
			strcat(tokString,nextChar);
			nextChar[0] = fgetc(fName);
			if(*col == INT_MAX){
				fprintf(stderr, "ERROR: scanner.h: FSADriver: Line too long (character count)");
				exit(-1);
			}
			*col = *col + 1;
		}
	}
	return tokenSetter(-2, NULL, -1, -1);	
}
//row and column should start at 0
Ttoken *filter(FILE* fName, char* c, int* row, int* col){
	Ttoken* token = malloc(sizeof(Ttoken));
	token->tokenInstance= malloc(sizeof(char)*MAX_LENGTH+1);
	token->tokenID = -3;
	if(*row == 1 && *col == 0){
		c[0] = fgetc(fName);
		*col = *col + 1;
	}
	while (c[0] != EOF) {
		if(isspace(c[0])){
			while(c[0] != EOF && c[0] != '\n'){
				c[0] = fgetc(fName);
			}
		}
		if(!isspace(c[0])){
			*token = FSADriver(fName, c, *row, col);
		}
		//skip to end of line if a comment
		if(token->tokenID == -1){
			while(c[0] != '\n' && c[0] != EOF){
				c[0] = fgetc(fName);
			}
		}
		//increment row if end of line reached
		if(c[0] == '\n'){
			if(*row == INT_MAX){
				fprintf(stderr, "ERROR: scanner.h: Filter: File too long (row count)");
				exit(-1);
			}
			*row = *row + 1;
			*col = 0;
		}
		if(token->tokenID >= 0){
			return token;
		}
		else{
			return NULL;
		}
	}
	return NULL;
}
void testScanner(FILE* fName){
	int *col = malloc(sizeof(int));
	int *row = malloc(sizeof(int));
	Ttoken *token;
	*col = 0;
	*row = 1;
	char c[2] = {'\0','\0'};				//iterator
	while((token = filter(fName, c, row, col))&& token->tokenID != EOFTK){
		if(token != NULL){
			fprintf(stdout,"\n%s,   %s,   row %d,  character %d.",tokenNames[token->tokenID],token->tokenInstance,token->row,token->column);
		}
	}
	1+2;
}

#endif
