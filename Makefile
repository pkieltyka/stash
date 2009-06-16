CC = gcc
CFLAGS1 = -O2 -Wall
STRIP = strip

default:
	@echo "-------------------------------"
	@echo "run: make stash"
	@echo "-------------------------------"


clean:
	/bin/rm -f stash

stash:	clean cc1 fin

cc1:
	$(CC) $(CFLAGS1) -o stash main.c encode.c decode.c prng/prng.c prng/func.c md5/md5c.c md5/func.c

fin:
	$(STRIP) stash
