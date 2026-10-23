// GIVING UP :)
#include <bits/stdc++.h>
using namespace std;
# define ll long long

map<int, set<int>> adj;
string fans = "";
void dfs(int start, string ans) {
    fans = max(fans, ans);
    for (auto &child: adj[start]) {
        ans += to_string(child);
        dfs(child, ans);
        ans.pop_back();
    }
}

void solve() {
    int n, m; cin >> n >> m;

    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        adj[u].insert(v);
    }

    dfs(1, "1");
    cout << fans.size() << endl;
    for (auto c: fans) cout << c << " ";
    cout << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);


    solve();
    return 0;
}

// oh time increased.
