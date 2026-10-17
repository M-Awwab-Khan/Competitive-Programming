from collections import deque

n, m, c = map(int, input().split())
nums = list(map(int, input().split()))

min_deque = deque()
max_deque = deque()
ret = []

for i in range(len(nums)):
    if min_deque and min_deque[0] <= i - m:
        min_deque.popleft()
    if max_deque and max_deque[0] <= i - m:
        max_deque.popleft()

    while min_deque and nums[min_deque[-1]] >= nums[i]:
        min_deque.pop()
    min_deque.append(i)

    while max_deque and nums[max_deque[-1]] <= nums[i]:
        max_deque.pop()
    max_deque.append(i)

    if i >= m - 1:
        if nums[max_deque[0]] - nums[min_deque[0]] <= c:
            ret.append(i - m + 2)

if not ret:
    print("NONE")
else:
    for i in ret:
        print(i)
