.PHONY = all run clean

CC := c++

LIBS := -lstdc++ -lm -framework OpenGL -lglfw -lglew

SRCS := $(filter-out src/main.cpp, $(wildcard src/*.cpp))
OBJS := $(SRCS:src/%.cpp=build/objects/%.o)

all: build build/pacman

build:
	mkdir -p build/objects
	cp -r src/assets build/assets
	cp -r src/shaders build/shaders

build/pacman: src/main.cpp $(OBJS)
	$(CC) $^ -o $@ $(LIBS)

build/objects/%.o: src/%.cpp
	$(CC) -c $< -o $@

run:
	cd build && ./pacman

clean:
	rm -rvf build
