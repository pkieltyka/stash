//==============================================================================
// Stash: ENCODE.C
// Part of the Stash project.
//
// Created: 01/20/03
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
d = (d & ~1) | (((s >> (7-b)) & 1) & 1);
assigns the LSB of 'd' the bit at location 'b' (0 => b <= 7, 0 = LSB) of byte 's'
*/
#define ENCODE_BIT(d,s,b) ((d&~1)|(((s>>(7-b))&1)&1))


void encode_file(FILE *, FILE *, FILE *);
int encode_data(unsigned char *, int, unsigned char *, int, int);

unsigned long get_max_hide(unsigned long);
unsigned long get_filesize(FILE *);

float get_speed(clock_t,clock_t);


int encode_steg(char *file_cont, char *file_data,
				char *file_output, unsigned char *key)
{
	FILE *fpc, *fpd, *fpo;
	unsigned char digest[16];
	unsigned long max_hide=0;
	//clock_t c1, c2;

	// Open files
	if((fpc = fopen(file_cont, "rb")) == NULL) {
		fprintf(stderr, "Cannot open container file!\n");
		return(-1);
	}
	if((fpd = fopen(file_data, "rb")) == NULL) {
		fprintf(stderr, "Cannot open data file!\n");
		return(-1);
	}
	if((fpo = fopen(file_output, "wb")) == NULL) {
		fprintf(stderr, "Cannot open output file!\n");
		return(-1);
	}

	// Make sure the data will fit in the container
	max_hide = get_max_hide(get_filesize(fpc)-STARTBYTE-(sizeof(struct stash_hdr)*8));
	if(max_hide < get_filesize(fpd)) {
		fprintf(stderr, "Error! Data file cannot fit in %s; %d bytes max!\n",
			file_cont, (int)max_hide);
		return(-1);
	}

	// Get MD5 Checksum of key
	MD5String(key, digest);

	// Seed the PRNG with the md5 checksum of the key
	prng_seed(digest);

	// Encode
	//c1 = clock();
	encode_file(fpc, fpd, fpo);
	//c2 = clock();
	//printf("%f\n", get_speed(c1,c2));
	//system("PAUSE");

	// Close files
	fclose(fpc);
	fclose(fpd);
	fclose(fpo);

	return(0);
}

void encode_file(FILE *fpc, FILE *fpd, FILE *fpo) {
	size_t n, x;
	char cont[CONTSIZE], data[DATASIZE];
	struct stash_hdr shdr = {0};

	// Write restricted area
	n = fread(cont, 1, STARTBYTE, fpc);
	fwrite(cont, 1, (int)n, fpo);

	// Write header
	shdr.len = get_filesize(fpd);
	memset(cont, 0, sizeof(cont));
	n = fread(cont, 1, sizeof(struct stash_hdr)<<3, fpc);
	encode_data(cont, (int)n, (unsigned char *)&shdr, sizeof(struct stash_hdr), 0); 
	fwrite(cont, 1, n, fpo);

	// Write data
	while((n = fread(cont, 1, sizeof(cont), fpc))) {
		if((x = fread(data, 1, n>>3, fpd)) > 0)
			encode_data(cont, (int)x<<3, data, (int)x, 1);

		fwrite(cont, 1, (int)n, fpo);
	}

	return;
}

int encode_data(unsigned char *dst, int dst_len, 
				unsigned char *src, int src_len, int rand)
{
	int i, b, x, srcb_len=src_len<<3;
	unsigned char *srcb = malloc(srcb_len * sizeof *srcb);

	if(dst_len != (src_len<<3))
		return(-1);

	// store bits into srcb
	x=0;
	memset(srcb, 0, srcb_len);
	for(i=0; i<src_len; i++) {
		for(b=0; b<8; b++) {
			srcb[x] = ENCODE_BIT(srcb[x], src[i], b);
			x++;
		}
	}

	// Shuffle bytes randomly if necessary
	if(rand == 1)
		prng_array_shuffle(srcb, (unsigned int)srcb_len);

	// Set destination bits
	for(i=0; i<dst_len; i++) {
		dst[i] = ENCODE_BIT(dst[i], srcb[i], 7);
	}

	free(srcb);
	return(0);
}


unsigned long get_max_hide(unsigned long fsize) {
	return((fsize)/8);
}

unsigned long get_filesize(FILE *fp) {
	fpos_t pos;
	unsigned long fsize;

	fgetpos(fp, &pos);

	(void)fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);

	fsetpos(fp, &pos);

	return(fsize);
}
