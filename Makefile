CC=gcc
CFLAGS=-Wall -Wextra -std=c99

SRCS=main.c utils.c link.c cross.c print.c checkwin.c init.c
OBJS=$(SRCS:.c=.o)
TARGET=project

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
