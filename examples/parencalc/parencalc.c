/*
 * Simple arithmetic program as a lex/yacc example
 *
 * Shawn Ostermann -- Wed Feb  7, 2022
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "parser.h"
#include "parencalc.h"

/* globals */


/* local routines */
static long long int evalexpr(struct exprtree *pass);
static void printexpr(struct exprtree *pass);



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


static void
printexpr(struct exprtree *pexpr)
{
    if (pexpr->left == NULL) {
        printf("%d", pexpr->number);
        return;
    }

    printf("(");
    printexpr(pexpr->left);
    switch(pexpr->operator) {
        case PLUS:    printf("+"); break;
        case MINUS:   printf("-"); break;
        case TIMES:   printf("*"); break;
        case DIVIDE:  printf("/"); break;
        case POWER:   printf("^"); break;
    }
    printexpr(pexpr->right);
    printf(")");
}


static void
printexpr_rpn(struct exprtree *pexpr)
{
    if (pexpr->left == NULL) {
        printf(" %d", pexpr->number);
        return;
    }

    printexpr_rpn(pexpr->left);
    printexpr_rpn(pexpr->right);
    switch(pexpr->operator) {
        case PLUS:    printf(" +"); break;
        case MINUS:   printf(" -"); break;
        case TIMES:   printf(" *"); break;
        case DIVIDE:  printf(" /"); break;
        case POWER:   printf(" ^"); break;
    }
}

static long long int power(int a, int b) 
    {return((long int)pow((double)a,(double)b));}

static long long int
evalexpr(struct exprtree *pexpr)
{
    if (pexpr->left == NULL)
	return(pexpr->number);

    switch(pexpr->operator) {
        case PLUS:    return(evalexpr(pexpr->left)+evalexpr(pexpr->right));
        case MINUS:   return(evalexpr(pexpr->left)-evalexpr(pexpr->right));
        case TIMES:   return(evalexpr(pexpr->left)*evalexpr(pexpr->right));
        case DIVIDE:  return(evalexpr(pexpr->left)/evalexpr(pexpr->right));
        case POWER:   return(power(evalexpr(pexpr->left),
                                   evalexpr(pexpr->right)));
        default:  printf("? "); exit(1);
    }
}


void
doline(struct exprtree *pexpr)
{
    printf("Read a line:\n");

    printf("  The question is:  ");
    printexpr(pexpr);
    printf("\n");

    printf("  In RPN form:     ");
    printexpr_rpn(pexpr);
    printf("\n");

    printf("  The answer is %lld\n", evalexpr(pexpr));
}
