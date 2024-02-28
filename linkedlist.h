#include <stdio.h>
#include <stdlib.h>
#include "ttoken.h"
#ifndef LINKEDLIST
#define LINKEDLIST
typedef struct Link{
	Ttoken* token;
	char* tokLabel;
	struct Link* next;
}Link;
struct Link* newLink(Ttoken* token){ // Allocate mem for new node
	struct Link* makeLink
		= (struct Link*)malloc(sizeof(struct Link));

	//allocate memory
	makeLink->token = token/*(struct Ttoken*)malloc(sizeof(token))*/;
	makeLink->tokLabel = malloc(sizeof(char)*15);
	makeLink->tokLabel = tokenNames[token->tokenID];
	//initialize children as NULL
	makeLink->next = NULL;
	//assign lettera
	return (makeLink);
}
struct Link* insert(Link* startLink, Ttoken *token){
	//creates a new node by loading up a char array and then putting it in
	if (startLink == NULL){
		return newLink(token);
	}
	//handler node to be set based on whether letter val is higher or lower
	struct Link** nextLink = &startLink->next;
	*nextLink = insert(*nextLink, token);
	return startLink;
}
void outputList(Link root, FILE* outFile){
	
}
void deleteList(Link root){}
//////////////////////////////////////////////
#endif
