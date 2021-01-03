#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include "DB.h"

using namespace std;

class Base {
  protected:
    FILE *text;
    DB b2[4000];
    int index[4000];
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
    int binSearch(DB*, char*);

};

#endif // BASE_H
