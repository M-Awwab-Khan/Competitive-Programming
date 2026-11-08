n = int(input())
skills = list(map(int, input().split()))
skills.sort()

left = 0
max_team_size = 0

for right in range(len(skills)):
    while skills[right] - skills[left] > 5:
        left += 1
    max_team_size = max(max_team_size, right - left + 1)

print(max_team_size)
