CXX=g++
CXXFLAGS= -g
RM=rm -f

test-intlist.o : test-intlist.cpp intlist.h

%.o:%.cpp; $(CXX) $(CXXFLAGS) -o $@ -c $<

clean :
	$(RM) test-intlist.o

int : test-intlist.o
	$(CXX) $(CXXFLAGS) $^ -o $@
