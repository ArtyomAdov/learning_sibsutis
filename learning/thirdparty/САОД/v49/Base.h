#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include "DB.h"
#include "B.h"
#include "queue.hpp"

using namespace std;

class Base {
  protected:
    FILE *text;
    DB b2[4000];
    int index[4000];
    queue *q;
    Node *root;
  public:
    Base();

    //Sort-----------------------------------
    void heapify(int, int);
    void heapMake(int);
    void heapSort();

    // Download------------------------------
    void loadBase();

    // Print---------------------------------
    void printBase();
    void printBaseIndex();

    // Search--------------------------------
    void searchBase();

    // Errors--------------------------------
    void errorEnterData();

    int cmp(int, int);
    void vivod(int);
    void DB_vivod(int);
    void Q_print();
    int binSearch(DB*, char*);
    void B_tree();
    void lookup_tree();
    void P_BTree();


};

#endif // BASE_H
