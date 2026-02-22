CC=g++
TARGET=game

SRC_DIR=src
INC_DIR=include

SOURCES = $(wildcard $(SRC_DIR)/*.cpp $(wildcard $(INC_DIR)/*.h))

CCFLAGS = $(shell pkg-config --cflags sdl3 eigen3) -I$(INC_DIR) -g -O3 -march=x86-64-v3 -fsanitize=address
LDFLAGS = -lSDL3 -lSDL3_ttf

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(SOURCES) $(CCFLAGS) $(LDFLAGS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(TARGET)