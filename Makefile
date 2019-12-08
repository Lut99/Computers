CC=g++
CC_ARGS = -std=c++17

test_instruction: tests/test_instruction.cpp src/Hardware/Support/Instruction.cpp
	$(CC) $(CC_ARGS) -o tests/bin/test_instruction tests/test_instruction.cpp src/Hardware/Support/Instruction.cpp
test_config_parser: tests/test_config_parser.cpp src/Hardware/Support/ConfigParser.cpp
	$(CC) $(CC_ARGS) -o tests/bin/test_config_parser tests/test_config_parser.cpp src/Hardware/Support/ConfigParser.cpp