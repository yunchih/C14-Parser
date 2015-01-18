CFLAGS=	-DDEBUG	-std=c99	-g
CC=gcc
parser:	parser.o	lineProcess.o	writeFile.o	fileOperation.o	table.o	debug.o

parser.o: parser.c
	$(CC)	$(CFLAGS)	-c	parser.c	-o	parser.o
lineProcess.o: lineProcess.c
	$(CC)	$(CFLAGS)	-c	lineProcess.c	-o	lineProcess.o
writeFile.o: writeFile.c
	$(CC)	$(CFLAGS)	-c	writeFile.c	-o	writeFile.o
fileOperation.o: fileOperation.c
	$(CC)	$(CFLAGS)	-c	fileOperation.c	-o	fileOperation.o
table.o: table.c
	$(CC)	$(CFLAGS)	-c	table.c	-o	table.o
debug.o: debug.c
	$(CC)	$(CFLAGS)	-c	debug.c	-o	debug.o

# test:	parser.o	lineProcess.o	writeFile.o	fileOperation.o	table.o	
clean:
	rm -f *.o

