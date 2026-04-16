CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
LIBS = -lcurl -lssl -lcrypto -lz -lcjson
SRC = src/main.c src/parser.c src/process.c
OUT = src/main

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LIBS)

clean:
	rm -f $(OUT)
