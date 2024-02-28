#ifndef TTOKEN_H
#define TTOKEN_H
enum tokenTypes{IDTK, INTTK, ASSIGNTK, GREATTK, LESSTK, ISEQUALTK, NOTEQUALTK, COLONTK, COLONEQLTK, PLUSTK, MINUSTK, MULTIPLYTK, DIVIDETK, EXPONTK, DOTTK, OPENPARENTK, CLOSEPARENTK, COMMATK, OPENCURLTK, CLOSECURLTK, SEMICOLONTK, OPENSQUARETK, CLOSESQUARETK, ORTK, ANDTK, STARTTK, STOPTK, WHILETK, REPEATTK, UNTILTK, LABELTK, RETURNTK, CINTK, COUTTK, TAPETK, JUMPTK, IFTK, THENTK, PICKTK, CREATETK, SETTK, FUNCTK, EOFTK};
char* tokenNames[43] = {"IDTK", "INTTK", "ASSIGNTK", "GREATTK", "LESSTK", "ISEQUALTK", "NOTEQUALTK", "COLONTK", "COLONEQLTK", "PLUS", "MINUSTK", "MULTIPLYTK", "DIVIDETK", "EXPONTK", "DOTTK", "OPENPARENTK", "CLOSEPARENTK", "COMMATK", "OPENCURLTK", "CLOSECURLTK", "SEMICOLONTK", "OPENSQUARETK", "CLOSESQUARETK", "ORTK", "ANDTK", "STARTTK", "STOPTK", "WHILETK", "REPEATTK", "UNTILTK", "LABELTK", "RETURNTK", "CINTK", "COUTTK", "TAPETK", "JUMPTK", "IFTK", "THENTK", "PICKTK", "CREATETK", "SETTK", "FUNCTK", "EOFTK"};

typedef struct {
	int tokenID;
	char* tokenInstance;//This is the actual token, not the Token ID, yes?
	int row;
	int column;	
}Ttoken;
#endif