all: prog

prog: main.cpp
	g++ -Wall main.cpp entities.cpp entities.h patch.cpp patch.h 
	player.cpp player.h PowerUps.cpp PowerUps.h world.cpp world.h -o prog
	
clean:
	rm -f prog

run:
	prog
	./prog
