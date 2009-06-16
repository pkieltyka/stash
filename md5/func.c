//==============================================================================
// MD5 Handler Functions, based on mddriver.c: MD5/FUNC.C
// Part of the Stash project.
//
// Created: 02/02/03
// Updated: 02/20/03
//
// Copyright (C) 2003 Peter Kieltyka
//==============================================================================

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "global.h"
#include "md5.h"

void MD5String(char *str, unsigned char digest[16]) {
	MD5_CTX context;
	size_t len = strlen(str);

	MD5Init(&context);
	MD5Update(&context, str, (unsigned int)len);
	MD5Final(digest, &context);
}

void MD5File(char *filename, unsigned char digest[16]) {
	FILE *fp;
	MD5_CTX context;
	size_t len;
	unsigned char buffer[1024];

	if((fp = fopen(filename, "rb")) == NULL)
		return;
	else {
		MD5Init(&context);
		while((len = fread(buffer, 1, 1024, fp)))
			MD5Update(&context, buffer, (unsigned int)len);
		MD5Final(digest, &context);

		fclose(fp);
	}
}

void MD5Print(unsigned char digest[16]) {
	unsigned int i;

	for(i=0; i<16; i++)
		printf("%02x", digest[i]);
}

/*
void
main() {
	char *str = "md5 this!";
	unsigned char digest[16];

	MD5String(str, digest);
	MD5Print(digest);
}
*/
