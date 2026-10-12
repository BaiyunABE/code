### Semaphore

#### Introduction
- Semaphore is an object with one integer value
- Use `wait` and `post` to operate semaphore
- When the value is negative, its magnitude represents the number of waiting threads

```c
#include <semaphore.h>
sem_t s;
sem_init(&s, 0, 1);

int sem_wait(sem_t* s) {
	decrement the value of semaphore s by one
	wait if value of semaphore s is negative
}

int sem_post(sem_t* s) {
	increment the value of semaphore s by one
	if there are one or more threads waiting, wake one
}
```

#### Binary Semaphore(Lock)
- Initialize semaphore to 1

```c
sem_t m;
sem_init(&m, 0, 1); // initialize semaphore to 1

sem_wait(&m);
// critical section here
sem_post(&m);
```

#### Condition Variable
- Initialize semaphore to 0

```c
sem_t s;

void* child(void*) {
	printf("child\n");
	sem_post(&s); // signal here: child is done
	return NULL;
}

int main() {
	sem_init(&s, 0, 0); // initialize semaphore to 0
	printf("parent: begin\n");
	pthread_t c;
	Pthread_create(c, NULL, child, NULL);
	sem_wait(&s); // wait here for child
	printf("parent: end\n");
	return 0;
}
```

#### Producer-Consumer Problem
```c
sem_t empty;
sem_t full;
sem_t mutex;

void* producer() {
	for (;;) {
		sem_wait(&empty);
		sem_wait(&mutex);
		put(i);
		sem_post(&mutex);
		sem_post(&full);
	}
}

void* consumer() {
	for (;;) {
		sem_wait(&full);
		sem_wait(&mutex);
		get();
		sem_post(&mutex);
		sem_post(&empty);
	}
}

int main() {
	// ...
	sem_init(&empty, 0, MAX);	// MAX buffers are empty to begin with...
	sem_init(&full, 0, 0);		// ... and 0 are full
	sem_init(&mutex, 0, 1);		// mutex=1 because it is a lock
	// ...
}
```

#### Reader-Writer Lock
- Readers should wait writers, but need not wait other writers
- Writers should wait readers, and should wait other writers
- Let readers not wait other readers, increase concurrency

```c
typedef struct _rwlock_t {
	sem_t lock;		// binary semaphore (basic lock)
	sem_t writelock;	// used to allow ONE writer or MANY readers
	int readers;		// count of readers reading in critical section
} rwlock_t;

void rwlock_init(rwlock_t* rw) {
	rw->readers = 0;
	sem_init(&rw->lock, 0, 1);
	sem_init(&rw->writelock, 0, 1);
}

void rwlock_acquire_readlock(rwlock_t* rw) {
	sem_wait(&rw->lock);
	rw->readers++;
	if (rw->readers == 1)
		sem_wait(&rw->writelock); // first reader acquires writelock
	sem_post(&rw->lock);
}

void rwlock_release_readlock(rwlock_t* rw) {
	sem_wait(&rw->lock);
	rw->readers--;
	if (rw->readers == 0)
		sem_post(&rw->writelock); // last reader releases writelock
	sem_post(&rw->lock);
}

void rwlock_acquire_writelock(rwlock_t* rw) {
	sem_wait(&rw->writelock);
}

void rwlock_release_writelock(rwlock_t* rw) {
	sem_post(&rw->writelock);
}
```

#### Dining Philosopher’s Problem
- Deadlock: every philosopher get the fork on the left
- Method: let one philosopher get the fork on the right first

```c
void getforks() {
	if (p == 4) {
		sem_wait(forks[right(p)]);
		sem_wait(forks[left(p)]);
	} else {
		sem_wait(forks[left(p)]);
		sem_wait(forks[right(p)]);
	}
}
```

#### Zemaphore(My Semaphore)
- Different from Dijkstra's, value will not be negative
- Easy to achieve
- Used in Linux

```c
typedef struct _Zem_t {
	int value;
	pthread_cond_t cond;
	pthread_mutex_t lock;
} Zem_t;

// only one thread can call this
void Zem_init(Zem_t *s, int value) {
	s->value = value;
	Cond_init(&s->cond);
	Mutex_init(&s->lock);
}

void Zem_wait(Zem_t *s) {
	Mutex_lock(&s->lock);
	while (s->value <= 0)
		Cond_wait(&s->cond, &s->lock);
	s->value--;
	Mutex_unlock(&s->lock);
}

void Zem_post(Zem_t *s) {276
	Mutex_lock(&s->lock);
	s->value++;
	Cond_signal(&s->cond);
	Mutex_unlock(&s->lock);
}
```
