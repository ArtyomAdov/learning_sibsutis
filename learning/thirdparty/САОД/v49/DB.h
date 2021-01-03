#ifndef DB_H
#define DB_H

struct DB {
    char author[12];
    char title[32];
    char publisher[16];
    short int year;
    short int num_of_page;
};

struct listnode {
    DB data;
    listnode *next;
    listnode *prev;
};

#endif // DB_H
