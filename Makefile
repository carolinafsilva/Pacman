.PHONY = all update run clean

CC := c++

LIBS := -lstdc++ -lm -framework OpenGL -lglfw -lglew

SRCS := $(filter-out src/main.cpp, $(wildcard src/*.cpp))
OBJS := $(SRCS:src/%.cpp=build/objects/%.o)

all: build build/assets build/shaders/ build/objects build/pacman update

build:
	mkdir build

build/assets:
	mkdir build/assets

build/shaders:
	mkdir build/shaders

build/objects:
	mkdir -p build/objects

build/objects/%.o: src/%.cpp
	$(CC) -c $< -o $@

build/pacman: src/main.cpp $(OBJS)
	$(CC) $^ -o $@ $(LIBS)

update:
	rsync -rt src/assets build/
	rsync -rt src/shaders build/

run:
	cd build && ./pacman

clean:
	rm -rvf build
