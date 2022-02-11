/*
 * Simple lex/yacc example
 *
 */

/* recursive tree structure shared by parser and main program */
struct opchain {
    int number;
    int operator;
    struct opchain *next;
};


/* externals */
extern int yydebug;

/* routine decls */
void doline(struct opchain *pop);
int yyparse(void);
