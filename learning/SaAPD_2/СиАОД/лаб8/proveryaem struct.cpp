#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int n=5;
struct directory
{
	string surname;
	string name;
	long long call;
	int flat;
};
int main()
{	
	struct directory Data[n];
	directory abonentone;
	abonentone.surname="Adov";
	abonentone.name="Artyom";
	abonentone.call=8983100643;
	abonentone.flat=901;
	Data[0]=abonentone;
	directory abonenttwo;
	abonenttwo.surname="Nikita";
	abonenttwo.name="Zahlevniy";
	abonenttwo.call=89069108346;
	abonenttwo.flat=901;
	Data[1]=abonenttwo;
	directory abonentthree;
	abonentthree.surname="Istomina";
	abonentthree.name="Anna";
	abonentthree.call=89836007818;
	abonentthree.flat=45;
	Data[2]=abonentthree;
	directory abonentfour;
	abonentfour.surname="Ivan";
	abonentfour.name="Gromov";
	abonentfour.call=89095218722;
	abonentfour.flat=914;
	Data[3]=abonentfour;
	directory abonentfive;
	abonentfive.surname="Angelina";
	abonentfive.name="Kataeva";
	abonentfive.call=89830510891;
	abonentfive.flat=710;
	Data[4]=abonentfive;
}
