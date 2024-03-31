#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <windows.h>
//Описать структуру(класс) с именем  BOOK, содержащую следующие поля : название книги(char*, string); автор(char*, string); дата выхода книги(три целых числа).
//Написать программу, выполняющую следующие действия :
//Ввод данных(файл, клавиатура на выбор пользователя).
//Упорядочить  записи  по автору  и дате выхода.
//Вывод на экран информации о книгах автора К .
//Вывод на экран информации о книгах, вышедших после даты K(автор, название).
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
	cout << "Действия которые вы можете совершить: " << endl
		<< "1. Ввод информации из консоли" << endl
		<< "2. Ввод информации из файла" << endl
		<< "3. Вывод информации на консоль" << endl
		<< "4. Сортировка" << endl
		<< "5. Добавление элементов" << endl
		<< "6. Удаление элемента по номеру" << endl
		<< "7. Изменение элемента по номеру" << endl
		<< "8. Вывод информации о книгах определенного автора" << endl
		<< "9. Вывод информации о книгах, вышедших после определенной даты" << endl
		<< "10. Выход" << endl
		<< "Введите пункт меню для выполнения >";
	cin >> number;
	return number;
}

void inputDataConsole(vector<book>& data) {
	int count;
	cout << "Сколько книг вы хотите ввести? >";
	cin >> count;
	for (int i = 0; i < count; i++) {
		string inputName, inputAuthor;
		date inputDate;
		cout << "Введите название книги >" << endl;;
		cin >> inputName;
		cout << "Введите автора книги >" << endl;;
		cin >> inputAuthor;
		cout << "Введите дату выхода книги в формате ДД ММ ГГГГ >" << endl;
		cin >> inputDate;
		while (!inputDate.check_date()) {
			cout << "Вы ввели некорректную дату, попробуйте ещё раз " << endl;
			cin >> inputDate;
		}
		data.push_back(book(inputName, inputAuthor, inputDate));
		system("cls");
	}
	cout << "Данные успешно записаны " << endl;
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
	if (flag) cout << "Данные успешно записаны :)" << endl;
	else cout << "В некоторых записях была допущена ошибка, они не были записаны " << endl;
}

void outputData(vector<book>& data, ostream& out) {
	if (data.size()==0)
	{
		cout << "Книг не найдено" << endl; return;
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
		cout << "Книг не найдено" << endl; return;
	}
	cout << "Введите номер записи для изменения >";
	cin >> num;
	while (num < 0 || num > data.size()) {
		cout << "Некорректный номер, попробуйте ещё раз ";
		cin >> num;
	}
	cout << "Данные успешно изменены " << endl;
	int izm, OutKey = 0;
	while (OutKey != 1)
	{
		cout << "Изменение:" << endl;
		cout << "1.Название " << endl;
		cout << "2.Автор " << endl;
		cout << "3.Дата издания " << endl;
		cout << "4.Просмотреть изменение " << endl;
		cout << "5.Выход " << endl;
		cin >> izm;
		switch (izm) {
		case 1: cout << "Введите новое название "; cin >> a; 	data[num - 1].set_name(a);; cout << endl;  break;
		case 2: cout << "Введите нового автора"; cin >> a; ;	data[num - 1].set_author(a); cout << endl;  break;
		case 3: cout << "Введите новую дата издания "; cin >> b; 
			while (!b.check_date()) {
			cout << "Вы ввели некорректную дату, попробуйте ещё раз :)";
			cin >> b;
		    }; data[num - 1].set_date(num-1); cout << endl;  break;
		case 4: cout << "№" << num << " " << data[num-1]; break;
		case 5: cout << "Изменения закончены" << endl; OutKey = 1; break;
		default: cout << "Такого пункта нет, выберете число в промежутке от 1 до 5" << endl; break;
		}
	}
}

void deleteNote(vector<book>& data) {
	outputData(data, cout);
	int num;
	if (data.size() == 0)
	{
		cout << "Книг не найдено" << endl; return;
	}
	cout << "Введите номер записи для удаления >";
	cin >> num;
	while (num < 0 || num >= data.size()) {
		cout << "Некорректный номер, попробуйте ещё раз ";
		cin >> num;
	}
	data.erase(data.begin() + num - 1);
	cout << "Данные успешно удалены " << endl;
}

void findAuthor(vector<book>& data) {
	string author; bool flag = 0;
	if (data.size() == 0)
	{
		cout << "Список книг пуст" << endl; return;
	}
	cout << "Введите автора книги >";
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
		cout << "Автор не найден " << endl;
	}
}

void findDate(vector<book>& data) {
	date Date; bool flag = 0;
	if (data.size() == 0)
	{
		cout << "Список книг пуст" << endl; return;
	}
	cout << "Введите дату выхода книги >";
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
		cout << "Книг не найдено " << endl;
	}
}

int main() {
	SetConsoleCP(1251); //ввод русский язык
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
				cout << "Файл не найден " << endl;
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
			cout << "Данные успешно отсортированы" << endl;
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
			cout << "Пока" << endl;
			return 0;
			break;

		deafult:
			cout << "Такого пункт меню не существует. Попробуйте ещё раз " << endl;
			system("pause");
		}
	}
	fin.close();
	return 0;
}