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

int main(){
	vector<vector<int>> vec;
    vec = input();

    return 0;
}