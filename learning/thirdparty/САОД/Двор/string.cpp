#include <iostream>
#include <conio.h>

using namespace std;

// Функция вычисления контрольной суммы
float myHash1(char* inString, int N)
{
    int hash_sum=0;
    for(int i=0; i<N; i++)
    {
        hash_sum+=(int)inString[i];
    }
    return hash_sum;
}


// Алгоритм Рабина-Карпа
int RabinKarp(char* needle, int m, char* haystack, int n)
{
    float hash_needle = myHash1(needle,m); // Получаем ХЕШ подстроки
    float hash_haystack = myHash1(haystack, m);
    for(int i=0; i<(n-m+1); i++)
    {
        if(hash_haystack == hash_needle)
        {
            for(int j=i, jj=0; j<(i+m-1), jj<m; j++, jj++)
            {
                if(haystack[j] == needle[jj])
                {
                    cout<<"String found! :)"<<endl;
                    return i+1; // Возвращаем индекс
                }
            }
        }
        hash_haystack = myHash1(&haystack[i+1],m);
    }
    cout<<"String not found! :("<<endl;
    return -1;
}


// Определение длины строки
int length(char *string)
{
    int i=0;
    for(i=0;string[i] != '\0' ; i++);
    return i;
}


int main()
{
    char T[10000] = "ab"; // Сено
    char W[10000] = "ac"; // Игла

    cout<<"Please input STROKA: ";
    cin>>T;

    cout<<"Please input PODSTROKA: ";
    cin>>W;

    cout<<"STROKA = "<<T<<endl;
    cout<<"PODSTROKA = "<<W<<endl;

    int flag = RabinKarp(W,   length(W),   T,   length(T));
    cout<<"index = "<<flag;

    getch();
    return 0;
}
