CC=g++
CC_ARGS = -std=c++17 -O2 -Wall -Wextra

FLEX=flex
BISON=bison

SRC=src
BIN=bin/linux
OBJ=$(BIN)/obj

LIBRARIES = $(OBJ)/AssemblyParser.o $(OBJ)/AssemblyScanner.o $(OBJ)/chaos_make.o $(OBJ)/Version.o

.PHONY: default
default: $(BIN)/chaos_make.out ;

$(SRC)/parser/output/AssemblyScanner.flex.c:
	$(FLEX) -o $@ $(SRC)/parser/AssemblyScanner.l
$(SRC)/parser/output/AssemblyParser.tab.c:
	$(BISON) --defines=$(SRC)/parser/output/AssemblyParser.tab.h --output=$@ $(SRC)/parser/AssemblyParser.y

$(OBJ)/AssemblyParser.o: $(SRC)/parser/output/AssemblyParser.tab.c
	$(CC) $(CC_ARGS) -o $@ -c $<
$(OBJ)/AssemblyScanner.o: $(SRC)/parser/output/AssemblyScanner.flex.c
	gcc -Wall -Wextra -o $@ -c $<

$(OBJ)/chaos_make.o: $(SRC)/chaos_make.cpp
	$(CC) $(CC_ARGS) -o $@ -c $<

$(OBJ)/%.o: $(SRC)/lib/%.cpp
	$(CC) $(CC_ARGS) -o $@ -c $<

$(BIN)/chaos_make.out: $(LIBRARIES)
	$(CC) $(CC_ARGS) -o $@ $(LIBRARIES) -lfl

clean:
	rm -f $(BIN)/*.out
	rm -f $(OBJ)/*.o
	rm -f $(SRC)/parser/output/*.c
	rm -f $(SRC)/parser/output/*.h