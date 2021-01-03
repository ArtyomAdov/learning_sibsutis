#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include "myclass.cpp"

using namespace std;

void FillRand(int A[], int D){
	int a=1, b=10, i;
	srand(time(NULL));
	for(i=0;i<D;i++){
		A[i]=rand()%(b-a+1)+a;
		//A[i]=i+1;
	}
}

void PrintMass(int A[], int D){
	int i;
	cout<<"������ A:"<<endl;
	for(i=0;i<D;i++){
		cout<<A[i]<<" ";
	}
}

int main(){
	int *A, N, i, j=1, k, z, s;
	setlocale(LC_ALL, "Russian");
	cout<<"������� ���-�� ��������� ������: ";
	cin>>N;
	A=new int [N];
	FillRand(A, N);
	ocher H(A,N);
	spisok K(A,N);
	stek G(A,N);
	cout<<"�������� ��� ������: "<<endl;
	cout<<"1) ������"<<endl;
	cout<<"2) �������"<<endl;
	cout<<"3) ����"<<endl;
	cout<<"����: ";
	cin>>s;
	if(s==2){
		while(j!=0){
			z=H.getKol(H);
			cout<<"����:"<<endl;
			cout<<"1. ������� ������"<<endl;
			cout<<"2. �������� ��������"<<endl;
			cout<<"3. ������� ��������� � �� �����"<<endl;
			cout<<"4. ����������� ��������"<<endl;
			cout<<"5. ���������� ��������"<<endl;
			cout<<"0. �����"<<endl;
			cout<<"����: ";
			cin>>j;
			system("CLS");
			while(j<0 || j>5){
				cout<<"����������� ����!"<<endl;
				cout<<"����:"<<endl;
				cout<<"1. ������� ������"<<endl;
				cout<<"2. �������� ��������"<<endl;
				cout<<"3. ������� ��������� � �� �����"<<endl;
				cout<<"4. ����������� ��������"<<endl;
				cout<<"5. ���������� ��������"<<endl;
				cout<<"0. �����"<<endl;
				cout<<"����: ";
				cin>>j;
				system("CLS");
			}
			if(j==1){
				cout<<"������ �����:"<<endl;
				H.List();
			}
			if(j==2){
				try{
					H.del();
					cout<<"������ �����:"<<endl;
					H.List();
				}
				catch(const char *ex){
					cout<<"�� ���������� "<<ex<<endl;
				}
			}
			if(j==3){
				k=spisok::getSum(H);
				i=spisok::getKol(H);
				cout<<"����� �����: "<<k<<endl;
				cout<<"���������� ��������� �����: "<<i<<endl;
			}
			if(j==4){
				try{
					H.peremeshenie(z);
					cout<<"������ �����:"<<endl;
					H.List();
				}
				catch(const char *ex){
					cout<<"�� ���������� "<<ex<<endl;
				}
			}
			if(j==5){
				try{
					H.Addnode();
					cout<<"������ �����:"<<endl;
					H.List();
				}	
				catch(const char *ex){
					cout<<"�� ���������� "<<ex<<endl;
				}
			}	
		}
	}
		if(s==1){
			while(j!=0){
			z=K.getKol(H);
			cout<<"����:"<<endl;
			cout<<"1. ������� ������"<<endl;
			cout<<"2. �������� ��������"<<endl;
			cout<<"3. ������� ��������� � �� �����"<<endl;
			cout<<"4. ����������� ��������"<<endl;
			cout<<"5. ���������� ��������"<<endl;
			cout<<"0. �����"<<endl;
			cout<<"����: ";
			cin>>j;
			system("CLS");
			while(j<0 || j>5){
				cout<<"����������� ����!"<<endl;
				cout<<"����:"<<endl;
				cout<<"1. ������� ������"<<endl;
				cout<<"2. �������� ��������"<<endl;
				cout<<"3. ������� ��������� � �� �����"<<endl;
				cout<<"4. ����������� ��������"<<endl;
				cout<<"5. ���������� ��������"<<endl;
				cout<<"0. �����"<<endl;
				cout<<"����: ";
				cin>>j;
				system("CLS");
			}
			if(j==1){
				cout<<"������ �����:"<<endl;
				K.List();
			}
			if(j==2){
				try{
					K.del(z);
					cout<<"������ �����:"<<endl;
					H.List();
				}
				catch(const char *ex){
					cout<<"�� ���������� "<<ex<<endl;
				}
			}
			if(j==3){
				k=spisok::getSum(H);
				i=spisok::getKol(H);
				cout<<"����� �����: "<<k<<endl;
				cout<<"���������� ��������� �����: "<<i<<endl;
			}
			if(j==4){
				try{
					K.peremeshenie(z);
					cout<<"������ �����:"<<endl;
					K.List();
				}
				catch(const char *ex){
					cout<<"�� ���������� "<<ex<<endl;
				}
			}
			if(j==5){
				try{
					K.Addnode(z);
					cout<<"������ �����:"<<endl;
					K.List();
				}
				catch(const char *ex){
					cout<<"�� ���������� "<<ex<<endl;
				}
			}
		}
	}
	if(s==3){
		while(j!=0){
		z=G.getKol(H);
			cout<<"����:"<<endl;
			cout<<"1. ������� ������"<<endl;
			cout<<"2. �������� ��������"<<endl;
			cout<<"3. ������� ��������� � �� �����"<<endl;
			cout<<"4. ���������� ��������"<<endl;
			cout<<"0. �����"<<endl;
			cout<<"����: ";
			cin>>j;
			system("CLS");
			while(j<0 || j>5){
				cout<<"����������� ����!"<<endl;
				cout<<"����:"<<endl;
				cout<<"1. ������� ������"<<endl;
				cout<<"2. �������� ��������"<<endl;
				cout<<"3. ������� ��������� � �� �����"<<endl;
				cout<<"4. ���������� ��������"<<endl;
				cout<<"0. �����"<<endl;
				cout<<"����: ";
				cin>>j;
				system("CLS");
			}
			if(j==1){
				cout<<"������ �����:"<<endl;
				G.List();
			}
			if(j==2){
				try{
					G.del();
					cout<<"������ �����:"<<endl;
					G.List();
				}
				catch(const char *ex){
					cout<<"�� ���������� "<<ex<<endl;
				}
			}
			if(j==3){
				k=spisok::getSum(H);
				i=spisok::getKol(H);
				cout<<"����� �����: "<<k<<endl;
				cout<<"���������� ��������� �����: "<<i<<endl;
			}
			if(j==4){
				try{
					G.Addnode();
					cout<<"������ �����:"<<endl;
					G.List();
				}
				catch(const char *ex){
					cout<<"�� ���������� "<<ex<<endl;
				}
			}
		}
	}
	system("PAUSE");
	return 0;
}
