CXX = gcc

OBJECTS_FLAGS = -Wall -Werror -std=c99

COMPILE_FLAGS = -c -Wall -Werror -std=c99

CREATE_PICTURE = gnuplot "picture/drawing.plt"

OPEN_PICTURE = xdg-open picture/out.png

all: default

default: makedirs bin/key

bin/key: build/main.o
	$(CXX) $(OBJECTS_FLAGS) build/main.o -lm -o bin/key

build/main.o: src/main.c
	$(CXX) $(COMPILE_FLAGS) src/main.c -lm -o build/main.o

makedirs:
	mkdir -p bin
	mkdir -p build

clean:
	rm -rf bin
	rm -rf build

run: default
	bin/key
	$(CREATE_PICTURE)
	$(OPEN_PICTURE)
