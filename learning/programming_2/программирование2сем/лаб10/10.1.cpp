#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
using namespace std;
int random (int n) {return rand()%10;}
int foo(char c){
	string glasnye("aeiouy");
 	return (string::npos != glasnye.find(c)) ? 1 : 0;
}
int main(){
	char bk, sl[50];
	FILE *gl, *sogl, *sl2;
	int i, z=0;
	setlocale(0,"rus");
	while(z!=1){
		cout<<"vvedite slovo ";
		cin>>sl;
		sl2=fopen("slova.txt","a");
		fprintf(sl2,"%s \n", sl);
		cout<<"zakonchit? 1-yes/0-no"<<endl;
		cin>>z;
		fclose(sl2);
	}
	sl2=fopen("slova.txt","r");
	while(!feof(sl2)){
		gl=fopen("glasnie.txt","a");
		sogl=fopen("soglasnie.txt","a");
		bk=getc(sl2);
		if(foo(bk)==1){
			fscanf(sl2,"%s \n", sl);
			fprintf(gl,"%c%s \n",bk,sl);
		}
		else{
			fscanf(sl2,"%s \n", sl);
			fprintf(sogl,"%c%s \n",bk,sl);
		}
		fclose(gl);
		fclose(sogl);
	}
	fclose(sl2);
	gl=fopen("glasnie.txt","r");
	while(!feof(gl)){
		fscanf(gl,"%s \n", sl);
		cout<<sl<<endl;
	}
	sogl=fopen("soglasnie.txt","r");
	while(!feof(sogl)){
		fscanf(sogl,"%s \n", sl);
		cout<<sl<<endl;;
	}
	return 0;
}
