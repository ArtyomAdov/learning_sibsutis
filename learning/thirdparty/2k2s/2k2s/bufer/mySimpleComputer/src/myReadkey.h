#ifndef MYREADKEY_H
#define MYREADKEY_H

#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

struct termios stored_settings;

enum keys {
	key_num = 0,
	key_up = 10,
	key_down,
	key_right,
	key_left,
	key_f5,
	key_f6,
	key_l,
	key_s,
	key_r,
	key_tt,
	key_i,
	key_plus,
	key_minus,
	key_other,
	key_q
};

int rk_readkey(enum keys *key);
int rk_mytermsave(void);
int rk_mytermrestore(void);
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);

void set_keypress(void);

#endif
