#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int subarraySum(vector<int>& nums, int k) {
    // Stores how many times a particular prefix sum has occurred
    unordered_map<int, int> prevSum;
    
    int count = 0;
    int currentSum = 0;
    
    // Base case: A sum of 0 has occurred once (empty prefix)
    prevSum[0] = 1;
    
    for (int num : nums) {
        currentSum += num;
        
        // If (currentSum - k) exists in the map, it means there's
        // a subarray ending here that sums to k.
        if (prevSum.find(currentSum - k) != prevSum.end()) {
            count += prevSum[currentSum - k];
        }
        
        // Update the frequency of the current prefix sum in the map
        prevSum[currentSum]++;
    }
    
    return count;
}

int main() {
    vector<int> nums = {1, 2, 3, -2, 1};
    int k = 3;
    cout << "Total subarrays with sum " << k << " is: " << subarraySum(nums, k) << endl;
    return 0;
}