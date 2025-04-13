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

list *find(list*& h, list*& t) {
    list *p = h;
    list* head1 = nullptr;
    list* tail1 = nullptr;
    list* head_res = nullptr;
    list* tail_res = nullptr;

    while (p) {
        if (p->inf % 2 == 0)
            push_back(head_res, tail_res, p->inf);
        else
            push_back(head1, tail1, p->inf);
        p = p->next;
    }

    while (head1) {
        push_back(head_res, tail_res, head1->inf);
        head1 = head1->next;
    }
    return head_res;
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
    
    list* res = find(head, tail);

    cout << endl;
    print(res);

    del_list(res);
    del_list(head);
    return 0;
}