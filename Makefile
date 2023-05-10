# Copyright Caragia Andrei Bogdan 314AA

CC=gcc
CFLAGS=-g -Wall -Wextra -std=c99

SRCS=$(wildcard *.c)
OBJS=$(SRCS:%.c=%.o)
TARGETS=$(OBJS:%.o=%)


build: $(OBJS)
	$(CC) $(CFLAGS) -o lanparty $(OBJS)

run_vma:build
	./lanparty

clean:
	rm -f $(TARGETS) $(OBJS)

.PHONY: pack clean