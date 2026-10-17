def count_sequence_in_matrix():
    n, m = list(map(int, input().split()))
    matrix = [input() for _ in range(n)]
    count = 0

    top, bottom, left, right = 0, n - 1, 0, m - 1

    while top <= bottom and left <= right:
        result_sequence = []
        for j in range(left, right + 1):
            result_sequence.append(matrix[top][j])
        top += 1

        for i in range(top, bottom + 1):
            result_sequence.append(matrix[i][right])
        right -= 1

        if top <= bottom:
            for j in range(right, left - 1, -1):
                result_sequence.append(matrix[bottom][j])
            bottom -= 1

        if left <= right:
            for i in range(bottom, top - 1, -1):
                result_sequence.append(matrix[i][left])
            left += 1

        if len(result_sequence) >= 4:
            result_sequence.extend(result_sequence[0:3])
            count += "".join(result_sequence).count('1543')

    return count




t = int(input())
while t:
    t -= 1
    print(count_sequence_in_matrix())
