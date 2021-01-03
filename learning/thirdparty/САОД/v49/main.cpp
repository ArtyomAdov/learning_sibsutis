#include "Base.h"
#include "Huffman.h"
#include <cstdlib>

int main() {
    Base o;

    system("cls");
	int key = 0;
	do{
        cout << "_______________________" << endl;
		cout << "1. Print Base" << endl
            << "2. Sort" << endl
            << "3. Search In Base" << endl
            << "4. Print Queue" << endl
            << "5. Build " << endl
            << "6. Print Tree" << endl
            << "7. Search In Tree" << endl
            << "8. Code" << endl
            << "9. Print index" << endl
            << "0. Exit" << endl;
        cout << ">> ";
		cin >> key;
        system("cls");
		switch(key){
			case 1: o.printBase(); break;
			case 2: o.heapSort(); break;
			case 3: o.searchBase(); break;
			case 4: o.Q_print(); break;
			case 5: o.B_tree(); break;
			case 6: o.P_BTree(); break;
			case 7: o.lookup_tree(); break;
			case 8: Huffi(); break;
			case 9: o.printBaseIndex(); break;
			case 0: return 0;
			default: break;
		}
	} while(1);

    return 0;
}
