#ifndef MYREADKEY_H
#define MYREADKEY_H

#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

struct termios stored_settings;

enum keys {
	key_minus = -1,
	key_plus = 1,
	key_enter = 10,
	key_up,
	key_down,
	key_right,
	key_left,
	key_accumulator,
	key_instructionCounter,
	key_load,
	key_save,
	key_run,
	key_step,
	key_reset,
	key_other,
	key_quit,
};

int rk_readkey(enum keys *key);
int rk_mytermsave(void);
int rk_mytermrestore(void);
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);

void set_keypress(void);

#endif
