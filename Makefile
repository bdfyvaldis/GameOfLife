life: Main.o Life.o Menu.o
	mkdir -p bin
	g++ -Wall Main.o Life.o Menu.o -o bin/life
Main.o: Main.cpp
	g++ -c Main.cpp
Life.o: Life.cpp
	g++ -c Life.cpp
Menu.o: Menu.cpp
	g++ -c Menu.cpp
clear:
	rm life Main.o Life.o test
test: tests/test.cpp tests/main.cpp 
	g++ tests/main.cpp tests/test.cpp Life.cpp -o bin/test
run: life 
	./bin/life
runtests: test
	./bin/test