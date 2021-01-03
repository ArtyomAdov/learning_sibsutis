#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
struct spis {
    spis *next; 
        char el;   
};
struct tle {
    spis *head; 
	spis *tail;
};

void Fillocheredrand(spis *head,int n){
      srand((unsigned int) time(NULL));
      int k=n; spis *p,*tail=head;
     while (n){
     p=new spis;
     p->el=char(65+rand()%17);
     n--;
     p->next=tail->next;
     tail->next=p;}
     }
 
 void PrintSpis(spis *head) {
    spis *p;
    for(p = head; p; p = p->next)
        printf("%c ", p->el);
    printf("\n\n");

}
void priamoe(int m, char str[], tle array[]) {
    int H;
    for (int i = 0; i < m; ++i) {
        array[i].head = new spis;
        array[i].head->next = NULL;
        array[i].tail = array[i].head;
    }
    int length = strlen(str);
    for (int i = 0; i < length; ++i) {
        H = int(str[i]) % m;
        spis *p = new spis;
        p->el = str[i];
        p->next = NULL;
        array[H].tail->next = p;
        array[H].tail = p;
    }
    for(int i = 0; i < m; ++i) {
        printf("Spis %d: ", i);
        PrintSpis(array[i].head->next);
    }
}
    void priamoesearch(int m, char key, tle array[]) {
    int H;
    H = int(key) % m;
    spis *p = array[H].head;
    int i=-1;
    while (p) {
        if (p->el == key) {
            printf("Key found = %c nomer pozicii v %d spiske %d \n", p->el,H,i);
            break;
        }
        p = p->next;i++;
    }
    if (p == NULL) printf("Key not found\n");
} 
    int priamaialinins(int m, char *arr, char ch) {
    int i = 1, count = 0;
    while (i != m) {
        int j = (int(ch) + i) % m;
        if (arr[j] != 0) {
            count++;
        }
        if (arr[j] == ch) break;
        if (arr[j] == 0) {
            arr[j] = ch;
            break;
        }
        ++i;
    }
    if (i==m){printf("perepolnenieline ");}
    return count;
}
void priamaialin(int t, char *array, char string[]) {
    int length = strlen(string);
    for (int i = 0; i < length; ++i) {
        char ch = string[i];
        priamaialinins(t, array, ch);
    }
    
    for (int i = 0; i < t; ++i) {
        printf("%d   ", i);printf("%c   ", array[i]);printf("\n");
    }
    printf("\n");
    
    
    printf("\n");
}
int poiskpopriamoilin(int m, char array[], char key) {
    
    int i = int(key) % m;
    while (i != m) {
        
        if (array[i] == key) {
            printf("nashli simvol = %c v meste %d\n", key,i);
            return i;
        }
        i++;
    }
    printf("ne nashli simvol\n");
}
int priamaia4ins(int m, char *arr, char ch) {
    int count = 0;
    int h = int(ch) % m;
    int d = 1;
    while (1) {//printf("%d ",d);
        if (arr[h] != 0) {count++;//printf("%d %d    ",arr[h],ch);
        }/////
        if (arr[h] == ch) {break;}       
        if (arr[h] == 0) {arr[h] = ch;{break;}}
        
        if (d >= m) {{printf("perepolnenie");break;}}
     
        h = h + d;
        if (h >= m) {h = h - m;}
        d=d+2;
        
    }
    return count;
}
void priamaia4(int t, char *array, char string[]) {
    int length = strlen(string);
    for (int i = 0; i < length; ++i) {
        char ch = string[i];
        
       priamaia4ins(t, array, ch);
        
    }
  
    for (int i = 0; i < t; ++i) {
        printf("%d  ", i);printf("%c  ", array[i]);printf("\n");
    }
    printf("\n");
 
    
    printf("\n");
}
int poiskpriamaia4(int m, char *array, char ch) {
    int h = int(ch) % m;
    int d = 1;
    while (1) {
        if (array[h] == ch) {
            printf("nashli simvol = %c v meste %d\n", ch,h);
            break;
        }
        if (array[h] == 0) {
            printf("ne nashli \n");
            break;
        }
        
        if (d >= m) {
            break;
        }
        h = h + d;
        if (h >= m) h = h - m;
        d = d + 2;
    }
}
void Print_Table(int t, char *arr, char *arr_2, char *str) {
    int length = strlen(str);
    int S_1 = 0, S_2 = 0;
    length = strlen(str);
    for (int n = 0; n < length; ++n) {
        char ch = str[n];
        int count_1 = priamaialinins(t, arr, ch);
        S_1 += count_1;
        int count_2 = priamaia4ins(t, arr_2, ch);
        S_2 += count_2;
    }
    printf("%d  %d \n", S_1, S_2);
}
     int main(){
         int n=11;
         tle c[n];
         int i;
         spis* p;
        char array[n];
    char array1[n];
         for (i = 0; i < n; i++) {
            c[i].tail = (spis *) &c[i].head;
        }
         spis *S=NULL;
     S=new spis;
      S->next=NULL; 
        Fillocheredrand(S,n);
    
     p=S->next;
     char string[] = "DVORNIKOVBCDEF";
     char st[] = "bewithlonkymarz";
     for (int i = 0; i < n; ++i) {
        array[i] = 0;
        array1[i] = 0;
    }
     //priamaialin(n, array, string);
    //poiskpopriamoilin(n, array, 'R');
    priamaia4(n, array1, string);
    poiskpriamaia4(n, array1, 'R');
     Print_Table(n, array, array1, string);
    
            //priamoe(n,st,c);
        //priamoesearch(n, 'r', c);
         
        //for(int e=0;e<17;e++){
                //PrintSpis(c[e].head->next);
                //}
        system("PAUSE");
         }
