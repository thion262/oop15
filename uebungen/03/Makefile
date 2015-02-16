Sources :=	$(wildcard *.[ch]pp)
CPPFiles :=	$(wildcard *.cpp)
Objects :=	$(patsubst %.cpp,%.o,$(CPPFiles))
Target :=	${patsubst %.cpp,%,${shell grep -l '\<main *(' $(CPPFiles)}}

CC :=		g++
CXX :=		g++
CXXFLAGS :=	-Wall -g -std=gnu++11
CPPFLAGS :=

.PHONY:		all depend clean realclean
all:		Makefile $(Target)
depend: ;	gcc-makedepend $(CPPFLAGS) $(CPPFiles)
Makefile:	$(Sources)
		gcc-makedepend $(CPPFLAGS) $(CPPFiles)
clean: ;	rm -f $(Objects)
realclean:	clean
		rm -f $(Target)

$(Target):	$(Objects)
		$(CXX) -o $@ $(LDFLAGS) $(Objects) $(LOADLIBES) $(LDLIBS)

# DO NOT DELETE
Nim.o: Nim.cpp NimMove.hpp NimGame.hpp
NimGame.o: NimGame.cpp NimGame.hpp NimMove.hpp
NimMove.o: NimMove.cpp NimMove.hpp
