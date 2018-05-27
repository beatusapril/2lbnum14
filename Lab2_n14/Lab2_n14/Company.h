#pragma once
#include <stdio.h>
#include <sstream>
#include <math.h>
#include <string>
#include <iostream>
#include <string>
#include "HelpUtils.h"
//using namespace std;

//подтип дата
class MyDate {

	// проверка является ли год високосным
	bool IsLeap(int year)
	{
		if (year % 4)
			return false;
		if (year % 100)
			return true;
		return !(year % 400);
	}

	// проверка даты на корректность
	bool CorrectDate(int day, int month, int year,string &message) {

	    // если год вискосный                            если не високосный
		if ((month == 2 && day > 29 && IsLeap(year)) || (month == 2 && day > 28 && !IsLeap(year)))
		{
			message = "Неверное кол-во дней в феврале!";
			return false;
		}
		//кол-во дней в месяце
		if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			if (day > 30) 
			{
				message = "Неверное кол-во дней в месяце!";
				return false;
			}
		}
	}
public:
	// день
	int day;
	// месяц
	int month;
	// год
	int year;

	// конструктор по умолчанию
	MyDate()
	{
		int day=1;
		int month=1;
		int year = 1970;
	}

	// ввод даты с консоли
	void InputDate()
	{
		bool correct_date = true; // корректна ли введенная дата
		string message = "";  // сообщение о причине ошибки
		do
		{
			if (!correct_date)
				cout << message << endl;
			day = InputNumber(1, 31, "Ввод даты:\nВведите день (1-31): ");
			month = InputNumber(1, 12, "Введите номер месяца (1-12): ");
			year = InputNumber(1970, 2100, "Введите год (1970-2100): ");
			correct_date = CorrectDate(day, month, year, message);
		} while (!correct_date);  // повторять ввод пока не корректная дата
	}

	// перевод даты в строку (для последующей записи в файл)
	 string ToString()
	{
		return (to_string(day) + ' ' + to_string(month) + ' ' + to_string(year));
	}
	
	// перегруженный оператор равенства
	bool operator == (const MyDate &c)
	{
		return ((day == c.day) && (month == c.month) && (year == c.year));
	}

	// конструктор копирования
	MyDate& operator = (MyDate c)
	{
		day = c.day;
		month = c.month;
		year = c.year;

		return (*this);
	}

	// перегруженный оператор больше
	bool operator > (const MyDate &c)
	{
		return ((year > c.year) || ((year == c.year) && (month > c.month)) || ((year == c.year) && (month == c.month) && (day>c.day)));
	}

	// перегруженные оператор меньше
	bool operator < (const MyDate &c)
	{
		return ((year < c.year) || ((year == c.year) && (month < c.month)) || ((year == c.year) && (month == c.month) && (day<c.day)));
	}

};

class Company {
public:
	// название фирмы
	string company_name;
	// вид работы
	string type_of_work;
	// единица измерения
	string unit;
	// стоимость единицы выполнения работ
	int cost;
	// дата исполнения
	MyDate exec_date;
	// обьем работ
	int scope_of_work;

	// конструктор по умолчанию
	Company()
	{
		string company_name="";
		string type_of_work="";
		string unit="";
		int cost=0.0;
		MyDate exec_date;
		int scope_of_work=0;
	}


	// изменение структуры "компания"
	Company ChangeCompany(Company &result)
	{
		if (InputNumber(0,1,"Вы хотите изменить имя компании "+result.company_name+" (0 - нет, 1 - да)\nВыш выбор: ")==1)
			result.company_name = InputInformation("Введите новое имя компании: ");
		if (InputNumber(0, 1, "Вы хотите изменить тип работы " + result.type_of_work + " (0 - нет, 1 - да)\nВыш выбор: ") == 1)
			result.type_of_work = InputInformation("Введите новый тип работы: ");
		if (InputNumber(0, 1, "Вы хотите изменить единицу измерения " + result.unit + " (0 - нет, 1 - да)\nВыш выбор: ") == 1)
			result.unit = InputInformation("Введите новую единицу измерения: ");
		if (InputNumber(0, 1, "Вы хотите изменить стоимость единицы выполнения работ " + to_string(result.cost) + " (0-нет, 1 - да)\nВыш выбор: ") == 1)
			result.cost = InputNumber(0,1000000,"Введите новую стоимость (0 - 1000000): ");
		if (InputNumber(0, 1, "Вы хотите изменить дату исполнения (0 - нет, 1 - да) \nВыш выбор: ") == 1)
			result.exec_date .InputDate();
		if (InputNumber(0, 1, "Вы хотите изменить обьем работ " + to_string(result.cost) + " (0 - нет, 1 - да)\nВыш выбор: ") == 1)
			result.scope_of_work = InputNumber(0, 100000, "Введите обьем работ (0 - 100000): ");

		return result;
	}

	// перегруженный оператор равенства для структуры "компания"
	Company& operator = (Company c)
	{
		company_name = c.company_name;
		type_of_work = c.type_of_work;
		unit = c.unit;
		cost = c.cost;
		exec_date = c.exec_date;
		scope_of_work = c.scope_of_work;

		return (*this);
	}
};

// функция ввода структуры "компания" с консоли
Company InputScreenCompany()
{
	Company c;
	c.company_name = InputInformation("Введите имя компании: ");
	c.type_of_work = InputInformation("Введите тип работы: ");
	c.unit = InputInformation("Введите единицу измерения: ");
	c.cost = InputNumber(0, 1000000, "Введите стоимость единицы выполненной работы (0 - 1000000): ");
	c.exec_date.InputDate();
	c.scope_of_work = InputNumber(0, 10000, "Введите обьем работ (0 - 10000): ");
	return c;
}

// функция вывода структуры "компания" на консоль
void OutputScreenCompany(Company c)
{
	cout << "Имя компании: " << c.company_name << endl;
	cout << "Тип работы: " << c.type_of_work << endl;
	cout << "Единица измерения: " << c.unit << endl;
	cout << "Стоимость единицы работы: " << c.cost << endl;
	cout << "Дата: " << c.exec_date.ToString() << endl;
	cout << "Обьем работ: " << c.scope_of_work << endl;
}


//извлечение структуры "дата" из строки 
// Формат:
// день месяц год
MyDate FromString(string str)
{
	MyDate result;
	try
	{
		istringstream is(str);
		string s;
		if (getline(is, s, ' '))
			result.day = atoi(s.c_str());
		if (getline(is, s, ' '))
			result.month = atoi(s.c_str());
		if (getline(is, s, ' '))
			result.year = atoi(s.c_str());
	}
	catch (...)
	{
		cout << "Ошибка записи в файл!" << endl;
	}
	return result;
}

//перевод структуры "компания" в строку
string ToString(Company c,int i)
{
	string result ="Запись № "+to_string(i)+"\n"+ "Имя компании: "+c.company_name+"\n"+"Тип работы: "+c.type_of_work+"\n"+"Единица измерения: "+c.unit+"\n"+"Стоимость единицы работы: "+to_string(c.cost)+"\n"+"Дата: " + c.exec_date.ToString() + "\n"+ "Обьем работ: " + to_string(c.scope_of_work)+"\n";
	return result;
}

////считывание структуры "компания" из строки
Company ReadFromString(ifstream& input)
{
	Company result;
	string s;
	try
	{
		if (!input.eof())
		{
			getline(input, s);
		}
		if (!input.eof())
		{
			getline(input, s,'\n');
			string wrd = "Имя компании: ";
			result.company_name = s.substr(wrd.length(), s.length());
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Тип работы: ";
			result.type_of_work = s.substr(wrd.length(), s.length());
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Единица измерения: ";
			result.unit = s.substr(wrd.length(), s.length());
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Стоимость единицы работы: ";
			result.cost = atoi(s.substr(wrd.length(), s.length()).c_str());
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Дата: ";
			result.exec_date = FromString(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Обьем работ: ";
			result.scope_of_work = atoi(s.substr(wrd.length(), s.length()).c_str());
		}
	}
	catch (...)
	{
		cout << "Ошибка записи в файл!" << endl;
	}
	return result;
}


// поиск равного элемента по выбранному критерию
// type_search - тип поиска
//1 - по имени компании
//2 - по типу работы
//3 - по дате
bool SearchElement(Company m, Company n, int type_search)
{
	switch (type_search)
	{
		case 1:
			return (m.company_name == n.company_name);
		case 2:
			return (m.type_of_work == n.type_of_work);
		case 3:
			return (m.exec_date == n.exec_date);
		default:
			return false;
	}
}

// ввод критерия поиска в зависимости от выбранного типа 
// type_search - тип поиска
//1 - по имени компании
//2 - по типу работы
//3 - по дате
Company InputChangeTypeSearch(int type_search)
{
	Company result;
	switch (type_search)
	{
	case 1:
		result.company_name = InputInformation("Введите имя компании: ");
		return result;
	case 2:
		result.type_of_work = InputInformation("Введите тип работы: ");
		return result;
	case 3:
		result.exec_date.InputDate();
		return result;
	default:
		return result;
	}
}

// сравнения структур в зависимости от выбранного поля для сортировки
// type_search - тип поиска
//1 - по имени компании
//2 - по типу работы
//3 - по дате
int Sorte(Company n, Company m, int type_search)
{
	switch (type_search)
	{
	case 1:
		if (n.company_name > m.company_name) return 1;
		else if (n.company_name < m.company_name) return -1;
		else return 0;
	case 2:
		if (n.type_of_work > m.type_of_work) return 1;
		else if (n.type_of_work < m.type_of_work) return -1;
		else return 0;
	case 3:
		if (n.exec_date > m.exec_date) return 1;
		else if (n.exec_date < m.exec_date) return -1;
		else return 0;
	default:
		return -2;
	}
}




