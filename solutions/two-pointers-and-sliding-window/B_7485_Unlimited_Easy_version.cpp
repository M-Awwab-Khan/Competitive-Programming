#include <iostream>
#include <vector>
#include <string>

using namespace std;

// State transition matrix
struct DP {
    int d[4][4];
    DP() {
        for(int i = 0; i < 4; ++i)
            for(int j = 0; j < 4; ++j)
                d[i][j] = 0;
    }
};

// Identity element for empty combination
DP identityy() {
    return DP();
}

// DP configuration for a single character
DP make_dp(int c) {
    DP res;
    for(int i = 0; i < 4; ++i) {
        for(int j = i; j < 4; ++j) {
            if(i <= c && c <= j) res.d[i][j] = 1;
        }
    }
    return res;
}

// Combining two subsequences
DP combine(const DP& a, const DP& b) {
    DP res;
    for(int i = 0; i < 4; ++i) {
        for(int j = i; j < 4; ++j) {
            int mx = 0;
            for(int k = i; k <= j; ++k) {
                int val = a.d[i][k] + b.d[k][j];
                if(val > mx) mx = val;
            }
            res.d[i][j] = mx;
        }
    }
    return res;
}

// Stack capable of returning subset combinations in O(1)
struct Stack {
    vector<int> chars;
    vector<DP> sums;
    bool is_in;

    Stack(bool in) {
        is_in = in;
        sums.push_back(identityy());
    }

    void push(int c) {
        chars.push_back(c);
        DP cur = make_dp(c);
        if (is_in) {
            sums.push_back(combine(sums.back(), cur));
        } else {
            sums.push_back(combine(cur, sums.back()));
        }
    }

    int pop() {
        int c = chars.back();
        chars.pop_back();
        sums.pop_back();
        return c;
    }

    bool empty() const {
        return chars.empty();
    }

    DP get_sum() const {
        return sums.back();
    }
};

// Queue maintained by Two Stacks
struct Queue {
    Stack in, out;

    Queue() : in(true), out(false) {}

    void push(int c) {
        in.push(c);
    }

    void pop() {
        if (out.empty()) {
            while (!in.empty()) {
                out.push(in.pop());
            }
        }
        out.pop();
    }

    DP get_sum() const {
        return combine(out.get_sum(), in.get_sum());
    }
};

int main() {
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    string s;
    cin >> s;

    Queue q;
    int l = 0;
    int max_len = 0;

    for (int r = 0; r < n; ++r) {
        int c = 0;
        if (s[r] == '7') c = 0;
        else if (s[r] == '4') c = 1;
        else if (s[r] == '8') c = 2;
        else if (s[r] == '5') c = 3;

        q.push(c);

        while (l <= r) {
            DP cur = q.get_sum();
            int len = r - l + 1;
            int max_good = cur.d[0][3];
            
            // Re-adjust window if constraints have failed
            if (len - max_good > k) {
                q.pop();
                l++;
            } else {
                break;
            }
        }
        int current_len = r - l + 1;
        if (current_len > max_len) {
            max_len = current_len;
        }
    }

    cout << max_len << "\n";
    return 0;
}