struct lock {
	int flag;
};

int CompareAndSwap(int* ptr, int expected, int new) {
	int actual = *ptr;
	if (actual == expected)
		*ptr = new;
	return actual;
}

void init(struct lock* lock) {
	// 0 indicates that lock is available, 1 that it is held
	lock->flag = 0;
}

void lock(struct lock* lock) {
	while (CompareAndSwap(&lock->flag, 0, 1) == 1)
		;
}

void unlock(struct lock* lock) {
	lock->flag = 0;
}

