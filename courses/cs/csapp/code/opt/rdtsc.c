#include <stdio.h>
#include <stdint.h>

static inline uint64_t rdtsc(void)
{
	uint32_t lo, hi;
	__asm__ volatile("rdtsc" : "=a"(lo), "=d"(hi));
	return ((uint64_t)hi << 32) | lo;
}

void psum1(float a[], float p[], long n)
{
	long i;
	p[0] = a[0];
	for (i = 1; i < n; i++)
		p[i] = p[i - 1] + a[i];
}

void psum2(float a[], float p[], long n)
{
	long i;
	p[0] = a[0];
	for (i = 1; i < n - 1; i += 2)
	{
		float mid_val = p[i - 1] + a[i];
		p[i] = mid_val;
		p[i + 1] = mid_val + a[i + 1];
	}

	if (i < n)
		p[i] = p[i - 1] + a[i];
}

#define K 200
#define WARMUP 10

int main()
{
	float a[K];
	float p[K];

	int x[K];
	int y[K];

	for (int i = 0; i < K; i++)
	{
		a[i] = 1.0f;
		p[i] = 0.0f;
	}

	for (int w = 0; w < WARMUP; w++)
	{
		psum2(a, p, K);
	}

	for (int i = 0; i < K; i++)
	{
		uint64_t start = rdtsc();
		psum2(a, p, i);
		uint64_t end = rdtsc();
		int cycles = end - start;
		x[i] = i;
		y[i] = cycles;
		printf("%d\n", cycles);
	}

	return 0;
}
