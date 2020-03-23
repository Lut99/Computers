GXX=g++
GXX_ARGS=-std=c++17 -O2 -Wall -Wextra

SRC=src
LIB=$(SRC)/lib
BIN=bin/linux
OBJ=$(BIN)/obj

TESTS=tests
TESTS_BIN=$(BIN)/tests

INCLUDES=-I $(LIB)/include
LIBRARIES=

.PHONY: default
default: $(BIN)/assembler.out

$(OBJ)/%.o: $(LIB)/%.cpp
	$(GXX) $(GXX_ARGS) $(INCLUDES) -o $@ -c $<

test_scanner: $(OBJ)/Scanner.o
	$(GXX) $(GXX_ARGS) $(INCLUDES) -o $(TESTS_BIN)/$@.out $(TESTS)/test_scanner.cpp $<

clean:
	rm $(OBJ)/*.o
	rm $(TESTS_BIN)/*.out
	rm $(BIN)/*.out