#include "bits/stdc++.h"
using namespace std;

void solve() {
	int n; cin >> n;
	char c; cin >> c;
	string s; cin >> s;

	if (string(n, c) == s) {
		cout << 0 << "\n";
	} else {
		for (int i = n; i >= 1; --i) {
			bool found = true;
			for (int j = i; j <= n; j += i) {
				if (s[j-1] != c) {
					found = false; break;
				}
			}
			if (found) {
				cout << 1 << "\n";
				cout << i << "\n";
				return ;
			}
		}
		cout << 2 << "\n";
		cout << n << " " << n - 1<< "\n";
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

	int t; cin >> t; while(t--) solve();
	return 0;
}