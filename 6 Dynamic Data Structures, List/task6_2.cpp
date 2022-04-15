#include <iostream>
using namespace std;

// Структура списка
struct list
{
    int inf;    // Значение элемента
    list *prev; // Следюущий элемент
    list *next; // Предыдущий элемент
};

// Добоавление в конец списка
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
void task(list *&h, list *&t, int min, int max)
{
    list *r = h; // Указатель на голову
    while (r)    // Проход по списку
    {
        if (r->inf == max)              // Если элемент равен max
            insert_after(h, t, r, min); // Вставить после него min
        r = r->next;
    }
}

int main()
{
    int n, min = 99999, max = -min;
    list *head = NULL, *tail = NULL; // Указатели на голову и хвост списка

    cout << "n: ";
    cin >> n;

    // Заполнение списка
    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        push(head, tail, t);
        if (t > max) // Максимальный элемент
            max = t;
        if (t < min) // Минимальный элемент
            min = t;
    }

    task(head, tail, min, max);
    print(head, tail);
}