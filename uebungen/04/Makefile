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
Walk.o: Walk.cpp Location.hpp Territory.hpp
