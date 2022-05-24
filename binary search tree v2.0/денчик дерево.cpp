#include <iostream>
#include <iomanip>
#include <Windows.h>

using namespace std;

class Tree
{
private:
    int money; // стипендия
    char surname[20]; // Фамилия студента
    int id; // идентификационный номер

    Tree* left;
    Tree* right;

public:
    Tree* head; // адрес "головы"(начала) дерева

    void createTree(int n); // создание дерева
    void outputTree(Tree* head); // вывод на экран вершин дерева
    void insertElement(Tree obj, Tree*& head); // вставка элемента по ключу
    void deleteTree(Tree*& head); // удаление дерева
    void deleteElement(int studentID, Tree*& head); // удаление по ключу
    void searchElement(int studentID_2, Tree* head); // поиск элемента по ключу
};

void Tree::outputTree(Tree* head) // вывод дерева
{
    // head - адресс корня дерева
    if (head != nullptr) // выводим по прямому обходу. Прямой обход идет в следующем порядке: корень, левый потомок, правый потомок
    {
        outputTree(head->left);
        cout << "\n| " << head->surname << setw(7) << "|" << setw(3) << head->money << setw(7) << "|" << setw(3) << head->id << setw(6) << "|";
        outputTree(head->right);
    }
}

void Tree::insertElement(Tree obj, Tree*& head) // obj - ключаемая вершина, head - адрес корня дерева
{
    if (head == nullptr) // тут тоже самое что и вставка в списке, BUT проверка ключа немного другая. в бинарном дереве поиска в правом потомке - больше, в левом - меньше. ссылка на статью про БДП в шапке
    {
        head = new Tree;
        head->money = obj.money;
        strcpy_s(head->surname, obj.surname);
        head->id = obj.id;
        head->left = nullptr;
        head->right = nullptr;
    }
    else
    {
        if (obj.id < head->id)
            insertElement(obj, head->left);
        else
        {
            if (obj.id > head->id)
                insertElement(obj, head->right);
        }
    }
}

void Tree::createTree(int n)
{
    Tree obj; // объект класса Tree(временная переменная)
    head = nullptr;

    for (int i = 1; i <= n; i++) // n - количество вершин
    {
        cout << "Введите фамилию студента: ";
        cin >> obj.surname; // ввод строки с клавиатуры
        cout << "Введите размер стипендии: ";
        cin >> obj.money; // ввод ключа с клавиатуры
        cout << "Введите номер студенческого билета: ";
        cin >> obj.id; // ввод ключа с клавиатуры
        insertElement(obj, head); // включение вершины в дерево
    }
}

void Tree::searchElement(int studentID_2, Tree* head)
{
    if (head == NULL) 
    {
        cout << "Дерево не существует.";
    }
    else
    {
        while ((head != NULL) && (head->id != studentID_2))// поиск такой же как в списке, но с особенность работы с деревом. если ключ больше ключа элемента на котором стоим, то идём вправо, если нет, то влево. и так ходим, пока ключ не равен искомому
        {
            if (head->id < studentID_2)
            {
                head = head->right;
            }
            else
            {
                head = head->left;
            }
        }
        if (head == NULL)
        {
            cout << "Элемент не найден.";
        }
        else
        {
            cout << "\n|-------------|---------|---------|";
            cout << "\n|    ФИО      |Стипендия|    ID   |";
            cout << "\n|-------------|---------|---------|";
            cout << "\n| " << head->surname << setw(13) << " | " << setw(3) << head->money << setw(7) << " | " << setw(3) << head->id << setw(6) << "|";
            cout << "\n|---------------------------------|";
        }
    }
}

void Tree::deleteTree(Tree*& p) // удаления дерева(для отсутсвия утечек памяти)
{
    //p- адрес корня дерева
    if (p != NULL)
    {
        deleteTree(p->left);
        deleteTree(p->right);
        delete p;
        p = NULL;
    }
}

void Tree::deleteElement(int studentID, Tree*& head) // удаление по ключу
{
    if (head == NULL)
    {
        cout << "Элемент не найден";
    }
    else
    {
        if (studentID < head->id)
        {
            deleteElement(studentID, head->left); // искать в левом поддереве
        }
        else
        {
            if (studentID > head->id)
            {
                deleteElement(studentID, head->right); // искать в правом поддереве
            }
            else
            {//элемент найден
                Tree* currentNode = head;
                if (currentNode->right == NULL) //алгоритм удаления такой же как и в списке, но ОПЯТЬ ЖЕ поиск удаляемого элемента ищется по поддеревам
                {
                    head = currentNode->left;
                }
                else
                {
                    if (currentNode->left == NULL)
                    {
                        head = currentNode->right;
                    }
                    else delete(currentNode->left);
                }
                delete currentNode;//удаление элемента из дерева
            }
        }
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int menu = 0;

    Tree* first = new Tree;

    int n;
    cout << "Введите количество студентов: ";
    cin >> n;

    while (menu != 7)
    {
        cout << "Выберите вариант:\n";
        cout << "1.Создание дерева\n"
            << "2.Вывод дерева на экран\n"
            << "3.Поиск элемента дерева пр ключу\n"
            << "4.Удаление элемента дерева по ключу\n"
            << "5.Выйти" << endl;
        cout << ">>> ";
        cin >> menu;

        switch (menu)
        {
        case 1:
        {
            cout << "\n\nСоздание дерева." << endl;
            first->createTree(n);
            cout << "\n\n\n";
            break;
        }
        case 2:
        {
            cout << "\nВывод дерева:" << endl;
            cout << "\n|-------------|---------|---------|";
            cout << "\n|    ФИО      |Стипендия|    ID   |";
            cout << "\n|-------------|---------|---------|";
            first->outputTree(first->head);
            cout << "\n\n\n";
            break;
        }
        case 3:
        {
            cout << "\nВведите идентификационный номер: ";
            int studentID;
            cin >> studentID;
            first->searchElement(studentID, first->head);
            cout << "\n\n\n";
            break;
        }
        case 4:
        {
            cout << "\n\nВведите идентификационный номер студента, которого нужно удалить: ";
            int studentID;
            cin >> studentID;
            first->deleteElement(studentID, first->head);

            cout << "Дерево после удаления элемента: ";
            first->outputTree(first->head);

            cout << endl << endl << endl;
            break;
        }
        case 5:
        {
            cout << "\n\nДерево удалено." << endl;
            first->deleteTree(first->head);
            cout << endl << endl;
            break;
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
