CC       = gcc
CPPFLAGS =
CFLAGS   = -Wall -Wextra -std=c11 -O2
LDFLAGS  = -lm

.PHONY: all clean

all: similar_lines

similar_lines: src/similar_lines.o src/safealloc.o src/vector.o src/lines.o src/groups.o src/parsing.o src/solve.o src/sort.o
		gcc -o $@ $^ $(LDFLAGS)		
similar_lines.o: src/similar_lines.c src/groups.h src/lines.h src/solve.h src/sort.h src/vector.h    
solve.o: src/solve.c src/groups.h src/lines.h src/safealloc.h src/solve.h src/sort.h src/vector.h
sort.o: src/sort.c src/lines.h src/sort.h src/vector.h
groups.o: src/groups.c src/groups.h src/safealloc.h src/vector.h 
lines.o: src/lines.c src/lines.h src/parsing.h src/safealloc.h src/vector.h
parsing.o: src/parsing.c src/lines.h src/parsing.h src/vector.h
vector.o: src/vector.c src/safealloc.h src/vector.h
safealloc.o: src/safealloc.c src/safealloc.h
clean:
		rm -f src/*.o similar_lines
