#include<iostream>

#include <cstdlib>
#include <ctime> 

using namespace std;

void genRandArray(int size, int maxValue, int * arr)
{
	arr[0]=size;
    for (int i = 1; i <= size; i++) 
	    {
            arr[i] =  rand() % maxValue;
        }
}

void print(int size, int *arr)
{
	for(int i=0; i<=size; i++)
	    {
	    	cout << arr[i] << "  ";
		}
}


int main()
{
	srand (time(NULL));
	int size, maxValue = 100;
	size = rand()%10;
	int *arr = new int [size+1];
	genRandArray (size, maxValue, arr);
	print (size, arr);
	delete [] arr;
	system("PAUSE");
	return 0;
}
