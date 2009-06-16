//==============================================================================
// Pseudo Random Number Generator: PRNG/FUNC.C
// Part of the Stash project.
//
// Created: 01/14/03
// Updated: 05/28/03
//
// Copyright (C) 2003 Peter Kieltyka <peter_kieltyka@hotmail.com>
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//==============================================================================

#include <stdio.h>
#include <stdlib.h>
#include "prng.h"

void prng_seed(unsigned char digest[16]) {
	init_by_array((unsigned long *)digest, 4);
}

/*void
prng_seed(unsigned long seed) {
	init_genrand(seed);
}*/

unsigned long prng(unsigned long  min, unsigned long  max) {
	return((genrand_int32() % (max-min+1)) + min);
	
	/*
	1 to 10
	j=1+(int) (10.0*rand()/(RAND_MAX+1.0));
	
	*/
}

void prng_array_shuffle(unsigned char *ptr, unsigned int length) {
	unsigned int i=0,randval=0;
	unsigned char tmpval=0;

	for(i=0; i<length; i++) {
		randval = (unsigned int)prng(0, length-1);

		tmpval = ptr[i];
		ptr[i] = ptr[randval];
		ptr[randval] = tmpval;
	}
}

void prng_array_unshuffle(unsigned char *ptr, unsigned int length) {
	int i=0;
	unsigned int randval=0,*randnum=malloc(length * sizeof *randnum);
	unsigned char tmpval=0;

	for(i=0; i<(int)length; i++) {
		randnum[i] = (unsigned int)prng(0, length-1);
	}

	for(i=(int)length-1; i>=0; i--) {
		randval = randnum[i];

		tmpval = ptr[i];
		ptr[i] = ptr[randval];
		ptr[randval] = tmpval;
	}

	free(randnum);
}

/*void
main() {
	int i;
	unsigned char test[10] = {5,4,88,2,111,1,43,2,125,0};

	prng_seed(32423234);

	prng_array_shuffle(test, 10);


	for(i=0; i<10; i++) {
		printf("%d\n", test[i]);
	}
	system("pause");
}*/
