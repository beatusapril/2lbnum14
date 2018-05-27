#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Company.h"
#include "HelpUtils.h"
using namespace std;


template <class Type>
class Task {
private:
	// ���������� �� ��������� ��������
	// int(*Compare)(Type, Type, int) - ��������� �� �������, ������� ���������� ������� ��-� � ������� �� type_search  
	void ShellSort(int n, int typ, int(*Compare)(Type, Type, int))
	{
		int i, j, step;
		Type tmp;
		for (step = n / 2; step > 0; step /= 2)  
			for (i = step; i < n; i++)
			{
				tmp = vect[i];
				for (j = i; j >= step; j -= step)
				{
					if ((Compare(tmp, vect[j - step], typ) == -1))
						vect[j] = vect[j - step];
					else
						break;
				}
				vect[j] = tmp;
			}

	}
	// �������� �����
	// int(*Compare)(Type, Type, int) - ��������� �� �������, ������� ���������� ������� ��-� � ������� �� type_search  
	int Binary_Search_Element(int left, int right, int type_search, Type d, int(*Compare)(Type, Type, int))
	{
		int midd = 0;
		while (1)
		{
			midd = (left + right) / 2;

			if (Compare(d, vect[midd], type_search) == -1)// ���� ������� ������ �������� � ������
				right = midd - 1;				// ������� ������ ������� ������
			else if (Compare(d, vect[midd], type_search) == 1)  // ���� ������� ������ �������� � ������
				left = midd + 1;					// ������� ����� ������� ������
			else                       // ����� (�������� �����)
				return midd;           // ������� ���������� ������ ������

			if (left > right)          // ���� ������� ���������� 
				return -1;
		}
	}
public:
	vector<Type> vect;
	Task() {}
	~Task() {}

	// �������� ��������
	void Remove( int numb)
	{
		if (numb != 0)
			vect.erase(vect.begin() + numb-1);
	}
	
	// ���������� ��������
	void Add(Type &elem)
	{
		vect.push_back(elem);
	}

	//������ �������
	int size()
	{
		return vect.size();
	}

	// �������� �� �������
	bool Is_empty()
	{
		return (vect.size() == 0);
	}

	// ����� � ����
	// void(*f) (Type) - ��������� �� �������, ������� ���������� ���� ��������� � ����  
	void OutputFile(vector<Type> items,string (*f)(Type,int))
	{
		string newfname = InputFileName();
		ofstream fout(newfname);
		if (fout)
		{
			vector<Type>::const_iterator pos;
			int count = 1;
			for (pos = items.begin(); pos != items.end(); ++pos)
			{
				fout << f(*pos,count) << ' ';
				count++;
			}
			cout << endl << "���� ��������!" << endl;
			fout.close();
		}
		else
		{
			cout << "���� �� ��������!" << endl;
		}
	}

	// ����� �� �����
	// void(*f) (Type) - ��������� �� �������, ������� ��������� ���� ��������� �� �����  
	void OutputScreen(vector<Type> items, void (*f) (Type))
	{
		vector<Type>::const_iterator pos;
		int count = 1;
		for (pos = items.begin(); pos != items.end(); ++pos)
		{
			cout << "������ � " << count << endl;
			f(*pos);
			++count;
		}
		cout << "����� ������!" << endl;
	}

	// ���� �� �����
	// Type(*f)(ifstream&) - ��������� �� �������, ������� ��������� ���� ��������� �� ����� 
	bool ReadFromFile(Type(*f)(ifstream&))
	{
		string newfname = InputFileName();
		std::ifstream input;

		input.open(newfname);

		if (!input)
		{
			cout << "�� ������� ������� ����" << endl;
			return false;
		}
		else
		{
			while (!input.eof())
			{
				vect.push_back(f(input));
			}
			vect.erase(vect.begin() + vect.size() - 1);

			input.close();
			return true;
		}
	}

	// ���� � ������
	//Type(*f)() - ��������� �� �������, ������� ������ ���� ��������� � �������
	void ReadFromScreen(Type (*f)())
	{
		int n;
		Type elem;
		do
		{
			vect.push_back(f());
			n = InputNumber(0, 1, "�� ������ �������� �������? (1 - ��, 0 - ���)\n��� �����: ");
		} while (n != 0);
	}

	// �������� �����
	// bool(*Equal)(Type, Type, int) - ��������� �� �������, ������� ��������� ��������� �������� ��-�� � ������� �� type_search
	vector<Type> LinearySearch(Type search_elem,bool(*Equal)(Type,Type, int),int type_search)
	{
		vector<Type> NewVect;
		for (auto iter = vect.begin(); iter != vect.end(); iter++)
		{
			if (Equal(search_elem,*iter, type_search))
				NewVect.push_back(*iter);

		}

		return NewVect;
	}

	// �������� �����
	// int(*Compare)(Type, Type, int) - ��������� �� �������, ������� ���������� ������� ��-� � ������� �� type_search 
	// bool(*Equal)(Type, Type, int) - ��������� �� �������, ������� ��������� ��������� �������� ��-�� � ������� �� type_search
	vector<Type> BinarySearch( int type_search, Type find_element, int(*Compare)(Type, Type, int), bool(*Equal)(Type, Type, int))
	{
		vector<Type> NewVect;
		ShellSort(vect.size(), type_search, Compare);
		int left = 0;
		int right = vect.size();
		int index;
	    if  ((index = Binary_Search_Element(left, right-1,type_search,find_element,Compare)) != -1)
		{
			NewVect.push_back(vect[index]);
			int first_index = index;
			while ((++index<right)&&Equal(vect[index], find_element, type_search))
				NewVect.push_back(vect[index]);
			while ((--first_index >= 0)&&Equal(vect[first_index], find_element, type_search))
				NewVect.push_back(vect[first_index]);
		}
		return NewVect;
	}
};