all:
	clang++ -o ExGame -std=c++11 -Wall main.cpp -lalut -lopenal

clean:
	$(RM) ExGame
