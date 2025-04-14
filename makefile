CXX = clang++
CXXFLAGS = -Wall -std=c++17 -ggdb
OBJ = ./obj/
SRC = ./src/
INC = ./inc/

all: Main


Main: $(OBJ)main.o $(OBJ)matrix_func.o $(OBJ)my_math.o
	mkdir -p $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@
	./Main

$(OBJ)main.o: $(SRC)main.cpp $(INC)matrix_func.hpp $(INC)my_math.hpp
	mkdir -p $(OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ)matrix_func.o: $(SRC)matrix_func.cpp $(INC)matrix_func.hpp $(INC)my_math.hpp
	mkdir -p $(OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ)my_math.o: $(SRC)my_math.cpp $(INC)my_math.hpp
	mkdir -p $(OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean valgrind test all

test:
	@echo "Need to be implemented"

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
	sudo ulimit -n 1024
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./Main

clean:
	rm -rf *.o Main core.* $(OBJ)