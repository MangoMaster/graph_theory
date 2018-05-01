objects = weight_incidence.o weight_edge.o weight_forward.o \
		  weight_adjacency.o edge_incidence.o forward_edge.o forward_adjacency.o \
		  graph_trans.o ~graph_trans.o \
		  main.o load.o output.o

all: graph.exe

graph.exe: $(objects) func.h
	g++ $(objects) -o $@
%.o: %.cpp func.h
	g++ $< -c -std=c++11 -o $@

.PHONY: clean
clean:
	del *.o *.exe