CC=g++ -std=c++11
CFLAGS=-Wall -g -Wno-unused-variable -pthread
LDFLAGS=-lglfw -lglew -lfreetype -framework OpenGL
OPTS = -I"../../include" -L"/usr/lib" /usr/local/include/irrKlang/bin/macosx-gcc/libIrrKlang.dylib -pthread


#recursivly finds all cpp files in src
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
ALL_CPP := $(call rwildcard,src/,*.cpp)

all: app

app: $(ALL_CPP)
	$(CC) $(CFLAGS) -o $@ $^ $(OPTS) $(LDFLAGS)

clean:
	$(RM) app
	$(RM) *.o