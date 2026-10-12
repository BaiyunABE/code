#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define N 32

int a[N];
int b[N];
int c[N];
int d[N];
int q[N];

void init()
{
	for (int i = 0; i < N; i++) {
		a[i] = i;
		b[i] = i + i % 5;
		c[i] = i;
		d[i] = 0;
		q[i] = 0;
	}
}

void calc1()
{
	for (int i = 0; i < N; i++) {
		d[i] = a[i] * (b[i] - c[i]);
	}
}

void calc2()
{
	for (int i = 0; i < N; i++) {
		q[i] = b[i] - c[i];
	}
	for (int i = 0; i < N; i++) {
		d[i] = a[i] * q[i];
	}
}

static inline uint64_t get_time_ns() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000 + ts.tv_nsec;
}

void test(void(*func)())
{
	uint64_t start = get_time_ns();
	func();
	uint64_t end = get_time_ns();
	double time_used = (double)(end - start) / CLOCKS_PER_SEC;
	printf("run time：%lu ns\n", end - start);
}

void use_d()
{
	int sum = 0;
	for (int i = 0; i < N; i++) {
		sum += d[i];
	}
	printf("sum = %d\n", sum);
}

int main()
{
	init();
	test(calc1);
	use_d();	
	init();
	test(calc2);
	use_d();	
	return 0;
}

