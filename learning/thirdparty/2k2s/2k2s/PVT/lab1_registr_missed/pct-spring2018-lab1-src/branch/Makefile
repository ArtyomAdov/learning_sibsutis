branch := branch
branch_objs := branch.o hpctimer.o

CC := gcc
CFLAGS := -O0 -Wall -g -std=c11
LDFLAGS :=

.PHONY: all clean

all: $(branch)

$(branch): $(branch_objs)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

branch.o: branch.c
hpctimer.o: hpctimer.c hpctimer.h

clean:
	@rm -rf *.o $(branch)
