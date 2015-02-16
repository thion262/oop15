Target :=	testtrie
Sources :=	$(wildcard *.[ch]pp)
CPPFiles :=	$(wildcard *.cpp)
Objects :=	$(patsubst %.cpp,%.o,$(CPPFiles))

CC :=		g++
CXX :=		g++
CXXFLAGS :=	-Wall -g -std=gnu++11
CPPFLAGS :=

.PHONY:		all depend clean realclean
all:		makefile $(Target)
depend: ;	gcc-makedepend $(CPPFLAGS) $(CPPFiles)
makefile:	$(Sources)
		gcc-makedepend $(CPPFLAGS) $(CPPFiles)
clean: ;	rm -f $(Objects)
realclean:	clean
		rm -f $(Target)

$(Target):	$(Objects)
		$(CXX) -o $@ $(LDFLAGS) $(Objects) $(LOADLIBES) $(LDLIBS)

# DO NOT DELETE
TestTrie.o: TestTrie.cpp Trie.hpp
