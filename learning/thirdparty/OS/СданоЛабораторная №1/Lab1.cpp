#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct student 
{
    string surname;
    string name;
    string middle;
    string date;
    string number_group;
    float gpa;
    student *next;
} *head;

void AddStudent(student *&ph, student *&pt, string surname, string name, string middle, string date, string number_group, float gpa) 
{
    student *t = new student;
    t->surname = surname;
	t->name = name;
	t->middle = middle;
	t->date = date;
	t->number_group = number_group;
	t->gpa = gpa;
    t->next = NULL;
    if (ph == NULL) 
	    ph = pt = t; 
	else 
	    pt = pt->next = t;
}	

void PrintStudent(student *ph) 
{
	setlocale(0,"RUS");
    if (ph == NULL) 
        cout << "Queque clear";
    while (ph != NULL) 
	{
        cout << ph->surname <<" "<< ph->name <<" "<< ph->middle <<" "<< ph->date <<" "<< ph->number_group <<" "<< ph->gpa;
        cout << endl; 
		ph = ph->next;
    }
    cout << endl; 
}

void FindStudent (student *ph, string surname, string number_group) 
{
	int k = 1;
	while (ph != NULL) 
	{
        if (ph->surname == surname && ph->number_group == number_group)  
		{
			cout << "Information of Find: " << endl;
            cout << k <<": " << ph->surname <<" "<< ph->name <<" "<< ph->middle <<" "<< ph->date <<" "<< ph->number_group <<" "<< ph->gpa << endl;
	        return;
	    } 
	    ph = ph->next;	
		k++;
    }
    cout << "Find of error!" << endl;
    return;
}

void DeleteStudent(student *&ph, int n) 
{
	student *t1 = ph;
	if (n == 1) 
	{
	    ph = t1->next;
	    delete t1;
	    return;
	}
	for (int i = 1; i < n - 1; ++i) 
	{
	    t1 = t1->next;
	    if ((t1 == NULL) || (t1->next == NULL)) 
		{
	        cout << "Error";
            cout << endl;
	        return;
	    }
	}
	student *t2 = t1->next;
	t1->next = t2->next;
	delete t2;
	return;
}
            
int main() 
{
    system("CLS");
    setlocale(0,"RUS");
    
    string surname, name, middle, date, number_group;
    float gpa; 
    student *t = new student;
    student *ph = NULL;
    student *pt = NULL; 
    int variant = 0;
    bool flag = true;
    while (1) 
	{	   
        cout << "Выберите вариант\n" << endl;
        cout << "1. Добавить\n"
        << "2. Посмотреть\n"
        << "3. Поиск по фамилии имени и группе\n"
        << "4. Удалить студента по номеру\n"
        << "5. Выйти\n" << endl;
        cout << "Выберите действие\n" << endl;
        
        cin >> variant;
        system("CLS");
        switch (variant) 
		{
            case 1: 
                while (flag) 
				{
                    cout << "Добавить студента:" << endl;
	                cout << "Фамилия, имя, отчество, дата рождения, номер группы, средний балл" << endl;
                    
					cin >> surname; 
					if (surname == "end") 
					{ 
					    break; 
					}
                    cin >> name >> middle >> date >> number_group >> gpa;
                    AddStudent(ph, pt, surname, name, middle, date, number_group, gpa);
	                
					cout << "Студент добавлен" << endl;
	                cout << endl;	
                }
                system("CLS");        	
	            break; 
            case 2:
	            cout << endl;	
                PrintStudent(ph);
                break;
            case 3:	
                cout <<"Поиск по фамилии и группе: " << endl;
                cin >> surname >> number_group; 
                FindStudent(ph, surname, number_group);
                break;                                         
            case 4:
                cout <<"Номер студента: ";
                int n;
	            cin >> n;
                cout << endl;
                DeleteStudent(ph, n);
                break;
	        case 5:
	            cout <<"Завершение работы" << endl;
              //  exit(EXIT_SUCCESS);	
            default:
                cout << "Вы выбрали неверный вариант";
        }
    }
    
	system("PAUSE");
    return 0;
}
