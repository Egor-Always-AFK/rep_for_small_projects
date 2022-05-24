#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <Windows.h>

using namespace std;

class Peoples
{
private:
    string nameAndSurname;
    int inn;

    Peoples* left;
    Peoples* right;

public:
    Peoples* Head;

    void createTree(int numOfPeoples);

    void outputTree(Peoples* Head);

    void insertNode(Peoples node, Peoples*& Head);

    void deleteNode(int key, Peoples*& Head);

    void search(int key3, Peoples* Head);

    void InsertKey(int key4, Peoples* Head);

    void Del(Peoples*& Head);
};

void Peoples::insertNode(Peoples node, Peoples*& Head)
{
    if (Head == NULL)
    {
        Head = new Peoples;
        Head->nameAndSurname = node.nameAndSurname;
        Head->inn = node.inn;
        Head->left = NULL;
        Head->right = NULL;
    }
    else
    {
        if (node.inn < Head->inn)
            insertNode(node, Head->left);
        else
            insertNode(node, Head->right);
    }
}

void Peoples::createTree(int numOfPeoples)
{
    int i;
    Peoples newNode;
    Head = NULL;

    for (i = 0; i < numOfPeoples; i++)
    {
        cout << "\nВведите фамилию работника: ";
        cin >> newNode.nameAndSurname;
        cout << "Введите ИНН работника: ";
        cin >> newNode.inn;

        insertNode(newNode, Head);
    }
}

void Peoples::outputTree(Peoples* Head)
{

    if (Head != NULL)
    {
        cout << "\n" << "|" << setw(7) << Head->nameAndSurname << setw(7) << "|" << setw(5) << Head->inn << setw(5) << "|";
        outputTree(Head->left);
        outputTree(Head->right);
    }
}

void Peoples::deleteNode(int key2, Peoples*& Head)
{
    if (Head == NULL)
    {
        cout << "\nЭлемент не найден\n";
    }
    else
    {
        if (key2 < Head->inn)
            deleteNode(key2, Head->left);
        else
        {
            if (key2 > Head->inn)
                deleteNode(key2, Head->right);
            else
            {
                Peoples* currentNode = Head;
                if (currentNode->right == NULL)
                    Head = currentNode->left;
                else
                {
                    if (currentNode->left == NULL)
                        Head = currentNode->right;
                    else 
                        delete(currentNode->left);
                }
                delete currentNode;
            }
        }
    }
}

void Peoples::search(int key3, Peoples* Head)
{
    if (Head == NULL)
    {
        cout << "\nДерево не существует\n";
    }
    else
    {
        while (Head != NULL && Head->inn != key3)
        {
            if (Head->inn < key3)
                Head = Head->right;
            else
                Head = Head->left;
        }
        if (Head == NULL)
        {
            cout << "\nЭлемент не найден\n";
        }
        else
        {
            cout << "\n|-------------|---------|";
            cout << "\n|    ФИО      | ИНН     |";
            cout << "\n|-------------|---------|";
            cout << "\n" << "|" << setw(7) << Head->nameAndSurname << setw(7) << "|";
            cout << setw(5) << Head->inn << setw(5) << "|";
            cout << "\n|-------------|---------|";
        }
    }
}

void Peoples::InsertKey(int key4, Peoples* Head)
{
    if (Head == NULL)
    {
        cout << "\nДерево не существует\n";
    }
    else
    {
        Peoples newNode;
        cout << "\nВведите ФИО работника: ";
        cin >> newNode.nameAndSurname;
        cout << "Введите ИНН работника: ";
        cin >> newNode.inn;
        while (Head != NULL && Head->inn != key4)
        {
            if (key4 > Head->inn)
                Head = Head->right;
            else
                Head = Head->left;
        }
        insertNode(newNode, Head);
    }
}

void Peoples::Del(Peoples*& Head)
{
    Peoples* current;
    current = Head;
    if (Head != NULL)
    {
        Del(Head->left);
        Del(Head->right);
        delete Head;
    }
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Введите количество работников: ";
    int numOfPeoples;
    cin >> numOfPeoples;

    Peoples* tree = new Peoples;

    int menu;

    while (true)
    {
        cout << "\n\nВыберите вариант:\n"
            << "1.Заполнение дерева\n"
            << "2.Вывод дерева на экран \n"
            << "3.Удаление элемента по ключу\n"
            << "4.Поиск данных по ключу\n"
            << "5.Вставка данных по ключу\n"
            << "6.Выйти" << endl;
        cout << ">>> ";
        cin >> menu;

        switch (menu)
        {
        case 1:
        {
            cout << "\n\nСоздание дерева: ";
            tree->createTree(numOfPeoples);
            break;
        }
        case 2:
        {
            cout << "\n|-------------|---------|";
            cout << "\n|    ФИО      | ИНН     |";
            cout << "\n|-------------|---------|";
            tree->outputTree(tree->Head);
            break;
        }
        case 3:
        {
            cout << "\n\nВведите номер ИНН работника, которого надо удалить: ";
            int key2;
            cin >> key2;
            tree->deleteNode(key2, tree->Head);

            cout << "\n\nДерево после удаления элемента: ";
            tree->outputTree(tree->Head);
            break;
        }
        case 4:
        {
            cout << "\n\nВведите номер ИНН работника, по которому надо искать данные: ";
            int key3;
            cin >> key3;
            tree->search(key3, tree->Head);
            break;
        }
        case 5:
        {
            cout << "\n\nВведите номер ИНН: ";
            int key4;
            cin >> key4;

            tree->InsertKey(key4, tree->Head);

            break;
        }
        case 6:
        {
            tree->Del(tree->Head);
            exit(EXIT_SUCCESS);
            break;
        }
        default:
        {
            cout << "Введите 1-6!" << endl;
            break;
        }
        }
    }

    return 0;
}
