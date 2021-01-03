#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct fractions_array
{
	int numerator;//числитель
	int	denominator;//знаменатель
} fractions; 

const int size=3;

void Menu()
{
	printf("1) Fill Matrix Test\n");
	printf("2) Print Matrix\n");
	printf("3) Simple Gauss\n");
	printf("4) Super Gauss\n");
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

fractions** Print_Matrix(fractions **Arr)
{
	for(short int i=0;i<size;i++)
	{
		printf("(");
		for(short int j=0;j<size+1;j++)
		{
			if(j==size)
			{
				printf(" |");
			}
			printf("%3d",Arr[i][j].numerator);
		}
		printf("  )\n( ");
		for(short int j=0;j<size+1;j++)
		{
			if(j==size)
			{
				printf("| ");
			}
			printf(" = ");
		}
		printf(" )\n(");
		for(short int j=0;j<size+1;j++)
		{
			if(j==size)
			{
				printf(" |");
			}
			printf("%3d",Arr[i][j].denominator);
		}
		printf("  )\n");
		if(i!=size-1)
		{
			printf("(\t\t )\n");	
		}
	}
	printf("\n");
}

fractions** Fill_Matrix_Test(fractions **Arr)
{
	Arr = (fractions**) calloc (size,sizeof(fractions*));
	for(short int i=0; i<size; i++)
	{
		Arr[i] = (fractions*) calloc (size+1,sizeof(fractions));
	}
	for(short int i=0;i<size;i++)
	{
		for(short int j=0;j<size+1;j++)
		{
			Arr[i][j].denominator=1;
		}
	}
	Arr[0][0].numerator=-3;
	Arr[0][1].numerator=1;
	Arr[0][2].numerator=2;
	Arr[0][3].numerator=1;
	Arr[1][0].numerator=2;
	Arr[1][1].numerator=1;
	Arr[1][2].numerator=-3;
	Arr[1][3].numerator=-4;
	Arr[2][0].numerator=-4;
	Arr[2][1].numerator=2;
	Arr[2][2].numerator=1;
	Arr[2][3].numerator=-2;
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

fractions** Simple_Gauss(fractions **Arr)
{
	fractions coefficient;
	fractions temp_frac;
	coefficient.numerator=coefficient.denominator=0;
	temp_frac.numerator=temp_frac.denominator=0;
	for(short int k=0;k<size-1;k++)//наждо сделдать так чтобы везде где знаменатель отрицательный то мы бы и числитель и знаменатель умножали на -1
	{
		if(Arr[k][k].numerator==0)
		{
			printf("Cant calculating system\n");
			printf("Please fill matrix again\n");
			return NULL;
		}
		for(short int i=k+1;i<size;i++)
		{
			Print_Matrix(Arr);
			coefficient.numerator=Arr[i][k].numerator*Arr[k][k].denominator;
			coefficient.denominator=Arr[i][k].denominator*Arr[k][k].numerator;
			if(coefficient.denominator<0)
			{
				coefficient.denominator=coefficient.denominator*(-1);
				coefficient.numerator=coefficient.numerator*(-1);
			}
			printf("%d : %d\n",coefficient.numerator,coefficient.denominator);
			for(short int j=k;j<size+1;j++)
			{
				temp_frac.numerator=Arr[k][j].numerator*coefficient.numerator;
				temp_frac.denominator=Arr[k][j].denominator*coefficient.denominator;
				if(temp_frac.denominator<0)
				{
					temp_frac.denominator=temp_frac.denominator*(-1);
					temp_frac.numerator=temp_frac.numerator*(-1);
				}
				printf("%d : %d\n",temp_frac.numerator,temp_frac.denominator);
				if(Arr[i][j].denominator=temp_frac.denominator)//бля дикая хуйня в том что я делаю строка - строка а должен делать строка + строка
				{	
					Arr[i][j].numerator=Arr[i][j].numerator+temp_frac.numerator;
					//возможно тоже условие на знаменатель
				}
				else
				{
					Arr[i][j].numerator=Arr[i][j].numerator*temp_frac.denominator+temp_frac.numerator*Arr[i][j].denominator;
					Arr[i][j].denominator=Arr[i][j].denominator*temp_frac.denominator;
					if(Arr[i][j].denominator<0)
					{
						Arr[i][j].denominator=Arr[i][j].denominator*(-1);
						Arr[i][j].numerator=Arr[i][j].numerator*(-1);
					}
				}
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
	bool Gauss_flag=false;
	fractions **Arr=NULL;
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
//			case (4):
//			{
//				if((Gauss_flag==false)&&(Arr!=NULL))
//				{		
//					Arr=Super_Gauss(Arr);
//					Gauss_flag=true;	
//				}
//				else
//				{
//					printf("Please fill matrix at first\n");
//				}
//				break;
//			}
//			case (6):
//			{
//				if(Gauss_flag==true)
//				{
//					Calculating_Variables(Arr);	
//				}
//				else
//				{
//					printf("Please click on Gauss method at first\n");
//				}
//				break;
//			}
//			case (7):
//			{
//				if((Gauss_flag==false)&&(Arr!=NULL))
//				{		
//					Arr=Simple_Gauss_Reverse(Arr);
//					Gauss_flag=true;	
//				}
//				else
//				{
//					printf("Please fill matrix at first\n");
//				}
//				break;
//			}
			case (8):
			{
				system("CLS");
				break;	
			}
//			case (9):
//			{
//				if(Gauss_flag==true)
//				{
//					Calculating_Variable_Reverse(Arr);
//				}
//				else
//				{
//					printf("Please click on Gauss method at first\n");
//				}
//				break;
//			}
			case (0):
			{
				return 0;
			}
		}
	}
}
