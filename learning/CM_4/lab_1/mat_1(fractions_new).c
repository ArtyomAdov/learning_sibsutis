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
	fractions temp;
	for(short int k=0;k<size-1;k++)
	{
		Print_Matrix(Arr);
		if(Arr[k][k].numerator==0)
		{
			printf("Cant calculating system\n");
			printf("Please fill matrix again\n");
			return NULL;
		}
		for(short int i=k+1;i<size;i++)
		{
			coefficient.numerator=Arr[i][k].numerator*Arr[k][k].denominator;
			coefficient.denominator=Arr[i][k].denominator*Arr[k][k].numerator;
			if(coefficient.denominator<0)
			{
				coefficient.denominator=coefficient.denominator*(-1);
				coefficient.numerator=coefficient.numerator*(-1);
			}//пока что все верно //мне нужно будет делать строку минус строку а не плюс
			printf("%d : %d\n",coefficient.numerator,coefficient.denominator);
			for(short int j=k;j<size+1;j++)
			{
				temp.numerator=Arr[k][j].numerator*coefficient.numerator;
				temp.denominator=Arr[k][j].denominator*coefficient.denominator;
				if(temp.denominator<0)
				{
					temp.denominator=temp.denominator*(-1);
					temp.numerator=temp.numerator*(-1);
				}
				Arr[i][j].numerator=Arr[i][j].numerator*temp.denominator-temp.numerator*Arr[i][j].denominator;
				Arr[i][j].denominator=Arr[i][j].denominator*temp.denominator;
				if(Arr[i][j].denominator<0)
				{
					Arr[i][j].denominator=Arr[i][j].denominator*(-1);
					Arr[i][j].numerator=Arr[i][j].numerator*(-1);
				}
				if(Arr[i][j].numerator==0)
				{
					Arr[i][j].denominator=1;
				}
				if(abs(Arr[i][j].numerator)%abs(Arr[i][j].denominator)==0)
				{
					Arr[i][j].numerator=Arr[i][j].numerator/Arr[i][j].denominator;
					Arr[i][j].denominator=1;
				}
			}
		}
	}
	return Arr;
}

fractions* Calculating_Variables(fractions **Arr)
{
	fractions *Var_Arr=NULL;
	fractions temp;
	printf("!!!\n");
	Var_Arr= (fractions*) calloc (size ,sizeof(fractions));
	for(short int i=1;i<size+1;i++)
	{
		Var_Arr[size-i].numerator=Arr[size-i][size].numerator;
		Var_Arr[size-i].denominator=Arr[size-i][size].denominator;
		for(short int j=size+1-i;j<size;j++)
		{
			temp.numerator=Arr[size-i][j].numerator*Var_Arr[j].numerator;
			temp.denominator=Arr[size-i][j].denominator*Var_Arr[j].denominator;
			if(temp.denominator<0)
			{
				temp.denominator=temp.denominator*(-1);
				temp.numerator=temp.numerator*(-1);
			}
			//Var_Arr[size-i]=Var_Arr[size-i]-Arr[size-i][j]*Var_Arr[j];
			Var_Arr[size-i].numerator=Var_Arr[size-i].numerator*temp.denominator-temp.numerator*Var_Arr[size-i].denominator;
			Var_Arr[size-i].denominator=Var_Arr[size-i].denominator*temp.denominator;
			if(Var_Arr[size-i].denominator<0)
			{
				Var_Arr[size-i].denominator=Var_Arr[size-i].denominator*(-1);
				Var_Arr[size-i].numerator=Var_Arr[size-i].numerator*(-1);
			}
		}
		Var_Arr[size-i].numerator=Var_Arr[size-i].numerator*Arr[size-i][size-i].denominator;
		Var_Arr[size-i].denominator=Var_Arr[size-i].denominator*Arr[size-i][size-i].numerator;
		if(Var_Arr[size-i].denominator<0)
		{
			Var_Arr[size-i].denominator=Var_Arr[size-i].denominator*(-1);
			Var_Arr[size-i].numerator=Var_Arr[size-i].numerator*(-1);
		}
		//Var_Arr[size-i]=Var_Arr[size-i]/Arr[size-i][size-i];
	}
	for(short int i=0;i<size;i++)
	{
		printf("\nX%d = %d\n    ----\n   %d\n",i,Var_Arr[i].numerator,Var_Arr[i].denominator);
	}
	printf("\nЌ≈ «јЅ”ƒ№ ” ќ–ќ“»“№ ќ“¬≈“ “ќ ≈—“№ —ќ –“ј»“№ ƒ–ќЅ»");
}

fractions** Super_Gauss(fractions **Arr)
{
	fractions coefficient;
	fractions temp;
	short int max;
	for(short int k=0;k<size-1;k++)
	{
		Print_Matrix(Arr);
		if(Arr[k][k].numerator==0)
		{
			printf("Cant calculating system\n");
			printf("Please fill matrix again\n");
			return NULL;
		}
		for(short int i=k+1;i<size;i++)
		{
			if(abs(Arr[i][k].numerator/Arr[i][k].denominator)>abs(Arr[k][k].numerator/Arr[k][k].denominator))
			{
				max=i;
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
			coefficient.numerator=Arr[i][k].numerator*Arr[k][k].denominator;
			coefficient.denominator=Arr[i][k].denominator*Arr[k][k].numerator;
			if(coefficient.denominator<0)
			{
				coefficient.denominator=coefficient.denominator*(-1);
				coefficient.numerator=coefficient.numerator*(-1);
			}//пока что все верно //мне нужно будет делать строку минус строку а не плюс
			printf("%d : %d\n",coefficient.numerator,coefficient.denominator);
			for(short int j=k;j<size+1;j++)
			{
				temp.numerator=Arr[k][j].numerator*coefficient.numerator;
				temp.denominator=Arr[k][j].denominator*coefficient.denominator;
				if(temp.denominator<0)
				{
					temp.denominator=temp.denominator*(-1);
					temp.numerator=temp.numerator*(-1);
				}
				Arr[i][j].numerator=Arr[i][j].numerator*temp.denominator-temp.numerator*Arr[i][j].denominator;
				Arr[i][j].denominator=Arr[i][j].denominator*temp.denominator;
				if(Arr[i][j].denominator<0)
				{
					Arr[i][j].denominator=Arr[i][j].denominator*(-1);
					Arr[i][j].numerator=Arr[i][j].numerator*(-1);
				}
				if(Arr[i][j].numerator==0)
				{
					Arr[i][j].denominator=1;
				}
				if(abs(Arr[i][j].numerator)%abs(Arr[i][j].denominator)==0)
				{
					Arr[i][j].numerator=Arr[i][j].numerator/Arr[i][j].denominator;
					Arr[i][j].denominator=1;
				}
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
