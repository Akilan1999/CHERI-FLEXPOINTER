SRC := $(wildcard *.cpp)

all: tlb-sim

tlb-sim: $(SRC)
	clang-morello -march=morello+c64 
-mabi=purecap -o $@ -g -Wno-unused-result -O2 $(SRC)

.PHONY: clean
clean:
	rm -f tlb-sim
