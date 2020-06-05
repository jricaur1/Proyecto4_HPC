CXX=gcc

default : app


prediction.o : prediction.cc
	${CXX} -c -o "$@" "$<"

app : main.cc prediction.o
	${CXX}  -o "$@" "$<" prediction.o

clean :
	rm app prediction.o *.optrpt