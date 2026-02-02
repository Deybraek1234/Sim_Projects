CC=g++
TARGET=game

SRC_DIR=src
INC_DIR=include

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

CCFLAGS = $(shell pkg-config --cflags sdl3) -I$(INC_DIR) -g -fsanitize=address
LDFLAGS = -lSDL3 -lSDL3_ttf

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(SOURCES) $(CCFLAGS) $(LDFLAGS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(TARGET)