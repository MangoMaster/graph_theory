objects = main.o solve.o print.o \
		  load_forward_table.o \
		  dijkstra.o ~dijkstra.o 
all: dijkstra.exe

dijkstra.exe: $(objects) dijkstra.h
	g++ $(objects) -o $@

%.o: %.c dijkstra.h
	g++ $< -c -std=c++11 -o $@

.PHONY: clean
clean:
	del *.o *.exe