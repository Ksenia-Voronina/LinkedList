#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

template <class T>
struct Element
{
    T data; // данные
    Element<T>* next; // адрес следующего элемента в списке
    Element<T>* prev; // адрес предыдущего элемента в списке
};

template <class T>
class LinkedList
{
private:
    Element<T>* head;
    Element<T>* tail;
    int size;

    Element<T>* Find(int index); //находит и возвращает указатель на элемент списка по заданной позиции

    bool CorrectIndex(int index); //проверка на корректность позиции (индекса) в списке

public:
    LinkedList(); //конструктор

    ~LinkedList(); //деструктор

    int Size();

    T GetElement(int index); //возвращает элемент списка по заданному индексу

    void AddEnd(T _data); //добавление элемента в конец списка

    void AddBegin(T _data); //добавление элемента в начало списка

    void Insert(T _data, int index); //вствка элемента в заданную позицию списка

    void Set(T _data, int _index); //изменение элемента по определенному индексу

    void Del(int index); //удаление элемента с заданной позиции

    void Clear(); //очистка списка

    void Print(); // Вывод списка


};

template <class T>
LinkedList<T>::LinkedList()
{
    head = NULL;
    tail = NULL;
    size = 0;
}

template <class T>
LinkedList<T>::~LinkedList()
{
    Clear();
}

template <class T>
Element<T>* LinkedList<T>::Find(int index)
{
    Element<T>* t = head;

    for (int i = 0; i < index; i++)
        t = t->next;

    return t;
}

template <class T>
bool LinkedList<T>::CorrectIndex(int index)
{
    return (index >= 0) && (index < size);
}

template <class T>
T LinkedList<T>::GetElement(int index)
{
    if (!CorrectIndex(index))
        throw out_of_range("Некорректный индекс");

    Element<T>* t = Find(index);

    cout << "Под этим индексом находится элемент: " << t->data << "\n";
    return t->data;
}

template <class T>
int LinkedList<T>::Size() {
    int size = 0;
    Element<T>* current = head;
    while (current != NULL) {
        current = current->next;
        size++;
    }
    cout << "Размер списка: " << size << "\n";
    return size;
}

template <class T>
void LinkedList<T>::AddEnd(T _data)
{
    Element<T>* t = new Element<T>;
    t->next = nullptr;
    t->prev = tail;
    t->data = _data;

    if (tail != nullptr)
        tail->next = t;

    if (size == 0)
    {
        head = t;
        tail = t;
    }
    else
    {
        tail = t;
    }
    size++;
}

template <class T>
void LinkedList<T>::AddBegin(T _data)
{
    Element<T>* t = new Element<T>;
    t->data = _data;
    t->prev = nullptr;

    t->next = head;

    if (size > 0)
    {
        head->prev = t;
        head = t;
    }
    else
    {
        head = t;
        tail = t;
    }
    size++;
}

template <class T>
void LinkedList<T>::Insert(T _data, int index)
{
    if (!CorrectIndex(index)) {
        cout << "Введен некорректный индекс";
        return;
    }

    if (index == size) {
        AddEnd(_data);
        return;
    }

    if (index == 0) {
        AddBegin(_data);
        return;
    }

    Element<T>* itemPrev = Find(index - 1);

    Element<T>* item = Find(index);

    Element<T>* t = new Element<T>;
    t->data = _data;
    t->next = item;
    t->prev = itemPrev;
    itemPrev->next = t;
    item->prev = t;

    size++;
}

template <class T>
void LinkedList<T>::Set(T _data, int _index) {
    Element<T>* item = Find(_index);
    item->data = _data;
}

template <class T>
void LinkedList<T>::Del(int index)
{
    if (size == 0) {
        cout << "В списке нет элементов";
        return;
    }
    if (!CorrectIndex(index)) {
        cout << "Введен некорректный индекс";
        return;
    }

    Element<T>* item = Find(index);

    Element<T>* itemPrev = item->prev;

    Element<T>* itemNext = item->next;

    if ((size > 1) && (itemPrev != nullptr))
        itemPrev->next = itemNext;

    if ((itemNext != nullptr) && (size > 1))
        itemNext->prev = itemPrev;

    if (index == 0)
        head = itemNext;

    if (index == size - 1)
        tail = itemPrev;

    delete item;

    size--;
}

template <class T>
void LinkedList<T>::Clear()
{
    int n = size;
    for (int i = 0; i < n; i++)
        Del(0);
}

template <class T>
void LinkedList<T>::Print()
{
    cout << "Список List: ";

    if (size == 0) {
        cout << "пустой((\n";
        return;
    }
    Element<T>* t = head;
    for (int i = 0; i < size; i++)
    {
        cout << t->data << " ";
        t = t->next;
    }
    cout << endl;
}


int main() {
    setlocale(LC_ALL, "Russian");

    LinkedList<double> List;

    double el;
    int index;
    while (true) {
        system("cls");

        cout << "Выберите действие, которое хотите совершить со списком\n\n";
        SetConsoleTextAttribute(hConsole, 11);
        cout << "<1> - Найти элемент по индексу\n\n";
        cout << "<2> - Добавить элемент в начало списка\n\n";
        cout << "<3> - Добавить элемент в конец списка\n\n";
        cout << "<4> - Вставить элемент в заданную позицию\n\n";
        cout << "<5> - Изменить элемент в массиве по определенному индексу\n\n";
        cout << "<6> - Удалить элемент с заданной позиции\n\n";
        cout << "<7> - Вывести размер списка (кол-во элементов в нем)\n\n";
        cout << "<8> - Очистить список\n\n";
        cout << "<9> - Вывод списка\n\n";
        SetConsoleTextAttribute(hConsole, 12);
        cout << "<0> - Выход из программы\n\n";
        SetConsoleTextAttribute(hConsole, 15);

        switch (_getch()) {
        case '0':
            return 0;
        case '1':
            cout << "Введите индекс того элемента, который хотите получить: ";
            cin >> index;
            List.GetElement(index);
            cout << "\n\n";
            system("pause");
            break;
        case '2':
            cout << "Введите тот элемент, который хотите добавить: ";
            cin >> el;
            List.AddBegin(el);
            cout << "\n\n";
            system("pause");
            break;

        case '3':
            cout << "Введите тот элемент, который хотите добавить: ";
            cin >> el;
            List.AddEnd(el);
            cout << "\n\n";
            system("pause");
            break;

        case '4':
            cout << "Введите тот элемент, который хотите добавить: ";
            cin >> el;
            cout << "\n";
            cout << "Введите индекс для элемента (в это место будет добавлен ваш элемент): ";
            cin >> index;
            List.Insert(el, index);
            cout << "\n\n";
            system("pause");
            break;

        case '5':
            cout << "Введите тот элемент, который хотите добавить: ";
            cin >> el;
            cout << "\n";
            cout << "Введите индекс для элемента (в это место будет добавлен ваш элемент): ";
            cin >> index;
            List.Set(el, index);
            cout << "\n\n";
            system("pause");
            break;

        case '6':
            cout << "Введите индекс того элемента, который хотите удалить: ";
            cin >> index;
            List.Del(index);
            cout << "\n\n";
            system("pause");
            break;

        case '7':
            List.Size();
            cout << "\n\n";
            system("pause");
            break;

        case '8':
            List.Clear();
            cout << "\n\n";
            system("pause");
            break;

        case '9':
            List.Print();
            cout << "\n\n";
            system("pause");
            break;

        default:
            continue;
            break;
        }
    }

}
