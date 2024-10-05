all:
	gcc -c main.c
	g++ -c test.cpp
	g++ main.o test.o -o test -lgtest
	del main.o
	del test.o