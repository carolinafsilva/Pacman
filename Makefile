.PHONY = all update run clean

CC := clang

CFLAGS := -std=c++11 -O0 -g -I/usr/local/Cellar/freetype/2.10.1/include/freetype2
LIBS := -lstdc++ -lm -lfreetype -lglfw -lglew -framework OpenGL

SRCS := $(filter-out src/main.cpp, $(wildcard src/*.cpp))
OBJS := $(SRCS:src/%.cpp=build/%.o)

all: build dist dist/pacman update

build:
	mkdir build

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

dist:
	mkdir dist

dist/pacman: src/main.cpp $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

update:
	rsync -rt src/shaders dist
	rsync -rt src/assets dist

run:
	cd dist && ./pacman

clean:
	rm -rvf build dist
