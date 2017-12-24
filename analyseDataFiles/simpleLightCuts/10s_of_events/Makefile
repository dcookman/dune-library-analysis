CXXFLAGS=-std=c++11 $(shell root-config --cflags)
LIBS=$(shell root-config --libs)


run : cut_ana
	@echo "Complied... cut_ana"
cut_ana : cut_ana.o

	g++ -o $@ $^ ${LIBS}

%.o : %.cc
	g++ ${CXXFLAGS} -o $@ -c $^

