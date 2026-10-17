#include "bits/stdc++.h"
using namespace std;

void solve() {
	int n; cin >> n;
	vector<int> a(n); for (auto &x: a) cin >> x;

	vector<vector<int>> results;
	if (a[n-2] > a[n-1]) {
		cout << -1 << endl;
	} else if (a[n-1] >= 0) {
		//possible
		for (int i = 0; i < n -2; ++i) {
			results.push_back({i + 1, n-1, n});
		}
		cout << results.size() << endl;
		for (auto &v: results) cout << v[0] << " " << v[1] << " " << v[2] << endl;
	} else {
		// hope that arrray is already sorted
		if (is_sorted(a.begin(), a.end())) {
			cout << 0 << endl;
		} else {
			cout << -1 << endl;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("myoutput.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif

	int t; cin >> t; while(t--)
	solve();

	return 0;
}