
# Primitive

- Mutex
	- Lock und Unlock
	- Es kann nur ein Thread den Lock halten

- Event
	- Signal und Wait
	- Mehere Threads k�nnen warten und wenn ein anderer Thread singal 
	  aufruft werden alle wartenden aufgeweckt.

- Semphore
	- Increment/Decrement
	- So lange der Counter gro�er 0 ist blockiert Decrement nicht sonst
	  bockiert es bis ein anderer Thread Increment aufruft

- ReadWriteLock/ReadWriteMutex
	- LockRead/UnlockRead und LockWrite/UnlockWrite
	- Mehere Threads k�nnen lesen aber wenn einer schreiben will m�ssen alle anderen Locks gel�st sein


# Complex

- Thread Safe Data
	- Mutex mit generischen Daten

- SPMCQueue
	- Single Producer Multi Consumer Queue

- MPMCQueue
	- Multi Producer Multi Consumer Queue

# Atomics

- 32bit auf 32bit und 64bit auf 64bit gro�
- K�nnen in einem Cycle verarbeitet werden
- Increment, Decrement, Add, Sub, And, Or, Xor, Exchange/Set
- Relaxed, Acquire, Release