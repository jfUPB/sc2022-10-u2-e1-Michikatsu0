CC = gcc
CFLGAS = -Wall -g

%.o: %.c
	$(CC) $< $(CFLAGS) -c -g -o $@

main: main.o
	$(CC) $(CFLGAS) -o main main.o

clean:
	rm main main.o