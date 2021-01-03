#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <time.h>

const int size=3;

void Menu()
{
	printf("1) Fill Matrix Test\n");
	printf("2) Print Matrix\n");
	printf("3) Simple Gauss\n");
	printf("4) Super Gauss\n");
	printf("5) Fill Matrix Rand\n");
	printf("6) Calculating Variables\n");
	printf("7) Simple Gauss Reverse\n");
	printf("8) Clear Monitor \n");
	printf("9) Calculating Variable Reverse\n");
	printf("0) Exit\n");
}

double* Calculating_Variable_Reverse(double **Arr)
{
	double *Var_Arr=NULL;
	Var_Arr= (double*) malloc (size *sizeof(double));
	for(short int i=0;i<size;i++)
	{
		Var_Arr[i]=Arr[i][size];
		for(short int j=0;j<i;j++)
		{
			Var_Arr[i]=Var_Arr[i]-Arr[i][j]*Var_Arr[j];
		}
		Var_Arr[i]=Var_Arr[i]/Arr[i][i];
	}
	for(short int i=0;i<size;i++)
	{
		printf("\nX%d = %f\n",i,Var_Arr[i]);
	}
}

void Print_Matrix(double **Arr)
{
	printf("\n");
	for(int i=0; i<size; i++)
	{
		printf("(");
		for(int j=0; j<size+1; j++)
		{
			if(j==size)
			{
				printf("|%5.1f",Arr[i][j]);
			}
			else
			{
				printf("%5.1f",Arr[i][j]);	
			}
		}
		printf(")\n");
	}
	printf("\n");
}

double** Fill_Matrix_Test(double **Arr)
{
	Arr = (double**) calloc (size,sizeof(double*));
	for(short int i=0; i<size; i++)
	{
		Arr[i] = (double*) calloc (size+1,sizeof(double));
	}
	Arr[0][0]=-3;
	Arr[0][1]=1;
	Arr[0][2]=2;
	Arr[0][3]=1;
	Arr[1][0]=2;
	Arr[1][1]=1;
	Arr[1][2]=-3;
	Arr[1][3]=-4;
	Arr[2][0]=-4;
	Arr[2][1]=2;
	Arr[2][2]=1;
	Arr[2][3]=-2;
//	Arr[0][0]=1;
//	Arr[0][1]=1;
//	Arr[0][2]=1;
//	Arr[0][3]=0;
//	Arr[1][0]=4;
//	Arr[1][1]=2;
//	Arr[1][2]=1;
//	Arr[1][3]=1;
//	Arr[2][0]=9;
//	Arr[2][1]=3;
//	Arr[2][2]=1;
//	Arr[2][3]=3;
	return Arr;
}

double** Fill_Matrix_Rand(double **Arr)
{
	Arr = (double**) malloc (size *sizeof(double*));
	for(short int i=0; i<size; i++)
	{
		Arr[i] = (double*) malloc (size+1 *sizeof(double));
		for(short int j=0; j<size+1; j++)
		{
			Arr[i][j]= rand()%size*3-size*3/2;
		}
	}
	return Arr;
}

double** Simple_Gauss(double **Arr)
{
	double coefficient=1;
	for(short int k=0;k<size-1;k++)
	{
		if(Arr[k][k]==0)
		{
			printf("Cant calculating system\n");
			printf("Please fill matrix again\n");
			return NULL;
		}
		for(short int i=k+1;i<size;i++)
		{
			coefficient=Arr[i][k]/Arr[k][k];
			for(short int j=k;j<size+1;j++)
			{
				Arr[i][j]=Arr[i][j]-Arr[k][j]*coefficient;
			}
		}	
	}
	return Arr;
}

double* Calculating_Variables(double **Arr)
{
	double *Var_Arr=NULL;
	printf("!!!\n");
	Var_Arr= (double*) calloc (size ,sizeof(double));
	for(short int i=1;i<size+1;i++)
	{
		Var_Arr[size-i]=Arr[size-i][size];
		for(short int j=size+1-i;j<size;j++)
		{
			Var_Arr[size-i]=Var_Arr[size-i]-Arr[size-i][j]*Var_Arr[j];
		}
		Var_Arr[size-i]=Var_Arr[size-i]/Arr[size-i][size-i];
	}
	for(short int i=0;i<size;i++)
	{
		printf("\nX%d = %f\n",i,Var_Arr[i]);
	}
	printf("\n");
}

double** Super_Gauss(double **Arr)
{
	double temp=0;
	short int max=0;
	double coefficient=1;
	for(short int k=0;k<size-1;k++)
	{
		for(short int i=k+1;i<size;i++)
		{
			if(abs(Arr[i][k])>abs(Arr[k][k]))
			{
				max=i;
			}
		}
		if(max!=k)
		{
			for(short int j=0;j<size+1;j++)
			{
				temp=Arr[k][j];
				Arr[k][j]=Arr[max][j];
				Arr[max][j]=temp;
			}
		}
		if(Arr[k][k]==0)
		{
			printf("Cant calculating system\n");
			printf("Please fill matrix again\n");
			return NULL;
		}
		for(short int i=k+1;i<size;i++)
		{
			coefficient=Arr[i][k]/Arr[k][k];
			for(short int j=k;j<size+1;j++)
			{
				Arr[i][j]=Arr[i][j]-Arr[k][j]*coefficient;
			}
		}	
	}
	return Arr;
}

double **Simple_Gauss_Reverse(double **Arr)
{
	double coefficient=1;
	for(short int k=size-1;k>0;k--)
	{
		if(Arr[k][k]==0)
		{
			printf("Cant calculating system\n");
			printf("Please fill matrix again\n");
			return NULL;
		}
		for(short int i=k-1;i>=0;i--)
		{
			coefficient=Arr[i][k]/Arr[k][k];
			for(short int j=size;j>=0;j--)
			{
				Arr[i][j]=Arr[i][j]-Arr[k][j]*coefficient;
			}
		}	
	}
	return Arr;
}
int main()
{
	srand(time(NULL));
	bool Gauss_flag=false;
	double **Arr=NULL;
	while(1)
	{
		Menu();
		short int key_choise;
		scanf("%hu",&key_choise);
		switch(key_choise)
		{
			case (1):
			{
				Arr=Fill_Matrix_Test(Arr);
				Gauss_flag=false;
				break;
			}
			case (2):
			{
				if(Arr==NULL)
				{
					printf("Fill matrix please\n");
				}
				else
				{
					Print_Matrix(Arr);	
				}
				break;
			}
			case (3):
			{
				if((Gauss_flag==false)&&(Arr!=NULL))
				{		
					Arr=Simple_Gauss(Arr);
					Gauss_flag=true;	
				}
				else
				{
					printf("Please fill matrix at first\n");
				}
				break;
			}
			case (4):
			{
				if((Gauss_flag==false)&&(Arr!=NULL))
				{		
					Arr=Super_Gauss(Arr);
					Gauss_flag=true;	
				}
				else
				{
					printf("Please fill matrix at first\n");
				}
				break;
			}
			case (5):
			{
				Arr=Fill_Matrix_Rand(Arr);
				Gauss_flag=false;
				break;
			}
			case (6):
			{
				if(Gauss_flag==true)
				{
					Calculating_Variables(Arr);	
				}
				else
				{
					printf("Please click on Gauss method at first\n");
				}
				break;
			}
			case (7):
			{
				if((Gauss_flag==false)&&(Arr!=NULL))
				{		
					Arr=Simple_Gauss_Reverse(Arr);
					Gauss_flag=true;	
				}
				else
				{
					printf("Please fill matrix at first\n");
				}
				break;
			}
			case (8):
			{
				system("CLS");
				break;	
			}
			case (9):
			{
				if(Gauss_flag==true)
				{
					Calculating_Variable_Reverse(Arr);
				}
				else
				{
					printf("Please click on Gauss method at first\n");
				}
				break;
			}
			case (0):
			{
				return 0;
			}
		}
	}
}
