#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

#define fast ios::sync_with_stdio(0); cin.tie(0);
#define pii pair<int, int>
const int MAXN = 1e5 + 5;

struct Team {
    int solved, penalty, id;
    bool operator<(const Team& other) const {
        if (solved != other.solved) return solved > other.solved; 
        if (penalty != other.penalty) return penalty < other.penalty;
        return id < other.id; 
    }
};

typedef tree<Team, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main() {
    fast
    int n, m;
    cin >> n >> m;

    vector<Team> team(n + 1);
    for (int i = 1; i <= n; ++i)
        team[i] = {0, 0, i};

    ordered_set scores;
    for (int i = 2; i <= n; ++i)
        scores.insert(team[i]);

    for (int i = 0; i < m; ++i) {
        int t, p;
        cin >> t >> p;

        if (t != 1)
            scores.erase(team[t]);

        team[t].solved += 1;
        team[t].penalty += p;

        if (t != 1)
            scores.insert(team[t]);

        int better = scores.order_of_key(team[1]);
        cout << better + 1 << '\n';
    }

    return 0;
}
