int flag[2];
int turn;

void init() {
	flag[0] = flag[1] = 0; // 1->thread wants to grab lock
	turn = 0; // whose turn? (thread 0 or 1?)
}

void lock() {
	flag[self] = 1; // self: thread ID of caller
	turn = 1 - self; // make it other thread's turn
	while (flag[1 - self] == 1 && turn == 1 - self)
		; // spin-wait
}

void unlock() {
	flag[self] = 0; // simple undo your intent
}
/*
flag[other] == 0 or turn == self
	    init  0,0,0
	0   lock  1,0,1  0 lock
	1   lock  1,1,0  1 wait
	0 unlock  0,1,0  1 lock
	
*/
