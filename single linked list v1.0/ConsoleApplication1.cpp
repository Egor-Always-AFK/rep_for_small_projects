#include <iomanip>
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

class Node
{
private:
	class Students
	{
	public:
		Students* next;
		string surname;
		int id;
		int money;
	};
	Students* Head = NULL;
public:
	void listInitialization(size_t count)
	{
		Students* tmp;

		Head = new Students;
		tmp = Head;
		cout << "\nВведите фамилию студента: ";
		cin >> tmp->surname;
		cout << "Введите стипендию студента: ";
		cin >> tmp->money;
		cout << "Введите id студента: ";
		cin >> tmp->id;
		for (size_t i = 0; i < count - 1; i++)
		{
			tmp->next = new Students;
			tmp = tmp->next;
			cout << "\nВведите фамилию студента: ";
			cin >> tmp->surname;
			cout << "Введите стипендию студента: ";
			cin >> tmp->money;
			cout << "Введите id студента:";
			cin >> tmp->id;
		}
		tmp->next = NULL;
	}
	void output()
	{
		cout << setw(10) << "Фамилия" << setw(10) << "|" << setw(10) << "стипендия" << setw(10) << "|" << setw(10) << "id студента\n";
		Students* tmp;
		tmp = Head;
		while (tmp != NULL)
		{
			cout << tmp->surname << setw(20) 
				<< setw(30) << tmp->money << setw(30) << tmp->id << "\n";
			tmp = tmp->next;
		}
	}
	void deleteNode(int idToDelete)
	{
		Students* tmp = Head;
		Students* secondTmp = NULL;

		while (tmp != nullptr)
		{
			if (tmp->id == idToDelete)
			{
				if (secondTmp != nullptr)
					secondTmp->next = tmp->next;
				else
					Head = tmp->next;
				delete tmp;
				break;
			}
			secondTmp = tmp;
			tmp = tmp->next;
		}
	}
	void search(int id)
	{
		Students* tmp;

		tmp = Head;

		while (tmp != NULL)
		{
			if (tmp->id == id)
				cout << tmp->surname << " | " << tmp->money << " | " << tmp->id << "\n";
			tmp = tmp->next;
		}
	}
	void insertInList(int index)
	{
		int out = 0;
		Students* tmp = Head;
		Students* secondTmp = nullptr;

		while (tmp != nullptr)
		{
			if (tmp->id == index)
			{
				if (tmp->next == NULL)
				{
					Students* current = Head;
					while (current->next != nullptr)
						current = current->next;
					current->next = new Students;
					cout << "\nВведите фамилию студента: ";
					cin >> current->next->surname;
					cout << "Введите стипендию студента: ";
					cin >> current->next->money;
					cout << "Введите id студента:";
					cin >> current->next->id;
				}
				else if (secondTmp != nullptr)
				{
					Students *secondTmp = Head;

					secondTmp = secondTmp->next;
					Students* newList = new Students;
					newList->next = secondTmp->next;
					secondTmp->next = newList;

					cout << "\nВведите фамилию студента: ";
					cin >> newList->surname;
					cout << "Введите стипендию студента: ";
					cin >> newList->money;
					cout << "Введите id студента:";
					cin >> newList->id;
				}
				else
				{
					Students* newStudents;
					newStudents = new Students;

					cout << "\nВведите фамилию студента: ";
					cin >> newStudents->surname;
					cout << "Введите стипендию студента: ";
					cin >> newStudents->money;
					cout << "Введите id студента:";
					cin >> newStudents->id;

					newStudents->next = Head;
					Head = newStudents;
				}
			}
			secondTmp = tmp;
			tmp = tmp->next;
		}
	}
};
void prnm();


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	size_t size = 0;
	cout << "Введите количество студентов: ";
	cin >> size;

	Node point;

	point.listInitialization(size);
	char key = getchar();
	while (key != 'esc')
	{
		prnm();
		key = getchar();
		system("cls");
		switch (key)
		{
		case'1':
		{
			point.output();
			key = getchar();
			break;
		}
		case'2':
		{
			cout << "Введите номер id студента, которого хотите удалить: ";
			int number = 0;
			cin >> number;
			point.deleteNode(number);
			key = getchar();
			break;
		}
		case'3':
		{
			cout << "Введите номер id студента, которого хотите найти в базе: ";
			int idSearch = 0;
			cin >> idSearch;

			point.search(idSearch);

			key = getchar();
			break;
		}
		case'4':
		{
			cout << "Введите id студента после которого хотите вставить нового студента: ";
			int index = 0;
			cin >> index;

			point.insertInList(index);

			key = getchar();
			break;
		}
		}
	}
}


void prnm()
{
	cout << "Введите\n1 - для вывода таблицы.\n" <<
		"2 - для удаления элемента\n" <<
		"3 - для поиска студента по id\n" <<
		"4 - для вставки элемента\n";
}
