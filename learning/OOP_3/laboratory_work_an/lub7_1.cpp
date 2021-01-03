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
	cout<<"Массив A:"<<endl;
	for(i=0;i<D;i++){
		cout<<A[i]<<" ";
	}
}

int main(){
	int *A, N, i, j=1, k, z, s;
	setlocale(LC_ALL, "Russian");
	cout<<"Введите кол-во элементов списка: ";
	cin>>N;
	A=new int [N];
	FillRand(A, N);
	ocher H(A,N);
	spisok K(A,N);
	stek G(A,N);
	cout<<"Выберите тип данных: "<<endl;
	cout<<"1) Список"<<endl;
	cout<<"2) Очередь"<<endl;
	cout<<"3) Стек"<<endl;
	cout<<"Ввод: ";
	cin>>s;
	if(s==2){
		while(j!=0){
			z=H.getKol(H);
			cout<<"Меню:"<<endl;
			cout<<"1. Вывести список"<<endl;
			cout<<"2. Удаление элемента"<<endl;
			cout<<"3. Подсчёт элементов и их суммы"<<endl;
			cout<<"4. Перемещение элемента"<<endl;
			cout<<"5. Добавление элемента"<<endl;
			cout<<"0. Выход"<<endl;
			cout<<"Ввод: ";
			cin>>j;
			system("CLS");
			while(j<0 || j>5){
				cout<<"Некоректный ввод!"<<endl;
				cout<<"Меню:"<<endl;
				cout<<"1. Вывести список"<<endl;
				cout<<"2. Удаление элемента"<<endl;
				cout<<"3. Подсчёт элементов и их суммы"<<endl;
				cout<<"4. Перемещение элемента"<<endl;
				cout<<"5. Добавление элемента"<<endl;
				cout<<"0. Выход"<<endl;
				cout<<"Ввод: ";
				cin>>j;
				system("CLS");
			}
			if(j==1){
				cout<<"Список равен:"<<endl;
				H.List();
			}
			if(j==2){
				try{
					H.del();
					cout<<"Список равен:"<<endl;
					H.List();
				}
				catch(const char *ex){
					cout<<"Мы обнаружили "<<ex<<endl;
				}
			}
			if(j==3){
				k=spisok::getSum(H);
				i=spisok::getKol(H);
				cout<<"Сумма равна: "<<k<<endl;
				cout<<"Количество элементов равно: "<<i<<endl;
			}
			if(j==4){
				try{
					H.peremeshenie(z);
					cout<<"Список равен:"<<endl;
					H.List();
				}
				catch(const char *ex){
					cout<<"Мы обнаружили "<<ex<<endl;
				}
			}
			if(j==5){
				try{
					H.Addnode();
					cout<<"Список равен:"<<endl;
					H.List();
				}	
				catch(const char *ex){
					cout<<"Мы обнаружили "<<ex<<endl;
				}
			}	
		}
	}
		if(s==1){
			while(j!=0){
			z=K.getKol(H);
			cout<<"Меню:"<<endl;
			cout<<"1. Вывести список"<<endl;
			cout<<"2. Удаление элемента"<<endl;
			cout<<"3. Подсчёт элементов и их суммы"<<endl;
			cout<<"4. Перемещение элемента"<<endl;
			cout<<"5. Добавление элемента"<<endl;
			cout<<"0. Выход"<<endl;
			cout<<"Ввод: ";
			cin>>j;
			system("CLS");
			while(j<0 || j>5){
				cout<<"Некоректный ввод!"<<endl;
				cout<<"Меню:"<<endl;
				cout<<"1. Вывести список"<<endl;
				cout<<"2. Удаление элемента"<<endl;
				cout<<"3. Подсчёт элементов и их суммы"<<endl;
				cout<<"4. Перемещение элемента"<<endl;
				cout<<"5. Добавление элемента"<<endl;
				cout<<"0. Выход"<<endl;
				cout<<"Ввод: ";
				cin>>j;
				system("CLS");
			}
			if(j==1){
				cout<<"Список равен:"<<endl;
				K.List();
			}
			if(j==2){
				try{
					K.del(z);
					cout<<"Список равен:"<<endl;
					H.List();
				}
				catch(const char *ex){
					cout<<"Мы обнаружили "<<ex<<endl;
				}
			}
			if(j==3){
				k=spisok::getSum(H);
				i=spisok::getKol(H);
				cout<<"Сумма равна: "<<k<<endl;
				cout<<"Количество элементов равно: "<<i<<endl;
			}
			if(j==4){
				try{
					K.peremeshenie(z);
					cout<<"Список равен:"<<endl;
					K.List();
				}
				catch(const char *ex){
					cout<<"Мы обнаружили "<<ex<<endl;
				}
			}
			if(j==5){
				try{
					K.Addnode(z);
					cout<<"Список равен:"<<endl;
					K.List();
				}
				catch(const char *ex){
					cout<<"Мы обнаружили "<<ex<<endl;
				}
			}
		}
	}
	if(s==3){
		while(j!=0){
		z=G.getKol(H);
			cout<<"Меню:"<<endl;
			cout<<"1. Вывести список"<<endl;
			cout<<"2. Удаление элемента"<<endl;
			cout<<"3. Подсчёт элементов и их суммы"<<endl;
			cout<<"4. Добавление элемента"<<endl;
			cout<<"0. Выход"<<endl;
			cout<<"Ввод: ";
			cin>>j;
			system("CLS");
			while(j<0 || j>5){
				cout<<"Некоректный ввод!"<<endl;
				cout<<"Меню:"<<endl;
				cout<<"1. Вывести список"<<endl;
				cout<<"2. Удаление элемента"<<endl;
				cout<<"3. Подсчёт элементов и их суммы"<<endl;
				cout<<"4. Добавление элемента"<<endl;
				cout<<"0. Выход"<<endl;
				cout<<"Ввод: ";
				cin>>j;
				system("CLS");
			}
			if(j==1){
				cout<<"Список равен:"<<endl;
				G.List();
			}
			if(j==2){
				try{
					G.del();
					cout<<"Список равен:"<<endl;
					G.List();
				}
				catch(const char *ex){
					cout<<"Мы обнаружили "<<ex<<endl;
				}
			}
			if(j==3){
				k=spisok::getSum(H);
				i=spisok::getKol(H);
				cout<<"Сумма равна: "<<k<<endl;
				cout<<"Количество элементов равно: "<<i<<endl;
			}
			if(j==4){
				try{
					G.Addnode();
					cout<<"Список равен:"<<endl;
					G.List();
				}
				catch(const char *ex){
					cout<<"Мы обнаружили "<<ex<<endl;
				}
			}
		}
	}
	system("PAUSE");
	return 0;
}
