CC=g++
CFLAGS=-std=c++11 -c
LDFLAGS=-lglfw -lglew -framework OpenGL

all: main

main: main.o shader.o scene.o window.o objects.o camera.o libraries.o
	$(CC) *.o -o main $(LDFLAGS)

main.o: *.cpp
	$(CC) *.cpp $(CFLAGS)

camera.o: camera/*.cpp camera/*.h
	$(CC) camera/camera.cpp $(CFLAGS)

objects.o: objects/*.cpp objects/*.h
	$(CC) objects/*.cpp $(CFLAGS)

window.o: window/*.cpp window/*.h
	$(CC) window/*.cpp $(CFLAGS)

shader.o: shaders/*.cpp shaders/*.h
	$(CC) shaders/*.cpp $(CFLAGS)

scene.o: scene/*.cpp scene/*.h
	$(CC) scene/*.cpp $(CFLAGS)

libraries.o: ../libraries/imgui/*.cpp ../libraries/imageLoading/*.cpp
	$(CC) ../libraries/imgui/*.cpp ../libraries/imageLoading/*.cpp $(CFLAGS)

clean: 
	$(RM) *.o 
	$(RM) main
	$(RM) imgui.ini