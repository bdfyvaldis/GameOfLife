life: Main.o Life.o App.o
	mkdir -p bin
	g++ -Wall Main.o Life.o App.o -o bin/life
Main.o: Main.cpp
	g++ -c Main.cpp
Life.o: Life.cpp
	g++ -c Life.cpp
App.o: App.cpp
	g++ -c App.cpp
clear:
	rm life bin/Main.o bin/Life.o bin/test
test: tests/test.cpp tests/main.cpp 
	g++ tests/main.cpp tests/test.cpp Life.cpp -o bin/test
run: life 
	./bin/life
runtests: test
	./bin/test