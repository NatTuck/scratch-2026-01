
CC := gcc
CFLAGS := -g

SRCS := $(wildcard *.c)
BINS := $(SRCS:.c=)

all: $(BINS)

%: %.c

clean:
	rm -f $(BINS)

.PHONY: clean

