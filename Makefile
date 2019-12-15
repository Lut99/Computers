CC=g++
CC_ARGS = -std=c++17

test_instruction: tests/test_instruction.cpp src/Hardware/Support/Instruction.cpp
	$(CC) $(CC_ARGS) -o tests/bin/test_instruction tests/test_instruction.cpp src/Hardware/Support/Instruction.cpp
test_config_parser: tests/test_config_parser.cpp src/Hardware/Support/ConfigParser.cpp
	$(CC) $(CC_ARGS) -o tests/bin/test_config_parser tests/test_config_parser.cpp src/Hardware/Support/ConfigParser.cpp

chaos_compiler: src/compilers/ChaosCompiler/ChaosCompiler.cpp src/compilers/ChaosCompiler/Chaos1_0.cpp
	$(CC) $(CC_ARGS) -o bin/compilers/linux64/chaos_make src/compilers/ChaosCompiler/ChaosCompiler.cpp src/compilers/ChaosCompiler/Chaos1_0.cpp

LinkedList.o: src/support/LinkedList.cpp
	$(CC) $(CC_ARGS) -o bin/objects/linux64/LinkedList.o -c src/support/LinkedList.cpp
test_linked_list: tests/test_linked_list.cpp LinkedList.o
	$(CC) $(CC_ARGS) -o tests/bin/test_linked_list tests/test_linked_list.cpp bin/objects/linux64/LinkedList.o
