n = int(input())
num = input()

smallest = float("inf")
mid = n // 2
l = mid
while l > 0 and num[l] == "0":
    l -= 1

r = mid + 1
while r < n and num[r] == "0":
    r += 1

if l:
    smallest = min(smallest, int(num[:l]) + int(num[l:]))
if r < n:
    smallest = min(smallest, int(num[:r]) + int(num[r:]))
print(smallest)
