#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

int val __attribute__ ((aligned(8), bitsliced)) = 2;
/*
void encrypt(uint8_t *ptext, uint8_t *key){
	int i;
	
	for(i=0; i<8; i++){
		ptext[i] = ptext[i] ^ key[i+16];
	}
}
*/

int offset(){
	return 6;
}

uint8_t value(uint8_t arr){
	return arr;
}

uint8_t *address(uint8_t *arr){
	return arr;
}


int main(){

	uint8_t __attribute__ ((bitsliced)) v1;
	uint8_t __attribute__ ((bitsliced)) ptext[8];
	
	uint8_t __attribute__ ((bitsliced)) Mkey[10];
	uint8_t __attribute__ ((bitsliced)) Matrix[5][6];
	uint8_t __attribute__ ((bitsliced)) Cube[5][6][8];
	int i;
	//v1 = 0x8e;
	//Mkey[3] = 0x1e;
	/*
	for(i=0;i<8;i++){
		Mkey[i] = 0x01 << i;
	}
	*/
	
	
	
	uint8_t a = 0, b;
	//b = 0x33;
	//a = b << 0x01;
	//uint8_t tmp[8];
	
	//a = a | b;
	//a = tmp[5];
	//a = Mkey[3];
	
	/*
	for(i=0;i<8;i++){
		a = a | (Mkey[i] << i);
	}
	*/
	
	//b = a;
	/*
	a = 0;
	b = a + 2;
	//srand(time(NULL));
	v1 = 0x04;
	*/
	/*
	for(i=0;i<8;i++){
		a = a | tmp[i] << i;
	}
	*/
	
	/*
	for(i=0;i<8;i++){
		ptext[i] = i;
	}
	*/
	
	for(i=0;i<10;i++){
		Mkey[i] = 0x55;
	}
	
	//encrypt(ptext, Mkey);
	//v1 = v1 * 2;
	
	for(i=0; i<4; i++){
		ptext[i] = 0xaa;
		ptext[i+4] = 0x55;
	}
	
	uint8_t bit = __builtin_bit(ptext[1], 2);
	
	for(i=0; i<8; i++){
		ptext[i] = ptext[i] ^ Mkey[i+2];
	}
	
	i = 6;
	
	//*(ptext + offset()) = 0xaa;
	//*(address(ptext[6])) = 0xaa;
	a = value(ptext[6]);
	*address(&ptext[6]) = 0xaa;
	/*
	for(i=0;i<8;i++){
		v2 = A[i];
	}
	*/
	
	/*
	ptext[3] = ((ptext[0] ^ 0xff) & (ptext[2] ^ 0xff) & (ptext[3] ^ 0xff)) |
				((ptext[0] ^ 0xff) & ptext[2] & ptext[3]) |
				((ptext[0] ^ 0xff)&ptext[1] & ptext[2] & (ptext[3] ^ 0xff)) |
				(ptext[0] & (ptext[1] ^ 0xff)&ptext[3]) |
				(ptext[0] & (ptext[1] ^ 0xff)&ptext[2] & (ptext[3] ^ 0xff));
	*/
	/*
	a = Mkey[4];
	b = Mkey[2];
	*/
	
	for(i=0;i<8;i++){
		printf("P[%d]: %d\n", i, ptext[i]);
		}
	
	return 0;
}


