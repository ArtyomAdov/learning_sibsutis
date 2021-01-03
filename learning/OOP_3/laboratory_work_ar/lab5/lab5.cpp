#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Table
{
	private:
		string tmp;
		string line;
		string note;
		string filename;
	public:
		Read_Files()
		{
			cout << "Write file name" << endl;
			cin >>filename;
			filename+=".txt";
			ifstream file;
    		file.open(filename.c_str(),ios::in);
			while(!file.eof())
			{
				getline(file,line,'\0');
				for (int i=0; i<int(line.length()); i++)
        		{
            		note +=line[i];
        		}
			}
			line.clear();
			file.close();
		}
		Input_Table()
		{
			ofstream file;
			file.open("Table.txt",ios::app);
			file << note;
			file.close();
			note.clear();
		}
		Print_Table()
		{
			ifstream file;
    		file.open("Table.txt",ios::in);
			while(!file.eof())
			{
				getline(file,line,'\0');
				for (int i=0; i<int(line.length()); i++)
        		{
            		note +=line[i];
        		}
			}
			cout << note << endl;
			line.clear();
			note.clear();
			file.close();
		}
		Delete_Table()
		{
			ofstream file;
			file.open("Table.txt",ios::out);
			file.close();
		}
		Menu()
		{
    		cout << "1) Read file" << endl;
    		cout << "2) Print Table" << endl;
    		cout << "3) Delete Table" << endl;
    		cout << "0) Exit" <<endl;
		}
};
int main()
{
	Table table;
	short int key=9;
	//short int key=0;
	while(key!=0)
	{
		system("CLS");
		table.Menu();
		cin >> key;
		switch(key)
		{
			case 1:
			{
				system("CLS");
				table.Read_Files();
				table.Input_Table();
				break;
			}
			case 2:
			{
				system("CLS");
				table.Print_Table();
				system("PAUSE");
				break;
			}
			case 3:
			{
				system("CLS");
				table.Delete_Table();
				break;
			}
			case 0:
			{
				break;
			}
		}
	}
	//table.Read_File();
	//table.Input_Table();
	//table.Print_Table();
}
