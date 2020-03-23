GXX=g++
GXX_ARGS = -std=c++17 -O2 -Wall -Wextra
GCC=gcc
GCC_ARGS = -O2 -Wall -Wextra

FLEX=flex
BISON=bison

SRC=src
BIN=bin/linux
OBJ=$(BIN)/obj
LANG=$(SRC)/languages

LIBRARIES=$(OBJ)/chaos_make.o $(OBJ)/Version.o
LANGUAGES=$(LANG)/main_1.0.0

OPTS=

ifdef DEBUG
OPTS+= -g
endif

.PHONY: default
default: all ;

$(OBJ)/chaos_make.o: $(SRC)/chaos_make.cpp
	$(GXX) $(GXX_ARGS) $(OPTS) -o $@ -c $<

$(OBJ)/%.o: $(SRC)/lib/%.cpp
	$(GXX) $(GXX_ARGS) $(OPTS) -o $@ -c $<
$(OBJ)/%.o: $(SRC)/lib/%.c
	$(GCC) $(GCC_ARGS) $(OPTS) -o $@ -c $<

$(BIN)/chaos_make.out: $(LIBRARIES)
	$(GXX) $(GXX_ARGS) $(OPTS) -o $@ $(LIBRARIES) -lfl -ldl

languages:
	for dir in $(LANGUAGES); do \
		$(MAKE) -C $$dir; \
	done

tests/bin/test_tools.out: tests/test_tools.c src/languages/Tools.c
	$(GCC) $(GCC_ARGS) $(OPTS) -o $@ $< src/languages/Tools.c

all: $(BIN)/chaos_make.out languages

clean:
	for dir in $(LANGUAGES); do \
		$(MAKE) -C $$dir clean; \
	done
	rm -f $(BIN)/*.out
	rm -f $(OBJ)/*.o
	rm -f $(SRC)/parser/output/*.c
	rm -f $(SRC)/parser/output/*.h
	rm -f tests/bin/*.out