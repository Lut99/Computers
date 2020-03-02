GCC=gcc
GCC_ARGS = -O2 -Wall -Wextra

FLEX=flex
BISON=bison

SRC=.
BIN=../../../bin/linux
OBJ=obj
PARSER=$(SRC)/parser

.PHONY: default
default: $(BIN)/main_1_0_0.so ;

$(PARSER)/scanner.flex.c:
	$(FLEX) -o $(PARSER)/scanner.flex.c $(SRC)/scanner.l
$(PARSER)/parser.tab.c:
	$(BISON) --defines=$(PARSER)/parser.tab.h --output=$(PARSER)/parser.tab.c $(SRC)/parser.y

$(OBJ)/scanner.o: $(PARSER)/scanner.flex.c
	$(GCC) $(GCC_ARGS) -fPIC -o $@ -c $<
$(OBJ)/parser.o: $(PARSER)/parser.tab.c
	$(GCC) $(GCC_ARGS) -fPIC -o $@ -c $<

$(OBJ)/instructions.o: $(SRC)/instructions.c
	$(GCC) $(GCC_ARGS) -fPIC -o $@ -c $<

$(OBJ)/main.o: $(SRC)/main.c
	$(GCC) $(GCC_ARGS) -fPIC -o $@ -c $<

$(BIN)/main_1_0_0.so: $(OBJ)/parser.o $(OBJ)/scanner.o $(OBJ)/instructions.o $(OBJ)/main.o 
	$(GCC) $(GCC_ARGS) -shared -o $@ $(OBJ)/parser.o $(OBJ)/scanner.o $(OBJ)/instructions.o $(OBJ)/main.o -lfl

clean:
	rm -f $(PARSER)/*.h
	rm -f $(PARSER)/*.c
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/main_1_0_0.so