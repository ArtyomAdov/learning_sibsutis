#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class A{
	private:
		int Age;
		int Rost;
	public:
		A(int Age, int Rost){
			this->Age=Age;
			this->Rost=Rost;
			cout<<"Constructing class A-Parametr"<<endl;
		}	
		A(){
			Age=25;
			Rost=175;
			cout<<"Constructing class A-NoParametr"<<endl;
		}
		void setAge(int Age){
			Age=Age;
		}
		int getAge(){
			return Age;
		}
		void setRost(int Rost){
			Rost=Rost;
		}
		int getRost(){
			return Rost;
		}
		void Method(){
			cout<<"Rost"<<":"<<Rost<<endl;
			cout<<"Age"<<":"<<Age<<endl;
			cout<<"I am a base class method"<<endl;
		}
		~A(){
			cout<<"Destryct"<<endl;
		}
};
void Funct1(){
	A a1;
	a1.setAge(25);
	a1.setRost(175);
	a1.Method();
	a1.~A();
}
void Funct2(int p1,int p2){
	int per1,per2;
	per1=p1;
	per2=p2;
	A a2{per1,per2};
	a2.Method();
	a2.~A();
}
int main()
{
	Funct1();
	Funct2(25,175);
}
