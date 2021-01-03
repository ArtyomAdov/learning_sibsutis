#include "Base.h"

int sizeBase = 4000;

Base::Base() {
    for(int i(0); i < sizeBase; i++) index[i] = i;
    loadBase();

    cout << "--- Base load in memory. Index array is build. Base ready for work ---" << endl;
}

int Base::cmp(int pos, int t) {
    char t1 = b2[index[pos]].publisher[3],
         t2 = b2[index[t]].publisher[3];
    b2[index[pos]].publisher[3] = b2[index[t]].publisher[3] = '\0';
    if (strcmp(b2[index[pos]].publisher, b2[index[t]].publisher) < 0) { // check years
        b2[index[pos]].publisher[3] = t1;
        b2[index[t]].publisher[3] = t2;
        return 1;
    } else if (strcmp(b2[index[pos]].publisher, b2[index[t]].publisher) > 0) {
        b2[index[pos]].publisher[3] = t1;
        b2[index[t]].publisher[3] = t2;
        return 0;
    } else if (strcmp(b2[index[pos]].publisher, b2[index[t]].publisher) == 0) { // check mounth
        b2[index[pos]].publisher[3] = t1;
        b2[index[t]].publisher[3] = t2;

        t1 = b2[index[pos]].author[3];
        t2 = b2[index[t]].author[3];
        if (strcmp(b2[index[pos]].author, b2[index[t]].author) < 0) {
            b2[index[pos]].author[3] = t1;
            b2[index[t]].author[3] = t2;
            return 1;
        } else if (strcmp(b2[index[pos]].author, b2[index[t]].author) > 0) {
            b2[index[pos]].author[3] = t1;
            b2[index[t]].author[3] = t2;
            return 0;
        } else {
            b2[index[pos]].author[3] = t1;
            b2[index[t]].author[3] = t2;
            return 0;
        }
    }
}

void Base::heapify(int pos, int n) {
    while (2 * pos + 1 < n) {
        int t = 2 * pos + 1;

        if (2 * pos + 2 < n && !cmp(2 * pos + 2, t)) {
            t = 2 * pos + 2;
        }
        if (cmp(pos, t)) {
            int itmp = index[pos];
            index[pos] = index[t];
            index[t] = itmp;

            pos = t;
        } else break;

    }
}

void Base::heapMake(int n) {
    for (int i = n - 1; i >= 0; i--) {
        heapify(i, n);
    }
}

void Base::heapSort() {
    int n = sizeBase;
    heapMake(n);
    while(n > 0) {
        int itmp = index[0];
        index[0] = index[n - 1];
        index[n - 1] = itmp;

        n--;
        heapify(0, n);
    }
}

void Base::loadBase() {
    text = fopen("testBase1.dat", "rb");
    for(int i(0); i < sizeBase; i++) {
        fread(&b2[i], sizeof(b2[i]), 1, text);
    }
}

void Base::printBase() {
    int lockFlag;
    int printFlag = 21;
    for(int i = 0; i < printFlag; i++) {
        vivod(i);
        if(i == printFlag - 1) {
            if(printFlag >= 4000) return;
            cout << "Next? ";
            cin >> lockFlag;
            if(lockFlag) printFlag += 20;
            else return;
        }
    }
}

void Base::printBaseIndex() {
    int lockFlag;
    int printFlag = 21;
    for(int i(0); i < printFlag; i++) {
        vivod(i);
        if(i == printFlag - 1) {
            cout << "Next? ";
            cin >> lockFlag;
            if(lockFlag) printFlag += 20;
            else return;
        }
    }
}

int Base::binSearch(DB *b1, char *key) {
    int l = 0,
        r = sizeBase;
    int m = 0;
    while(l < r) {
        m = (l + r) / 2;
        if(strcmp(key, b1[index[m]].publisher) > 0)
            l = m + 1;
        else r = m;
    }

    return r;
}

void Base::searchBase() {
    int keyRoom;
    char *keySearch;

    cout << "Enter key search:";
    cin.getline(keySearch, 16);

    cout << "1. First" << endl
         << "2. All" << endl;
    cin >> keyRoom;
    int r = binSearch(b2, keySearch);
    switch(keyRoom) {
    case 1: {
        if(strcmp(b2[index[r]].publisher, keySearch) == 0) {
            vivod(r);
        } else cout << "Record is not found" << endl;
        break;
    }
    case 2: {
        for(int i = binSearch(b2, keySearch); ; i++) {
            if(strcmp(b2[index[r]].publisher, keySearch) == 0) {
                vivod(i);
            }
        }
        break;
    }
    default:
        cout << " !Error! ";
    }
    cout << "_______________________________________________" << endl;
}

void Base::errorEnterData() {
    cout << "!!! Error enter data !!!" << endl;
}

void Base::DB_vivod(int _i) {
    cout << setw(12) << b2[_i].author << ' '
         << setw(32) << b2[_i].title << ' '
         << setw(16) << b2[_i].publisher << ' '
         << setw(4) << b2[_i].year << ' '
         << setw(4) << b2[_i].num_of_page << ' '
         << endl;
}

void Base::vivod(int _i) {
    cout << setw(12) << b2[index[_i]].author << ' '
         << setw(32) << b2[index[_i]].title << ' '
         << setw(16) << b2[index[_i]].publisher << ' '
         << setw(4) << b2[index[_i]].year << ' '
         << setw(4) << b2[index[_i]].num_of_page << ' '
         << endl;
}


