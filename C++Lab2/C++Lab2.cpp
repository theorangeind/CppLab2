#include "pch.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <algorithm>

using namespace std;

struct Worker
{
	int tableNumber;

	string fullName[3]; //first name, surname, last name
	string address;
	string education;
	
	unsigned short int birthday[3]; //day, month, year
 
	unsigned int department, employmentYear;

	string getFullName()
	{
		return fullName[0] + " " + fullName[2] + " " + fullName[1];
	}

	string getBirthday()
	{
		return (birthday[0] <= 9 ? "0" : "") + to_string(birthday[0]) + "." + (birthday[1] <= 9 ? "0" : "") + to_string(birthday[1]) + "." + to_string(birthday[2]);
	}

	void printWorkerInfo()
	{
		cout << "Worker: " << getFullName() << "\nTable number: " << tableNumber << "\nDepartment: " << department;
		cout << "\nEmployment year: " << employmentYear;
		cout << "\nAddress: " << address;
		cout << "\nBirthday: " << getBirthday() << "\nEducation info: " << education << "\n";
	}
};

Worker* InitArray();
Worker InitWorker();
Worker EditWorkerInfo(Worker);
int FindByTableNumber(int);
void AddWorker();
void PrintArray();
void arrSort();
void Question();

Worker* workers;
int length;

int main()
{
	cout << "Enter a new worker list length:\n";
	scanf_s("%u", &length, 2);

	if ((int)length < 1) length = 1;

	workers = InitArray();

	Question();

	return 0;
}

void Question()
{
	bool exit = false;

	string choise;
	int l = length;

	cout << "\nEnter a command ('add' - add new worker, 'find' - find worker in list, 'print' - print worker list, 'edit' - edit worker info, 'sort' - sort list by table number, 'exit' - close program):\n";

	getline(cin, choise);

	if (choise == "add")
	{
		if (l == NULL || l < 0) cout << "\nWorker list does not exists\n";
		else AddWorker();
	}
	else if (choise == "find")
	{
		if (l == NULL || l < 0) cout << "\nWorker list does not exists\n";
		else
		{
			cout << "\nEnter a table number:\n";
			int n;
			scanf_s("%u", &n);

			if ((int)n < 1) n = 1;

			cout << "\n";

			try
			{
				workers[FindByTableNumber(n)].printWorkerInfo();
			}
			catch (string s)
			{
				cout << "\n" << s << "\n";
			}
		}
	}
	else if (choise == "print")
	{
		if (l == NULL || l < 0) cout << "\nWorker list does not exists\n";
		else
		{
			cout << "\n";
			PrintArray();
		}
	}
	else if (choise == "edit")
	{
		if (l == NULL || l < 0) cout << "\nWorker list does not exists\n";
		else
		{
			cout << "\nEnter a table number:\n";
			int n;
			scanf_s("%u", &n);

			if ((int)n < 0) n = 1;

			cout << "\n";

			try
			{
				workers[FindByTableNumber(n)] = EditWorkerInfo(workers[FindByTableNumber(n)]);
			}
			catch (string s)
			{
				cout << "\n" << s << "\n";
			}
		}
	}
	else if (choise == "sort")
	{
		arrSort();
	}
	else if (choise == "exit")
	{
		exit = true;
	}
	else
	{
		cout << "\nNo such command\n";
	}

	if(!exit) Question();
}

Worker InitWorker()
{
	Worker w;

	printf("\nEnter first name: ");
	getline(cin, w.fullName[0]);
	printf("\nEnter surname: ");
	getline(cin, w.fullName[1]);
	printf("\nEnter last name: ");
	getline(cin, w.fullName[2]);

	printf("\n\nEnter birthday:\nDay: ");
	scanf_s("%u", &w.birthday[0]);
	printf("\nMonth: ");
	scanf_s("%u", &w.birthday[1]);
	printf("\nYear: ");
	scanf_s("%u", &w.birthday[2]);

	printf("\n\nEnter address: ");
	cin.ignore();
	getline(cin, w.address);

	printf("\n\nEnter education info: ");
	getline(cin, w.education);

	printf("\n\nEnter employment year: ");
	scanf_s("%u", &w.employmentYear);

	printf("\n\nEnter table number: ");
	scanf_s("%u", &w.tableNumber);

	printf("\n\nEnter department number: ");
	scanf_s("%u", &w.department);

	return w;
}

void AddWorker()
{
	Worker* temp = new Worker[length + 1];

	for (int i = 0; i < length; i++)
	{
		temp[i] = workers[i];
	}
	temp[length] = InitWorker();

	workers = temp;
	length++;

	cin.ignore();
}

Worker* InitArray()
{
	cin.ignore();

	if (length < 1) length = 1;

	Worker* arr = (Worker*)malloc(length * sizeof(Worker)); 

	arr = new Worker[length];

	if (arr == NULL) return NULL;

	string choise;

	for (int i = 0; i < length; i++)
	{
		if (choise != "n")
		{
			printf("\nEnter worker data:\n");
			arr[i] = InitWorker();

			if (i < length - 1)
			{
				do
				{
					printf("\nDo you want to continue? (y/n)\n");
					cout << choise << "\n";
					cin >> choise;
				} while (choise != "y" && choise != "n");
			}
		}
		else
		{
			arr[i].address = "<Empty>";
			arr[i].birthday[0] = 0;
			arr[i].birthday[1] = 0;
			arr[i].birthday[2] = 0;
			arr[i].department = 0;
			arr[i].education = "<Empty>";
			arr[i].employmentYear = 0;
			arr[i].fullName[0] = "<Empty>";
			arr[i].fullName[1] = "";
			arr[i].fullName[2] = "";
			arr[i].tableNumber = 0;
		}
	}
	cout << "\nWorker list saved!\n\n";

	cin.ignore();

	return arr;
}

void PrintArray()
{
	for (int i = 0; i < length; i++)
	{
		workers[i].printWorkerInfo();
		cout << "\n";
	}
}

int FindByTableNumber(int number)
{
	int counter = 0;

	for (int i = 0; i < length; i++)
	{
		if (workers[i].tableNumber == number)
		{
			counter++;
			cin.ignore();
			return i;
		}
	}

	string s = "No workers found with table number " + to_string(number);

	if(counter == 0) throw  s;

	cin.ignore();
}

Worker EditWorkerInfo(Worker w)
{
	Worker k;
	k = w;
	cout << "\nEnter field to edit (name/birthday/address/education/emplyear/department/tablenum):\n";

	string field;
	getline(cin, field);
	
	if (field == "name")
	{
		printf("\nEnter first name: ");
		getline(cin, k.fullName[0]);
		printf("\nEnter surname: ");
		getline(cin, k.fullName[1]);
		printf("\nEnter last name: ");
		getline(cin, k.fullName[2]);
	}
	else if (field == "birthday")
	{
		printf("\n\nEnter birthday:\nDay: ");
		scanf_s("%d", &k.birthday[0], 2);
		printf("\nMonth: ");
		scanf_s("%d", &k.birthday[1], 2);
		printf("\nYear: ");
		scanf_s("%d", &k.birthday[2], 4);
	}
	else if (field == "address")
	{
		printf("\n\nEnter address: ");
		getline(cin, k.address);
	}
	else if (field == "education")
	{
		printf("\n\nEnter education info: ");
		getline(cin, k.education);
	}
	else if (field == "emplyear")
	{
		printf("\n\nEnter employment year: ");
		scanf_s("%d", &k.employmentYear, 4);
	}
	else if (field == "department")
	{
		printf("\n\nEnter department number: ");
		scanf_s("%d", &k.department);
	}
	else if (field == "tablenum")
	{
		printf("\n\nEnter table number: ");
		scanf_s("%d", &k.tableNumber);
	}
	else
	{
		cout << "\nNo such field\n";
		EditWorkerInfo(k);
	}

	cout << "\nInformation saved!\n\n";

	return k;
}

void arrSort()
{
	Worker* w = new Worker[length];
	Worker temp;
	w = workers;

	for (int i = 0; i < length - 1; i++) {
		for (int j = 0; j < length - i - 1; j++) {
			if (w[j].tableNumber > w[j + 1].tableNumber) {
				temp = w[j];
				w[j] = w[j + 1];
				w[j + 1] = temp;
			}
		}
	}
	workers = w;
}