SRC := $(*.cpp)

all: tlb-sim

tlb-sim: $(SRC)
	clang-morello -o tlb-sim -g -Wno-unused-result 
-lc++ -static -fuse-ld=lld -O2 *.cpp

.PHONY: clean
clean:
	rm -f tlb-sim
