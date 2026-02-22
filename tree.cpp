#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Node {
    ll val;
    Node *left, *right;
    Node(ll v) : val(v), left(NULL), right(NULL) {}
};

Node* buildTree(const vector<ll> &a) {
    if (a.empty()) return NULL;
    if (a[0] < 0) return NULL;

    vector<Node*> nodes(a.size(), NULL);
    for (int i = 0; i < a.size(); i++) {
        if (a[i] >= 0) nodes[i] = new Node(a[i]);
    }

    for (int i = 0; i < a.size(); i++) {
        if (!nodes[i]) continue;
        int l = 2*i + 1;
        int r = 2*i + 2;
        if (l < a.size()) nodes[i]->left = nodes[l];
        if (r < a.size()) nodes[i]->right = nodes[r];
    }
    return nodes[0];
}

struct Node2 {
    bool isBST;
ll sum;
    ll minv, maxv;
};

ll ans = 0;

Node2 dfs(Node *root) {
    if (!root)
        return { true, 0, LLONG_MAX, LLONG_MIN };

    Node2 L = dfs(root->left);
    Node2 R = dfs(root->right);

    if (!L.isBST || !R.isBST || !(L.maxv < root->val && root->val < R.minv)) {
        return { false, 0, 0, 0 };
    }

    ll sum = L.sum + R.sum + root->val;
    ans = max(ans, sum);

    ll mn = min(L.minv, root->val);
    ll mx = max(R.maxv, root->val);

    return { true, sum, mn, mx };
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<ll> arr;
    ll x;
    while (cin >> x) arr.push_back(x);

    Node *root = buildTree(arr);

    ans = 0;
    dfs(root);

    cout << ans << "\n";
}
