CXX = gcc

CFLAGS = -c -O0 -Wall -Werror -std=c99 -D_POSIX_C_SOURCE=199309L

FLAGS  =  -O0 -Wall -Werror -std=c99 -D_POSIX_C_SOURCE=199309L

OBJECTS = build/src/main.o build/src/death_arg.o build/src/death_char.o build/src/death_matrix.o build/src/death_file.o

.PHONY: clean all bin build default run

all: bin build bin/key

bin/key: $(OBJECTS)
	$(CXX) $(FLAGS) $(OBJECTS) -o bin/key

build/src/main.o: src/main.c 
	$(CXX) $(CFLAGS) src/main.c -o build/src/main.o

build/src/death_arg.o: src/death_arg.c 
	$(CXX) $(CFLAGS) src/death_arg.c -o build/src/death_arg.o

build/src/death_char.o: src/death_char.c 
	$(CXX) $(CFLAGS) src/death_char.c -o build/src/death_char.o

build/src/death_matrix.o: src/death_matrix.c 
	$(CXX) $(CFLAGS) src/death_matrix.c -o build/src/death_matrix.o

build/src/death_file.o: src/death_file.c 
	$(CXX) $(CFLAGS) src/death_file.c -o build/src/death_file.o

build:
	mkdir -p build/src

bin:
	mkdir -p bin 
	mkdir -p picture

clean:
	-rm -rf build bin picture

run:
	./bin/key 5 2