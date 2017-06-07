#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int val __attribute__ ((aligned(8), bitsliced)) = 2;

int __attribute__ ((aligned(16), bitsliced)) foo(int num __attribute__((aligned(32), bitsliced)), uint8_t *A){
	val = 5;
	int g __attribute__ ((aligned(16), bitsliced)) = val;
	return (num)*2;
}


int main(){
	uint8_t v1, v2, A[8];
	int i __attribute__ ((aligned(16), bitsliced)) = 0;
	int a;
	
	v1 = 0xd4;
	v2 = v1;
	a = i+i;
	a = A[i] + i;
	//v2 = v1<<2;
	
	int s = foo(i,A);
	
	s = i+1;
	val = 3;
	/*
	for(i=0;i<8;i++){
		v2 = A[i];
	}
	*/
	return 0;
}


