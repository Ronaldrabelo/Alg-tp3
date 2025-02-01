# Definir o compilador
CXX = g++

# Definir flags de compilação
CXXFLAGS = -std=c++2a -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror -I./services -I./utils 

# Arquivos-fonte com caminhos completos
SRC = main.cpp \
	  src/algorithms/BruteForce.cpp \
	  src/algorithms/DynamicProgramming.cpp \
	  src/algorithms/Greedy.cpp \
	  src/utils/GraphUtils.cpp \
	  src/utils/PermutationUtils.cpp \

# Arquivos-objeto correspondentes
OBJ = main.o \
	  src/algorithms/BruteForce.o \
	  src/algorithms/DynamicProgramming.o \
	  src/algorithms/Greedy.o \
	  src/utils/GraphUtils.o \
	  src/utils/PermutationUtils.o \

# Nome do executável
EXEC = tp3

# Regra padrão: compilar tudo
all: $(EXEC)

# Regra para compilar o executável
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regras para compilar arquivos .cpp em .o
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

# Limpar arquivos gerados
clean:
	rm -f $(OBJ) $(EXEC)
