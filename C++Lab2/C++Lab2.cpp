#include "pch.h"
#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

const int tNlen = 10; //tableNumber length
const int dNlen = 2; //department number length

struct Worker
{
	int tableNumber;

	string fullName[3]; //first name, surname, last name
	string address;
	string education;
	
	unsigned short int birthday[3]; //day, month, year
 
	unsigned short int department;
	unsigned short int employmentYear;

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
		cout << "\nEmployment year: " << employmentYear << "\nAddress: " << address;
		cout << "\nBirthday: " << getBirthday() << "\nEducation info: " << education << "\n";
	}
};

Worker InitWorker();
Worker* InitArray(int);
Worker* AddWorker(Worker*, int);
Worker FindByTableNumber(Worker*, int, int);
void PrintArray(Worker*, int);
void EditWorkerInfo(Worker);

void Question(Worker*);

int main()
{
	int length;
	cout << "Enter a new worker list length:\n";
	scanf_s("%d", &length, 2);

	Worker* workers = InitArray(length);

	Question(workers);

	return 0;
}

void Question(Worker* arr)
{
	string choise;
	int l = NULL;

	cout << "\nEnter a command ('add' - add new worker, 'addarr' - add worker list, 'find' - find worker in list, 'print' - print worker list):\n";
	getline(cin, choise);

	if (choise == "add")
	{
		if (l == NULL || l < 0) cout << "\nWorker list does not exists\n";
		else AddWorker(arr, l);
	}
	else if (choise == "addarr")
	{
		cout << "\nEnter a length of list: ";
		scanf_s("%d", &l, 2);
		arr = InitArray(l);
		cout << "\n";
	}
	else if (choise == "find")
	{
		if (l == NULL || l < 0) cout << "\nWorker list does not exists\n";
		else
		{
			int n;
			scanf_s("%d", &n, tNlen);
			cout << "\n";
			FindByTableNumber(arr, l, n).printWorkerInfo();
		}
	}
	else if (choise == "print")
	{
		if (l == NULL || l < 0) cout << "\nWorker list does not exists\n";
		else
		{
			cout << "\n";
			PrintArray(arr, l);
		}
	}
	else
	{
		cout << "\nNo such command\n";
	}

	Question(arr);
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
	scanf_s("%d", &w.birthday[0], 2);
	printf("\nMonth: ");
	scanf_s("%d", &w.birthday[1], 2);
	printf("\nYear: ");
	scanf_s("%d", &w.birthday[2], 4);

	printf("\n\nEnter address: ");
	getline(cin, w.address);
	getline(cin, w.address);

	printf("\n\nEnter education info: ");
	getline(cin, w.education);

	printf("\n\nEnter employment year: ");
	scanf_s("%d", &w.employmentYear, 4);

	printf("\n\nEnter table number: ");
	scanf_s("%d", &w.tableNumber, tNlen);

	printf("\n\nEnter department number: ");
	scanf_s("%d", &w.department, dNlen);

	return w;
}

Worker* AddWorker(Worker* arr, int arrLength)
{
	int newLength = arrLength + 1;
	Worker* temp = InitArray(newLength);

	for (int i = 0; i < arrLength; i++)
	{
		temp[i] = arr[i];
	}
	temp[arrLength] = InitWorker();

	delete[] arr;

	return temp;
}

Worker* InitArray(int length)
{
	if (length < 1) length = 1;

	Worker* arr = (Worker*)malloc(length * sizeof(Worker)); 

	if (arr == NULL) return NULL;

	for (int i = 0; i < length; i++)
	{
		printf("\nEnter worker data:\n");
		arr[i] = InitWorker();

		string choise = "";

		while (choise != "y" || choise != "n")
		{
			printf("\nDo you want to continue? (y/n)");
			getline(cin, choise);
		}
		if (choise == "n") break;
	}
	return arr;
}

void PrintArray(Worker* arr, int arrLength)
{
	for (int i = 0; i < arrLength; i++)
	{
		arr[i].printWorkerInfo();
		cout << "\n";
	}
}

Worker FindByTableNumber(Worker* arr, int arrLength, int number)
{
	for (int i = 0; i < arrLength; i++)
	{
		if (arr[i].tableNumber == number) return arr[i];
	}

	cout << "No workers found with table number " << number;
}

void EditWorkerInfo(Worker w)
{
	cout << "\nEnter field to edit (name/birthday/address/education/emplyear/department/tablenum):\n";
	
	string field;
	getline(cin, field);
	
	if (field == "name")
	{
		printf("\nEnter first name: ");
		getline(cin, w.fullName[0]);
		printf("\nEnter surname: ");
		getline(cin, w.fullName[1]);
		printf("\nEnter last name: ");
		getline(cin, w.fullName[2]);
	}
	else if (field == "birthday")
	{
		printf("\n\nEnter birthday:\nDay: ");
		scanf_s("%d", &w.birthday[0], 2);
		printf("\nMonth: ");
		scanf_s("%d", &w.birthday[1], 2);
		printf("\nYear: ");
		scanf_s("%d", &w.birthday[2], 4);
	}
	else if (field == "address")
	{
		printf("\n\nEnter address: ");
		getline(cin, w.address);
	}
	else if (field == "education")
	{
		printf("\n\nEnter education info: ");
		getline(cin, w.education);
	}
	else if (field == "emplyear")
	{
		printf("\n\nEnter employment year: ");
		scanf_s("%d", &w.employmentYear, 4);
	}
	else if (field == "department")
	{
		printf("\n\nEnter department number: ");
		scanf_s("%d", &w.department, dNlen);
	}
	else if (field == "tablenum")
	{
		printf("\n\nEnter table number: ");
		scanf_s("%d", &w.tableNumber, tNlen);
	}
	else
	{
		cout << "\nNo such field\n";
		EditWorkerInfo(w);
	}
}