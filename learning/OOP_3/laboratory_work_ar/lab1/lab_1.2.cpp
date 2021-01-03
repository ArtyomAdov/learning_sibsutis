#include<iostream>
#include <cstdlib>
#include <ctime> 

using namespace std;

int genRandMatrix(int size, int maxValue, int **matrix)
{
	int cols[10];
    for (int i = 0; i < size; i++) 
	{
	   	cols[i]=rand()%10 + 1;
	   		for(int j = 0; j < cols[i]; j++)
	    	{
	    		if(j==0)
	    		{
	    			matrix[i][j]=cols[i];
				}
				else
				{
					matrix[i][j] =  rand() % maxValue;	
				}
			}
    }
}

void print (int size, int **matrix)
{
	for (int i = 0; i < size; i++) 
	    {
	    	for(int j=0; j < matrix[i][0]; j++)
	    	{	
	    		cout << matrix[i][j] << "  ";
	    		/*if(j==0)
	    		{
	    			cout << ": ";
				}
				*/
			}
            cout << endl;
        }
}

int main()
{
	srand (time(NULL));
	int size = rand()%10;
	cout << size << endl;
	cout << "========" <<endl;
	int maxValue = 100;
	int** matrix = new int* [size];
	for (int i = 0; i < size; i++)
	    {
	     	matrix[i] = new int [size];
		}
	genRandMatrix(size, maxValue, matrix);
	print(size, matrix);
	for (int i=0; i<size; i++)
	    {
	    	delete [] matrix[i];
		}
	delete [] matrix;
}
