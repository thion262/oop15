Target :=	Nim
MainSources :=	Nim.cpp NimGame.cpp NimMove.cpp
SharedSrc :=	HumanNimPlayer.cpp OptimalNimPlayer.cpp RandomNimPlayer.cpp
Sources :=	$(wildcard *.[ch]pp)
CPPFiles :=	$(wildcard *.cpp)
Objects :=	$(patsubst %.cpp,%.o,$(CPPFiles))
SharedObjs :=   $(patsubst %.cpp,%.so,$(SharedSrc))
MainObjs :=     $(patsubst %.cpp,%.o,$(MainSources))

CC :=		g++
CXX :=		g++
CXXFLAGS :=	-Wall -g -std=gnu++11
CPPFLAGS :=
SHARED :=	-fPIC -shared

.PHONY:		all depend clean realclean
all:		makefile $(Target) $(SharedObjs)
depend: ;	gcc-makedepend $(CPPFLAGS) $(CPPFiles)
makefile:	$(Sources)
		gcc-makedepend $(CPPFLAGS) $(CPPFiles)
clean: ;	rm -f $(Objects)
realclean:	clean
		rm -f $(Target) $(SharedObjs)

$(Target):	$(MainObjs)
		$(CXX) -o $@ -rdynamic $(LDFLAGS) $(MainObjs) $(LDLIBS)

$(SharedObjs):	%.so: %.cpp
		$(CXX) -o $@ $(SHARED) $(LDFLAGS) $< $(LDLIBS)

# DO NOT DELETE
HumanNimPlayer.o: HumanNimPlayer.cpp HumanNimPlayer.hpp NimPlayer.hpp \
 NimGame.hpp NimMove.hpp
Nim.o: Nim.cpp NimMove.hpp NimGame.hpp NimPlayer.hpp
NimGame.o: NimGame.cpp NimGame.hpp NimMove.hpp
NimMove.o: NimMove.cpp NimMove.hpp
OptimalNimPlayer.o: OptimalNimPlayer.cpp OptimalNimPlayer.hpp \
 NimPlayer.hpp NimGame.hpp NimMove.hpp
RandomNimPlayer.o: RandomNimPlayer.cpp RandomNimPlayer.hpp NimPlayer.hpp \
 NimGame.hpp NimMove.hpp
