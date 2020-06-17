UNAME_S=$(shell uname -s)
EMACS_ROOT ?= ../..

EMACS ?= emacs
CC      = gcc
LD      = gcc
CFLAGS = -std=gnu99 -ggdb3 -Wall -fPIC -I$(EMACS_ROOT)/src

.PHONY : format clean test

all: openssl-bn-core.so

openssl-bn-core.so: openssl-bn-core.o
	$(LD) -shared -o $@ $^ -lcrypto

openssl-bn-core.o: openssl-bn-core.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.so

format:
	clang-format -i *.c

test:
	$(EMACS) -Q -batch -L . \
		-l test/test.el \
		-f ert-run-tests-batch-and-exit
