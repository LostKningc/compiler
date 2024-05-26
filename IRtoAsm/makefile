all:
	g++ ../src/IRtoAsm.cpp ../src/visit.cpp unitTest.cpp -L$(CDE_LIBRARY_PATH)/native -lkoopa

testasm: all
	./a.out
	riscv64-unknown-elf-gcc -march=rv32imac -mabi=ilp32 -o tr.out test.s
	qemu-riscv32 tr.out