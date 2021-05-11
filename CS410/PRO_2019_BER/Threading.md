
# Primitive

- Mutex
	- Lock und Unlock
	- Es kann nur ein Thread den Lock halten

- Event
	- Signal und Wait
	- Mehere Threads können warten und wenn ein anderer Thread singal 
	  aufruft werden alle wartenden aufgeweckt.

- Semphore
	- Increment/Decrement
	- So lange der Counter großer 0 ist blockiert Decrement nicht sonst
	  bockiert es bis ein anderer Thread Increment aufruft

- ReadWriteLock/ReadWriteMutex
	- LockRead/UnlockRead und LockWrite/UnlockWrite
	- Mehere Threads können lesen aber wenn einer schreiben will müssen alle anderen Locks gelöst sein


# Complex

- Thread Safe Data
	- Mutex mit generischen Daten

- SPMCQueue
	- Single Producer Multi Consumer Queue

- MPMCQueue
	- Multi Producer Multi Consumer Queue

# Atomics

- 32bit auf 32bit und 64bit auf 64bit groß
- Können in einem Cycle verarbeitet werden
- Increment, Decrement, Add, Sub, And, Or, Xor, Exchange/Set
- Relaxed, Acquire, Release