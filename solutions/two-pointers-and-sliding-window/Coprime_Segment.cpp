#include "bits/stdc++.h"
// make debug injects the colored helpers; normal/judge builds discard calls.
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
using namespace std;

using ll = long long;

template <typename T>
struct Node {
    T val, g;
};

template <typename T>
struct GCDQueue {
    stack<Node<T>> in, out;

    void push(T x) {
        T g = in.empty() ? x: gcd(x, in.top().g);
        in.push({x, g});
    }

    void transfer() {
       while (!in.empty()) {
           T x = in.top().val;
           in.pop();
           T g = out.empty() ? x: gcd(x, out.top().g);

           out.push({x, g});
       }
    }

    void pop() {
        if (out.empty()) transfer();
        out.pop();
    }

    T getGCD() {
        if (in.empty()) return out.top().g;
        if (out.empty()) return in.top().g;
        return gcd(in.top().g, out.top().g);
    }
};
void solve() {
    int n; cin >> n;
    vector<ll> a(n); for (int i = 0; i < n; ++i) cin >> a[i];

    int l = 0;
    GCDQueue<ll> q;
    int ans = INT_MAX;
    for (int r = 0; r < n; ++r) {
        q.push(a[r]);
        while (l <= r && q.getGCD() == 1) {
            ans = min(ans, r - l + 1);
            q.pop();
            ++l;
        }
    }
    cout << (ans == INT_MAX ? -1 : ans) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
