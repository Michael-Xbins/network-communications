SRCS:=$(wildcard *.c)
TARGETS:=$(SRCS:%.c=%)
CC:=gcc
CFLAGS:=-Wall
all:$(TARGET)
	@for i in $(TARGETS);do gcc -o $${i} $${i}.c;done
clean:
	rm $(TARGETS)
