#include "bits/stdc++.h"
// #include "debugging.cpp"
using namespace std;

int n, m;
long long k;
vector<vector<long long>> grid;

int totalMoves, halfMoves;

unordered_map<long long, long long> mp[22][22];

void dfs1(int i, int j, int steps, long long sum) {
    sum %= k;
    if (steps == halfMoves) {
        mp[i][j][sum % k]++;
        return;
    }

    if (i + 1 < n)
        dfs1(i+1, j, steps+1, sum + grid[i+1][j]);

    if (j + 1 < m)
        dfs1(i, j+1, steps+1, sum + grid[i][j+1]);
}

long long ans = 0;

void dfs2(int i, int j, int steps, long long sum) {
    sum %= k;
    if (steps == totalMoves - halfMoves) {
        // debug(i, j, sum);
        long long need = (k - ((sum - grid[i][j])% k)) % k;
            ans += mp[i][j][need];

        return;
    }

    if (i - 1 >= 0)
        dfs2(i-1, j, steps+1, sum + grid[i-1][j]);

    if (j - 1 >= 0)
        dfs2(i, j-1, steps+1, sum + grid[i][j-1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;

    grid.assign(n, vector<long long>(m));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> grid[i][j];

    totalMoves = (n-1) + (m-1);
    halfMoves = totalMoves / 2;

    dfs1(0, 0, 0, grid[0][0]);
    // debug(mp);
    dfs2(n-1, m-1, 0, grid[n-1][m-1]);

    cout << ans << "\n";
}