CC = gcc
CFLAGS = -Wall -Wextra -std=c11 
LDFLAGS = -lm

SRCS = main.c matrix1.c int.c complex.c io.c complex_main.c 
TARGET = laba2

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean