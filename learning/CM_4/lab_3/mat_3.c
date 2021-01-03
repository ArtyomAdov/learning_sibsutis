#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define function(x) x*x-3
#define first_derivative(x) x*2
#define second_derivative(x) 2

void Menu()
{
	printf("1) Method Half Division \n");
	printf("2) Method Chord\n");
	printf("3) Method Tangent\n");
	printf("8) Clear Monitor \n");
	printf("0) Exit\n");
}

void Half_Division(double x, double eps, double left_limit,double right_limit)
{
	if((function(left_limit)*function(right_limit))<0)
	{
		int quantity_steps=0;
		while(1)
		{
			x=(left_limit+right_limit)/2;
			quantity_steps++;
			if (fabs((function(x)))<eps)
			{
				break;	
			} 
			if (((function(left_limit))*(function(x)))<0)
			{
				right_limit=x;
			}
			else 
			{
				left_limit=x;
			}
		}
		printf("quantity steps=%d\n",quantity_steps);
		printf("X=%f\n",x);
	}
	else 
	{
		printf("Not completed convergence condition\n");
	}
}

void Chord(double x, double eps, double left_limit, double right_limit)
{
	int quantity_steps=0;
	double temp=0.0;
	x=left_limit;
	temp=((x*(function(right_limit))-right_limit*(function(x)))/((function(right_limit))-(function(x))));
	while(1)
	{
		if((fabs(temp-x))>eps)
		{
			quantity_steps++;
			temp=x;
			x=(temp*(function(right_limit))-right_limit*(function(temp)))/((function(right_limit))-(function(temp)));
		}
		else 
		{
			break;
		}
	}
	printf("quantity steps=%d\n",quantity_steps);
	printf("X=%f\n",x);
}

void Tangent(double x, double eps, double left_limit, double right_limit)
{
	bool convergence_flag=true;
	if (((function(left_limit))*(first_derivative(left_limit)))>0)
	{
		x=left_limit;
	}
	else
	{
		if (((function(left_limit))*(second_derivative(left_limit)))<0)
		{
			x=right_limit;
		}
		else
		{
			printf("Not completed convergence condition\n");
			convergence_flag=false;
		}
	}
	if (convergence_flag==true)
	{
		double temp=0.0;
		int quantity_steps=0;
		while(1)
		{
			temp=x;
			x=(x-((function(x))/(first_derivative(x))));
			quantity_steps++;
			if (fabs(x-temp)<eps)
			{
				break;
			}
		}
		printf("quantity steps=%d\n",quantity_steps);
		printf("X=%f\n",x);
	}
}

int main()
{
	double x=0,eps=0.001,left_limit=1,right_limit=2;
	while(1)
	{
		Menu();
		short int key_choise;
		scanf("%hu",&key_choise);
		switch(key_choise)
		{
			case (1):
			{
				Half_Division(x,eps,left_limit,right_limit);
				break;	
			}
			case (2):
			{
				Chord(x,eps,left_limit,right_limit);
				break;
			}
			case (3):
			{
				Tangent(x,eps,left_limit,right_limit);
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

