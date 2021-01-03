#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Menu
{
private:
	string text;
public:
	void open_file_string();
	void input_string();
	void output_string();
	void search_string(string);
	void search_delete_string(string);
	void delete_string();
	void save_file_string();
};

void Menu::open_file_string()
{
	string str;
	ifstream file;
	file.open("save_string.txt");
	file >> str;
	text = str;
	file.close();
}

void Menu::input_string()
{
	string str;
	cout << "Input string: ";
	cin >> str;
	text += str;
}

void Menu::output_string()
{
	cout << text << endl;
}

void Menu::search_string(string str)
{
	for (int i = 0; i < (int)text.length(); i++){
		if (str == text.substr(i, str.length())){
			cout << text.substr(i, str.length()) << endl;
		}
	}
}

void Menu::search_delete_string(string str)
{
	int k;
	while((k = text.find(str)) != -1){
		text.erase(k, str.length());
	}
}

void Menu::delete_string()
{
	text.clear();
}

void Menu::save_file_string()
{
	ofstream file;
	file.open("save_string.txt");
	file << text;
	file.close();
}

int main()
{

	string str = "people";
 
	Menu text;
	
	text.open_file_string();
	text.output_string();
	text.input_string();
	text.output_string();
	text.search_string(str.substr(0, 6));
	text.search_delete_string(str.substr(0, 6));
	text.output_string();
	text.save_file_string();
	text.delete_string();
	text.output_string();
	return 0;
}
