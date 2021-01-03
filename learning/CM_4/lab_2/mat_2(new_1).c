#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <math.h>

const int size=3;

void Menu()
{
	printf("1) Fill Matrix Test\n");
	printf("2) Print Matrix\n");
	printf("3) Simple Iteration\n");
	printf("4) Zeiydel\n");
	printf("8) Clear Monitor \n");
	printf("0) Exit\n");
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
				printf("|%5.2f",Arr[i][j]);
			}
			else
			{
				printf("%5.2f",Arr[i][j]);	
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
//	Arr[0][0]=5.0;
//	Arr[0][1]=-1.0;
//	Arr[0][2]=2.0;
//	Arr[0][3]=3.0;
//	Arr[1][0]=-1.0;
//	Arr[1][1]=4.0;
//	Arr[1][2]=1.0;
//	Arr[1][3]=6.0;
//	Arr[2][0]=2.0;
//	Arr[2][1]=-1.0;
//	Arr[2][2]=-10.0;
//	Arr[2][3]=-21.0;
	Arr[0][0]=10.0;
	Arr[0][1]=4.0;
	Arr[0][2]=-1.0;
	Arr[0][3]=8.0;
	Arr[1][0]=-1.0;
	Arr[1][1]=-5.0;
	Arr[1][2]=2.0;
	Arr[1][3]=3.0;
	Arr[2][0]=1.0;
	Arr[2][1]=1.0;
	Arr[2][2]=10.0;
	Arr[2][3]=21.0;
	
	return Arr;
}

double** Transformation_Matrix(double **Arr)
{
	for(short int i=0;i<size;i++)
	{
		for(short int j=0;j<size+1;j++)
		{
			if((j==i))
			{
				if(j!=size)
				{
					j++;	
				}
			}
			Arr[i][j]=Arr[i][j]/Arr[i][i];
		}
		Arr[i][i]=0.0;
	}
	return Arr;
}

double Find_Norm(double **Arr, double norm, bool free_var_flag)
{
	if(free_var_flag==false)
	{
		for(short int i=0;i<size;i++)
		{
			double temp=0.0;
			for(short int j=0;j<size;j++)
			{
				temp=temp+fabs(Arr[i][j]);
			}
			if(temp>norm)
			{
				norm=temp;
			}
		}
	}
	if(free_var_flag==true)
	{
		for(short int i=0;i<size;i++)
		{
			if(fabs(Arr[i][size])>norm)
			{
				norm=fabs(Arr[i][size]);
			}
		}
	}
	return norm;
}

double Calculating_Steps(double quantity_step,double norm_C,double norm_B,const double eps)
{
	quantity_step=(log((eps*(1-norm_C))/(norm_B)))/(log(norm_C))+1;
	printf("q=%f",quantity_step);
	return quantity_step;
}

double** Iteration(double **Var_Arr,double **Arr)
{
	double *temp_arr=NULL;
	double sum=0.0;
	temp_arr=(double*) calloc (size,sizeof(double));
	for (int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			sum=sum+Arr[i][j]*Var_Arr[j][0];//0
		}
		//printf("sum%d=%f\n",i,sum);
		temp_arr[i]=sum;
		sum=0.0;
	}
	for(short int i=0;i<size;i++)
	{
		//printf("\nt=%f",temp_arr[i]);
		temp_arr[i]=Arr[i][size]-temp_arr[i];
		//printf("\tt=%f\n",temp_arr[i]);
	}
	for(short int i=0;i<size;i++)
	{
		Var_Arr[i][0]=Var_Arr[i][1];
		Var_Arr[i][1]=temp_arr[i];
		printf("X%d=%f\n",i,Var_Arr[i][1]);
	}
	return Var_Arr;
}

double** Simple_Iteration(double **Arr,const double eps)
{
	double **Var_Arr=NULL;
	double norm_C=0.0;
	double norm_B=0.0;
	double quantity_step=0.0;
	Arr=Transformation_Matrix(Arr);//приводим к виду
	norm_C=Find_Norm(Arr,norm_C,false);
	norm_B=Find_Norm(Arr,norm_B,true);
	printf("norm_C=%f\nnorm_B=%f",norm_C,norm_B);
	quantity_step=Calculating_Steps(quantity_step,norm_C,norm_B,eps);
	Var_Arr = (double**) calloc (size,sizeof(double*));
	for(short int i=0; i<size; i++)
	{
		Var_Arr[i] = (double*) calloc (2,sizeof(double));
	}
	for(short int i=0;i<size;i++)
	{
		Var_Arr[i][0]=0;
		Var_Arr[i][1]=Arr[i][size];
	}
	printf("\nquantity step=%f\n",quantity_step+1);
	for(short int i=0;i<quantity_step;i++)
	{
		printf("\nnumber step=%d\n",i);
		Var_Arr=Iteration(Var_Arr,Arr);
	}
//	for(short int i=0;i<size;i++)
//	{
//		printf("X%d=%f\n",i,Var_Arr[i][1]);
//	}
	return Arr;
}

double* Zeydel_Iteration(double *Var_Arr,double **Arr)
{
	for (int i=0;i<size;i++)
	{
		double sum=0.0;
		for(int j=0;j<size;j++)
		{
			sum=sum+Arr[i][j]*Var_Arr[j];//0//i
		}
		Var_Arr[i]=Arr[i][size]-sum;
		sum=0.0;
	}
	for(short int i=0;i<size;i++)
	{
		printf("X%d=%f\n",i,Var_Arr[i]);
	}
	return Var_Arr;
}

double** Zeiydel(double **Arr,const double eps)
{
	double *Var_Arr=NULL;
	double norm_C=0.0;
	double norm_B=0.0;
	double quantity_step=0.0;
	Arr=Transformation_Matrix(Arr);//приводим к виду
	norm_C=Find_Norm(Arr,norm_C,false);
	norm_B=Find_Norm(Arr,norm_B,true);
	printf("norm_C=%f\nnorm_B=%f",norm_C,norm_B);
	quantity_step=Calculating_Steps(quantity_step,norm_C,norm_B,eps);
	Var_Arr = (double*) calloc (size,sizeof(double));
	for(short int i=0;i<size;i++)
	{
		Var_Arr[i]=0;
	}
	printf("\nquantity step=%f\n",quantity_step+1);
	for(short int i=0;i<quantity_step;i++)
	{
		printf("\nnumber step=%d\n",i);
		Var_Arr=Zeydel_Iteration(Var_Arr,Arr);
	}
//	for(short int i=0;i<size;i++)
//	{
//		printf("X%d=%f\n",i,Var_Arr[i]);
//	}
	return Arr;
}

int main()
{
	bool decided_flag=false;
	double **Arr=NULL;
	double eps=0.001;
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
				decided_flag=false;
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
				if((decided_flag==false)&&(Arr!=NULL))
				{		
					Arr=Simple_Iteration(Arr,eps);
					decided_flag=true;	
				}
				else
				{
					printf("Please fill matrix at first\n");
				}
				break;
			}
			case (4):
			{
				if((decided_flag==false)&&(Arr!=NULL))
				{		
					Arr=Zeiydel(Arr,eps);
					decided_flag=true;	
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
			case (0):
			{
				return 0;
			}
		}
	}
}
