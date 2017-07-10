CLANG := /home/paolo/SECURE/build/bin/clang

no-pass:
	$(CLANG) -O0 -emit-llvm -S sample.c -o 00sample.ll

with-pass:
	$(CLANG) -O0 -emit-llvm -Xclang -load -Xclang build/lib/LLVMBitSlicer.so -S sample.c -o 01sample.ll

exe:
	$(CLANG) -O0 -Xclang -load -Xclang build/lib/LLVMBitSlicer.so sample.c -o 02sample

