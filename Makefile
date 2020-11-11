CC=gcc
CC_args=-Wall -g -lm

all: client server

client: client.c
		$(CC) client.c -o client $(CC_args)

server: server.c
		$(CC) server.c -o server $(CC_args)

clean:
	rm -f client server

.PHONY: all clean