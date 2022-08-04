all: test-suite

prog: catch.o library.o test-suite.o 
	g++ catch.o library.o test-suite.o -o test-suite 

catch.o: catch.cpp catch.h 
	g++ -c catch.cpp -o catch.o

library.o:library.cpp library.h
	g++ -c library.cpp -o library.o

test-suite.o: test-suite.cpp library.cpp catch.cpp	
	g++ -c test-suite.cpp -o test-suite.o

clean:
	rm -rf *.o test-suite


# make 
# g++ -c catch.o -o catch.o 
# g++ -c library.o -o library.o 
# g++ -c test-suite.o -o test-suite.o 
# g++ catch.o library.o test-suite.o -o test-suite 

# g++ -c catch.o library.o test-suite.o 
# g++ -c catch.o library.o test-suite.o 
