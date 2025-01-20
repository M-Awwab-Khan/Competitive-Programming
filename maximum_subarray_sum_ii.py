from collections import deque

n, a, b = [int(x) for x in input().split()]

arr = [int(x) for x in input().split()]

prefix = [0]

for i in arr:
    prefix.append(prefix[-1] + i)

mininum = deque([0])

result = float("-inf")
for r in range(a, len(prefix)):

    # finding maximum subarray sum
    result = max(prefix[r] - prefix[mininum[0]], result)

    temp = mininum[-1]

    # making the deque monotonically increasing
    while mininum and prefix[mininum[-1]] >= prefix[temp + 1]:
        mininum.pop()
    mininum.append(temp + 1)

    # making sure the range is correct for next coming values
    while r - mininum[0] + 1 > b:
        mininum.popleft()

print(result)
