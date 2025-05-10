#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <utility>
#include <algorithm>
using namespace std;

vector<vector<int>> gr;
bool orient = false; // неориентированный граф
unordered_set<int> vertices;

void input() {
    ifstream in("input.txt");
    int x, y;
    int max_vertex = -1;
    
    while (in >> x >> y) { // вводим ребро в виде x -> y
        vertices.insert(x);
        vertices.insert(y);
        max_vertex = max(max_vertex, max(x, y));
    }
    gr.resize(max_vertex + 1);
    
    in.clear();
    in.seekg(0);

    while (in >> x >> y) { // вводим ребро в виде x -> y
        if (find(gr[x].begin(), gr[x].end(), y) == gr[x].end()) { // проверяем существует ли ребро x -> y
            gr[x].push_back(y); // добавляем x -> y
            if (!orient) { // неориентированный
                gr[y].push_back(x); // добавляем y -> x
            }
        }
    }
}

void print(vector<vector<int>> &vc) {
    for (int i = 0; i < vc.size(); i++, cout << endl) {
        cout << i << ": ";
        for (int j = 0; j < vc[i].size(); j++) {
            cout << vc[i][j] << " ";
        }
    }
}

void del_el(vector<int> &vc, int x) {
    vector<int>::iterator it = remove(vc.begin(), vc.end(), x);
    vc.erase(it, vc.end());
}

void del(vector<vector<int>> &vc, int x) {
    int temp;
    for (int i = 0; i < vc[x].size(); i++) {
        temp = vc[x][i];
        del_el(vc[temp], x);
    }
    vc.erase(vc.begin() + x);
}

void del_edges(vector<vector<int>> &vc, int x, int y) {
    del_el(vc[x], y);
    del_el(vc[y], x);
}

void euler(vector<vector<int>>& gr, int n) {
    vector<int> degrees(n, 0); // находим степени вершин
    for (int i = 0; i < n; i++) {
        degrees[i] = gr[i].size();
    }

    int v1 = -1, v2 = -1;
    for (int i = 0; i < n; i++) {
        if (degrees[i] % 2 != 0) {
            if (v1 == -1) v1 = i;
            else if (v2 == -1) v2 = i;
            else {
                cout << "no path, no cycle" << endl;
                return;
            }
        }
    }

    bool eu_cycle = (v1 == -1 && v2 == -1);
    bool eu_path = (v1 != -1 && v2 != -1);

    if (!eu_cycle && !eu_path) {
        cout << "no path, no cycle" << endl;
        return;
    }

    // если есть путь, добавляем фиктивное ребро для превращения его в цикл
    bool add_edge = false;
    if (eu_path) {
        gr[v1].push_back(v2);
        gr[v2].push_back(v1);
        degrees[v1]++;
        degrees[v2]++;
        add_edge = true;
    }

    stack<int> st;
    vector<int> res;

    int start;
    if (eu_path) start = v1;
    else start = 0;
    st.push(start);

    while (!st.empty()) {
        int cur = st.top();
        if (!gr[cur].empty()) {
            int next = gr[cur].back();
            st.push(next);
            del_edges(gr, cur, next);
            degrees[cur]--;
            degrees[next]--;
        }
        else {
            res.push_back(cur);
            st.pop();
        }
    }

    // если было добавлено фиктивное ребро, удаляем его из пути
    if (add_edge) {
        for (int i = 0; i + 1 < res.size(); ++i) {
            if ((res[i] == v1 && res[i + 1] == v2) || (res[i] == v2 && res[i + 1] == v1)) {
                vector<int> temp(res.begin() + i + 1, res.end());
                temp.insert(temp.end(), res.begin() + 1, res.begin() + i + 1);
                res = temp;
                break;
            }
        }
    }

    if (eu_cycle) cout << "euler cycle: ";
    else cout << "euler path: ";

    bool fl = true;
    for (int i : res) {
        if (fl) {
            cout << i;
            fl = false;
        }
        else cout << " -> " << i;
    }
    cout << endl;
}

int main() {
    input();
    print(gr);
    cout << endl;
    int n = gr.size();
    euler(gr, n);

    return 0;
}