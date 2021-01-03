#include "myReadkey.h"

int rk_readkey(enum keys *key)
{
	rk_mytermregime(1, 0, 1, 1, 1);

	char buf[8] = { 0 };

	read(STDIN_FILENO, buf, 8);

	if (strcmp(buf, "\E[A") == 0) {
		*key = key_up;
	} else if (strcmp(buf, "\E[B") == 0) {
		*key = key_down;
	} else if (strcmp(buf, "\E[C") == 0) {
		*key = key_right;
	} else if (strcmp(buf, "\E[D") == 0) {
		*key = key_left;
	} else if (strcmp(buf, "\E[15~") == 0) {
		*key = key_f5;
	} else if (strcmp(buf, "\E[17~") == 0) {
		*key = key_f6;
	} else if (buf[0] == 'l') {
		*key = key_l;
	} else if (buf[0] == 's') {
		*key = key_s;
	} else if (buf[0] == 'r') {
		*key = key_r;
	} else if (buf[0] == 't') {
		*key = key_tt;
	} else if (buf[0] == 'i') {
		*key = key_i;
	} else if (buf[0] >= '0' && buf[0] <= '9') {
		*key = buf[0] - 48;
	} else if (buf[0] == 'q') {
		*key = key_q;
	} else if (buf[0] == '+') {
		*key = key_plus;
	} else if (buf[0] == '-') {
		*key = key_minus;
	} else {
		*key = key_other;
	}

	rk_mytermrestore();

	return 0;
}

int rk_mytermsave(void)
{
	if (tcgetattr(0, &stored_settings)) {
		return 1;
	}
	
	return 0;
}

int rk_mytermrestore(void)
{
	if (tcsetattr(0, TCSANOW, &stored_settings)){
		return 1;
	}

	return 0;
}

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)
{
	struct termios new_settings;
	rk_mytermsave();
	new_settings = stored_settings;

	if (regime == 1) {
		new_settings.c_lflag &= (~ICANON);

		if (sigint == 1) {
			new_settings.c_lflag &= (~ISIG);
		} else if (sigint == 0) {
			new_settings.c_lflag |= ISIG;
		}

		if (echo == 1) { 
			new_settings.c_lflag &= (~ECHO);
		} else if (echo == 0) {
			new_settings.c_lflag |= ECHO;
		}

		new_settings.c_cc[VMIN] = vmin;		
		new_settings.c_cc[VTIME] = vtime;
	} else if (regime == 0) {
		new_settings.c_lflag |= ICANON;
	}

	tcsetattr(0, TCSANOW, &new_settings);
	return 0;
}
