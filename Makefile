#
# Sample lex/yacc Makefile
# Shawn Ostermann - Mon Sep 24, 2001
#
CFLAGS = -g -Wall -Werror -O3
CC = gcc

PROGRAM = bash
CFILES = bash.c
HFILE = bash.h


##################################################
#
# You shouldn't need to change anything else
#
##################################################


# compute the OFILES
OFILES = ${CFILES:.c=.o}

# all of the .o files that the program needs
OBJECTS = parser.tab.o lex.yy.o ${OFILES}


# How to make the whole program
${PROGRAM} : ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o ${PROGRAM} 


# 
# Turn the parser.y file into parser.tab.c using "bison"
# 
# Also, bison generates a header file called "parser.tab.h" which lex needs
# It's almost always the same, so we'll have lex use a different
# file and just update it when parser.tab.h changes (to save compiles)
#
parser.tab.c : parser.y ${HFILES}
	bison -dvt ${YFLAGS} parser.y
parser.tab.o: parser.tab.c
	${CC} ${CFLAGS} -c parser.tab.c
parser.tab.h: parser.tab.c
parser.h: parser.tab.h
	cmp -s perser.tab.h parser.h || cp parser.tab.h parser.h

# 
#  Turn the scanner.l file into lex.yy.c using "lex"
# 
lex.yy.c : scanner.l parser.h ${HFILE}
	flex ${LFLAGS} scanner.l
lex.yy.o: lex.yy.c
	${CC} ${CFLAGS} -Wno-unused-function -g -c lex.yy.c

#
# File dependencies
#
${OFILES}: ${HFILE} parser.h

test: bash
	-chmod a+rx ./test.*
	-./test.1
	-./test.2
	-./test.3
	-./test.4
	-./test.5
	-./test.6
	-./test.7
	-./test.8
	

clean:
	/bin/rm -f *.o lex.yy.c parser.tab.c ${PROGRAM} parser.h parser.output *.tab.c *.tab.h core test.*.myoutput test.*.correct test.*.input
