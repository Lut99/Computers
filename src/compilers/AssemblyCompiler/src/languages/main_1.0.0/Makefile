GCC=gcc
GCC_ARGS = -O2 -Wall -Wextra

FLEX=flex
BISON=bison

SRC=.
BIN=../../../bin/linux/lang
OBJ=obj
LIB=..
PARSER=$(SRC)/parser

LIBRARIES=$(OBJ)/parser.o $(OBJ)/scanner.o $(OBJ)/instructions.o $(OBJ)/Tools.o

OPTS=

ifdef DEBUG
OPTS+= -g
endif

.PHONY: default
default: $(BIN)/main_1_0_0.so ;

$(PARSER)/scanner.flex.c:
	$(FLEX) -o $(PARSER)/scanner.flex.c $(SRC)/scanner.l
$(PARSER)/parser.tab.c:
	$(BISON) --defines=$(PARSER)/parser.tab.h --output=$(PARSER)/parser.tab.c $(SRC)/parser.y

$(OBJ)/scanner.o: $(PARSER)/scanner.flex.c
	$(GCC) $(GCC_ARGS) $(OPTS) -fPIC -o $@ -c $<
$(OBJ)/parser.o: $(PARSER)/parser.tab.c
	$(GCC) $(GCC_ARGS) $(OPTS) -fPIC -o $@ -c $<

$(OBJ)/%.o: $(SRC)/%.c
	$(GCC) $(GCC_ARGS) $(OPTS) -fPIC -o $@ -c $<
$(OBJ)/%.o: $(LIB)/%.c
	$(GCC) $(GCC_ARGS) $(OPTS) -fPIC -o $@ -c $<

$(BIN)/main_1_0_0.so: $(LIBRARIES)
	$(GCC) $(GCC_ARGS) $(OPTS) -shared -o $@ $(LIBRARIES) -lfl

clean:
	rm -f $(PARSER)/*.h
	rm -f $(PARSER)/*.c
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/main_1_0_0.so