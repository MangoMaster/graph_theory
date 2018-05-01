MYSOURCES=$(wildcard *.cpp)
MYOBJECTS=$(MYSOURCES:%.cpp=%.o)
OTHERSOURCES=$(wildcard *.cxx) #TODO:delete or modify
OTHEROBJECTS=$(OTHEROBJECTS:%.cxx=%.o) #TODO:delete or modify
HEADERS=$(wildcard *.h)
LIB=huffman.a #TODO:modify
TARGET=huffman.exe #TODO:modify

all: $(TARGET)

$(TARGET): $(MYOBJECTS) $(HEADERS)
	g++ $(MYOBJECTS) -o $(TARGET)

$(LIB): $(MYOBJECTS) $(HEADERS)
	ar -rv $(LIB) $(MYOBJECTS)
	ranlib $(LIB)

%.o: %.cpp $(HEADERS)
	g++ $< -c -std=c++11 -o $@

.PHONY: lib
lib: $(LIB)

.PHONY: clean
clean: 
	del *.exe *.o $(LIB)

.PHONY: explain
explain:
	@echo "sources: $(MYSOURCES)"
	@echo "objects: $(MYOBJECTS)"
	@echo "headers: $(HEADERS)"
	@echo "lib: $(LIB)"
	@echo "target: $(TARGET)"