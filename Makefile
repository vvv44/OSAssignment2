#
# EE 4374 Assignment 2 Makefile
# Author: ???
#
all: files

files: vvargas_prog2.o vvargas_argtok.o vvargas_exec.o
	gcc vvargas_exec.o vvargas_prog2.o vvargas_argtok.o -o program

vvargas_argtok.o: vvargas_argtok.c
	gcc -c vvargas_argtok.c

vvargas_exec.o: vvargas_exec.c 
	gcc -c vvargas_exec.c 

vvargas_prog2.o: vvargas_prog2.c
	gcc -c vvargas_prog2.c
	
clean:
	rm *.o; rm program
