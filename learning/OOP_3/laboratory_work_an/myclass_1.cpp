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
		virtual void otris(){
			setcolor(color);
			circle(x, y, R);
		}
		virtual void animeline(){
			int d=800, ch=600;
        	if((x>d) || (x<0)){
				z=-z;
			}
        	if((y>ch) || (y<0)) p=-p;
			x+=(5*z);
			y+=(5*p);    	
    	}
    	virtual void animer(float a){
		}
};

class otrez: public tPoint{
	protected:
		int x2;
		int y2;
	public: 
		otrez(){
		}
		otrez(int k){
			int d=800, ch=600;
			
				x2=rand()%((x+30)-(x-30)+1)+(x-30);
			
			
				y2=rand()%((y+30)-(y-30)+1)+(y-30);
			
			if(k==2){
				if(x>x2 && y<y2){
					p=-1;
					z=-1;
				}
				if(x<x2 && y<y2) p=-1;
				if(x>x2 && y>y2) z=-1;
			}		
		}
		virtual void otris() override{
			moveto(x, y);
			setcolor(color);
			lineto(x2, y2);
		}
		void Print(int i){
			cout<<i<<") ";
			cout<<"X: "<<x<<" Y: "<<y<<endl<<" X2: "<<x2<<" Y2: "<<y2;
			cout<<" R: "<<R;
			cout<<" Color: "<<color<<endl;
		}
		virtual void animeline() override{
			int d=800, ch=600;
        	if((x>d) || (x<0)) z=-z;
        	else if((x2>d) || (x2<0)) z=-z;
        	if((y>ch) || (y<0)) p=-p;
        	else if((y2>ch) || (y2<0)) p=-p;
			x+=(5*z);
			y+=(5*p);
			x2+=(5*z);
			y2+=(5*p);      	
    	}
    	virtual void animer(float a) override{
			if(y==y2 || y+1==y2){
				p=-p;
			}
			if(x==x2 || x+1==x2){
				z=-z;
			}
			x+=p;
			x2+=(-(p));
			y+=z;
			y2+=(-(z));
		}
};

class okr: public tPoint{
	public:
		okr(){
			R=rand()%(20-5+1)+5;
		}
		void otris() override{
			setcolor(color);
			circle(x, y, R);
			setfillstyle(1, color);
			floodfill(x, y, color);
		}
};

class pryam: public otrez{
	protected:
		int prym[10];
		int s, u;
	public:
		pryam(){
		}
		pryam(int k):otrez(k){
			int d=800, ch=600;
			if(k==2){
				z=1;
				p=1;
				s=1;
				u=1;
				x2=rand()%(x+30-(x+1)+1)+(x+1);
				y2=rand()%(y+50-(y+10)+1)+(y+10);
			}
			if(k==1){
				x2=rand()%(x+30-(x+1)+1)+(x+1);
				y2=rand()%(y+50-(y+10)+1)+(y+10);
			}
			prym[0]=x;
			prym[1]=y;
			
			prym[2]=x;
			prym[3]=y2;
			
			prym[4]=x2;
			prym[5]=y2;
			
			prym[6]=x2;
			prym[7]=y;
			
			prym[8]=prym[0];
			prym[9]=prym[1];
		}
		virtual void otris() override{
			setfillstyle(1,color);
			setcolor(color);
			fillpoly(5, prym);
		}
		virtual void animer(float a) override{
			if((prym[2]==prym[6]) || (prym[2]+1==prym[6])){
				z=-z;
			}
			if((prym[1]==prym[5]) || (prym[1]+1==prym[5])){
				s=-s;
			}
			if((prym[0]==prym[4]) || (prym[0]+1==prym[4])){
				u=-u;
			}
			if((prym[3]==prym[7]) || (prym[3]+1==prym[7])){
				p=-p;
			}
			prym[0]+=-s;
			prym[2]+=p;
			prym[4]+=s;
			prym[6]+=-p;
			prym[8]=prym[0];
			prym[1]+=u;
			prym[3]+=z;
			prym[5]+=-u;
			prym[7]+=-z;
			prym[9]=prym[1];
		}
		void Print(int i){
			for(i=0;i<10;i++){
				cout<<"prym["<<i<<"]= ";
				cout<<prym[i]<<" ";
			}
			cout<<" R: "<<R;
			cout<<" Color: "<<color<<endl;
		}
		virtual void animeline() override{
			int d=800, ch=600;
        	if((x>d) || (x<0)) z=-z;
        	else if((x2>d) || (x2<0)) z=-z;
        	if((y>ch) || (y<0)) p=-p;
        	else if((y2>ch) || (y2<0)) p=-p;
			x+=(5*z);
			y+=(5*p);
			x2+=(5*z);
			y2+=(5*p);
			
			prym[0]=x;
			prym[1]=y;
			
			prym[2]=x;
			prym[3]=y2;
			
			prym[4]=x2;
			prym[5]=y2;
			
			prym[6]=x2;
			prym[7]=y;
			
			prym[8]=prym[0];
			prym[9]=prym[1];      	
    	}
};

class trey:public otrez{
	private:
		int triy[8];
		int st[3];
		int s;
	public:
		trey(){
		}
		trey(int k):otrez(k){
			int i;
			if(k==2){
				x2=rand()%(x+30-(x+30)+1)+(x+30);
				y2=rand()%(y+30-(y+30)+1)+(y+30);
			}
			if(k==1){
				x2=rand()%(x+30-(x+30)+1)+(x+30);
				y2=rand()%(y+30-(y+30)+1)+(y+30);
			}
			s=1;
			triy[0]=x;
			triy[1]=y;
			
			triy[2]=x2;
			triy[3]=y;
			
			triy[4]=x2;
			triy[5]=y2;
			
			triy[6]=triy[0];
			triy[7]=triy[1];
			if(k==2){
				st[0]=sqrt(pow((triy[0]-triy[0]),2)+pow((triy[1]-triy[1]),2));
				st[1]=sqrt(pow((triy[2]-triy[0]),2)+pow((triy[3]-triy[1]),2));
				st[2]=sqrt(pow((triy[4]-triy[0]),2)+pow((triy[5]-triy[1]),2));
			}
		}
		void otris() override{
			setfillstyle(1,color);
			setcolor(color);
			fillpoly(4, triy);
		}
		void animeline() override{
			int d=800, ch=600;
        	if((x>d) || (x<0)) z=-z;
        	else if((x2>d) || (x2<0)) z=-z;
        	if((y>ch) || (y<0)) p=-p;
        	else if((y2>ch) || (y2<0)) p=-p;
			x+=(5*z);
			y+=(5*p);
			x2+=(5*z);
			y2+=(5*p);
			
			triy[0]=x;
			triy[1]=y;
			
			triy[2]=x2;
			triy[3]=y;
			
			triy[4]=x2;
			triy[5]=y2;
			
			triy[6]=triy[0];
			triy[7]=triy[1];
		}
		void animer(float a) override{
			triy[0]=st[0]*cos(a)+triy[0];
			triy[1]=st[0]*sin(a)+triy[1];
			
			triy[2]=st[1]*cos(a)+triy[0];
			triy[3]=st[1]*sin(a)+triy[1];
			
			if(s==1){
				triy[4]=triy[0];
				triy[5]=triy[3];
			}
			else{
				triy[4]=triy[2];
				triy[5]=triy[1];
				s=-s;
			}
			
		}
		void Print(int i){
			for(i=0;i<8;i++){
				cout<<"triy["<<i<<"]= ";
				cout<<triy[i]<<" ";
			}
			cout<<"X: "<<x<<" Y: "<<y<<endl<<" X2: "<<x2<<" Y2: "<<y2;
			cout<<" R: "<<R;
			cout<<" Color: "<<color<<endl;
		}
};

class ellips:public okr{
	private:
		float pro[2];
		float R2;
		float s=0.25, u;
	public:
		ellips(){
			R2=rand()%(20-5+1)+5;
			while(R2==R){
				R2=rand()%(25-5+1)+5;
			}
			
			pro[0]=R;
			pro[1]=R2;
		}
		void otris() override{
			setcolor(color);
			fillellipse(x,y,R,R2);
		}
		void animer(float a) override{
			if(pro[0]>pro[1]){
				if(R!=pro[1]){
					R+=(-s);
					R2+=s;
				}
				else{
					pro[0]=R;
					pro[1]=R2;
				}
			}
			if(pro[0]<pro[1]){
				if(R!=pro[1]){
					R+=s;
					R2+=-s;
				}
				else{
					pro[0]=R;
					pro[1]=R2;
				}
			}
		}
		void Print(int i){
			cout<<i<<") ";
			cout<<"X: "<<x<<" Y: "<<y;
			cout<<" R: "<<R<<" R2: "<<R2<<" S: "<<s;
			cout<<" Color: "<<color<<endl;
		}
};

class romb:public pryam{
	public:
		romb(){
		}
		romb(int k):pryam(k){
			x2=x;
			prym[0]=x;
			prym[1]=y;
			
			prym[2]=x-20;
			prym[3]=((y2-y)/2)+y;
			
			prym[4]=x;
			prym[5]=y2;
			
			prym[6]=x+20;
			prym[7]=((y2-y)/2)+y;;
			
			prym[8]=prym[0];
			prym[9]=prym[1];
		}
		void animeline() override{
			int d=800, ch=600;
        	if((x>d) || (x<0)) z=-z;
        	else if((x2>d) || (x2<0)) z=-z;
        	if((y>ch) || (y<0)) p=-p;
        	else if((y2>ch) || (y2<0)) p=-p;
			x+=(5*z);
			y+=(5*p);
			x2+=(5*z);
			y2+=(5*p);
			
			prym[0]=x;
			prym[1]=y;
			
			prym[2]=x-20;
			prym[3]=((y2-y)/2)+y;
			
			prym[4]=x;
			prym[5]=y2;
			
			prym[6]=x+20;
			prym[7]=((y2-y)/2)+y;;
			
			prym[8]=prym[0];
			prym[9]=prym[1];      	
    	}
    	void animer(float a) override{
			if((prym[2]==prym[6]) || (prym[2]+1==prym[6])){
				z=-z;
			}
			if((prym[1]==prym[5]) || (prym[1]+1==prym[5])){
				s=-s;
			}
			if((prym[0]==prym[4]) || (prym[0]+1==prym[4])){
				u=-u;
			}
			if((prym[3]==prym[7]) || (prym[3]+1==prym[7])){
				p=-p;
			}
			prym[0]+=-s;
			prym[2]+=-p;
			prym[4]+=s;
			prym[6]+=p;
			prym[8]=prym[0];
			prym[1]+=-u;
			prym[3]+=z;
			prym[5]+=u;
			prym[7]+=-z;
			prym[9]=prym[1];
		}
};
