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

int main() {
    input();
    print(gr);
    cout << endl;
    int n = gr.size();

    return 0;
}