
int atomicIncrement(int *var){
	int tmp = *var;
	*var = tmp + 1;
	returm tmp;
}


struct lock_s {
	int ticketNumber;
	int turnNumber;
}

void init(struct lock_s lock){
	lock.ticketNumber=0;
	lock.turnNumber=0;
}

void lock(struct lock_s lock){
	int turn=atomicIncrement(&lock.ticketNumber);
	while(turn!=lock.ticketNumber);
}

void unlock(struct lock_s lock){
	atomicIncrement(&lock.turnNumber);
}

