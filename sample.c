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

int main(){
	uint8_t __attribute__ ((bitsliced)) ptext[8];
	uint8_t __attribute__ ((bitsliced)) Mkey[8];
	uint8_t __attribute__ ((bitsliced)) v1;
	int i;
	//srand(time(NULL));
	v1 = 0x04;
	
	for(i=0;i<8;i++){
		ptext[i] = i;
	}
	
	for(i=0;i<10;i++){
		Mkey[i] = 0x5a;
	}
	
	//encrypt(ptext, Mkey);
	v1 = v1 * 2;
	
	for(i=0; i<8; i++){
		ptext[i] = Mkey[i+16];
	}
	
	/*
	for(i=0; i<8; i++){
		ptext[i] = ptext[i] ^ Mkey[i+16];
	}
	*/
	/*
	for(i=0;i<8;i++){
		v2 = A[i];
	}
	*/
	
	
	ptext[3] = ((ptext[0] ^ 0xff) & (ptext[2] ^ 0xff) & (ptext[3] ^ 0xff)) |
				((ptext[0] ^ 0xff) & ptext[2] & ptext[3]) |
				((ptext[0] ^ 0xff)&ptext[1] & ptext[2] & (ptext[3] ^ 0xff)) |
				(ptext[0] & (ptext[1] ^ 0xff)&ptext[3]) |
				(ptext[0] & (ptext[1] ^ 0xff)&ptext[2] & (ptext[3] ^ 0xff));
	
	return 0;
}


