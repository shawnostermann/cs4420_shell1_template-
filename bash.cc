/*
 * Headstart for Ostermann's shell project
 *
 * Shawn Ostermann -- Sept 11, 2022
 */
 
#include <string.h>
#include <iostream>

using namespace std;

// types and definitions live in "C land" and must be flagged
extern "C" {
#include "parser.tab.h"
#include "bash.h"
extern "C" void yyset_debug(int d);
}


int
main(
     int argc,
     char *argv[])
{
    yydebug = 1;  /* turn on ugly YACC debugging */
    yydebug = 0;  /* turn off ugly YACC debugging */

    /* parse the input file */
    yyparse();

    exit(0);
}



void
doline(
    struct command *pcmd)
{
    cout << "Got a command\n";
}
