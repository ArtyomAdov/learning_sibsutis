loop := loop
loop_objs := loop.o hpctimer.o

CC := gcc
CFLAGS := -O0 -Wall -g -std=c11
LDFLAGS :=

.PHONY: all clean

all: $(loop)

$(loop): $(loop_objs)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

loop.o: loop.c
hpctimer.o: hpctimer.c hpctimer.h

clean:
	@rm -rf *.o $(loop)
