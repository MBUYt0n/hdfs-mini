CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lmicrohttpd

all: restapi pinger

restapi: restapi.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

pinger: pinger.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

.PHONY: clean run

clean:
	rm -f restapi pinger

run: all
	./restapi & sleep 1 && ./pinger
