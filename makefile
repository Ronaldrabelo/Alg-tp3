CXX = g++

CXXFLAGS = -std=c++2a -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror -I./services -I./utils

SRC = main.cpp \
	  src/algorithms/BruteForce.cpp \
	  src/algorithms/DynamicProgramming.cpp \
	  src/algorithms/Greedy.cpp \
	  src/utils/GraphUtils.cpp \
	  src/utils/PermutationUtils.cpp \

OBJ = main.o \
	  src/algorithms/BruteForce.o \
	  src/algorithms/DynamicProgramming.o \
	  src/algorithms/Greedy.o \
	  src/utils/GraphUtils.o \
	  src/utils/PermutationUtils.o \

EXEC = tp3

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/algorithms/BruteForce.o: src/algorithms/BruteForce.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/algorithms/DynamicProgramming.o: src/algorithms/DynamicProgramming.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/algorithms/Greedy.o: src/algorithms/Greedy.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/utils/GraphUtils.o: src/utils/GraphUtils.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/utils/PermutationUtils.o: src/utils/PermutationUtils.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
