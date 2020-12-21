CXX=g++
CXXFLAGS= -g
RM=rm -f

test_pile : test_pile.o
	$(CXX) $(CXXFLAGS) $^ -o $@

test_copy : test-copy.o
	$(CXX) $(CXXFLAGS) $^ -o $@


test_pile.o : test_pile.cpp IntStack.h
test-copy.o : test-copy.cpp IntStack.h

%.o:%.cpp; $(CXX) $(CXXFLAGS) -o $@ -c $<

clean :
	$(RM) test_pile.o test-copy.o

