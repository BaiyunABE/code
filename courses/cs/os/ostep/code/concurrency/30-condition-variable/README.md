### Condition Variable

#### Introduction
Condition Variable is a queue of thread
- Thread use `wait` to add itself to the queue
- Thread use `signal` to wake one or more thread in the queue
- Hold the lock when calling signal or wait

#### Producer-Consumer Problem
- Use `while` but `if` when checking condition variable in multi-thread program

```c
void* producer(void*) {
	for (;;) {
		lock();
		while (cnt == MAX)
			wait(&empty);
		put(i);
		signal(&fill);
		unlock();
	}
}

void* consumer(void*) {
	for (;;) {
		lock();
		while (cnt == 0)
			wait(&fill);
		get();
		signal(&empty);
		unlock();
	}
}
```

#### Covering Condition
- Thread use `broadcast` to wake all thread in the queue
