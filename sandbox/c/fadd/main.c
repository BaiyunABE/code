#include <stdio.h>
#include <assert.h>

void putuchar(unsigned char c) {
	printf("%02x", c);
	fflush(stdout);
}

int get_bit(unsigned char *p, size_t n) {
/*
	putuchar(n);
	putuchar(n / 8);
	putuchar(n % 8);
	putuchar(p[n / 8]);
*/
	return (p[n / 8] >> (n % 8)) & 0x01;
}

/*
void test() {
	int a = 0xdeadbeef;
	unsigned char *p = (unsigned char *)&a;
	assert(get_bit(p, 0x10) == 1);
	assert(get_bit(p, 0x11) == 0);
	assert(get_bit(p, 0x12) == 1);
	assert(get_bit(p, 0x13) == 1);
	assert(get_bit(p, 0x14) == 0);
	assert(get_bit(p, 0x15) == 1);
	assert(get_bit(p, 0x16) == 0);
	assert(get_bit(p, 0x17) == 1);
}
*/

struct Float {
	int s;
	int exp;
	int fraction;
};

void dump(float f) {
	unsigned u = *(unsigned *)&f;
	struct Float flo;
	flo.s = u >> 31;
	flo.exp = (u >> 23) & 0xff;
	flo.fraction = u & 0x007fffff;
	printf("input:\t\t%f\n", f);
	printf("S:\t\t%d\n", flo.s);
	printf("Exp:\t\t%d\n", flo.exp - 127);
	printf("Fraction:\t%d\n", flo.fraction);
	
}

int main() {
	float f = -1.0;
	unsigned char *p = (unsigned char *)&f;
	for (int i = 31; i >= 0; i--) {
		printf("%d", get_bit(p, i));
	}
	printf("\n");
	dump(f);
	return 0;
}
