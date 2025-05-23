#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

vector<vector<int>> gr;
bool orient = true; // ориентированный граф
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
                gr[y].push_back(x); // добавляем y->x
            }
        }
    }
}

void print(vector<vector<int>> vc) {
    for (int i = 0; i < vc.size(); i++, cout << endl) {
        cout << i << ": ";
        for (int j = 0; j < vc[i].size(); j++) {
            cout << vc[i][j] << " ";
        }
    }
}

vector<int> order;
bool a[1000] = {false};

void dfs(int x) {
    a[x] = true;
    for (auto y : gr[x]) {
        if (!a[y]) {
            dfs(y);
        }
    }
    order.push_back(x);
}

int main() {
    input();
    print(gr);
    cout << endl;
    
    for (int i = 0; i < gr.size(); i++) {
        if (!a[i]) {
            dfs(i);
        }
    }
    reverse(order.begin(), order.end());

    cout << "topological sort: ";
    bool fl = true;
    for (int i : order) {
        if (fl) {
            cout << i;
            fl = false;
        }
        else cout << " -> " << i;
    }
    cout << endl;

    return 0;
}