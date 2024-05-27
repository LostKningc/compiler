all: IRtoAsm.o visit.o unitTest.o
	g++ IRtoAsm.o visit.o unitTest.o -L$(CDE_LIBRARY_PATH)/native -lkoopa -o backend

IRtoAsm.o: ../src/IRtoAsm.cpp
	g++ -c ../src/IRtoAsm.cpp -lkoopa -o IRtoAsm.o 

visit.o: ../src/visit.cpp
	g++ -c ../src/visit.cpp -lkoopa -o visit.o

unitTest.o: unitTest.cpp
	g++ -c unitTest.cpp -o unitTest.o

.PHONY: clean testasm
clean:
	rm -f *.o backend

testasm: test.s
	clang test.s -c -o tr.o -target riscv32-unknown-linux-elf -march=rv32im -mabi=ilp32
	ld.lld tr.o -L$(CDE_LIBRARY_PATH)/riscv32 -lsysy -o tr.out
	qemu-riscv32 tr.out

test.s: all test.kp
	./backend