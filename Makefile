CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -Iinclude

TARGET = build/server

SRC = main.c \
      src/server/server.c \
      src/client/client.c

OBJ = $(SRC:%.c=build/%.o)


$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)


build/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf build


run: $(TARGET)
	./$(TARGET)


.PHONY: clean run
