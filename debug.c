#include <stdio.h>
#include <time.h>

void print_byte(unsigned char);
void print_num_byte(unsigned char *, int);
float get_speed(clock_t, clock_t);

void
print_byte(unsigned char byte) {
	int k;

	for(k=0; k<8; k++) {
		printf("%d", (byte >> (7-k)) & 1);
	}
	printf(" ");
}

void
print_num_byte(unsigned char *byte, int len) {
	int i,x;

	x=0;
	for(i=0; i<len; i++) {
		print_byte(byte[i]);
		x++;

		if(x == 8) {
			printf("\n");
			x=0;
		}
	}
}

float
get_speed(clock_t c1, clock_t c2) {
	return(((float)(c2-c1)) / ((float)CLOCKS_PER_SEC));
}