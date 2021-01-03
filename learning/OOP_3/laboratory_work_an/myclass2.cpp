#include <iostream>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <conio.h>
#include <time.h>
#include <math.h>

using namespace std;

class tPoint{
	protected:
		int x;
		int y;
		float R;
		int color;
		int z;
		int p;
	public:
		tPoint(){
			int d=800, ch=600, i, k;
			R=1;
			z=1;
			p=1;
			x=rand()%((d)-(0)+1)+(0);
			y=rand()%((ch)-(0)+1)+(0);
			color=rand()%(15-1+1)+1;
		}
		void Print(int i){
			cout<<i<<") ";
			cout<<"X: "<<x<<" Y: "<<y;
			cout<<" R: "<<R;
			cout<<" Color: "<<color<<endl;
		}
		void otris(){
			setcolor(color);
			circle(x, y, R);
		}
		void animeline(){
			int d=800, ch=600;
        	if((x>d) || (x<0)){
				z=-z;
			}
        	if((y>ch) || (y<0)) p=-p;
			x+=(5*z);
			y+=(5*p);    	
    	}
    	void animechaos(){
    		int d=800, ch=600, k;
    		if(rand() % 2){
    			p=-p;
			}
			if(rand() % 2){
				z=-z;
			}
        	if((x>d) || (x<0)){
				z=-z;
			}
        	if((y>ch) || (y<0)) p=-p;
			x+=(5*z);
			y+=(5*p);  
		}
    	
};
