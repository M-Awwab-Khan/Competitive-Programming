#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    unordered_map<int, vector<pair<int, int>>> g;       // stop -> [(next_stop, route_id)]
    unordered_map<int, vector<int>> routes;             // stop -> [route_ids]

    for (int i = 0; i < n; ++i) {
        vector<int> arr;
        string line;
        getline(cin >> ws, line);  // read full line including spaces

        stringstream ss(line);
        int stop;
        while (ss >> stop) {
            arr.push_back(stop);
            routes[stop].push_back(i);
        }

        int k = arr.size();
        for (int j = 0; j < k; ++j) {
            int u = arr[j];
            int v = arr[(j + 1) % k];  // circular route
            g[u].push_back({v, i});
        }
    }

    int s, dest;
    cin >> s >> dest;

    if (s == dest) {
        cout << 0 << endl;
        return 0;
    }

    queue<tuple<int, int, int>> q; // (current_stop, current_route, cost)
    set<pair<int, int>> visited;
    int ans = INT_MAX;
    bool flag = false;

    for (int r : routes[s]) {
        q.push({s, r, 0});
        visited.insert({s, r});
    }

    while (!q.empty()) {
        auto [curr, currR, c] = q.front();
        q.pop();

        if (curr == dest) {
            flag = true;
            ans = min(ans, c);
            continue;
        }

        for (auto& [v, r] : g[curr]) {
            if (!visited.count({v, r})) {
                visited.insert({v, r});
                if (r == currR) {
                    q.push({v, currR, c});
                } else {
                    q.push({v, r, c + 1});
                }
            }
        }
    }

    if (!flag)
        cout << -1 << endl;
    else
        cout << ans << endl;

    return 0;
}