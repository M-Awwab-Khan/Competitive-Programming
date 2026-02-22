#include <bits/stdc++.h>
#include "../debugging.cpp"
using namespace std;

struct cmp {
    bool operator()(const tuple<int, int, char>& a, const tuple<int, int, char>& b) {
        if (get<1>(a) == get<1>(b)) return get<0>(a) < get<0>(b);
        return get<1>(a) > get<1>(b);
    }
};

 int leastInterval(vector<char>& tasks, int n) {
        int nn = tasks.size();
                priority_queue<tuple<int, int, char>, vector<tuple<int, int, char>>, cmp> pq; // min heap for storing (task, freq, last Executed);

        map<char, int> mp;
        for (auto task: tasks) mp[task]++;
        for (auto [k, v]: mp) pq.push({INT_MIN, mp[k], k});
        debug(pq);

        int ci = 1;
        while(!pq.empty()) {
            auto [le, freq, task] = pq.top();
            if (le + n < ci) {
                pq.pop();

                mp[task]--;
                if (mp[task] > 0) pq.push({ci, mp[task], task});
                ++ci;
                debug(pq);
            } else {
                while (le + n >= ci) ++ci;
            }
        }
        return ci-1;
    }


int main() {    vector<char> tasks = {'B','C','D','A','A','A','A','G'};
    int n = 1;
    cout << leastInterval(tasks, n) << endl;
    return 0;}