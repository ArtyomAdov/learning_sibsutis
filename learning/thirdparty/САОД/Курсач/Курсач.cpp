/*              Библиогpафическая база данных "Жизнь замечательных людей"

     Стpуктуpа записи:
        Автоp:          текстовое поле 12 символов
                        фоpмат <Фамилия>_<буква>_<буква>
        Заглавие:       текстовое поле 32 символа
                        фоpмат <Имя>_<Отчество>_<Фамилия>
        Издательство:   текстовое поле 16 символов
        Год издания:    целое число
        Кол-во стpаниц: целое число

     Пpимеp записи из БД:
        Кловский_В_Б
        Лев_Hиколаевич_Толстой_________
        Молодая_гваpдия_
        1963
        864


				B = 1                 testBase1.dat
				C = 2                 по году издания и автоpу, К = год издания
				S = 4                 Цифpовая соpтиpовка
				D = 2                 Двоичное Б-дерево
				E = 3                 Код Фано
*/

const int N = 4000;
const int ESCAPE = 27;
const int n = 256;

#include <cstdio>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <cmath>

int *w, *ostIndex;
unsigned long int number;
float entropy;
float averageLength;

struct enterprise {
	char name[12];
	short int god;
	char zaglavie[32];
	char izdatelstvo[16];
	short int straniz;
};

struct qEnterprise {
	enterprise *data;
	qEnterprise *next;
} * ost[1000];

struct vertex {
	vertex *l;
	vertex *r;
	enterprise *data;
	int weight;
} * root;

struct codeStruct {
	unsigned char a;
	float p;
	char codeWord[50];
	int l;
} codeArray[n];

int stringCompare(char s1[], char s2[], int number) {
	int i;
	i = 0;
	do {
		if (s1[i] < s2[i])
			return 1;
		else if (s1[i] > s2[i])
			return 0;
		else
			i++;
	} while (i < number);
	return 2;
}

int izdatelstvoCompare(char s1[], char s2[]) {
	char p1[2], p2[2];
	int i = 7, k;
	while (1) {
		p1[0] = s1[i - 1];
		p1[1] = s1[i];
		p2[0] = s2[i - 1];
		p2[1] = s2[i];
		k = stringCompare(p1, p2, 2);
		if (k == 1 || k == 0)
			break;
		else
			i -= 3;
		if (i == 1 && k == 2) break;
	}
	return k;
}

void treeSearch(vertex *p, char *key_search) {
	if (p == NULL) return;
	while (p != NULL) {
		if (izdatelstvoCompare(key_search, p->data->izdatelstvo) == 1)
			p = p->l;
		else if (izdatelstvoCompare(key_search, p->data->izdatelstvo) == 0)
			p = p->r;
		else if (izdatelstvoCompare(key_search, p->data->izdatelstvo) == 2) {
			std::cout << std::setw(30) << p->data->name << " " << std::setw(3)
								<< p->data->god << " " << std::setw(22)
								<< p->data->zaglavie << " " << std::setw(10) << p->data->izdatelstvo
								<< std::endl;
			p = p->r;
			while (izdatelstvoCompare(key_search, p->data->izdatelstvo) == 2) {
				std::cout << std::setw(30) << p->data->name << " " << std::setw(3)
									<< p->data->god << " " << std::setw(22)
									<< p->data->zaglavie << " " << std::setw(10) << p->data->izdatelstvo
									<< std::endl;
				p = p->r;
				if (p == NULL) return;
			}
			return;
		}
	}
}

void print(struct enterprise **inx, int startNumber) {
	int key;
	system("CLS");
	for (int i = startNumber; i < startNumber + 20; ++i) {
		std::cout << std::setw(4) << i + 1 << " " << std::setw(12) << inx[i]->name
							<< " "<< std::setw(32) << inx[i]->zaglavie << " " << std::setw(16)
							<< inx[i]->izdatelstvo << std::endl<< " " << std::setw(4) << inx[i]->god
							<< " " << std::setw(4) << inx[i]->straniz;
	}
	if (startNumber + 20 == N) {
		std::cout << std::endl
							<< "End of DB. Press any key to return to menu";
		_getch();
		return;
	}
	std::cout << "\nPress ESC to exit" << std::endl
						<< "OR press any key except ESC to print 20 more elements"
						<< std::endl;
	key = _getch();
	if (key == ESCAPE) {
		key = 0;
		return;
	}
	print(inx, startNumber + 20);
}

int quickSortCompare(struct enterprise *inx1, struct enterprise *inx2) {
	int flag = 1;
	if (inx1->izdatelstvo[0] > inx2->izdatelstvo[0]) return 0;
	if (inx1->izdatelstvo[0] < inx2->izdatelstvo[0]) return 1;
	if (inx1->izdatelstvo[1] > inx2->izdatelstvo[1]) return 0;
	if (inx1->izdatelstvo[1] < inx2->izdatelstvo[1]) return 1;
	for (int i = 0; i < 30; ++i) {
		if (inx1->name[i] > inx2->name[i])
			return 0;
		else if (inx1->name[i] < inx2->name[i])
			return 1;
	}
	return 0;
}

void quickSort(struct enterprise **inx, int l, int r) {
	int t, i, j;
	struct enterprise *p;
	struct enterprise *x;
	while (l < r) {
		x = inx[l];
		i = l;
		j = r;
		while (i <= j) {
			while (quickSortCompare(inx[i], x)) i++;
			while (quickSortCompare(x, inx[j])) j--;
			if (i <= j) {
				p = inx[i];
				inx[i] = inx[j];
				inx[j] = p;
				i++;
				j--;
			}
		}
		if (j - l < r - i) {
			quickSort(inx, i, r);
			r = j;
		} else {
			quickSort(inx, l, j);
			l = i;
		}
	}
}

int binSearchCompare(char *inx1, char *inx2) {
	if (inx1[0] < inx2[0]) return 1;
	if (inx1[0] > inx2[0]) return 0;
	if (inx1[1] < inx2[1]) return 1;
	if (inx1[1] > inx2[1]) return 0;
	return 2;
}

void printTree(vertex *p) {
	if (p == NULL) return;
	printTree(p->l);
	std::cout << std::setw(30) << p->data->name << " " << std::setw(3)
						<< p->data->god << " " << std::setw(22)
						<< p->data->zaglavie << " " << std::setw(10) << p->data->izdatelstvo
						<< std::endl;
	printTree(p->r);
}

void deleteTree(vertex **p) {
	if ((*p) == NULL) return;
	deleteTree(&((*p)->l));
	deleteTree(&((*p)->r));
	delete *p;
	*p = NULL;
}

void treeAdd(char s[], int x, int index) {
	vertex **p;
	p = &root;
	while (*p != NULL) {
		if (izdatelstvoCompare(s, (*p)->data->izdatelstvo) == 1)
			p = &((*p)->l);
		else
			p = &((*p)->r);
	}
	if (*p == NULL) {
		(*p) = (vertex *)malloc(sizeof(vertex));
		(*p)->data = ost[ostIndex[index]]->data;
		(*p)->r = (*p)->l = NULL;
		(*p)->weight = x;
	}
}

void A2(int L, int R) {
	int i, wes = 0, sum = 0;
	if (L <= R) {
		for (i = L; i <= R; i++) wes += w[i];
		for (i = L; i <= R - 1; i++) {
			if ((sum < wes / 2) && (sum + w[i] >= wes / 2)) break;
			sum += w[i];
		}
		treeAdd(ost[ostIndex[i]]->data->izdatelstvo, w[i], i);
		A2(L, i - 1);
		A2(i + 1, R);
	}
}

int LessDate(int p, int q) {
  if (izdatelstvoCompare(ost[p]->data->izdatelstvo, ost[q]->data->izdatelstvo) == 1)
    return 1;
  else
    return 0;
}

void QuickSort_tree(int L, int R) {
  int x, i, j, t;
  x = ostIndex[L];
  i = L;
  j = R;
  while (i <= j) {
    while (LessDate(ostIndex[i], x)) i++;
    while (LessDate(x, ostIndex[j])) j--;
    if (i <= j) {
      t = ostIndex[i];
      ostIndex[i] = ostIndex[j];
      ostIndex[j] = t;
      i++;
      j--;
    }
  }
  if (L < j) QuickSort_tree(L, j);
  if (R > i) QuickSort_tree(i, R);
}

void binSearch(struct enterprise **inx) {
	qEnterprise *p, *head;
	head = new qEnterprise;
	head = NULL;
	system("CLS");
	std::cout << "Input key: " << std::endl;
	int l = 0, r = N - 1, m, i;
	char k[2];
	std::cin >> k;
	int index = 0;
	while (l < r) {
		m = (l + r) / 2;
		if (binSearchCompare(inx[m]->izdatelstvo, k) == 1)
			l = m + 1;
		else
			r = m;
	}
	if (binSearchCompare(inx[r]->izdatelstvo, k) == 2) {
		p = new qEnterprise;
		p->data = inx[r];
		head = p;
		ost[index] = new qEnterprise;
		ost[index]->data = inx[r];
		++index;
		while ((++r < N) && (binSearchCompare(inx[r]->izdatelstvo, k) == 2)) {
			p->next = new qEnterprise;
			p->next->data = inx[r];
			p = p->next;
			ost[index] = new qEnterprise;
			ost[index]->data = inx[r];
			++index;
		}
		p->next = NULL;
		for (p = head; p; p = p->next)
			std::cout << std::setw(30) << p->data->name << " " << std::setw(3)
								<< p->data->god << " " << std::setw(22)
								<< p->data->zaglavie << " " << std::setw(10) << p->data->izdatelstvo
								<< std::endl;
	} else
		printf("Not found!\n");
	std::cout << "Queue created, press ESCAPE to return OR press any key EXCEPT "
							 "ESCAPE to create and print a tree..." << std::endl;
	int key = _getch();
	if (key == ESCAPE) return;

	system("cls");
	w = new int[index];
	for (int i = 0; i < index; ++i) w[i] = rand() % 100 + 1;
	ostIndex = new int[index];
	for (int i = 0; i < index; ++i) ostIndex[i] = i;
	QuickSort_tree(0, index - 1);
	A2(0, index - 1);
	printTree(root);
	std::cout << "To do a search, press any key EXCEPT ESCAPE..." << std::endl;
	key = _getch();
	if (key == ESCAPE) {
		deleteTree(&root);
		return;
	}
	system("cls");
	char key_search[8];
	std::cout << "Input key (DD-MM-YY)" << std::endl;
	std::cin >> key_search;
	treeSearch(root, key_search);
	std::cout << " Press any key to return..." << std::endl;
	deleteTree(&root);	
	_getch();
}

void openFile() {
	int i, j = 0;
	unsigned char ch;
	FILE *f = fopen("testBase2.dat", "rb");
	for (i = 0; i < n; i++) {
		codeArray[i].a = i;
		codeArray[i].p = (float)(0);
		codeArray[i].l = 0;
	}
	while (!feof(f)) {
		fscanf(f, "%c", &ch);
		codeArray[ch].p += 1.0;
		number++;
	}
	fclose(f);
	for (i = 0; i < n; i++)
		if (codeArray[i].p != (float)(0)) {
			codeArray[i].p /= (float)number;
			j++;
		}
	number = (unsigned long int)(j);
}

void deleteBlank() {
	int i, j, k;
	codeStruct temp;
	for (i = 0; i < n - 1; i++) {
		k = 1;
		if (codeArray[i].p == (float)(0))
			for (j = i + 1; j < n; j++)
				if (k)
					if (codeArray[j].p != (float)(0)) {
						temp = codeArray[i];
						codeArray[i] = codeArray[j];
						codeArray[j] = temp;
						k = 0;
					}
	}
	i = 0;
	while (codeArray[i].p != 0.0) i++;
	number = (unsigned long int)(i);
}

void gilbertMurCode() {
	float q[n], s = 0.0;
	int i, j = 0;
	q[0] = codeArray[0].p / 2;
	codeArray[0].l = (int)(-log(codeArray[0].p) / log(2) + 2);
	s = codeArray[0].p;
	for (i = 1; i < number; i++) {
		q[i] = s + codeArray[i].p / 2;
		codeArray[i].l = (int)(-log(codeArray[i].p) / log(2) + 2);
		s += codeArray[i].p;
	}
	for (i = 0; i < number; i++)
		for (j = 0; j < codeArray[i].l; j++) {
			q[i] *= 2;
			codeArray[i].codeWord[j] = (char)(q[i]);
			if (q[i] > 1) q[i]--;
		}
	for (i = 0; i < number; i++) {
		entropy += -codeArray[i].p * log(codeArray[i].p) / log(2);
		averageLength += codeArray[i].l * codeArray[i].p;
	}
}

void codePrint() {
	system("cls");
	int i, j;
	float check = 0;
	for (i = 0; i < number; i++) {
		std::cout.precision(6);
		std::cout.setf(std::ios::fixed);
		std::cout << std::setw(1) << (char)codeArray[i].a << " "
							<< (float)codeArray[i].p << " " << std::setw(2)
							<< (int)codeArray[i].l << " ";
		for (j = 0; j < codeArray[i].l; ++j)
			std::cout << (int)codeArray[i].codeWord[j];
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::setw(8) << entropy << " - Entropy" << std::endl;
	std::cout << std::setw(8) << averageLength << " - Average length"
						<< std::endl;
	std::cout << std::setw(8) << entropy + 2 << " > " << averageLength
						<< std::endl
						<< std::endl;
	for (int i = 0; i < number; ++i) check += (float)codeArray[i].p;
	std::cout << "Sum of all chances: " << check << std::endl
						<< std::endl;
	std::cout << "Press any key to return..." << std::endl;
	_getch();
}

int main() {
	int key;
	int sortFlag = 0;
	enterprise *inx[N];
	enterprise ent[N];
	FILE *fp;
	fp = fopen("testBase1.dat", "rb");
	int n = fread((enterprise *)ent, sizeof(enterprise), N, fp);
	fclose(fp);
	for (int i = 0; i < N; i++) inx[i] = &ent[i];
	while (key != ESCAPE) {
		system("CLS");
		if (sortFlag) std::cout << "\t==Sorted!==\n" << std::endl;
		std::cout << "\t1. Print DB" << std::endl
							<< "\t2. Sort DB" << std::endl
							<< "\t3. Coding" << std::endl
							<< "\t4. BinSearch" << std::endl
							<< "\tPress ESC to exit" << std::endl;
		key = _getch();
		switch (key - 48) {
			case 1: {
				print(inx, 0);
				break;
			}
			case 2: {
				sortFlag = 1;
				system("CLS");
				std::cout << "Sorting...";
				quickSort(inx, 0, N - 1);
				break;
			}
			case 3: {
				number = 0;
				entropy = (float)(0);
				averageLength = (float)(0);
				openFile();
				deleteBlank();
				gilbertMurCode();
				codePrint();
				FILE *code = fopen("code.txt", "wb");
				for (int i = 0; i < number; i++) {
					for (int j = 0; j < codeArray[i].l; j++)
						fprintf(code, "%d", codeArray[i].codeWord[j]);
					fprintf(code, "\r\n");
				}
				fclose(code);
				break;
			}
			case 4: {
				if (sortFlag == 0) {
					system("CLS");
					std::cout << "DB not sorted!\n\n"
										<< "Press any key to continue..." << std::endl;
					_getch();
					break;
				}
				binSearch(inx);
				break;
			}
		}
	}
}
