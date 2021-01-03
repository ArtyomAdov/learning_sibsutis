#include <iostream>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <conio.h>
#include <cmath>
#include <string>

using namespace std;

class subject{
	protected:
		int color;
		float x, y, speed;
		int xcenter;
		int ycenter;
	public:
		subject(){
			xcenter=0;
			ycenter=0;
		}
		subject(int d,int ch){
			xcenter=d/2;
			ycenter=ch/2;
	 }
		virtual void otris()=0;
		virtual void anime()=0;
};

class star:public subject{
	private:
		char *name; 
		int a, b;
		int j, i;
		float R;
	public:
		star(int rada, int radb, float skor, int cvet, float raz, char *nazv, int d, int ch):subject(d,ch), i(1), j(1){
			a=rada;
			b=radb;
			speed=skor;
			color=cvet;
			R=raz;
			name=nazv;
			x=xcenter+a;
			y=ycenter+sqrt(pow(b,2)*((pow(a,2)-pow((x-xcenter),2))/pow(a,2)));
		}
		star(float koor1, float koor2, int cvet, float raz, char *nazv, int d, int ch):subject(d, ch), a(0), b(0){
			x=xcenter-koor1;
			y=ycenter-koor2;
			color=cvet;
			R=raz;
			name=nazv;
			speed=0;
		}
		void otris() override{
			int i=0;
			setcolor(color);
			circle(x, y, R);
			setfillstyle(1, color);
			floodfill(x,y,color);
			setcolor(0);
			setbkcolor(color);
			outtextxy(x-13, y-7, name);
			setbkcolor(0);
			setcolor(color);
			luchiki();
		}
		void anime() override{
			if(j==1){
				if((x>xcenter-a) && (x-speed>xcenter-a)){
					i=-1;
				}
				else{
					j=0;
					i=1;
				}
			}
			if(j==0){
				if((x<xcenter+a) && (x+speed<xcenter+a)){
					i=1;
				}
				else{
					i=-1;
					j=1;
				}
			}
			if(speed>0){
				x=x+(speed*i);
				y=pow(b,2)*((pow(a,2)-pow((x-xcenter),2))/pow(a,2));
				y=sqrt(y);
				y=(y*i)+ycenter;
			}
			else throw "неправильной подачи в переменную skor";
		}
		void luchiki(){
			moveto(x+R+5,y);
			lineto(x+R+40,y);
			moveto(x-R-5,y);
			lineto(x-R-40,y);
			
			moveto(x,y+R+5);
			lineto(x,y+R+40);
			moveto(x,y-R-5);
			lineto(x,y-R-40);
			
			moveto(x+R-2.5,y+R-2.5);
			lineto(x+R+30,y+R+30);
			moveto(x-R+2.5,y-R+2.5);
			lineto(x-R-30,y-R-30);
			
			moveto(x+R-2.5,y-R+2.5);
			lineto(x+R+30,y-R-30);
			moveto(x-R+2.5,y+R-2.5);
			lineto(x-R-30,y+R+30);
			
			moveto(x+R+5,y-R+15);
			lineto(x+R+25,y-R+5);
			moveto(x-R-5,y-R+15);
			lineto(x-R-25,y-R+5);
			
			moveto(x-R-5,y+R-15);
			lineto(x-R-25,y+R-5);
			moveto(x+R+5,y+R-15);
			lineto(x+R+25,y+R-5);
			
			moveto(x+R-15,y-R-5);
			lineto(x+R-7.5,y-R-20);
			moveto(x-R+15,y-R-5);
			lineto(x-R+7.5,y-R-20);
			
			moveto(x-R+15,y+R+5);
			lineto(x-R+7.5,y+R+20);
			moveto(x+R-15,y+R+5);
			lineto(x+R-7.5,y+R+20);
		}
};

class planet:public subject{
	private:
		int a, b, kol, *dal;
		char *name;
		int i, j;
		float R;
		bool belt;
		
				
	public:
		planet(int rada, int radb, float skor, int cvet, float raz, char *nazv, int d, int ch, bool poyas):subject(d,ch), i(1), j(1){
			int k;
			float koor1, koor2, s;
			a=rada;
			b=radb;
			speed=skor;
			color=cvet;
			R=raz;
			name=nazv;
			belt=poyas;
			x=xcenter+a;
			y=ycenter+sqrt(pow(b,2)*((pow(a,2)-pow((x-xcenter),2))/pow(a,2)));
			if(belt){
				kol=rand()%(6-1+1)+1;
				dal=new int [kol];
				for(k=0;k<kol;k++){
					dal[k]=rand()%(15-3+1)+3;
				}
			}
		}
		void otris() override{
			int g;
			setcolor(color);
			circle(x, y, R);
			setfillstyle(1, color);
			floodfill(x,y,color);
			if(belt){
				setcolor(8);
				for(g=0;g<kol;g++){	
					circle(x,y,R+dal[g]);	
				}
				setcolor(15);
				setbkcolor(0);
				outtextxy(x-12, y-R-33, name);
			}
			else{
				setcolor(15);
				setbkcolor(0);
				outtextxy(x-12, y-R-17, name);
			}
		}
		void anime() override{
			if(j==1){
				if((x>=xcenter-a) && (x-speed>=xcenter-a)){
					i=-1;
				}
				else{
					j=0;
					i=1;
				}
			}
			if(j==0){
				if((x<=xcenter+a) && (x+speed<=xcenter+a)){
					i=1;
				}
				else{
					i=-1;
					j=1;
				}
			}
			if(speed>0){
				x=x+(speed*i);
				y=pow(b,2)*((pow(a,2)-pow((x-xcenter),2))/pow(a,2));
				y=sqrt(y);
				y=(y*i)+ycenter;
			}
			else throw "неправильной подачи в переменную skor";
		}
};

class kam:public subject{
	private:
		int a, b;
		float R;
		int i, j;
		int koltpoint;
		class tpoint{
			private:
				float x2, y2;
				int i, j;
				int a2, b2;	
			public:
				tpoint(){
				}
				tpoint(float x, float y, int z, int f, int a, int b): i(z), j(f){
					x2=x;
					y2=y;
					a2=a;
					b2=b;
				}
				void otrist(float R, int color){
					setcolor(color);
					circle(x2, y2, R);
					//cout<<"   |x2="<<x2<<"  | y2="<<y2<<endl;
				}
				void animet(int xcenter, int ycenter, float speed){
					if(j==1){
						if((x2>=xcenter-a2) && (x2-speed>=xcenter-a2)){
							i=-1;
						}
						else{
							j=0;
							i=1;
						}
					}
					if(j==0){
						if((x2<=xcenter+a2) && (x2+speed<=xcenter+a2)){
							i=1;
						}
						else{
							i=-1;
							j=1;
						}
					}
					if(speed>0){
						x2=x2+(speed*i);
						y2=pow(b2,2)*((pow(a2,2)-pow((x2-xcenter),2))/pow(a2,2));
						y2=sqrt(y2);
						y2=(y2*i)+ycenter;
					}
					//cout<<"   |x2="<<x2<<"  | y2="<<y2<<endl;
				}
		};
		tpoint *chastica;
	public:
		kam(int rada, int radb, float skor, int d, int ch, int kol1, int r1, int r2):subject(d,ch),i(1),j(1), R(1){
			int s, g;
			a=rada;
			b=radb;
			srand(time(NULL));
			speed=skor;
			color=8;
			koltpoint=kol1;
			chastica = new tpoint [koltpoint];
			x=xcenter+a;
			for(s=0;s<koltpoint;s++){
				g=rand()%(r1-(r2)+1)+(r2);
				a=g+rada;
				b=g+radb;
				if(j==1){
					if((x>xcenter-a) && (x-speed>xcenter-a)){
						i=-1;
					}
					else{
						j=0;
						i=1;
					}
				}
				if(j==0){
					if((x<xcenter+a) && (x+speed<xcenter+a)){
						i=1;
					}
					else{
						i=-1;
						j=1;
					}
				}
				if(speed>0){
					x=x+(5*i);
					y=pow(b,2)*((pow(a,2)-pow((x-xcenter),2))/pow(a,2));
					y=sqrt(y);
					y=(y*i)+ycenter;
					chastica[s]=tpoint(x,y, i, j, a, b);
				}
			}
		}
		void otris() override{
			int s;
			for(s=0;s<koltpoint;s++){
				//cout<<"s="<<s;
				chastica[s].otrist(R,color);
			}
			cout<<endl;
		}
		void anime() override{
			int s;
			for(s=0;s<koltpoint;s++){
				//cout<<"s="<<s;
				chastica[s].animet(xcenter,ycenter,speed);
			}
		}
};

class model{	
	public:
		system();
		void show(subject *object){
			object->otris();
		}
		void dvij(subject *object){
			object->anime();
		}
};


