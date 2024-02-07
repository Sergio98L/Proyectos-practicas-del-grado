CC = gcc
CFLAGS =  -g -Wall
EXECS = clientGame serverGame

all: $(EXECS)

serverGame: game.c serverGame.c  
	$(CC) $(CFLAGS) game.c serverGame.c -lpthread -o serverGame
	
clientGame: game.c clientGame.c  
	$(CC) $(CFLAGS) game.c clientGame.c  -o clientGame
	
clean:
	rm -f  *.o
	rm -f $(EXECS)
