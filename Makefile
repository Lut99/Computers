CC=g++
ARGS = -std=c++17 -O2

test_instruction: tests/test_instruction.cpp src/Hardware/Support/Instruction.cpp
	$(CC) $(ARGS) -o tests/bin/test_instruction tests/test_instruction.cpp src/Hardware/Support/Instruction.cpp
test_config_parser: tests/test_config_parser.cpp src/Hardware/Support/ConfigParser.cpp
	$(CC) $(ARGS) -o tests/bin/test_config_parser tests/test_config_parser.cpp src/Hardware/Support/ConfigParser.cpp

chaos_compiler: src/compilers/ChaosCompiler/ChaosCompiler.cpp src/compilers/ChaosCompiler/Chaos1_0.cpp
	$(CC) $(ARGS) -o bin/compilers/linux64/chaos_make src/compilers/ChaosCompiler/ChaosCompiler.cpp src/compilers/ChaosCompiler/Chaos1_0.cpp

LinkedList.o: lib/LinkedList.cpp
	$(CC) $(ARGS) -o bin/lib/linux64/LinkedList.o -c lib/LinkedList.cpp
test_linked_list: tests/test_linked_list.cpp LinkedList.o
	$(CC) $(ARGS) -o tests/bin/test_linked_list tests/test_linked_list.cpp bin/lib/linux64/LinkedList.o

StringConverter.o: lib/StringConverter.cpp
	$(CC) $(ARGS) -o bin/lib/linux64/StringConverter.o -c lib/StringConverter.cpp
test_stringconverter: tests/test_stringconverter.cpp StringConverter.o
	$(CC) $(ARGS) -o tests/bin/test_stringconverter tests/test_stringconverter.cpp bin/lib/linux64/StringConverter.o

Encoding.o: lib/Encoding.cpp
	$(CC) $(ARGS) -o bin/lib/linux64/Encoding.o -c lib/Encoding.cpp

BinaryStream.o: lib/BinaryStream.cpp Encoding.o
	$(CC) $(ARGS) -o bin/lib/linux64/BinaryStream.o -c lib/BinaryStream.cpp
test_binarystream: tests/test_binarystream.cpp BinaryStream.o Encoding.o
	$(CC) $(ARGS) -o tests/bin/test_binarystream tests/test_binarystream.cpp bin/lib/linux64/BinaryStream.o bin/lib/linux64/Encoding.o