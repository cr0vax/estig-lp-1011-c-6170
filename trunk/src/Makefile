
## Created by Anjuta

CC = gcc
CFLAGS = -g -Wall
OBJECTS = rebides.o\
rebides_wrap.o\
functions.o

INCFLAGS = -I/usr/include/python2.6

LDFLAGS = 
LIBS = -lsqlite3

all: _rebides.so

rebides_wrap.c: rebides.i
	swig -python rebides.i
	
rebides_wrap.o: rebides_wrap.c
	$(CC) -c -o rebides_wrap.o rebides_wrap.c $(INCFLAGS)

functions.o: functions.c
	$(CC) -c -o functions.o functions.c $(INCFLAGS)

rebides.o: rebides.c
	$(CC) -c -o rebides.o rebides.c $(INCFLAGS)

_rebides.so: $(OBJECTS)
	$(CC) -o _rebides.so $(OBJECTS) $(LDFLAGS) $(LIBS) -shared

.SUFFIXES:
.SUFFIXES:	.c .cc .C .cpp .o

.c.o :
	$(CC) -o $@ -c $(CFLAGS) $< $(INCFLAGS)

count:
	wc *.c *.cc *.C *.cpp *.h *.hpp

clean:
	rm -f *.o

.PHONY: all
.PHONY: count
.PHONY: clean