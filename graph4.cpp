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

vector<int> bfs(vector<vector<int>> vc, vector<int> a, int s) {
    int x = s;
    a[x] = 1;
    queue<int> q;
    q.push(x);

    while (!q.empty()) {
        x = q.front();
        q.pop();
        int i = 0;
        while (i < vc[x].size()) {
            if (a[vc[x][i]] == 0) {
                int y = vc[x][i];
                a[y] = 1;
                q.push(y);
            }
            i++;
        }
    }
    return a;
}

int main(){
	vector<vector<int>> vec;
    vec = input();
    print(vec);
    cout << endl;

    
    vector<int> a(vec.size()), n;
    for (int i = 0; i < vec.size(); i++) a[i] = 0;
    n = bfs(vec, a, vec[0][0]);

    cout << "nodes-origins: ";
    bool fl = true, count = true;
    for (int i = 0; i < n.size(); i++) {
        if (n[i] == 0) {
            count = false;
            if (fl) {
                cout << i;
                fl = false;
            }
            else cout << ", " << i;
        }
        if (!count)
            cout << "none found";
    }

    return 0;
}