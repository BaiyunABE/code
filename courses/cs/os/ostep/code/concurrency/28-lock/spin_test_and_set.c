struct lock {
	int flag;
};

int TestAndSet(int* old_ptr, int new) {
	int old = *old_ptr; // fetch old value at old_ptr
	*old_ptr = new; // store 'new' into old_ptr
	return old;
}

void init(struct lock* lock) {
	// 0 indicates that lock is available, 1 that it is held
	lock->flag = 0;
}

void lock(struct lock* lock) {
	while (TestAndSet(&lock->flag, 1) == 1)
		; // spin-wait (do nothing)
}

void unlock(struct lock* lock) {
	lock->flag = 0;
}

