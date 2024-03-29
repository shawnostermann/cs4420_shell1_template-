%{
#include <stdio.h>
#include <stdarg.h>
#include "bash.h"

/* some internal files generated by bison */
int yylex();
void yyerror(const char *s,...);
void yywarn(const char *s,...);

// data structure to hold a linked list of arguments for a command
struct args {
    char *arg;
    struct args *next;
};

// data structure to hold a linked list of redirections for a command
struct redirs {
    int redir_token;
	char *filename;
    struct redirs *next;
};


/* include debugging code, in case we want it */
#define YYDEBUG 1

int lines = 0;
static int synerrors = 0;


%}


%union	{ /* the types that we use in the tokens */
    char *string;
    struct command *pcmd;
    struct args *pargs;
    struct redirs *predir;
    int number;
}



%token EOLN PIPE 
%token INFILE					// standard input redirection
%token OUTFILE OUTFILE_APPEND	// standard output redirection
%token ERRFILE ERRFILE_APPEND	// standard error redirection
%token <string> WORD

%type <pcmd> line cmd	// main datatype from bash.h
%type <pargs> optargs arg
%type <predir> optredirs redir
  

%% 	/* beginning of the parsing rules	*/
input	: lines
	|
  	;

lines	: oneline
	| oneline lines
	;

oneline : line eoln
		{ doline($1); }
 	| eoln	/* blank line, do nothing */
	| error eoln
	/* if we got an error on the line, don't call the C program */
	;

eoln	: EOLN
		{ ++lines; }
	;


// you need to finish the rest of this...
line	: cmd
		{
			// cmd is a datastructure, pass it upstream
			$$ = $1;
		}
  	| cmd PIPE line
		{
			// cmd and line are both datastructures, hook them together in a linked list
			$$ = NULL;   // complete this!
		}
  	;

// FINISH THIS
cmd	: WORD optargs optredirs
		{ 
			// make and fill node of type "struct command "
			// grab the linked list for optargs and install it in the structure
			// grab the linked list for optredir and install it in the structure		
			printf("I found a command and it is '%s'\n", $1);
			$$ = NULL;
		}
	;

// FINISH THIS
// these 2 rules are for "optional arguments".  They should allow one or more "arg"s
// and assemble them into a linked list of type "struct args" and return it upstead
optargs : arg optargs
			{ $$ = NULL; 
			}
		|	
			{ $$ = NULL; // no more args 
			}
		;
arg		: WORD
		{
			// make a node for type "struct args" and pass it upsteam
		}
		;


// FINISH THIS
// these 2 rules are for "optional redirection".  They should  allow one or more sets of 
// redirection commands from the rule "redir"
// and assemble them into a linked list of type "struct redir" and return it upstead
optredirs : redir optredirs
			{ $$ = NULL;
			}
		|
			{ $$ = NULL; // no more redirection 
			}
		;
// just as a possible example		
redir	: INFILE WORD
		{ $$ = NULL;  // build a data structure of type struct redirs for this and pass it upstream
		}
		;

%%

void
yyerror(const char *error_string, ...)
{
    va_list ap;
    int line_nmb(void);

    FILE *f = stdout;

    va_start(ap,error_string);

    ++synerrors;

    fprintf(f,"Error on line %d: ", lines);
    vfprintf(f,error_string,ap);
    fprintf(f,"\n");
    va_end(ap);
}
