#include <iostream>
#include <utility>
#include <windows.h>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <cmath>
#include <time.h>
using namespace std;

struct list {
    int inf;
    list *next;
    list *prev;
};

void push_back(list*& h, list*& t, int x) {
    list *r = new list;
    r->inf = x;
    r->next = nullptr;
    if (!h && !t) {
        r->prev = nullptr;
        h = r;
    }
    else {
        t->next = r;
        r->prev = t;
    }
    t = r;
}

void print(list* h) {
    list *p = h;
    while (p) {
        cout << p->inf << " ";
        p = p->next;
    }
}

void insert_after(list*& h, list*& t, list *r, int y) {
    list *p = new list;
    p->inf = y;
    if (r == t) {
        p->next = nullptr;
        p->prev = r;
        r->next = p;
        t = p;
    }
    else {
        r->next->prev = p;
        p->next = r->next;
        p->prev = r;
        r->next = p;
    }
}

void del_list(list *&h) {
    while (h) {
        list *p = h;
        h = h->next;
        delete p;
    }
}

int find_min(list*& h, list*& t) {
    list *p = h;
    int min = p->inf;
    while (p) {
        if (p->inf < min) {
            min = p->inf;
        }
        p = p->next;
    }
    return min;
}

int find_last_odd(list*& h, list*& t) {
    list *p = h;
    int last_odd = -1;
    while (p) {
        if (p->inf % 2 != 0) {
            last_odd = p->inf;
        }
        p = p->next;
    }
    return last_odd;
}

void insert_after_min(list*& h, list*& t, int min, int last_odd) {
    if (last_odd != -1){
        list *p = h;
        while (p) {
            if (p->inf == min) {
                insert_after(h, t, p, last_odd);
            }
            p = p->next;
        }
    }
}

int main() {
    list* head = nullptr;
    list* tail = nullptr;

    int n = 10;
    int x;
    srand(time(0));
    for (int i = 0; i < n; i++){
        x = rand() % 10;
        push_back(head, tail, x);
    }
    print(head);

    int min = find_min(head, tail);
    int last_odd = find_last_odd(head, tail);

    if (last_odd != -1) {
        insert_after_min(head, tail, min, last_odd);
    }

    cout << endl;
    print(head);
    
    del_list(head);
    return 0;
}