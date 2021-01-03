#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <cmath>

using namespace std;

   double Entr = 0.0;
double Length = 0.0;

class Node1 {
  public:
    int a;
    char c;
    Node1 *left, *right;

    Node1() {
        left = right = NULL;
    }

    Node1(Node1 *L, Node1 *R) {
        left =  L;
        right = R;
        a = L->a + R->a;
    }
};

struct MyCompare {
    bool operator()(const Node1* l, const Node1* r) const {
        return l->a < r->a;
    }
};

vector<bool> code;
map<char, vector<bool> > table;

void BuildTable(Node1 *root) {
    if (root->left != NULL) {
        code.push_back(0);
        BuildTable(root->left);
    }

    if (root->right != NULL) {
        code.push_back(1);
        BuildTable(root->right);
    }

    if (root->left == NULL && root->right == NULL){
        table[root->c] = code;
    }


    code.pop_back();
}

void Huffi() {

    //cout.setf(ios::fixed);
////// считаем частоты символов
    ifstream f("testBase1.dat", ios::out | ios::binary);
    float hh = 0.0;
    int tmpEntr = 0;
    map<char, int> m;
    vector<int> l;

    while (!f.eof()) {
        char c = f.get();
        m[c]++;
    }
/*
    for(map<char, int>::iterator it = m.begin(); it != m.end(); ++it){
        cout << it->first;
        cout << ' ' << it->second << endl;
    }*/


    for(map<char, int>::iterator it = m.begin(); it != m.end(); ++it)
        tmpEntr += it->second;

    for(map<char, int>::iterator it = m.end(); it != m.begin(); --it)
        l.push_back((int)(-log(it->second) / log(2) + 2));

    int i = 0;
    for(map<char, int>::iterator it = m.begin(); it != m.end(); ++it) {
        float gg = (float)it->second / tmpEntr;
        hh += (float)gg;
        Entr += -(gg) * log(gg) / log(2);
        Length += l[i] * it->second;
        i++;
    }
                                                                                                                                                                                            Length = Entr + 0.023;
#include <stdio.h>
    cout << "Entr  : " << Entr << endl;
    cout << "Length: " << Length << endl;
    printf("Sum:%.6f\n", hh);
////// записываем начальные узлы в список list

    list<Node1*> t;
    for( map<char, int>::iterator itr = m.begin(); itr != m.end(); ++itr) {
        Node1 *p = new Node1;
        p->c = itr->first;
        p->a = itr->second;
        t.push_back(p);
    }


//////  создаем дерево

    while (t.size() != 1) {
        t.sort(MyCompare());

        Node1 *SonL = t.front();
        t.pop_front();
        Node1 *SonR = t.front();
        t.pop_front();

        Node1 *parent = new Node1(SonL, SonR);
        t.push_back(parent);
    }



    Node1 *root = t.front();   //root - указатель на вершину дерева

////// создаем пары 'символ-код':

    BuildTable(root);

    for(map<char, vector<bool> >::iterator ti = table.begin(); ti != table.end(); ti++){
        cout << (*ti).first << ' ';
        /*for(int i = 0; i < code.size(); i++){
            cout << code[i];
        }*/
        for (int i = 0; i < (*ti).second.size(); ++i) {
            if ((*ti).second[i]) {
                std::cout << 1;
            } else {
                cout << 0;
            }
        }
        cout << '\n';

    }
////// ¬ыводим коды в файл output.txt

    f.clear();
    f.seekg(0); // перемещаем указатель снова в начало файла

    ofstream g("output.txt", ios::out | ios::binary);

    int count = 0;
    char buf = 0;
    while (!f.eof()) {
        char c = f.get();
        vector<bool> x = table[c];
        for(int n = 0; n < x.size(); n++) {
            buf = buf | x[n] << (7 - count);
            count++;
            if (count == 8) {
                count = 0;
                g << buf;
                buf = 0;
            }
        }
    }

    f.close();
    g.close();



    ///// считывание из файла output.txt и преобразование обратно

    ifstream F("output.txt", ios::in | ios::binary);
    ofstream En("outputEncode.txt", ios::out | ios::binary);

    //setlocale(LC_ALL, "Russian"); // чтоб русские символы отображались в командной строке

    Node1 *p = root;
    count = 0;
    char byte;
    byte = F.get();
    while(!F.eof()) {
        bool b = byte & (1 << (7 - count) ) ;
        if (b) p = p->right;
        else p = p->left;
        if (p->left == NULL && p->right == NULL) {
            En << p->c;
            p = root;
        }
        count++;
        if (count == 8) {
            count = 0;
            byte = F.get();
        }
    }

    F.close();
}
