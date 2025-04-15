CXX = clang++
CXXFLAGS = -Wall -std=c++17 -ggdb
OBJ = ./obj/
SRC = ./src/
INC = ./inc/

all: mmain mtest

Main: mmain
	./Main

test: mtest
	./matxTest

mmain: $(OBJ)main.o $(OBJ)matrixFunc.o $(OBJ)myMath.o
	mkdir -p $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o Main

$(OBJ)main.o: $(SRC)main.cpp $(INC)matrixFunc.hpp $(INC)myMath.hpp
	mkdir -p $(OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ)matrixFunc.o: $(SRC)matrixFunc.cpp $(INC)matrixFunc.hpp $(INC)myMath.hpp
	mkdir -p $(OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ)myMath.o: $(SRC)myMath.cpp $(INC)myMath.hpp
	mkdir -p $(OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# New testing rules
$(OBJ)matxTest.o: $(SRC)matxTest.cpp $(INC)doctest.h $(INC)matrixFunc.hpp $(INC)myMath.hpp
	mkdir -p $(OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

mtest: $(OBJ)matxTest.o $(OBJ)matrixFunc.o $(OBJ)myMath.o
	$(CXX) $(CXXFLAGS) $^ -o matxTest

.PHONY: Main test valgrind clean all

#make sure to run 'ulimit -n 1024' before running valgrind, thank you
#
#--leak-check=full: "each individual leak will be shown in detail"
#--show-leak-kinds=all: Show all of "definite, indirect, possible, 
#				reachable" leak kinds in the "full" report.
#--track-origins=yes: Favor useful output over speed. This tracks 
#			the origins of uninitialized values, which could be very useful 
#			for memory errors. Consider turning off if Valgrind is unacceptably slow.
#
valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./Main

clean:
	rm -rf Main matxTest $(OBJ)