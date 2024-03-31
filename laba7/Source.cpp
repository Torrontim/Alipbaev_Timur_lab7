#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <windows.h>
//������� ���������(�����) � ������  BOOK, ���������� ��������� ���� : �������� �����(char*, string); �����(char*, string); ���� ������ �����(��� ����� �����).
//�������� ���������, ����������� ��������� �������� :
//���� ������(����, ���������� �� ����� ������������).
//�����������  ������  �� ������  � ���� ������.
//����� �� ����� ���������� � ������ ������ � .
//����� �� ����� ���������� � ������, �������� ����� ���� K(�����, ��������).
//
using namespace std;

class date {

	int _day;
	int _month;
	int _year;
public:

	date(int day = 1, int month = 1, int year = 1) :
		_day(day),
		_month(month),
		_year(year) {
	}
	bool check_date() {
		return !(_day < 1 || _day > 31 || _month < 1 || _month > 12);
	}
	friend bool operator> (const date& left, const date& right) {
		if (left._year > right._year) return true;
		else if (left._year == right._year) {
			if (left._month > right._month) return true;
			else if (left._month == right._month) {
				if (left._day > right._day) return true;
			}
		}
		return false;
	}
	friend bool operator< (const date& left, const date& right) {
		if (left._year < right._year) return true;
		else if (left._year == right._year) {
			if (left._month < right._month) return true;
			else if (left._month == right._month) {
				if (left._day < right._day) return true;
			}
		}
		return false;
	}
	friend istream& operator>> (istream& in, date& date) {
		in >> date._day >> date._month >> date._year;
		return in;
	}
	friend ostream& operator<< (ostream& out, date& date) {
		out << date._day << "/" << date._month << "/" << date._year;
		return out;
	}
};

class book {

	string _name;
	string _author;
	date _date;

public:

	book(string name = "", string author = "", date date = date()) :
		_name(name),
		_author(author),
		_date(date) {}

	string get_author() { return _author; }
	date get_date() { return _date; }

	void set_name(string name) { _name = name; }
	void set_author(string author) { _author = author; }
	void set_date(date date) { _date = date; }

	friend bool operator> (const book& left, const book& right) {
		return (left._author >= right._author && left._date > right._date);
	}

	friend bool operator< (const book& left, const book& right) {
		return (left._author <= right._author&& left._date < right._date);
	}

	friend ostream& operator<< (ostream& out, book& book) {
		out << book._author << " " << book._name << " " << book._date;
		return out;
	}

};

int showMenu() {
	int number;
	cout << "�������� ������� �� ������ ���������: " << endl
		<< "1. ���� ���������� �� �������" << endl
		<< "2. ���� ���������� �� �����" << endl
		<< "3. ����� ���������� �� �������" << endl
		<< "4. ����������" << endl
		<< "5. ���������� ���������" << endl
		<< "6. �������� �������� �� ������" << endl
		<< "7. ��������� �������� �� ������" << endl
		<< "8. ����� ���������� � ������ ������������� ������" << endl
		<< "9. ����� ���������� � ������, �������� ����� ������������ ����" << endl
		<< "10. �����" << endl
		<< "������� ����� ���� ��� ���������� >";
	cin >> number;
	return number;
}

void inputDataConsole(vector<book>& data) {
	int count;
	cout << "������� ���� �� ������ ������? >";
	cin >> count;
	for (int i = 0; i < count; i++) {
		string inputName, inputAuthor;
		date inputDate;
		cout << "������� �������� ����� >" << endl;;
		cin >> inputName;
		cout << "������� ������ ����� >" << endl;;
		cin >> inputAuthor;
		cout << "������� ���� ������ ����� � ������� �� �� ���� >" << endl;
		cin >> inputDate;
		while (!inputDate.check_date()) {
			cout << "�� ����� ������������ ����, ���������� ��� ��� " << endl;
			cin >> inputDate;
		}
		data.push_back(book(inputName, inputAuthor, inputDate));
		system("cls");
	}
	cout << "������ ������� �������� " << endl;
}

void inputDataFile(vector<book>& data, istream& in) {
	string inputName, inputAuthor;
	date inputDate;
	bool flag = true;
	while (in >> inputName >> inputAuthor >> inputDate) {
		if (inputDate.check_date()) {
			data.push_back(book(inputName, inputAuthor, inputDate));
		}
		else {
			flag = false;
		}
	}
	if (flag) cout << "������ ������� �������� :)" << endl;
	else cout << "� ��������� ������� ���� �������� ������, ��� �� ���� �������� " << endl;
}

void outputData(vector<book>& data, ostream& out) {
	if (data.size()==0)
	{
		cout << "���� �� �������" << endl; return;
	}
	for (int i = 0; i < data.size(); i++) {
		out << i + 1 << ". " << data[i] << endl;
	}
}

void changeNote(vector<book>& data) {
	outputData(data, cout);
	int num;
	string a;
	date b;
	if (data.size() == 0)
	{
		cout << "���� �� �������" << endl; return;
	}
	cout << "������� ����� ������ ��� ��������� >";
	cin >> num;
	while (num < 0 || num > data.size()) {
		cout << "������������ �����, ���������� ��� ��� ";
		cin >> num;
	}
	cout << "������ ������� �������� " << endl;
	int izm, OutKey = 0;
	while (OutKey != 1)
	{
		cout << "���������:" << endl;
		cout << "1.�������� " << endl;
		cout << "2.����� " << endl;
		cout << "3.���� ������� " << endl;
		cout << "4.����������� ��������� " << endl;
		cout << "5.����� " << endl;
		cin >> izm;
		switch (izm) {
		case 1: cout << "������� ����� �������� "; cin >> a; 	data[num - 1].set_name(a);; cout << endl;  break;
		case 2: cout << "������� ������ ������"; cin >> a; ;	data[num - 1].set_author(a); cout << endl;  break;
		case 3: cout << "������� ����� ���� ������� "; cin >> b; 
			while (!b.check_date()) {
			cout << "�� ����� ������������ ����, ���������� ��� ��� :)";
			cin >> b;
		    }; data[num - 1].set_date(num-1); cout << endl;  break;
		case 4: cout << "�" << num << " " << data[num-1]; break;
		case 5: cout << "��������� ���������" << endl; OutKey = 1; break;
		default: cout << "������ ������ ���, �������� ����� � ���������� �� 1 �� 5" << endl; break;
		}
	}
}

void deleteNote(vector<book>& data) {
	outputData(data, cout);
	int num;
	if (data.size() == 0)
	{
		cout << "���� �� �������" << endl; return;
	}
	cout << "������� ����� ������ ��� �������� >";
	cin >> num;
	while (num < 0 || num >= data.size()) {
		cout << "������������ �����, ���������� ��� ��� ";
		cin >> num;
	}
	data.erase(data.begin() + num - 1);
	cout << "������ ������� ������� " << endl;
}

void findAuthor(vector<book>& data) {
	string author; bool flag = 0;
	if (data.size() == 0)
	{
		cout << "������ ���� ����" << endl; return;
	}
	cout << "������� ������ ����� >";
	cin >> author;
	for (book b : data) {
		if (b.get_author() == author) flag=1;
	}
	if(flag)
	for (book b : data) {
		if (b.get_author() == author) cout << b << endl;
	}
	else
	{
		cout << "����� �� ������ " << endl;
	}
}

void findDate(vector<book>& data) {
	date Date; bool flag = 0;
	if (data.size() == 0)
	{
		cout << "������ ���� ����" << endl; return;
	}
	cout << "������� ���� ������ ����� >";
	cin >> Date;
	for (book b : data) {
		if (b.get_date() > Date) flag = 1;
	}
	if(flag)
	for (book b : data) {
		if (b.get_date() > Date) cout << b << endl;
	}
	else
	{
		cout << "���� �� ������� " << endl;
	}
}

int main() {
	SetConsoleCP(1251); //���� ������� ����
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	int item = 0;
	string readPath = "Book.txt";
	ifstream fin(readPath);
	vector<book> data;
	while (item != 10) {
		system("cls");
		item = showMenu();
		switch (item) {
		case 1:
			inputDataConsole(data);
			cout << endl;
			system("pause");
			break;
		case 2:
			if (!fin.is_open()) {
				cout << "���� �� ������ " << endl;
			}
			else {
				inputDataFile(data, fin);
				cout << endl;
			}
			system("pause");

			break;
		case 3:
			outputData(data, cout);
			cout << endl;
			system("pause");
			break;
		case 4:
			sort(data.begin(), data.end());
			cout << "������ ������� �������������" << endl;
			system("pause");
			break;

		case 5:
			inputDataConsole(data);
			cout << endl;
			system("pause");
			break;

		case 6:
			deleteNote(data);
			cout << endl;
			system("pause");
			break;

		case 7:
			changeNote(data);
			cout << endl;
			system("pause");
			break;

		case 8:
			findAuthor(data);
			cout << endl;
			system("pause");
			break;

		case 9:
			findDate(data);
			cout << endl;
			system("pause");
			break;

		case 10:
			fin.close();
			cout << "����" << endl;
			return 0;
			break;

		deafult:
			cout << "������ ����� ���� �� ����������. ���������� ��� ��� " << endl;
			system("pause");
		}
	}
	fin.close();
	return 0;
}