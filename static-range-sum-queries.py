n, q = map(int, input().split())
arr = list(map(int, input().split()))
queries = []
for _ in range(q):
    a, b = map(int, input().split())
    queries.append([a, b])
# 3 2 4 5 1 1 5 3
# [3, 5, 9, 14, 15, 16, 21, 24]

prefix_arr = [arr[0]] * n
for i in range(1, n):
    prefix_arr[i] = prefix_arr[i-1] + arr[i]

for (a, b) in queries:
    if a == 1:
        print(prefix_arr[b-1])
    else:
        print(prefix_arr[b-1] - prefix_arr[a-2])
