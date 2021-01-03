#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <map>
using namespace std;

int main()
{
	map<string, int> poisk;
	string s;
	setlocale(LC_ALL, "rus");
	ifstream file("vvod.txt");
	ofstream temp("vivod.txt");
	getline(file, slova);
	istringstream ist(slova);// разбивает стрку на слова
	while (ist >> slova)
	{
		poisk[slova]++;
	}
	for (auto it = poisk.begin(); it != poisk.end(); ++it)
	{
		cout << it->first << "\t" << it->second << endl;
		temp << it->first << " \t " << it->second << endl;
	}
	return 0;
}
