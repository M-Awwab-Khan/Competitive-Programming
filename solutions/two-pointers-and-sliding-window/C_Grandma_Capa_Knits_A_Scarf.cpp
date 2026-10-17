#include "bits/stdc++.h"
using namespace std;

void solve() {
	int n; cin >> n;
	string s; cin >> s;

	int ans = INT_MAX;

	for (int i = 0; i < 26; ++i) {
		char c = 'a' + i;
		int a = 0, b = n - 1;
		int cnt =0 ;
		while (a < b) {
			if (s[a] == s[b]) {
				++a; --b;
			}
			else if (s[a] == c) {
				++cnt; ++a;
			} else if (s[b] == c) {
				++cnt; --b;
			} else {
				cnt = -1;
				break;
			}
		}
		if (cnt != -1) ans = min(ans, cnt);
	}
	if (ans != INT_MAX) cout << ans << "\n";
	else cout << -1 << "\n";
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

}