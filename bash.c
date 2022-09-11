/*
 * Headstart for Ostermann's shell project
 *
 * Shawn Ostermann -- Sept 11, 2022
 */
 
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"
#include "bash.h"




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
    printf("Got a command\n");
}
