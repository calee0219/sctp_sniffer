CC      = gcc
CFLAGS  = -g -std=c11 -pthread
LD      = ld
LDFLAGS = -lpthread
OFILES  = main.o sctp_client.o sctp_server.o
RUN     = main

%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

all: $(OFILES)
	$(LD) $(LDFLAGS) $(OFILES) -o $(RUN)

clean:
	rm -f $(OFILES)
