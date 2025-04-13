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

void del_after(list*& h, list*& t, list *r) {
    if (r == h && r == t)
        h = t = nullptr;
    else if (r == h) {
        h = h->next;
        h->prev = nullptr;
    }
    else if (r == t) {
        t = t->prev;
        t->next = nullptr;
    }
    else {
        r->next->prev = r->prev;
        r->prev->next = r->next;
    }
    delete r;
}

void del_list(list *&h) {
    while (h) {
        list *p = h;
        h = h->next;
        delete p;
    }
}

int sred_arifm(list*& h) {
    int sum = 0, n = 0;
    if (h && h->next) {
        list *p = h;
        p = p->next;
        while (p) {
            sum += p->inf;
            n ++;
            p = p->next;
        }
    }
    if (n > 0) return sum/n;
    else return 0;
}

list *find_arifm(list*& h, list*& t) {
    list *p = h;
    list* head = nullptr;
    list* tail = nullptr;
    
    while (p) {
        int arifm = sred_arifm(p);
        if (p->inf <= arifm) 
            push_back(head, tail, p->inf);
        if (!p->next)
            push_back(head, tail, p->inf);
        p = p->next;
    }

    return head;
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

    list* res = find_arifm(head, tail);

    cout << endl;
    print(res);

    del_list(res);
    del_list(head);
    return 0;
}