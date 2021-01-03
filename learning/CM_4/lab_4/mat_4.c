#include <stdlib.h>
#include <stdio.h>

#define SIZE 2
#define EPS 0.00000001 //10^-8 == 0.7-0

#define FIRST_FUNCTION(X)  ( (X[0])*(X[1])-(2.3) )
#define SECOND_FUNCTION(X) ( (X[0])/(X[1])-(1.9) )
#define DEGREE_OF_NUMBER_ONE(a,b) (1-(2*(((a)+(b))%2)))


#define DETERMINANT_OF_THE_TWO_BY_TWO_MATRIX(array) \
( (array[0][0])*(array[1][1]) ) - ( (array[1][0])*(array[0][1]) )


#define PRINT_QUANTITY_STEPS(quantity_step) \
printf("steps number %d\n",quantity_step);	 \
quantity_step=((quantity_step)+1);


#define FILL_ARRAY_X(X,size)\
X = (double*) calloc (size,sizeof(double));\
X[0]=2;\
X[1]=1;\


#define ABSOLUT_OF_DIFFERENCE(a,b,array,size) \
for(short int i = 0; i < size; i++)			   \
{												\
	array[i] = (a[i]-b[i]);						 \
	if(array[i]<0.0)							  \
	{											   \
		array[i] = array[i] * (-1);					\
	}												 \
}


#define REPLACING_PREVIOS_BY_CURRENT_VARIABLE(a,b,size) \
for(short int i = 0; i < size; i++)					  	 \
{														  \
	a[i]=b[i];											   \
}



#define PRINT_SQUARE_MATRIX(array,size)\
for(int i = 0; i < size; i++)			\
{										 \
	printf("\n");						  \
   	for(int j = 0; j < size; j++)		   \
	{										\
		printf("%7.2f", array[i][j]);		 \
	}										  \
}											   \
printf("\n");


#define PRINT_MATRIX_WITH_FREE_TERMS(array,size) \
for(int i = 0; i < size; i++)					  \
{ 							 			  		   \
	printf("\n");								    \
   	for(int j = 0; j < size+1; j++)  			  	 \
	{							   					  \
		printf("%7.2f", array[i][j]);			  	   \
	}								   					\
}														 \
printf("\n");


#define PRINT_ONEDIMENSIONAL_ARRAY(array,size)\
for(short int i = 0; i < size; i++)			   \
{												\
	printf("\n%c%d=%f\t",'X',(i+1),array[i]);	 \
}												  \
printf("\n\n");


#define DRAW_MENU 						\
printf("1) Method inverse matrix\n");	 \
printf("2) Method with Gauss\n");	  	  \
printf("3) Print matrix\n");		   	   \
printf("4) Print matrix with free terms\n");\
printf("9) Clear Screen\n");				 \
printf("0) Exit\n");


double** Fill_Jacobi(double **jacobi_matrix, double *X)
{
	jacobi_matrix = (double**) calloc (SIZE,sizeof(double*));
	for(short int i = 0; i < SIZE; i++)
	{
		jacobi_matrix[i] = (double*) calloc (SIZE+1,sizeof(double));
	}
	jacobi_matrix[0][0]=X[1];
	jacobi_matrix[0][1]=X[0];
	jacobi_matrix[0][2]=FIRST_FUNCTION(X);
	jacobi_matrix[1][0]=1/X[1];
	jacobi_matrix[1][1]=-X[0]/(X[1]*X[1]);
	jacobi_matrix[1][2]=SECOND_FUNCTION(X);
	return jacobi_matrix;
}

double** Transposition_Matrix(double **array)
{
	double temp= 0.0;
	temp = array[1][0];
	array[1][0] = array[0][1];
	array[0][1] = temp;
	return array;
}

double** Fill_Extensions(double **algebraic_extensions, double **jacobi_matrix,int size)
{
	algebraic_extensions = (double**) calloc (size,sizeof(double*));
	for(short int i = 0; i < size; i++)
	{
		algebraic_extensions[i] = (double*) calloc (size,sizeof(double));
	}
	algebraic_extensions[0][0]=jacobi_matrix[1][1]; 
	algebraic_extensions[0][1]=jacobi_matrix[1][0];
    algebraic_extensions[1][0]=jacobi_matrix[0][1];
	algebraic_extensions[1][1]=jacobi_matrix[0][0];
	return algebraic_extensions;
}

double** Inverse_Matrix(double **jacobi_matrix, double **algebraic_extensions, double jacobi_determinant, int size)
{
	for(short int i = 0; i < size; i++)
	{
    	for(short int j = 0; j < size; j++)
    	{
    		jacobi_matrix[i][j]=(DEGREE_OF_NUMBER_ONE(i,j))*algebraic_extensions[i][j]/jacobi_determinant;
		}
    }
    return jacobi_matrix;
}

double *Calculating_Variables(double *Var_Arr, double *X, double **jacobi_matrix)
{
	double *S = NULL;
	S = (double*) calloc (SIZE,sizeof(double));
	Var_Arr = (double*) calloc (SIZE,sizeof(double));
	S[0]=FIRST_FUNCTION(X); 
	S[1]=SECOND_FUNCTION(X);
	for(int i=0; i<SIZE; i++)
	{
		Var_Arr[i]=0;
		for(int j=0; j<SIZE; j++)
		{
			Var_Arr[i] = Var_Arr[i]+jacobi_matrix[i][j]*S[j];	
		}
		Var_Arr[i] = X[i]-Var_Arr[i];
	}
	return Var_Arr;
}

double** Super_Gauss(double **Arr,int size)
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

double *Calculating_Variables_by_Gauss(double *Var_Arr, double *X, double **Arr, int size)
{
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
	for(short int i=0; i<size;i++)
	{
		Var_Arr[i]=X[i]-Var_Arr[i];
	}
	return Var_Arr;
}

int main()
{
	double **jacobi_matrix = NULL;
	double *X = NULL;
	while(1)
	{
		DRAW_MENU;
		short int key_choise;
		scanf("%hu",&key_choise);
		switch(key_choise)
		{
			case (1):
			{
				double **algebraic_extensions = NULL;
				double *Var_Arr = NULL;
				double jacobi_determinant = 0.0;
				double *absolute_difference = NULL;
				int quantity_steps = 1;
				FILL_ARRAY_X(X,SIZE);
				absolute_difference = (double*) calloc (SIZE,sizeof(double));
				do
				{	
					PRINT_QUANTITY_STEPS(quantity_steps);
					jacobi_matrix = Fill_Jacobi(jacobi_matrix,X);
					PRINT_SQUARE_MATRIX(jacobi_matrix,SIZE);
					jacobi_determinant = DETERMINANT_OF_THE_TWO_BY_TWO_MATRIX(jacobi_matrix);
					jacobi_matrix = Transposition_Matrix(jacobi_matrix);
					algebraic_extensions = Fill_Extensions(algebraic_extensions,jacobi_matrix,SIZE);
					jacobi_matrix = Inverse_Matrix(jacobi_matrix,algebraic_extensions,jacobi_determinant,SIZE);
					Var_Arr=Calculating_Variables(Var_Arr,X,jacobi_matrix);
					ABSOLUT_OF_DIFFERENCE(X,Var_Arr,absolute_difference,SIZE);
					REPLACING_PREVIOS_BY_CURRENT_VARIABLE(X,Var_Arr,SIZE);
					PRINT_ONEDIMENSIONAL_ARRAY(Var_Arr,SIZE);
				} while( ((absolute_difference[0] + absolute_difference[1]) > EPS) /*((absolute_difference[0])>EPS) && ((absolute_difference[1])>EPS)*/ );
				break;
			}
			case (2):
			{
				double *Var_Arr = NULL;
				double *absolute_difference = NULL;
				int quantity_steps = 1;
				FILL_ARRAY_X(X,SIZE);
				absolute_difference = (double*) calloc (SIZE,sizeof(double));
				do
				{
					PRINT_QUANTITY_STEPS(quantity_steps);
					jacobi_matrix = Fill_Jacobi(jacobi_matrix,X);
					PRINT_MATRIX_WITH_FREE_TERMS(jacobi_matrix,SIZE);
					jacobi_matrix=Super_Gauss(jacobi_matrix,SIZE);
					PRINT_MATRIX_WITH_FREE_TERMS(jacobi_matrix,SIZE);
					Var_Arr=Calculating_Variables_by_Gauss(Var_Arr,X,jacobi_matrix,SIZE);
					ABSOLUT_OF_DIFFERENCE(X,Var_Arr,absolute_difference,SIZE);
					REPLACING_PREVIOS_BY_CURRENT_VARIABLE(X,Var_Arr,SIZE);
					PRINT_ONEDIMENSIONAL_ARRAY(Var_Arr,SIZE);
				} while( ((absolute_difference[0] + absolute_difference[1]) > EPS)/*(absolute_difference[0])>EPS) && ((absolute_difference[1])>EPS)*/ );
				break;
			}
			case (3):
			{
				if(jacobi_matrix!=NULL)
				{
					PRINT_SQUARE_MATRIX(jacobi_matrix,SIZE);	
				}
				else
				{
					printf("\nerror:Fill matrix please\n");
				}
				break;
			}
			case (4):
			{
				if(jacobi_matrix!=NULL)
				{
					PRINT_MATRIX_WITH_FREE_TERMS(jacobi_matrix,SIZE);
				}
				else
				{
					printf("\nerror:Fill matrix please\n");
				}
				break;
			}
			case (9):
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
