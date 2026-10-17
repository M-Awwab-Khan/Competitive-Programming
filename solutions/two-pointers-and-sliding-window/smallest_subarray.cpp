#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
using namespace std;

vector<int> generate_sequence(int N, int M) {
    vector<int> sequence(N);
    sequence[0] = 1;
    sequence[1] = 2;
    sequence[2] = 3;
    for (int i = 3; i < N; i++) {
        sequence[i] = (sequence[i - 1] + sequence[i - 2] + sequence[i - 3]) % M + 1;
    }
    return sequence;
}

int find_smallest_subsequence_length(int N, int M, int K, const vector<int>& sequence) {
    unordered_map<int, int> freq_map;
    int left = 0;
    int unique_count = 0;
    int min_length = INT_MAX;

    for (int right = 0; right < N; right++) {
        int num = sequence[right];
        if (num >= 1 && num <= K) {
            if (freq_map[num] == 0) {
                unique_count++;
            }
            freq_map[num]++;
        }

        while (unique_count == K) {
            min_length = min(min_length, right - left + 1);
            int left_num = sequence[left];
            if (left_num >= 1 && left_num <= K) {
                freq_map[left_num]--;
                if (freq_map[left_num] == 0) {
                    unique_count--;
                }
            }
            left++;
        }
    }

    return min_length == INT_MAX ? -1 : min_length;
}

int main() {
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N, M, K;
        cin >> N >> M >> K;

        vector<int> sequence = generate_sequence(N, M);
        int min_length = find_smallest_subsequence_length(N, M, K, sequence);

        if (min_length == -1) {
            cout << "Case " << t << ": sequence nai" << endl;
        } else {
            cout << "Case " << t << ": " << min_length << endl;
        }
    }

    return 0;
}
