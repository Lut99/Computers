test_instruction: tests/test_instruction.cpp src/hardware/Tools/Instruction.cpp
	g++ -std=c++17 -o tests/bin/test_instruction tests/test_instruction.cpp src/hardware/Tools/Instruction.cpp