#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE* fin = fopen("file.in", "r");
	FILE* fout = fopen("file.out", "w");
	if (fin == NULL || fout == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	int V, N;
	if (fscanf(fin, "%d %d", &V, &N) != 2) {
		fprintf(stderr, "cannot read V and N\n");
		exit(EXIT_FAILURE);
	}

	int* a = (int*)malloc((V + 1) * sizeof(int));
	if (a == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	memset(a, 0, (V + 1) * sizeof(int));

	while (N--) {
		int c, w;
		if (fscanf(fin, "%d %d", &c, &w) != 2) {
			fprintf(stderr, "cannot read c and w\n");
			exit(EXIT_FAILURE);
		}

		for (int i = V; i >= 0; i--) {
			if (c <= i && a[i] < a[i - c] + w) {
				a[i] = a[i - c] + w;
			}
		}
	}

	fprintf(fout, "%d\n", a[V]);
	return EXIT_SUCCESS;
}
