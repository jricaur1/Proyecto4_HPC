CXX=icpc
CXXFLAGS=-xMIC-AVX512 -qopenmp -mkl -std=c++11
OPTRPT=-qopt-report=5

default : app


prediction.o : prediction.cc
	${CXX} -c ${OPTRPT} ${CXXFLAGS} -o "$@" "$<"

app : main.cc prediction.o
	${CXX} ${OPTRPT} ${CXXFLAGS} -o "$@" "$<" prediction.o

clean :
	rm app prediction.o *.optrpt