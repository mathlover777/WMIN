OPTIMIZEFLAG = -O1 -O2 -O3
DEBUGFLAG = -g
FLAG = -g
# BUILDFLAG = $1
DEBUG = debug
ifeq ($(BUILDFLAG),$(DEBUG))
	FLAG := $(DEBUGFLAG)
else
	FLAG := $(OPTIMIZEFLAG)
endif
all:other.o Set.o graph.o vectorarray.o vectorarray_test set_test graph_test
all:fileio.o equation.o svmio.o config.o graphtosvm precision
other.o:other.h other.cpp
	g++ -c other.cpp -o other.o $(FLAG)

Set.o:Set.cpp Set.h other.h other.cpp
	g++ -c Set.cpp -o Set.o $(FLAG)

vectorarray.o:vectorarray.h vectorarray.cpp
	g++ -c vectorarray.cpp -o vectorarray.o $(FLAG)

graph.o:vectorarray.h vectorarray.cpp Set.cpp Set.h graph.cpp graph.h other.h other.cpp
	g++ -c graph.cpp -o graph.o $(FLAG)

vectorarray_test:vectorarray_test.cpp vectorarray.h vectorarray.cpp
	g++ -c vectorarray_test.cpp -o vectorarray_test.o
	g++ vectorarray.o vectorarray_test.o -o vectorarray_test

set_test:set_test.cpp Set.cpp Set.h other.h other.cpp
	g++ -c set_test.cpp -o set_test.o $(FLAG)
	g++ set_test.o Set.o other.o -o set_test $(FLAG)

graph_test:vectorarray.h vectorarray.cpp Set.cpp Set.h graph.cpp graph.h other.h other.cpp graph_test.cpp
	g++ -c graph_test.cpp -o graph_test.o $(FLAG)
	g++ graph_test.o graph.o other.o vectorarray.o Set.o -o graph_test $(FLAG)
fileio.o:fileio.c fileio.h
	g++ -c fileio.c -o fileio.o $(FLAG)
equation.o:fileio.c fileio.h equation.cpp equation.h
	g++ -c equation.cpp -o equation.o $(FLAG)
svmio.o:svmio.h svmio.cpp fileio.c fileio.h equation.h equation.cpp graph.h graph.cpp vectorarray.h vectorarray.cpp Set.h Set.cpp other.h other.cpp
	g++ -c svmio.cpp -o svmio.o $(FLAG)

config.o:config.h config.cpp
	g++ -c config.cpp -o config.o $(FLAG)

graphtosvm:svmio.h svmio.cpp fileio.c fileio.h equation.h equation.cpp graph.h graph.cpp vectorarray.h vectorarray.cpp Set.h Set.cpp other.h other.cpp graphtosvm.cpp config.h config.cpp
	g++ -c graphtosvm.cpp -o graphtosvm.o $(FLAG)
	g++ graphtosvm.o svmio.o fileio.o equation.o graph.o vectorarray.o Set.o other.o config.o -o graphtosvm $(FLAG)

precision:precision.cpp fileio.c fileio.h equation.h equation.cpp graph.h graph.cpp vectorarray.h vectorarray.cpp Set.h Set.cpp other.h other.cpp graphtosvm.cpp config.h config.cpp
	g++ -c precision.cpp -o precision.o
	g++ precision.o fileio.o equation.o graph.o vectorarray.o Set.o other.o config.o -o precision $(FLAG)
	