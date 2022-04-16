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
void push(list *&h, list *&t, int x) {
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

// Вывод списка
void print(list *&h, list *&t) {
    list *r = h; // Указатель на голову
    while (r) {
        cout << r->inf << " ";
        r = r->next;
    }
    cout << endl;
}

// Поиск минимального элемента в списке
list *min(list *&h, list *&t) {
    list *min = h, *r = h->next; // Выходной элемент и указатель
    while (r) {
        if (r->inf < min->inf)
            min = r;
        r = r->next;
    }
    return min;
}

// Задание
void task(list *&h, list *&t) {
    list *l = h; // Указатель на голову, левая граница прохода цикла

    while (l) {
        // Альтернативный вариант
        /*for (list* i = l->next; i; i = i->next) {
            if (l->inf > i->inf)
                swap(l->inf, i->inf);
        }*/

        swap(l->inf, min(l, t)->inf);

        l = l->next;
    }

}

int main() {
    int n;
    list *head = NULL, *tail = NULL; // Указатели на голову и хвост списка

    cout << "n:";
    cin >> n;

    // Заполнение списка
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        push(head, tail, t);
    }

    task(head, tail);
    print(head, tail);
}