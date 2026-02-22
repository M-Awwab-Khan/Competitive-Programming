#include <vector>
#include <deque>

using namespace std;

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq; // Stores indices
    vector<int> result;

    for (int i = 0; i < nums.size(); i++) {
        // 1. Remove indices that are out of the current window range
        if (!dq.empty() && dq.front() == i - k) {
            dq.pop_front();
        }

        // 2. Remove indices of elements smaller than the current element
        // (Maintaining a monotonic decreasing deque)
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        // 3. Once we've hit the first window of size k, start recording results
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    return result;
}

vector<int> minSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq; // Stores indices
    vector<int> result;

    for (int i = 0; i < nums.size(); i++) {
        // 1. Remove indices that are out of the current window range
        if (!dq.empty() && dq.front() == i - k) {
            dq.pop_front();
        }

        // 2. Remove indices of elements larger than the current element
        // (Maintaining a monotonic increasing deque)
        while (!dq.empty() && nums[dq.back()] > nums[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        // 3. Once we've hit the first window of size k, start recording results
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    return result;
}