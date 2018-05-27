#pragma once
#include <stdio.h>
#include <sstream>
#include <math.h>
#include <string>
#include <iostream>
#include <string>
#include "HelpUtils.h"
//using namespace std;

//������ ����
class MyDate {

	// �������� �������� �� ��� ����������
	bool IsLeap(int year)
	{
		if (year % 4)
			return false;
		if (year % 100)
			return true;
		return !(year % 400);
	}

	// �������� ���� �� ������������
	bool CorrectDate(int day, int month, int year,string &message) {

	    // ���� ��� ���������                            ���� �� ����������
		if ((month == 2 && day > 29 && IsLeap(year)) || (month == 2 && day > 28 && !IsLeap(year)))
		{
			message = "�������� ���-�� ���� � �������!";
			return false;
		}
		//���-�� ���� � ������
		if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			if (day > 30) 
			{
				message = "�������� ���-�� ���� � ������!";
				return false;
			}
		}
	}
public:
	// ����
	int day;
	// �����
	int month;
	// ���
	int year;

	// ����������� �� ���������
	MyDate()
	{
		int day=1;
		int month=1;
		int year = 1970;
	}

	// ���� ���� � �������
	void InputDate()
	{
		bool correct_date = true; // ��������� �� ��������� ����
		string message = "";  // ��������� � ������� ������
		do
		{
			if (!correct_date)
				cout << message << endl;
			day = InputNumber(1, 31, "���� ����:\n������� ���� (1-31): ");
			month = InputNumber(1, 12, "������� ����� ������ (1-12): ");
			year = InputNumber(1970, 2100, "������� ��� (1970-2100): ");
			correct_date = CorrectDate(day, month, year, message);
		} while (!correct_date);  // ��������� ���� ���� �� ���������� ����
	}

	// ������� ���� � ������ (��� ����������� ������ � ����)
	 string ToString()
	{
		return (to_string(day) + ' ' + to_string(month) + ' ' + to_string(year));
	}
	
	// ������������� �������� ���������
	bool operator == (const MyDate &c)
	{
		return ((day == c.day) && (month == c.month) && (year == c.year));
	}

	// ����������� �����������
	MyDate& operator = (MyDate c)
	{
		day = c.day;
		month = c.month;
		year = c.year;

		return (*this);
	}

	// ������������� �������� ������
	bool operator > (const MyDate &c)
	{
		return ((year > c.year) || ((year == c.year) && (month > c.month)) || ((year == c.year) && (month == c.month) && (day>c.day)));
	}

	// ������������� �������� ������
	bool operator < (const MyDate &c)
	{
		return ((year < c.year) || ((year == c.year) && (month < c.month)) || ((year == c.year) && (month == c.month) && (day<c.day)));
	}

};

class Company {
public:
	// �������� �����
	string company_name;
	// ��� ������
	string type_of_work;
	// ������� ���������
	string unit;
	// ��������� ������� ���������� �����
	int cost;
	// ���� ����������
	MyDate exec_date;
	// ����� �����
	int scope_of_work;

	// ����������� �� ���������
	Company()
	{
		string company_name="";
		string type_of_work="";
		string unit="";
		int cost=0.0;
		MyDate exec_date;
		int scope_of_work=0;
	}


	// ��������� ��������� "��������"
	Company ChangeCompany(Company &result)
	{
		if (InputNumber(0,1,"�� ������ �������� ��� �������� "+result.company_name+" (0 - ���, 1 - ��)\n��� �����: ")==1)
			result.company_name = InputInformation("������� ����� ��� ��������: ");
		if (InputNumber(0, 1, "�� ������ �������� ��� ������ " + result.type_of_work + " (0 - ���, 1 - ��)\n��� �����: ") == 1)
			result.type_of_work = InputInformation("������� ����� ��� ������: ");
		if (InputNumber(0, 1, "�� ������ �������� ������� ��������� " + result.unit + " (0 - ���, 1 - ��)\n��� �����: ") == 1)
			result.unit = InputInformation("������� ����� ������� ���������: ");
		if (InputNumber(0, 1, "�� ������ �������� ��������� ������� ���������� ����� " + to_string(result.cost) + " (0-���, 1 - ��)\n��� �����: ") == 1)
			result.cost = InputNumber(0,1000000,"������� ����� ��������� (0 - 1000000): ");
		if (InputNumber(0, 1, "�� ������ �������� ���� ���������� (0 - ���, 1 - ��) \n��� �����: ") == 1)
			result.exec_date .InputDate();
		if (InputNumber(0, 1, "�� ������ �������� ����� ����� " + to_string(result.cost) + " (0 - ���, 1 - ��)\n��� �����: ") == 1)
			result.scope_of_work = InputNumber(0, 100000, "������� ����� ����� (0 - 100000): ");

		return result;
	}

	// ������������� �������� ��������� ��� ��������� "��������"
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

// ������� ����� ��������� "��������" � �������
Company InputScreenCompany()
{
	Company c;
	c.company_name = InputInformation("������� ��� ��������: ");
	c.type_of_work = InputInformation("������� ��� ������: ");
	c.unit = InputInformation("������� ������� ���������: ");
	c.cost = InputNumber(0, 1000000, "������� ��������� ������� ����������� ������ (0 - 1000000): ");
	c.exec_date.InputDate();
	c.scope_of_work = InputNumber(0, 10000, "������� ����� ����� (0 - 10000): ");
	return c;
}

// ������� ������ ��������� "��������" �� �������
void OutputScreenCompany(Company c)
{
	cout << "��� ��������: " << c.company_name << endl;
	cout << "��� ������: " << c.type_of_work << endl;
	cout << "������� ���������: " << c.unit << endl;
	cout << "��������� ������� ������: " << c.cost << endl;
	cout << "����: " << c.exec_date.ToString() << endl;
	cout << "����� �����: " << c.scope_of_work << endl;
}


//���������� ��������� "����" �� ������ 
// ������:
// ���� ����� ���
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
		cout << "������ ������ � ����!" << endl;
	}
	return result;
}

//������� ��������� "��������" � ������
string ToString(Company c,int i)
{
	string result ="������ � "+to_string(i)+"\n"+ "��� ��������: "+c.company_name+"\n"+"��� ������: "+c.type_of_work+"\n"+"������� ���������: "+c.unit+"\n"+"��������� ������� ������: "+to_string(c.cost)+"\n"+"����: " + c.exec_date.ToString() + "\n"+ "����� �����: " + to_string(c.scope_of_work)+"\n";
	return result;
}

////���������� ��������� "��������" �� ������
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
			string wrd = "��� ��������: ";
			result.company_name = s.substr(wrd.length(), s.length());
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "��� ������: ";
			result.type_of_work = s.substr(wrd.length(), s.length());
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "������� ���������: ";
			result.unit = s.substr(wrd.length(), s.length());
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "��������� ������� ������: ";
			result.cost = atoi(s.substr(wrd.length(), s.length()).c_str());
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "����: ";
			result.exec_date = FromString(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "����� �����: ";
			result.scope_of_work = atoi(s.substr(wrd.length(), s.length()).c_str());
		}
	}
	catch (...)
	{
		cout << "������ ������ � ����!" << endl;
	}
	return result;
}


// ����� ������� �������� �� ���������� ��������
// type_search - ��� ������
//1 - �� ����� ��������
//2 - �� ���� ������
//3 - �� ����
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

// ���� �������� ������ � ����������� �� ���������� ���� 
// type_search - ��� ������
//1 - �� ����� ��������
//2 - �� ���� ������
//3 - �� ����
Company InputChangeTypeSearch(int type_search)
{
	Company result;
	switch (type_search)
	{
	case 1:
		result.company_name = InputInformation("������� ��� ��������: ");
		return result;
	case 2:
		result.type_of_work = InputInformation("������� ��� ������: ");
		return result;
	case 3:
		result.exec_date.InputDate();
		return result;
	default:
		return result;
	}
}

// ��������� �������� � ����������� �� ���������� ���� ��� ����������
// type_search - ��� ������
//1 - �� ����� ��������
//2 - �� ���� ������
//3 - �� ����
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




