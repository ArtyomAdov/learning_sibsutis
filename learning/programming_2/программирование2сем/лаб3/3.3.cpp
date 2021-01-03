#include <iostream>
using namespace std;
int main(){
	int *a;
	int i, j, n, p;
	cout<<"vvedite poslednuu cifru posledovatelnosti"<<endl;
	cin>>n;
	a= new int [n+1];
	if(a==NULL){
		cout<<"ne udalos videlit pamyat"<<endl;
		return 1;
	}
	for(i=0;i<n+1;i++) a[i]=i;
	for (p=2;p<n+1;p++){
		if(a[p]!=0){
			cout<<a[p]<<endl;
			for(j=p*p;j<n+1;j+=p)
				a[j]=0;
		}
	}
	delete a;
	a=NULL;
	return 0;	
}
