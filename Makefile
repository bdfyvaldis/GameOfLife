life: Main.o Life.o
	g++ Main.o Life.o -o life
Main.o:
	g++ -c Main.cpp
Life.o:
	g++ -c Life.cpp
clear:
	rm life Main.o Life.o tests/test
test:
	g++ tests/main.cpp tests/test.cpp -o test