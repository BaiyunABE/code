#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int* a = malloc(100 * sizeof(int));
	int* p7 = a + 7;
	free(p7);
	return 0;
}
