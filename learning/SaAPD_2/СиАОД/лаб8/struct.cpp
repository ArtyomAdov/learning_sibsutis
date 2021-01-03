#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int n=6;
struct directory
{
	string surname;
	string name;
	long long call;
	int flat;
};
void SortSurname(struct directory Data[],int newsurname[])
{
	for(int i=0,e=i;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(Data[newsurname[j]].surname < Data[newsurname[e]].surname)
			{
				e=j;
			}
		}
		swap(newsurname[i],newsurname[e]);
	}
	for(int i=0;i<n;i++)
	{
		cout<<"  "<<Data[newsurname[i]].surname;
	}
}
void SortFlat(struct directory Data[],int newflat[])
{
	for(int i=0,e=i;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(Data[newflat[j]].flat < Data[newflat[e]].flat)
			{
				e=j;
			}
		}
		swap(newflat[i],newflat[e]);
	}
	for(int i=0;i<n;i++)
	{
		cout<<"  "<<Data[newflat[i]].surname;
		cout<<"  "<<Data[newflat[i]].name;
		cout<<"   "<<Data[newflat[i]].call;
		cout<<"   "<<Data[newflat[i]].flat<<endl;
	}
}
int main()
{	
	struct directory Data[n];
	directory spisokabonentov;
	spisokabonentov.surname="  ";
	spisokabonentov.name=" ";
	spisokabonentov.call=0;
	spisokabonentov.flat=0;
	Data[0]=spisokabonentov;
	
	directory abonentone;
	abonentone.surname="Adov";
	abonentone.name="Artyom";
	abonentone.call=8983100643;
	abonentone.flat=901;
	Data[1]=abonentone;
	
	directory abonenttwo;
	abonenttwo.surname="Zahlevniy";
	abonenttwo.name="Nikita";
	abonenttwo.call=89069108346;
	abonenttwo.flat=901;
	Data[2]=abonenttwo;
	
	directory abonentthree;
	abonentthree.surname="Istomina";
	abonentthree.name="Anna";
	abonentthree.call=89836007818;
	abonentthree.flat=45;
	Data[3]=abonentthree;
	
	directory abonentfour;
	abonentfour.surname="Gromov";
	abonentfour.name="Ivan";
	abonentfour.call=89095218722;
	abonentfour.flat=914;
	Data[4]=abonentfour;
	
	directory abonentfive;
	abonentfive.surname="Kataeva";
	abonentfive.name="Angelina";
	abonentfive.call=89830510891;
	abonentfive.flat=710;
	Data[5]=abonentfive;
	int newsurname[n],newflat[n];
	for(int i=0;i<n;i++)
	{
		newsurname[i]=i;
		newflat[i]=i;
	}
	//SortSurname(Data,newsurname);
	SortFlat(Data,newflat);
}
