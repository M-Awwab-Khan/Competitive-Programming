#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> findSum(vector<int> &nums, int target) {
    unordered_map<int, int> hash;
    vector<int> result;
    for (int i = 0; i < nums.size(); i++) {
        int numberToFind = target - nums[i];
        if (hash.find(numberToFind) != hash.end()) {
            result.push_back(hash[numberToFind]);
            result.push_back(i);
            return result;
        }
        hash[nums[i]] = i;
    }
    return result;
}

int main() {

    // take input
    int n, target;
    cin >> n >> target;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vector<int> result = findSum(nums, target);
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] + 1 << " ";
    }
    //print impossible if result is empty
    if (result.size() == 0) {
        cout << "IMPOSSIBLE";
    }
    return 0;
}
