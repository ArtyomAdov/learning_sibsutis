
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <conio.h>


int SearchScan (char *haystack, int n, char *needle, int m);
int RabinKarp (char *haystack, int n, char *needle, int m);
int Hash(char* str, int m);

int C;


int SearchScan(char *haystack, int n, char *needle, int m)
{
	int i = -1, j;
	do {
		i++;
		j = 0;
		C++;
		while ( (j < m) && (haystack[i+j] == needle[j]) )
		{
			j++;
			C++;
		}
	} while ( (j != m) && (i < (n - m)) );
	return i;
}

int RabinKarp (char *haystack, int n, char *needle, int m)
{
	int hash_needle = Hash(needle, m);
	int hash_haystack = Hash(haystack, m);
	int i;
	for(i = 0; i < (n - m + 1); i++)
	{
		if (hash_haystack == hash_needle)
		{
			C += m;
			if (strncmp(haystack+i, needle, m) == 0) 
			{
				return i;
			}
		}
		hash_haystack = Hash(haystack + i + 1, m);
	}
	return -1;
}

int Hash(char* str, int m) 
{
	int h = 0;
	for (int i = 0; i < m; i++)
		h = h*256 + str[i];
	h = h % 17;
	return h;
}



int main()
{
	setlocale(LC_ALL, "Russian");
 
	char haystack[] = {"Books in our life \n It is interesting to read different kind of books. Except of a living man there is nothing more wonderful than a book! They teach us and open their hearts to us as brothers, wrote Charles Kingsley, an English writer of the 19th century. \n Books teach us to live. We learn many things by reading books. There different kinds of books: novels, short stories, tales, fairy-tales, fables, poems, plays, memoirs, atlases and text-books.  Book can be humorous, adventurous, detective, fantastic, historical, political, and scientific. They can be interesting, thrilling, fascinating, exciting, powerful, useful, unusual, original, amusing, moving, true-to-life, well well-written, unoriginal.  Books are certainly one of the greatest inventions of man.  O. Wilde wrote: Books, I believe, may be divided into three groups:  obooks to read;  obooks to re-read;  obooks not to read at all. The third class is the most important. To tell people what to read is? As a rule, either useless or harmful. But to tell people what not to read is a very difficult matter.  Some English author once wrote: Some books are to be tasted, others to be swallowed and some few to be chewed and digested .  This quotation tells us how to read books of different kinds. Most travel books are to be tasted: it's enough to dip into them and read bits here and there. If you are fond of crime stories (Agatha Christie, Simenon and the rest of modern favourites), you will read them quickly, you'll swallow them. If a book is on an important subject, a\n"};
	char needle1[10] = {"Book"};
    char needle2[50] = {"Except of a living man there is nothing more"};
	char needle3[100] = {"Books teach us to live. We learn many things by reading books. There different kinds of"};
	printf("Haystack: ");
	puts(haystack);
	printf("Length: %i\n", strlen(haystack));
	printf("Needle1: ");
	puts(needle1);
	printf("Needle2: ");
	puts(needle2);
	printf("Needle3: ");
	puts(needle3);
 	
	int m;
	int i = 0;
	C = 0;
    printf("\n\nSearchScan: ");
	while (1){
		m = SearchScan(haystack + i, strlen(haystack + i), needle1, strlen(needle1));
		if (m + i == strlen(haystack) - strlen(needle1))
		{
			break;
		}
//		printf("SearchScan1: %d \n", m + i);
		i += m + 1;
	}
	printf("\nNumcomp1: %d \n",C);
	i = 0;
	m = 0;
	C = 0;
	
		while (1){
		m = SearchScan(haystack + i, strlen(haystack + i), needle2, strlen(needle2));
		if (m + i == strlen(haystack) - strlen(needle2))
		{
			break;
		}
//		printf("SearchScan2: %d \n", m + i);
		i += m + 1;
	}
	printf("Numcomp2: %d \n",C);
	i = 0;
	m = 0;
	C = 0;
	
	
		while (1){
		m = SearchScan(haystack + i, strlen(haystack + i), needle3, strlen(needle3));
		if (m + i == strlen(haystack) - strlen(needle3))
		{
			break;
		}
//		printf("SearchScan3: %d \n", m + i);
		i += m + 1;
	}
	printf("Numcomp3: %d \n",C);
 
	i = 0;
	m = 0;
	C = 0;
   //  printf("\n\nRabinKarp: ");
	while (1){
		m = RabinKarp(haystack + i, strlen(haystack + i), needle1, strlen(needle1));
		if (m == -1)
		{
			break;
		}
	//	printf("RabinKarp: %d \n", m + i);
		i += m + 1;
	}
	printf("\nNumcomp1: %d \n",C);

		C = i = m = 0;
		while (1){
			m = RabinKarp(haystack + i, strlen(haystack + i), needle1, strlen(needle1));
			if (m == -1)
			{
				break;
			}
			i += m + 1;
		}

	i = 0;
	m = 0;
	C = 0;
	
	while (1){
		m = RabinKarp(haystack + i, strlen(haystack + i), needle2, strlen(needle2));
		if (m == -1)
		{
			break;
		}
	//	printf("RabinKarp: %d \n", m + i);
		i += m + 1;
	}
	printf("Numcomp2: %d \n",C);

		C = i = m = 0;
		while (1){
			m = RabinKarp(haystack + i, strlen(haystack + i), needle2, strlen(needle2));
			if (m == -1)
			{
				break;
			}
			i += m + 1;
		}


	i = 0;
	m = 0;
	C = 0;
	while (1){
		m = RabinKarp(haystack + i, strlen(haystack + i), needle3, strlen(needle3));
		if (m == -1)
		{
			break;
		}
	//	printf("RabinKarp: %d \n", m + i);
		i += m + 1;
	}
	printf("Numcomp3: %d \n",C);

		C = i = m = 0;
		while (1){
			m = RabinKarp(haystack + i, strlen(haystack + i), needle3, strlen(needle3));
			if (m == -1)
			{
				break;
			}
			i += m + 1;
		}


	system("PAUSE");
}

