//==============================================================================
// Stash: DECODE.C
// Part of the Stash project.
//
// Created: 03/01/03
// Updated: 05/28/03
//
// Copyright (C) 2003 Peter Kieltyka
//==============================================================================

#include "stash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "prng/prng.h"
#include "md5/global.h"
#include "md5/md5.h"


/*
d = (d & ~(1 << (7-b))) | ((s & 1) << (7-b));
assigns 'd' the LSB of 's' at bit location 'b' (0 => b <= 7, 0 = LSB)
*/
#define DECODE_BIT(d,s,b) ((d&~(1<<(7-b)))|((s&1)<<(7-b)))


void decode_file(FILE *, FILE *);
int decode_data(unsigned char *, int, unsigned char *, int, int);

float get_speed(clock_t,clock_t);

int decode_steg(char *file_input, char *file_output, unsigned char *key) {
	FILE *fpi, *fpo;
	unsigned char digest[16];
	//clock_t c1, c2;

	// Open files
	if((fpi = fopen(file_input, "rb")) == NULL) {
		fprintf(stderr, "Cannot open input file!\n");
		return(-1);
	}
	if((fpo = fopen(file_output, "wb")) == NULL) {
		fprintf(stderr, "Cannot open output file!\n");
		return(-1);
	}

	// Get MD5 Checksum of key
	MD5String(key, digest);

	// Seed the PRNG with the md5 checksum of the key
	prng_seed(digest);

	// Decode
	//c1 = clock();
	decode_file(fpi, fpo);
	//c2 = clock();
	//printf("%f\n", get_speed(c1,c2));
	//system("PAUSE");


	// Close files
	fclose(fpi);
	fclose(fpo);

	return(0);
}

void decode_file(FILE *fpi, FILE *fpo) {
	size_t n, x;
	unsigned long len;
	unsigned char cont[CONTSIZE], data[DATASIZE];
	struct stash_hdr shdr = {0};

	// Skip restricted area
	(void)fseek(fpi, STARTBYTE, SEEK_SET);

	// Get header
	n = fread(data, 1, sizeof(struct stash_hdr)<<3, fpi);
	decode_data((unsigned char *)&shdr, sizeof(struct stash_hdr), data, (int)n, 0);

	// Decode data
	len = shdr.len;
	while(len > 0) {
		if(len >= DATASIZE)
			x = DATASIZE;
		else
			x = len;

		n = fread(cont, 1, x<<3, fpi);
		decode_data(data, (int)n>>3, cont, (int)n, 1);

		fwrite(data, 1, (int)x, fpo);
		len -= (unsigned long)x;
	}

	return;
}

int decode_data(unsigned char *dst, int dst_len, 
				unsigned char *src, int src_len, int rand)
{
	int i, b, x;

	if((dst_len<<3) != src_len)
		return(-1);

	// rand
	if(rand == 1)
		prng_array_unshuffle(src, (unsigned int)src_len);

	// Set destination bits
	x=0;
	memset(dst, 0, dst_len);
	for(i=0; i<dst_len; i++) {
		for(b=0; b<8; b++) {
			dst[i] = DECODE_BIT(dst[i], src[x], b);
			x++;
		}
	}

	return(0);
}
