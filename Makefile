CC = gcc
CFLAGS = -Wall -Wextra -std=c11 
LDFLAGS = -lm

SRCS =  matrix1.c int.c complex.c io.c complex_main.c test.c assert.c
TARGET = laba2

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean