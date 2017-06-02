#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int val __attribute__ ((aligned(8))) = 2;

int foo(int num __attribute__((aligned(32))), int num2){
	val = 5;
	int g = val - num2;
	return (num)*2;
}


int main(){
	uint8_t v1, v2, A[8];
	int i __attribute__ ((aligned(16), bitsliced)) = 0;
	
	v1 = 0xd4;
	v2 = v1;
	//v2 = v1<<2;
	
	int s = foo(i,val);
	
	s = i+1;
	val = 3;
	/*
	for(i=0;i<8;i++){
		v2 = A[i];
	}
	*/
	return 0;
}


