CC = gcc
LIBS = -lstdc++ -lglfw -lglew

make:
	$(CC) *.cpp $(LIBS) -framework OpenGL
