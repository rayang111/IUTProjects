CC=gcc


A: A.o B1
	$(CC) -o A A.o

B1: B1.o C1 C2
	$(CC) -o B1 B1.o

C1: C1.o
	$(CC) -o C1 C1.o

C2: C2.o
	$(CC) -o C2 C2.o


run:
	A