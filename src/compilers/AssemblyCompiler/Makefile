GXX=g++
GXX_ARGS = -std=c++17 -O2 -Wall -Wextra
GCC=gcc
GCC_ARGS = -O2 -Wall -Wextra

FLEX=flex
BISON=bison

SRC=src
BIN=bin/linux
OBJ=$(BIN)/obj

LIBRARIES = $(OBJ)/chaos_make.o $(OBJ)/Version.o

OPTS=

ifdef DEBUG
OPTS+= -g
endif

.PHONY: default
default: $(BIN)/chaos_make.out ;

$(OBJ)/chaos_make.o: $(SRC)/chaos_make.cpp
	$(GXX) $(GXX_ARGS) $(OPTS) -o $@ -c $<

$(OBJ)/%.o: $(SRC)/lib/%.cpp
	$(GXX) $(GXX_ARGS) $(OPTS) -o $@ -c $<
$(OBJ)/%.o: $(SRC)/lib/%.c
	$(GCC) $(GCC_ARGS) $(OPTS) -o $@ -c $<

$(BIN)/chaos_make.out: $(LIBRARIES)
	$(GXX) $(GXX_ARGS) $(OPTS) -o $@ $(LIBRARIES) -lfl -ldl

clean:
	rm -f $(BIN)/*.out
	rm -f $(OBJ)/*.o
	rm -f $(SRC)/parser/output/*.c
	rm -f $(SRC)/parser/output/*.h