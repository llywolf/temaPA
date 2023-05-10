# Copyright Caragia Andrei Bogdan 314AA

CC=gcc
CFLAGS=-g -Wall -Wextra -std=c99

SRCS=$(wildcard *.c)
OBJS=$(SRCS:%.c=%.o)
TARGETS=$(OBJS:%.o=%)


build: $(OBJS)
	$(CC) $(CFLAGS) -o lanParty $(OBJS)

run_vma:build
	./lanParty

clean:
	rm -f $(TARGETS) $(OBJS)

.PHONY: pack clean