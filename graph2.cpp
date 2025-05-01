#include <iostream>
#include <utility>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <queue>
using namespace std;

vector<vector<int>> input() {
    ifstream in("input.txt");
    vector<vector<int>> vc;
    int pos_p = 0, pos_c = 0, i = 0;
    string str = "", deal = "";
    while (getline(in, str)) {
        vc.push_back(vector<int>());
        do {
            pos_p = str.find(" ", pos_c);
            deal = str.substr(pos_c, pos_p - pos_c);
            if (deal == "") vc[i].push_back(-1);
            else vc[i].push_back(atoi(deal.c_str()));
            pos_c = pos_p + 1;
        }
        while (pos_p != -1);
        i++;
    }
    return vc;
}

void print(vector<vector<int>> vc) {
    for (int i = 0; i < vc.size(); i++, cout << endl) {
        cout << i << ": ";
        for (int j = 0; j < vc[i].size(); j++) {
            if (vc[i][j] != -1)
                cout << vc[i][j] << " ";
        }
    }
}

void del_el(vector<int> &vc, int x) {
    if (vc.size() == 1) vector<int>::iterator it = vc.insert(vc.begin(), -1);
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

int main(){
	vector<vector<int>> vec;
    vec = input();
    print(vec);
    cout << endl;

    int x, y;
    cout << "choose edge to delete: ";
    cin >> x >> y;
    del_edges(vec, x, y);
    cout << endl;
    print(vec);

    return 0;
}