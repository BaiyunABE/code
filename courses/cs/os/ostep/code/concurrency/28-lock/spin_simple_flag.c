struct lock {
	int flag;
};

void init(struct lock* mutex) {
	// 0 -> lock is available, 1 -> held
	mutex->flag = 0;
}

void lock(struct lock* mutex) {
	while (mutex->flag == 1)
		; // spin-wait (do nothing)
	mutex->flag = 1;
}

void unlock(struct lock* mutex) {
	mutex->flag = 0;
}

