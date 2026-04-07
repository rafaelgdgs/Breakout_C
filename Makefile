TARGET = Breakout

CC = gcc
LD_FLAGS = -lraylib -lm

C_SOURCE=$(wildcard *.c)

OBJ = $(C_SOURCE:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LD_FLAGS) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $<

clean:
	rm -rf $(TARGET) $(OBJ)

run: all
	./$(TARGET)
