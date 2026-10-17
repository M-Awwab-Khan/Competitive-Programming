#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long maximumSumSubarray(int k, vector<int>& arr) {
    int n = arr.size();
    if (n < k) return -1;

    long long currentSum = 0;
    
    // 1. Calculate sum of the first window
    for (int i = 0; i < k; i++) {
        currentSum += arr[i];
    }

    long long maxSum = currentSum;

    // 2. Slide the window
    for (int i = k; i < n; i++) {
        currentSum += arr[i] - arr[i - k]; // Add new, remove old
        maxSum = max(maxSum, currentSum);
    }

    return maxSum;
}