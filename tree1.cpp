#include <iostream>
#include <utility>
#include <windows.h>
#include <sstream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <queue>
using namespace std;

struct tree {
    int inf;
    tree *left;
    tree *right;
    tree *parent;
};

tree *node(int x){
    tree *n = new tree;
    n->inf = x;
    n->parent = NULL;
    n->right = NULL;
    n->left = NULL;
    return n;
}

void insert(tree *&tr, int x, tree *parent = NULL) {
    if (!tr) {
        tr = node(x);
        tr->parent = parent;
    }
    else if (x < tr->inf) {
        insert(tr->left, x, tr);
    }
    else insert(tr->right, x, tr);
}

int node_depth(tree *tre) {
    tree *tr = tre;
    int k = -1;
    while (tr != NULL) {
        tr = tr->parent;
        k++;
    }
    return k;
}

int tree_height(tree *tre) {
    tree *tr = tre;
    static int max = 0;
    if (tr) {
        tree_height(tr->left);
        tree_height(tr->right);
        if (!tr->left && !tr->right && node_depth(tr) > max) max = node_depth(tr); 
    }
    return max;
}

// 10
// 8 6 4 5 7 10 9 11 3 2
int main() {
    tree *tr = NULL;
    int n, x, val;

    cout << "n = ";
    cin >> n;

    cout << "tree values: ";
    for (int i = 0; i < n; i++) {
        cin >> x;
        insert(tr, x);
    }

return 0;
}