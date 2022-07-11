CC=gcc
CFLAGS=-c -Wall -Werror -Wextra

cipher: cipher.o
	$(CC) cipher.o -o ../build/cipher

cipher.o: cipher.c
	$(CC) $(CFLAGS) cipher.c

clean:
	rm -rf *.o
	rm -rf ../build/cipher

