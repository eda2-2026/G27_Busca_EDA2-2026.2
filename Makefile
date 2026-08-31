CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Iinclude

SRC = src/main.c src/player.c src/decision.c src/story.c src/search.c
OBJ = $(SRC:.c=.o)
TARGET = efeito_borboleta

TEST_SRC = tests/test_search.c src/decision.c src/search.c
TEST_TARGET = tests/test_search

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_SRC)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_SRC)
	./$(TEST_TARGET)

clean:
	rm -f $(OBJ) $(TARGET) $(TARGET).exe $(TEST_TARGET) $(TEST_TARGET).exe
