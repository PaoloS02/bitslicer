/*WARNING: security checks on buffer overload were disabled in order to test the program*/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define MASK_61_UPPER_80KEY 
#define CHECK 3

int Sbox[16] = {12, 5, 6, 11, 9, 0, 10, 13, 3, 14, 15, 8, 4, 7, 1, 2};
int SboxInv[16] = {5, 14, 15, 8, 12, 1, 2, 13, 11, 4, 6, 3, 0, 7, 9, 10};


int main(void) {


	char ptext[8], Rkey[8], ptexttmp[8], start[8];
	char Mkey[10], tmpkey[10];

	strcpy(ptext, "barbarro");	
	strcpy(Mkey, "_S21FEDCBA");

	int i,j,k;
	char c, m, b1, b2, B1;


	for (j = 0; j < 8; j++) {
		printf("%x ", (unsigned char)ptext[j]);
	}
	printf("\n");


	for (k = 0; k < 32; k++) {
		

		for (j = 0; j < 8; j++) {
			Rkey[j] = Mkey[2+j];
		}


/*-----------------------------ADDROUNDKEY-------------------------------*/

		for (j = 0; j < 8; j++) {
			ptext[j] = Rkey[j] ^ ptext[j];
		}

		/*BITSLICE: another for loop in which each bit of ptext is xored with the bit of
		  Mkey in the corresponding position plus 2
		*/

/*-----------------------------SBOX--------------------------------------*/

		for (j = 0; j < 8; j++) {
			ptext[j] = (Sbox[(int)((ptext[j] & 0xf0) >> 4)] << 4) | (Sbox[(int)(ptext[j] & 0x0f)]);
		}
		
		/*BITSLICE: to be implemented. The position in the Sbox array in which we find the
		  current Sbox value depends on the input to the Sbox. This is in principle a vulnerability
		  to cache-based attacks (even though the Sbox here is tiny, 8 byte)
		*/

/*-----------------------------PBOX--------------------------------------*/

		for (j = 0; j < 8; j++) {
			ptexttmp[j] = ptext[j];
		}

		for (i = 0; i < 8; i++) {
			c = 0x00;
			m = 0x01;
			for (j = 0; j < 8; j++) {
				m = m << j;
				b2 = i * 8 + j;
				b1 = (b2 % 16) * 4 + b2 / 16;
				B1 = b1 / 8;
				c = c | (( (ptexttmp[B1] & (0x01 << (b1 % 8))) >> (b1 % 8)) << j);
			}
			ptext[i] = (char)c;
		}
		/*Apparently the execution time doesn't depend on the input, maybe just on the position of the
		starting bit, (info leakage from the cache hits/misses?), anyway the representation of the block
		of plaintext through an array of 64 arrays (each array containing the i-bit of each of 64 consecutive
		blocks) semplifies the p-permutation since it will consist just in swapping the addresses of the
		arrays in the array of arrays,... regardless the contents of the plaintext
		*/
/*---------------------------KEY UPDATE----------------------------------*/
		for (j = 0; j < 10; j++) {
			tmpkey[j] = Mkey[j];
		}
		for (j = 0; j < 10; j++) {
			i = (j + 7) % 10;
			
			Mkey[i] = tmpkey[j];
			
		}

		for (j = 0; j < 9; j++) {
			tmpkey[j+1] = (Mkey[j] & 0xf8)>>3;
		}
		tmpkey[0] = (Mkey[9] & 0xf8) >> 3;
		
		for (j = 0; j < 10; j++) {
			Mkey[j] = (Mkey[j] << 5) | tmpkey[j];
		}

		/*BITSLICE: the rotation should be simpler in the bitsliced version. We will have 64 keys
		  for the 64 blocks inserted in parallel, so, it will be an array of 80 64-bit arrays
		*/

		c = Mkey[9];
		Mkey[9] = (Mkey[9] & 0x0f) | (((char)Sbox[(c & 0xf0)>>4]<<4));

		/*
		BITSLICE: the Sbox represents the main problem again. It might be implemented
		through minterms of 4 correspondent bits from 4 consecutive blocks
		*/

		Mkey[2] = (Mkey[2] & 0xf0) | ((Mkey[2] & 0x0f) ^ ((k & 0x1e) >> 1));
		Mkey[1] = (Mkey[1] & 0x7f) | ((Mkey[1] & 0x80) ^ ((k & 0x01) << 7));

		/*
		BITSLICE: simple xor operations on the arrays from 16th to 20th (indexed 15 to 19)
		*/

	}
	
	for (j = 0; j < 8; j++) {
		Rkey[j] = Mkey[2 + j];
	}

	for (j = 0; j < 8; j++) {
		ptext[j] = Rkey[j] ^ ptext[j];
		printf("%x ", (unsigned char)ptext[j]);
	}
	printf("\n");


	
/*--------------------------ADDROUNDKEY--------------------------*/

	for (j = 0; j < 8; j++) {
		ptext[j] = Rkey[j] ^ ptext[j];
	}



	for (k = 31; k >= 0; k--) {


		/*--------------------------KEYUPDATE----------------------------*/
		Mkey[2] = (Mkey[2] & 0xf0) | ((Mkey[2] & 0x0f) ^ ((k & 0x1e) >> 1));
		Mkey[1] = (Mkey[1] & 0x7f) | ((Mkey[1] & 0x80) ^ ((k & 0x01) << 7));

		/*---------------------------*/

		c = Mkey[9];
		Mkey[9] = (Mkey[9] & 0x0f) | (((char)SboxInv[(c & 0xf0) >> 4] << 4));

		/*---------------------------*/
		for (j = 0; j < 10; j++) {
			tmpkey[j] = Mkey[j];
		}

		strcpy(tmpkey, Mkey);
		for (j = 0; j < 10; j++) {
			i = (j + 7) % 10;

			Mkey[j] = tmpkey[i];

		}

		for (j = 0; j < 9; j++) {
			tmpkey[j] = (Mkey[j + 1] & 0x1f) << 3;
		}
		tmpkey[9] = (Mkey[0] & 0x1f) << 3;

		for (j = 0; j < 10; j++) {
			Mkey[j] = ((unsigned char)Mkey[j] >> 5) | tmpkey[j];
		}


		/*--------------------------PBOX---------------------------------*/
		for (j = 0; j < 8; j++) {
			ptexttmp[j] = ptext[j];
		}
		m = 0x00;
		for (i = 0; i < 8; i++) {
			c = 0x00;
			for (j = 0; j < 8; j++, m += 16) {
				if (m >= 64) m = m % 64 + 1;
				b2 = i * 8 + j;
				B1 = m / 8;
				c = c | (((ptexttmp[B1] & (0x01 << m % 8)) >> (m % 8)) << j);
			}
			ptext[i] = (char)c;
		}


		/*---------------------------------SBOX--------------------------------------*/
		for (j = 0; j < 8; j++) {
			ptext[j] = (SboxInv[(int)((ptext[j] & 0xf0) >> 4)] << 4) | (SboxInv[(int)(ptext[j] & 0x0f)]);
		}

		/*-----------------------------ADDROUNDKEY-------------------------------*/

		for (j = 0; j < 8; j++) {
			Rkey[j] = Mkey[2 + j];
		}

		for (j = 0; j < 8; j++) {
			ptext[j] = Rkey[j] ^ ptext[j];
		}

	}

	for (j = 0; j < 8; j++) {
		printf("%x ", (unsigned char)ptext[j]);
	}



	return 0;
}