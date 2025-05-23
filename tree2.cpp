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

void print_tree(tree *tr, int k){
    if (!tr) 
        cout << "tree is empty" << endl;
    else{
        queue<tree*> cur, next;
        tree *r = tr;
        cur.push(r);
        int j = 0;
        while (cur.size()){
            if (j == 0) {
                for (int i = 0; i < (int)pow(2.0, k) - 1; i++)
                    cout << ' ';
            }
            tree *buf = cur.front();
            cur.pop();
            j++;
            if (buf){
                cout << buf->inf;
                next.push(buf->left);
                next.push(buf->right);
                for (int i = 0; i < (int)pow(2.0, k + 1) - 1; i++)
                    cout << ' ';
            }

            if (!buf){
                for (int i = 0; i < (int)pow(2.0, k + 1) - 1; i++)
                    cout << ' ';
                cout << ' ';
            }

            if (cur.empty()){
                cout << endl;
                swap(cur, next);
                j = 0;
                k--;
            }
        }
    }
}

int sum_inside(tree* tr) {
    if (!tr || (!tr->left && !tr->right)) return 0;
    return tr->inf + sum_inside(tr->left) + sum_inside(tr->right);
}

// 10
// 8 6 4 5 7 10 9 11 3 2
int main() {
    tree *tr = NULL;
    int n, x;

    cout << "n = ";
    cin >> n;

    cout << "tree values: ";
    for (int i = 0; i < n; i++) {
        cin >> x;
        insert(tr, x);
    }

    cout << endl;
    print_tree(tr, tree_height(tr));

    int root = tr->inf;
    cout << "sum of internal values = " << (sum_inside(tr) - root);

return 0;
}