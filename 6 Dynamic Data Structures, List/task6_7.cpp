#include <iostream>
using namespace std;

// Структура списка
struct list
{
    int inf;    // Значение элемента
    list *prev; // Следюущий элемент
    list *next; // Предыдущий элемент
};

// Добавление в конец списка
void push(list *&h, list *&t, int x)
{
    list *r = new list; // Создание нового элемента
    r->inf = x;
    r->next = NULL;
    r->prev = t;
    if (!h && !t) // Первый элемент
        h = r;
    else
        t->next = r;
    t = r; // Перемещение хвоста на новый элемент
}

// Добавление нового элемента после заданного
void insert_after(list *&h, list *&t, list *&r, int x)
{
    list *p = new list; // Создание нового элемента
    p->inf = x;
    if (r == t) // Добавление в конец
    {
        p->next = NULL;
        p->prev = r;
        r->next = p;
        t = p;
    }
    else
    {
        r->next->prev = p;
        p->next = r->next;
        p->prev = r;
        r->next = p;
    }
}

// Удаление заданного элемента
void del_node(list *&h, list *&t, list *&r)
{
    int i = r->inf;
    if (r == h && r == t) // Единичный список
        h = t = NULL;
    else if (r == h) // Удаление головы
    {
        h = h->next;
        h->prev = NULL;
    }
    else if (r == t) // Удаление хвоста
    {
        t = t->prev;
        t->next = NULL;
    }
    else
    {
        r->next->prev = r->prev;
        r->prev->next = r->next;
    }
    delete r;
}

// Вывод списка
void print(list *&h, list *&t)
{
    list *r = h; // Указатель на голову
    while (r)
    {
        cout << r->inf << " ";
        r = r->next;
    }
    cout << endl;
}

// Задание
void task(list *&h, list *&t, int X)
{
    list *r = h, *rt = t; // Указатели на голову и хвост
    while (r != rt)       // Проход по списку
    {
        // Перемещение в конец, если >= X
        if (r->inf >= X)
        {
            list *p = r;        // Указатель на элемент
            push(h, t, r->inf); // Копирование в конец списка
            r = r->next;        // Перемещение на следующий
            del_node(h, t, p);  // Удаление
        }
        else
            r = r->next;
    }

    if (rt->inf >= X) // Проверка последнего элемнета элемента
    {
        push(h, t, rt->inf); // Копирование в конец списка
        del_node(h, t, rt);  // Удаление
    }
}

int main()
{
    int n, X;
    list *head = NULL, *tail = NULL; // Указатели на голову и хвост списка

    cout << "n, X: ";
    cin >> n >> X;

    // Заполнение списка
    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        push(head, tail, t);
    }

    task(head, tail, X);
    print(head, tail);
}