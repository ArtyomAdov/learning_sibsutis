#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
using namespace std;
int random (int n) {return rand()%10;}

int main(){
	char insl[50], sl[50];
	FILE *in, *is;
	int i, z=0, j;
	setlocale(0,"rus");
	while(z!=1){
		cout<<"vedite slovo ";
		cin>>sl;
		is=fopen("slova.txt","a");
		fprintf(is,"%s \n", sl);
		cout<<"zakonchit? 1-yes/0-no"<<endl;
		cin>>z;
		fclose(is);
	}
	is=fopen("slova.txt","r");
	while(feof(is)==0){
		in=fopen("invert.txt","a");
		fscanf(is ,"%s \n", sl);
		j=strlen(sl);
		insl[j]='\0';
		for(i=0,j=(strlen(sl)-1);sl[i]!='\0';i++, j--){
			insl[j]=sl[i];
		}
		fprintf(in,"%s\n",insl);
		fclose(in);
	}
	fclose(is);
	in=fopen("invert.txt","r");
	while(!feof(in)){
		fscanf(in,"%s \n", sl);
		cout<<sl<<endl;
	}

}
