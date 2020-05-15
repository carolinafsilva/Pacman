.PHONY = all update run clean

CC := c++

LIBS := -lstdc++ -lm -lglfw -lglew -framework OpenGL

SRCS := $(filter-out src/main.cpp, $(wildcard src/*.cpp))
OBJS := $(SRCS:src/%.cpp=build/%.o)

all: build dist dist/pacman update

build:
	mkdir build

build/%.o: src/%.cpp
	$(CC) -c $< -o $@

dist:
	mkdir dist

dist/pacman: src/main.cpp $(OBJS)
	$(CC) $^ -o $@ $(LIBS)

update:
	rsync -rt src/shaders dist
	rsync -rt src/assets dist

run:
	cd dist && ./pacman

clean:
	rm -rvf build dist
