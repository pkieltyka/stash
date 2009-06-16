//==============================================================================
// Stash: MAIN.C
// Part of the Stash project.
//
// Created: 01/20/03
// Updated: 05/28/03
//
// Copyright (C) 2003 Peter Kieltyka
//==============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stash.h"

void usage(char *);

void usage(char *program) {
    fprintf(stderr,
		"Stash v%s  -  by: Peter Kieltyka\n"
		"usage: stash [<infile> <outfile> <datafile> <key>] | [<infile> <datafile> <key>]\n\n"
		"examples:\n"
		"     to hide: %s image1.bmp image2.bmp secret.doc 'hello 123'\n"
		"  to extract: %s image2.bmp secret2.doc 'hello 123'\n"
		"\n", VERSION, program, program);

    exit(-1);
}

int main(int argc, char *argv[]) {
    if(argc < 4)
    	usage(argv[0]);
    
    if(argc == 4)
    	decode_steg(argv[1], argv[2], (unsigned char *)argv[3]);
    else
    	encode_steg(argv[1], argv[3], argv[2], (unsigned char *)argv[4]);

	exit(0);
}

