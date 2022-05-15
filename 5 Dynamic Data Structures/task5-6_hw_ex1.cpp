#include<iostream>
#include<string>

using namespace std;

struct stack
{
    char inf;
    stack *next;
};

void push(stack *&h, int x) {
    stack *r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

char pop(stack *&h) {
    char a = h->inf;
    stack *r = h;
    h = h->next;
    delete r;
    return a;
}

int prior(char ch) {
    if (ch == '(')
        return 1;
    if (ch == '+' || ch == '-')
        return 2;
    if (ch == '*' || ch == '/')
        return 3;
    return -1;
}

string postfix(string str) {
    string operations = "+-*/";
    string res = "";
    stack *stackres = NULL;

    for (char ch : str) {
        // Операнд
        if (operations.find(ch) == string::npos && ch != '(' && ch != ')')
            res += ch;
        // Открывающая скобка
        else if (ch == '(')
            push(stackres, ch);
        // Операция при пустом стеке
        else if (!stackres && operations.find(ch) != string::npos)
            push(stackres, ch);
        // Закрывающая скобка
        else if (ch == ')') {
            // Повторяем до открывающей скобки в стеке
            while (stackres->inf != '(')
                res += pop(stackres);
            // Удаляем скобку из стека
            pop(stackres);
        }
        // Операция при непустом стеке
        else if (operations.find(ch) != string::npos) {
            // Приоритет символа в данной строке больше верхнего элемента стека
            if (prior(ch) > prior(stackres->inf))
                // Добавление операции в стек
                push(stackres, ch);
            else {
                while (stackres && prior(ch) <= prior(stackres->inf)) {
                    // Запись в результирующую строку
                    res += pop(stackres);
                }
                // Добавляем символ из данной строки в стек
                push(stackres, ch);
            }
        }
    }
    // Запись в результирующую строку элементов стека
    while (stackres)
        res += pop(stackres);

    return res;
}

int main() {
    setlocale(LC_ALL, "RUS");
    cout << "Исходное выражение:\n";
    string s;
    getline(cin, s);
    cout << "Постфиксная запись:\n" << postfix(s) << endl;
}