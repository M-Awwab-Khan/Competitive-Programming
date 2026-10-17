#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int longestSubarrayWithSumK(vector<int>& nums, int k) {
    // Map stores {PrefixSum : First_Occurrence_Index}
    unordered_map<int, int> firstOccurrence;
    
    int currentSum = 0;
    int maxLength = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        currentSum += nums[i];
        
        // Case 1: The prefix sum itself is exactly K
        if (currentSum == k) {
            maxLength = i + 1;
        }
        
        // Case 2: Check if (currentSum - k) has been seen before
        if (firstOccurrence.find(currentSum - k) != firstOccurrence.end()) {
            int length = i - firstOccurrence[currentSum - k];
            maxLength = max(maxLength, length);
        }
        
        // CRITICAL: Only add currentSum to the map if it doesn't exist.
        // We want the EARLIEST index to keep the subarray as long as possible.
        if (firstOccurrence.find(currentSum) == firstOccurrence.end()) {
            firstOccurrence[currentSum] = i;
        }
    }
    
    return maxLength;
}

int main() {
    vector<int> nums = {10, 5, 2, 7, 1, 9};
    int k = 15;
    // Subarray {5, 2, 7, 1} sums to 15. Length = 4.
    cout << "Length of longest subarray: " << longestSubarrayWithSumK(nums, k) << endl;
    return 0;
}