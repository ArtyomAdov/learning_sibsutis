#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <clocale>
const int n=5;
int A[n];
int FillInc(int);
int FillDec(int);
int FillRand(int);
int CheckSum(int);
int RunNumber(int);
int PrintMas(int);
int SrednDlinaSer(int);
int Sosedstva(int);
int Vruchnuu(int);

main() {//доп задание лист 8
    int x;
    menu:
	printf("1) Zapolnit massiv po vozrastaniu\n");
	printf("2) Zapolnit massiv po ubivaniu\n");
	printf("3) Zapolnit massiv randomno\n");
	printf("4) Opredelit kontrolnuu summu\n");
	printf("5) Opredelit kolichestvo seriy\n");
	printf("6) Vivesti massiv\n");
	printf("7) Ochistit ekran\n");
	printf("8) Opredelit srednuu dlinu serii\n");
	printf("9) Opredelit chislo sosedstv dvuh chisel raznogo znaka\n");
	printf("0) Vihod is programmi\n");
	klavisha:
	scanf("%d",&x);
	switch(x) {
	    case 1: {
	        FillInc(n);
	        goto klavisha;
	    };
	    case 2: {
		    FillDec(n);
		    goto klavisha;
	    };
	    case 3: {
		    FillRand(n);
		    goto klavisha;
	    };
	    case 4: {
	        CheckSum(n);
	        goto klavisha;
        };
	    case 5: {
		    RunNumber(n);
	        goto klavisha;
	    };
	    case 6: {
		    PrintMas(n);
		    goto klavisha;
	    };
	    case 7: {
		    system("CLS");
		    goto menu;
	    };
	    case 8: {
			SrednDlinaSer(n);
			goto klavisha;
		}
		case 9: {
			Sosedstva(n);
			goto klavisha;
		}
	    case 0: {
		    break;
	    };
    };
    	if(x>10) {
		goto klavisha;
	};
}

FillInc(int n1) {
	for(int i=0;i<n1;i++) {
		A[i]=i;
	    printf("%d ",A[i]);
	};
	printf("\n\n");
}
FillDec(int n1) {
	for(int i=0;i<n1;i++) {
		A[i]=n1-i;
		printf("%d ",A[i]);
	};
	printf("\n\n");
}
FillRand(int n1) {
	srand(time(NULL));
	for(int i=0;i<n1;i++) {
		A[i]=rand()%n1;
		A[i]=A[i]-5;
		printf("%d ",A[i]);
	};
	printf("\n\n");
}
CheckSum(int n1) {
	int s=0;
	for(int i=0;i<n1;i++) {
		 s=s+A[i];
	};
	printf("%d\n\n",s);
}
int RunNumber(int n1) {
	int k=0;
	for(int i=0;i<n1;i++) {
		if(i==(n1-1)) {
			if(A[i]<=A[i-1]) {
				k++;
				printf("%d",A[i]);
				goto exit;
			};
		};
		if(A[i]<=A[i+1]) {
			printf("%d",A[i]);
		}
		else {
			k++;
			printf("%d ",A[i]);
		};
	};
	exit:
	printf("\nkol-vo seriy=%d\n\n",k);
}
int PrintMas(int n1) {
	for(int i=0;i<n1;i++) {
		printf("%d ",A[i]);
	};
	printf("\n\n");
}
int SrednDlinaSer(int n1) {
	int d=0;
	float s=0,k=0;
	for(int i=0;i<n1;i++) {
		if(i==(n1-1)) {
			if(A[i]<=A[i-1]) {
				k++;
				printf("%d",A[i]);
				goto exit;
			};
		};
		if(A[i]<=A[i+1]) {
			printf("%d",A[i]);
		}
		else {
			k++;
			printf("%d ",A[i]);
		};	
	};
	exit:
	s=n1/k;
	d=n1/k;
	if(s>d) {
		d++;//в ином случае само округляется
	};
	printf("\nsrednyaya dlina seriy=%d\n\n",d);
}
int Sosedstva(int n1) {
	int k=0;
	for(int i=0;i<n1;i++) {
		if(A[i]>=0) {
			if(A[i+1]<0) {
				k++;
			}
		}
		if(A[i]<0) {
			if(A[i+1]>=0) {
				k++;
			}	
		}
	}
	printf("kol-vo sosedstv raznogo znaka=%d\n",k);
}
