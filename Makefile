CXX = g++
CXX_FLAGS = -std=c++11 -g
CXX_LIBS  = -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread

INCLUDE = -Iinclude/
OBJECTS = hash iso

C_OS		:=
ifeq ($(OS),Windows_NT)
	C_OS += Windows
else
	C_OS += Linux
endif

all: os build trash

os:
	@echo $(C_OS)

build: $(OBJECTS)

hash: hash.o
	$(CXX) $(CXX_FLAGS) hash.o $(INCLUDE) -o hash $(CXX_LIBS)

hash.o: hash.cpp
	$(CXX) $(INCLUDE) -c hash.cpp $(CXX_FLAGS)

iso: iso.o
	$(CXX) $(CXX_FLAGS) iso.o $(INCLUDE) -o iso $(CXX_LIBS)

iso.o: iso.cpp
	$(CXX) $(INCLUDE) -c iso.cpp $(CXX_FLAGS)

noimages:
	rm -rf *.png *.dot

trash:
	rm -rf *.o

clean:
	rm -rf *.o main
