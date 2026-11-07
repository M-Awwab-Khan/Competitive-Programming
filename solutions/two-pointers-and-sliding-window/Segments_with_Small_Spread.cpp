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
    T val, mn, mx;
};

template <typename T>
struct MinMaxQueue {
    stack<Node<T>> in, out;

    void push(T x) {
        T mn = in.empty() ? x : min(x, in.top().mn);
        T mx = in.empty() ? x : max(x, in.top().mx);

        in.push({x, mn, mx});
    }

    void transfer() {
        while (!in.empty()) {
            T x = in.top().val;
            in.pop();

            T mn = out.empty() ? x : min(x, out.top().mn);
            T mx = out.empty() ? x : max(x, out.top().mx);

            out.push({x, mn, mx});
        }
    }

    void pop() {

        if (out.empty()) transfer();
        out.pop();
    }

    T getMin() {
        if (in.empty()) return out.top().mn;
        if (out.empty()) return in.top().mn;
        return min(in.top().mn, out.top().mn);
    }


    T getMax() {
        if (in.empty()) return out.top().mx;
        if (out.empty()) return in.top().mx;
        return max(in.top().mx, out.top().mx);
    }
};

void solve() {
    int n; cin >> n;
    ll k; cin >> k;
    vector<ll> a(n); for (int i = 0; i < n; ++i) cin >> a[i];

//     multiset<ll> st;
//     int l = 0;
//     ll ans = 0;
//     for (int r = 0; r < n; ++r) {
//         st.insert(a[r]);
//
//         while (*st.rbegin() - *st.begin() > k) {
//             st.erase(st.find(a[l++]));
//         }
//
//         ans += (r - l + 1);
//     }
//     cout << ans << endl;

    MinMaxQueue<ll> q;
    ll ans = 0;
    int l = 0;
    for (int r = 0; r < n; ++r) {
        q.push(a[r]);

        while(q.getMax() - q.getMin() > k) {
            q.pop();
            ++l;
        }

        ans += (r - l + 1);
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // For multiple test cases: cin >> t;
    while (t--) solve();
    return 0;
}
