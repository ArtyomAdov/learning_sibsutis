#include <iostream>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <conio.h>
#include <cmath>
#include <string>
#include "myclass.cpp"

using namespace std;

int main(){
	int d=1280, ch=864, page=0, i;
	model solar;
	char *s1="Sun";
	star Sun(15, 0, 14, 25,s1, d, ch);
	s1="Mer";
	planet Mer(50, 30, 6.5, 7, 2, s1, d, ch, false);
	s1="Ven";
	planet Ven(75, 45, 5, 12, 4, s1, d, ch, false);
	s1="Earth";
	planet Ear(100, 60, 3.5, 2, 4, s1, d, ch, false);
	s1="Mars";
	planet Mars(137, 82, 2.5, 4, 3, s1, d, ch, false);
	s1="Jup";
	planet Jup(312, 187, 0.5, 6, 10, s1, d, ch, false);
	s1="Sat";
	planet Sat(412, 287, 0.15, 13, 9, s1, d, ch, true);
	s1="Uran";
	planet Uran(512, 387, 0.1, 9, 7, s1, d, ch, false);
	s1="Nep";
	planet Nep(612, 487, 0.1, 3, 7, s1, d, ch, false);
	kam asteroid1(212, 137, 1, d, ch, 300, 20, -20);
	setlocale(LC_ALL, "Russian");
	initwindow(d,ch);
	while(!kbhit()){
		setactivepage(page);
		setvisualpage(1-page);
		cleardevice();
		solar.show(&Sun);
		solar.show(&Mer);
		solar.show(&Ven);
		solar.show(&Ear);
		solar.show(&Mars);
		solar.show(&Jup);
		solar.show(&Sat);
		solar.show(&Uran);
		solar.show(&Nep);
		solar.show(&asteroid1);
		
		solar.dvij(&Mer);
		solar.dvij(&Ven);
		solar.dvij(&Ear);
		solar.dvij(&Mars);
		solar.dvij(&Jup);
		solar.dvij(&Sat);
		solar.dvij(&Uran);
		solar.dvij(&Nep);
		solar.dvij(&asteroid1);
		page=1-page;
		delay(10);
	}
	closegraph();
	system("PAUSE");
	return 0;
}
