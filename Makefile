CFLAGS = -std=c++17
life: obj/Main.o obj/Life.o obj/App.o
	mkdir -p bin
	g++ $(CFLAGS) obj/Main.o obj/Life.o obj/App.o -o bin/life 
obj/Main.o: src/Main.cpp 
	mkdir -p obj
	g++ -$(CFLAGS) c src/Main.cpp -o obj/Main.o
obj/Life.o: src/Life.cpp
	mkdir -p obj
	g++ -$(CFLAGS) c src/Life.cpp -o obj/Life.o
obj/App.o: src/App.cpp
	mkdir -p obj
	g++ -$(CFLAGS) c src/App.cpp -o obj/App.o
clear:
	rm obj/Main.o obj/Life.o obj/App.o bin/life bin/test obj/test.o obj/testlib.a obj/main.o
obj/testlib.a: obj/Life.o obj/test.o 
	ar rcs obj/testlib.a obj/Life.o obj/test.o  
obj/test.o:
	g++ -$(CFLAGS) c -I third-party/ctest -I src tests/test.cpp -o obj/test.o
obj/main.o:
	g++ -$(CFLAGS) c -I third-party/ctest -I src -I test tests/main.cpp -o obj/main.o
test: obj/main.o obj/Life.o obj/test.o 
	g++ $(CFLAGS) obj/main.o obj/test.o obj/Life.o  -o bin/test
	
run: life 
	./bin/life
runtests: test
	./bin/test

