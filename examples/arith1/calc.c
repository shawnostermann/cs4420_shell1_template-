/*
 * Simple arithmetic program as a lex/yacc example
 *
 * Shawn Ostermann -- Wed Feb  7, 2022
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "calc.h"

/* globals */


/* local routines */
static long int evalexpr(struct opchain *pop);

int
main(
     int argc,
     char *argv[])
{
    if ((argc == 2) && (strcmp(argv[1],"-d") == 0))
	    yydebug = 1;  /* turn on ugly YACC debugging */
    else
	    yydebug = 0;  /* turn off ugly YACC debugging */

    /* parse the input file */
    yyparse();

    exit(0);
}

static long int
evalexpr(
    struct opchain *pop)
{
    long int sum = 0;
    if (pop) {
        sum = pop->number;
        printf("%d", pop->number);
    }
    while (pop) {
        if (pop->next != NULL) {
            long int nextterm = (pop->next)->number;
            switch(pop->operator) {
                case PLUS:    printf(" + "); sum += nextterm; break;
                case MINUS:   printf(" - "); sum -= nextterm; break;
                case TIMES:   printf(" * "); sum *= nextterm; break;
                case DIVIDE:  printf(" / "); sum /= nextterm; break;
                default:  printf(" ? ");
                }
            printf("%d", (int) nextterm);
        }
        pop=pop->next;
    }
    printf("\n");
    return(sum);
}


void
doline(
    struct opchain *pop)
{
    printf("Read a line:\n");

    printf("  Question: ");
    long int sum = evalexpr(pop);
    printf("  answer: %ld\n\n", sum);
}
