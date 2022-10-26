life: Main.o Life.o App.o
	mkdir -p bin
	g++ -Wall Main.o Life.o App.o -o bin/life -std=c++17
Main.o: Main.cpp
	g++ -c Main.cpp -std=c++17
Life.o: Life.cpp
	g++ -c Life.cpp -std=c++17
App.o: App.cpp
	g++ -c App.cpp -std=c++17
clear:
	rm life bin/Main.o bin/Life.o bin/test
test: tests/test.cpp tests/main.cpp 
	g++ tests/main.cpp tests/test.cpp Life.cpp -o bin/test -std=c++17
run: life 
	./bin/life
runtests: test
	./bin/test