#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Food
{
private:
	int pickle;
	int pineapple;
public:
	Food()
	{
	pickle=10;
	pineapple=15;
	}
	int pin(){
		pickle=15;
		return pickle;
	}
	int pinap(){
		pineapple=10;
		return pineapple;
	}
};

int main()
{
	Food foder;
	cout<<foder.pin()<<endl;
	cout<<foder.pinap()<<endl;
}
