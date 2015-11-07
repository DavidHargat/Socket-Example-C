
.PHONY: all

HEADERS = socklib.h
OBJECTS = main.o

all: main

# Make .o files from .c files, and .h files
# gcc = compiler
# -c  = don't run linker
# $<  = the first prereq
# (we exclude headers because they're
# included in the .c files themselves)
# -o  = compile to
# $@  = the target (in this case .o files)

%.o: %.c $(HEADERS)
	gcc -c $< -o $@

# create 'main' from every .o file
main: $(OBJECTS)
	gcc $^ -o main


