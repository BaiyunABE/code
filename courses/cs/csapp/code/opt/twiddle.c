void twiddle1(long *xp, long *yp)
{
	*xp += *yp;
	*xp += *yp;
}

void twiddle2(long *xp, long *yp)
{
	*xp += 2 * *yp;
}

int twiddle3(int *q, int *p)
{
	int x = 1000;
	int y = 3000;
	*q = y;
	*p = x;
	int t1 = *q;
	return t1;
}
