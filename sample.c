#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(){
	uint8_t v1, v2, A[8];
	int i;
	
	v1 = 0x04;
	v2 = v1<<2;
	
	for(i=0;i<8;i++){
		A[i] = v2 + i;
	}
	
	return 0;
}
