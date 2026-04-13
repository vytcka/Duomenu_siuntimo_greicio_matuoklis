CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LIBS = -lcjson -lcurl

SRC = src/main.c src/parser.c src/speedtest.c src/process.c
OUT = speedtest

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LIBS)

clean:
	rm -f $(OUT)
