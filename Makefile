CC = gcc
CFLAGS = -Wall -g

TARGETS = ping pong

all: $(TARGETS)

ping: ping.c
	$(CC) $(CFLAGS) -o ping ping.c

pong: pong.c
	$(CC) $(CFLAGS) -o pong pong.c

run:
	@echo "Starting processes..."
	gnome-terminal -- ./pong
	gnome-terminal -- ./ping
	@echo "The processes are running."

clean:
	rm -f $(TARGETS)
