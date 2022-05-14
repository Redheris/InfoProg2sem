#include<iostream>

using namespace std;

struct list
{
    int inf;
    list *next;
    list *prev;
};

void push(list *&h, list *&t, int x) {
    list *r = new list;
    r->inf = x;
    r->next = NULL;
    r->prev = t;
    if (!h && !t)
        h = r;
    else
        t->next = r;
    t = r;
}

void insert_after(list *&h, list *&t, list *&r, int x) {
    list *p = new list;
    p->inf = x;
    p->next = r->next;
    p->prev = r;
    r->next = p;
    if (r != t)
        p->next->prev = p;
    else
        t = p;
}

void del_node(list *&h, list *&t, list *&r) {
    list *p = r;
    if (r == h) {
        h = h->next;
        h->prev = NULL;
    }
    else if (r == t) {
        t = t->prev;
        t->next = NULL;
    }
    else {
        p->prev->next = r->next;
        p->next->prev = r->prev;
    }
    delete p;
}

void print(list *&h, list *&t, bool reverse = false) {
    list *r;
    if (!reverse) {
        r = h;
        while (r) {
            cout << r->inf << " ";
            r = r->next;
        }
    }
    else {
        r = t;
        while (r) {
            cout << r->inf << " ";
            r = r->prev;
        }
    }
    cout << endl;
}

list *find(list *&h, list *&t, int x, bool last = false) {
    list *p = NULL;
    if (!last) {
        p = h;
        while (p) {
            if (p->inf == x)
                return p;
            p = p->next;
        }
    }
    else {
        p = t;
        while (p) {
            if (p->inf == x)
                return p;
            p = p->prev;
        }
    }
    return NULL;
}

int find_last_odd(list *&h, list *&t) {
    list *p = t;
    while (p) {
        if (p->inf % 2 == 0)
            return p->inf;
        p = p->prev;
    }
    return -1;
}

int main() {
    list *head = NULL, *tail = NULL;
    int n, min = 999999, max = -min;
    cout << "n: "; cin >> n;

    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        push(head, tail, t);
        if (t < min)
            min = t;
        if (t > max)
            max = t;
    }


    cout << "1. ";
    print(head, tail, true);

    cout << "2. " << find_last_odd(head, tail) << endl;

    cout << "3. ";
    list *p = find(head, tail, min);
    del_node(head, tail, p);
    print(head, tail);

    cout << "4. ";
    p = find(head, tail, max, true);
    insert_after(head, tail, p, 0);
    print(head, tail);

}
