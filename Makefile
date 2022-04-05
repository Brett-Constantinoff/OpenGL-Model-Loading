
CC=g++ -std=c++11
CFLAGS=-Wall -g -Wno-unused-variable -pthread
LDFLAGS=-lglfw -lglew -framework OpenGL

all: app

app: src/*.cpp src/libs/*.cpp 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


clean:
	$(RM) app
	$(RM) *.o