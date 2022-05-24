#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <Windows.h>

using namespace std;


// ОДНОСВЯЗНЫЙ СПИСОК: по простому поезд. есть голова, от неё всё и зависит. важно понимать, что если мы "потеряем" ссылку на голову, то более мы к ней не вернемся
// пример: 1->2->3->4->5. как видим, из "головы" мы можем пойти ТОЛЬКО на следующий элемент. вернутся с "2" в "1" не можем (стрелки показывают направления движения)

class List
{
private:
	class Students
	{
	public:
		Students* Next; //ссылка на следующий элемент ЛОС
		int id; //индентификационный номер
		int money;  // стипендия студента
		string surname; // Фамилия студента
	};

	Students* Head = NULL;

public:

	void create(int numStudents)
	{
		Students* q; // создаем класс студент (как раз тот, что чуть выше)
		Head = new Students; // выделяем память на голову списка(первый элемент)(объявление - 22 строка)
		q = Head; // приравнием q(новосозданный объект класса) к голове (чтобы один раз выделить память + потом не было запар с заполнением)

		cout << "\nВведите фамилию студента: ";
		cin >> q->surname;
		cout << "Введите стипендию студента: ";
		cin >> q->money;
		cout << "Введите id студента: ";
		cin >> q->id;

		for (int i = 0; i < numStudents - 1; i++)
		{
			q->Next = new Students;
			q = q->Next;
			cout << "\nВведите фамилию студента: ";
			cin >> q->surname;
			cout << "Введите стипендию студента: ";
			cin >> q->money;
			cout << "Введите id студента: ";
			cin >> q->id;
		}
		q->Next = NULL; // приравнием последний элемент списка к NULL(ноль) для дальнейшей работы (траблы с пробегом по списку могут быть(чтобы ставить норм условия и не выходить за рамки дозволенного))
	}

	void output()//вывод списка на экран
	{
		Students* q; // создаем переменную класса студент (как раз тот, что чуть выше)
		q = Head; // приравнием переменную к "голове", чтобы потом не потерять голову односвязного списка

		while (q != NULL)
		{
			cout << q->id << " | " << q->money <<
				" | " << q->surname << "\n";
			q = q->Next;
		}
	}

	void search()//поиск элемента в списке
	{
		cout << "\nПоиск данных по студенту. \nВведите id студента: "; // id - ключ. поиск по ключу - поиск по определённому критерию, который НИ У ОДНОГО ЭЛЕМЕНТА НЕ МОЖЕТ ПОВТОРЯТЬСЯ (инн, ID телефона(серийный номер) итд.)
		int check_id = 0; 
		cin >> check_id;
		cout << "\n";

		Students* q = Head; // приравнием переменную к "голове", чтобы потом не потерять голову односвязного списка
		while (q != NULL) // суть поиска состоит в том, что мы просто идём по "узлам списка" и сравниваем значения узла с ключом. если выпадает совпадение - браво, мы победили.
		{
			if (q->id == check_id)
			{
				cout << q->surname << " | " << q->money <<
					" | " << q->id << "\n";
			}
			q = q->Next;
		}
	}

	void deleteElement() // удаление элемента списка
	{
		cout << "Удаление элемента." << endl;
		cout << "Введите ID студента который нужно удалить: ";
		int delete_id;
		cin >> delete_id;

		Students* tmp = Head;
		Students* second_tmp = NULL;

		while (tmp != nullptr)
		{
			if (tmp->id == delete_id) // снова работаем со списком для удаления, как с поиском(бежим и проверяем)
			{
				if (second_tmp != nullptr) //если следующий элемент не равен NULL (если следующий элемент существует), то наш элемент равен следующему
					second_tmp->Next = tmp->Next;
				else
					Head = tmp->Next; // если это не конец и не середина, то мы просто передвигаем голову на один элемент вперёд
				delete tmp; //просто чистим память
				break;
			}
			second_tmp = tmp;
			tmp = tmp->Next;
		}

	}

	void insert()
	{
		int index;
		cout << "Введите ID студента: "; //вставка работает также как удаление, но вместо удаления, мы двигаем указатель на следующий элемент на 1 и вместо него вставляем новый.
		cin >> index; // ПРИМЕР: 1->3->4->6 => 1-> ->3->4->6 => 1->2->3->4->6

		if (index == 0)
		{
			Students* newStudents;
			newStudents = new Students;

			cout << "\nВведите фамилию студента: ";
			cin >> newStudents->surname;
			cout << "Введите стипендия студента: ";
			cin >> newStudents->money;
			cout << "Введите ID студента: ";
			cin >> newStudents->id;

			newStudents->Next = Head;
			Head = newStudents;
		}
		else
		{
			Students* prev = Head;
			int counter = 0;

			while (counter != (index - 1))
			{
				prev = prev->Next;
				counter++;
			}

			Students* newStudents = new Students;
			newStudents->Next = prev->Next;
			prev->Next = newStudents;
			cout << "\nВведите фамилию студента: ";
			cin >> newStudents->surname;
			cout << "Введите стипендия студента: ";
			cin >> newStudents->money;
			cout << "Введите ID студента: ";
			cin >> newStudents->id;
		}
		numStudents++;
	}

};

int main()
{
	SetConsoleCP(1251); // установка приколов для консоли(поддержка ввода и вывода русского языка) если интересно большее - гугл в помощь :>
	SetConsoleOutputCP(1251);// установка локали

	int numStudents;
	cout << "Введите количество студентов: ";
	cin >> numStudents;

	List object;

	// Выбор варианта
	int menu;

	while (1)
	{
		cout << "\nВыберите вариант:" << endl;
		cout << "1.Заполнеие списка\n"
			<< "2.Вывод на экран \n"
			<< "3.Поиск определеного элемента \n"
			<< "4.Удаление определеного элемента \n"
			<< "5.Вставка элемента по ключу\n"
			<< "6.Выйти" << endl;
		cout << ">>> ";
		cin >> menu;

		switch (menu)
		{
		case 1:
		{
			cout << "\nВведите значения:" << endl;
			object.create(numStudents);
			break;
		}
		case 2:
		{
			cout << "Cозданный список: \n";
			object.output();
			break;
		}
		case 3:
		{
			object.search();
			break;
		}
		case 4:
		{
			object.deleteElement();

			cout << "Новый список: \n";
			object.output();
			break;
		}
		case 5:
		{
			object.insert();

			cout << "\nНовый список: \n";
			object.output();
			break;
		}
		case 6:
		{
			exit(EXIT_SUCCESS);
			break;
		}
		default:
		{
			cout << "Введите 1-5!" << endl;
			break;
		}
		}
	}
	return 0;
}