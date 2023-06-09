OBJS    = Ex1.o Ex1a.c
SRC    = %(willcard*.c)
OUT    = ex1
CC     = gcc
FLAGS     = -g -c 
LFLAGS     = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) -lgraph

Ex1.o: Ex1.c
	$(CC) $(FLAGS) Ex1.c

Ex1a.o: Ex1a.c
	$(CC) $(FLAGS) Ex1a.c 




clean:
	rm -f $(OBJS) $(OUT)