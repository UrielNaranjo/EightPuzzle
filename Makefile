VPATH = src
C++FLAGS = -g -ansi -pedantic -Wall -Werror -std=c++11
objects = $(addprefix obj/, main.o problem.o)

bin/EightPuzzle: $(objects) | bin
	g++ -o $@ $(objects)

obj/%.o: %.cpp 
	g++ $(C++FLAGS) -c -o $@ $<

obj/main.o: problem.h

$(objects): | obj

bin: 
	mkdir bin

obj:
	mkdir obj

clean:
	rm -rf obj bin
