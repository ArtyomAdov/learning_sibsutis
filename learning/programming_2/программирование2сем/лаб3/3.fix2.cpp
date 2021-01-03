#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int random (int N){ 
	return rand ()%N;
}



int main(){
	int **b, n, *a, i, j, *tmp;
	cout<<"input number of array elements ";
	cin>>n;
	cout<<endl;
	system("CLS");
	a=new int[n];
	if (a==NULL){
		cout<<"error";
		return 1;
	}
	b=new int *[n];
	if (b==NULL){
		cout<<"error";
		return 1;
	}
	cout<<"REMEMBER THIS GUY?"<<endl<<endl;
	for (i=0; i<n; i++){
		a[i]=random (21)-10;
		b[i]=&a[i];
	}
	for (i=0; i<n; i++){
		cout<<a[i]<<"~~~"<<*b[i]<<endl;
	}
	
	for (i=n-1; i>0; i--){
		for (j=0; j<i; j++)
		{
			if (*b[j]>*b[j+1])
			{
				tmp=b[j+1];
				b[j+1]=b[j];
				b[j]=tmp;
			}
		}
	}  
	
	
	cout<<endl<<endl<<endl<<"THIS IS HIM NOW"<<endl<<endl;
	for (i=0; i<n; i++){
		cout<<a[i]<<"~~~"<<*b[i]<<endl;
	}
	cout<<endl<<"FEEL OLD YET?"<<endl;
	delete a;
	delete b;
	a=NULL; b=NULL;
	system ("PAUSE");
	return 0;
}
