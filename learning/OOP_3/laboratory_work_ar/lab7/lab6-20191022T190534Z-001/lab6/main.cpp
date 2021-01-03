#include <iostream>
#include "Vector.h"

using namespace std;

int main (int argc, char *argv[]) {
	Vector<string> arr(12);
	for (int i = 0; i < 5; ++i)
	{
		arr.add_element("test", i);
	}
	arr.print();
	arr.delete_element(0);
	arr.print();
	arr.add_element("rrt", 0);
	arr.print();
	cout << arr.lookup_element(2) << endl;
	cout << arr[1] << endl;

	return 0;
}